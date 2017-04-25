//
//  Geometry.cpp
//  voronoi_0
//
//  Created by Ben Lewson on 3/10/17.
//  Copyright © 2017 Ben Lewson. All rights reserved.
//

#include "Geometry.hpp"

#include "SvgPacker.hpp" //Only for the PI

using namespace std;

//Functions

//Safe Division, stops divide by zero errors
double sDiv(double x, double y)
{
    if(y != 0.0)
    {
        return x / y;
    }
    else
    {
        return x / __DBL_MIN__;
    }
}

//Simple pythagorean distance
double dist(point A, point B)
{
    return sqrt(pow((A.X - B.X),2) + pow((A.Y - B.Y),2));
}

//Changes line (points form) to line_slope
line_slope toSlopeForm(line AB)
{
    point Start = AB.Start;
    point End   = AB.End;
    
    double xDist = End.X - Start.X;
    double yDist = End.Y - Start.Y;
    
    double Slope = sDiv(yDist,xDist);
    
    double Length = sqrt(xDist*xDist + yDist*yDist);
    
    return {Start, Slope, Length};
}

//Changes line_slope to line (points form)
line toPointForm(line_slope CD)
{
    point Start = CD.Start;
    
    double theta = atan(CD.Slope);
    
    point End;
    End.X = CD.Start.X + CD.Length * cos(theta);
    End.Y = CD.Start.Y + CD.Length * sin(theta);
    
    return {Start, End};
}

//Changes Focus and Directrix form of parabola to standard form coefficients
void directrixConversion(double pointX, double pointY, double sweepX, double &k_i, double &a_i, double &c_i)
{
    k_i = 1.0/(2.0*(pointX - sweepX));
    a_i = pointY;
    c_i = (pointX + sweepX)/2.0;
}

//Determinant form of line intersection
point detInter(line AB, line CD)
{
    point A = AB.Start;
    point B = AB.End;
    point C = CD.Start;
    point D = CD.End;
    
    //From wikipedia on line intersection formulae
    double retX =   ((A.X*B.Y - A.Y*B.X) * (C.X - D.X) - (C.X*D.Y - C.Y*D.X) * (A.X - B.X))/
    ((A.X - B.X) * (C.Y - D.Y) - (A.Y - B.Y) * (C.X - D.X));
    
    double retY =   ((A.X*B.Y - A.Y*B.X) * (C.Y - D.Y) - (C.X*D.Y - C.Y*D.X) * (A.Y - B.Y))/
    ((A.X - B.X) * (C.Y - D.Y) - (A.Y - B.Y) * (C.X - D.X));
    
    return {retX,retY};
}

point circCenter(point A, point B, point C)
{
    point Center;
    line AB = {A,B};
    line BC = {B,C};
    
    //Find mid points by averaging X and Y
    point midAB;
    midAB.X = (AB.End.X + AB.Start.X) / 2.0;
    midAB.Y = (AB.End.Y + AB.Start.Y) / 2.0;
    
    point midBC;
    midBC.X = (BC.End.X + BC.Start.X) / 2.0;
    midBC.Y = (BC.End.Y + BC.Start.Y) / 2.0;
    
    //Turn line to slope form
    line_slope _AB = toSlopeForm(AB);
    line_slope _BC = toSlopeForm(BC);
    
    //Find negative inverse of slope for perpendicular bisector
    line_slope _perpAB = {midAB, -1.0 * sDiv(1.0,_AB.Slope), MAX_LENGTH_OF_LINE};
    line_slope _perpBC = {midBC, -1.0 * sDiv(1.0,_BC.Slope), MAX_LENGTH_OF_LINE};
    
    //Change to points form for intersection calculation
    line perpAB = toPointForm(_perpAB);
    line perpBC = toPointForm(_perpBC);
    
    Center = detInter(perpAB, perpBC);
    
    return Center;
}

//Compute circle center point and radius from 3 sets of coordinates
circle circFromPoints(point A, point B, point C)
{
    point cen = circCenter(A, B, C);
    
    double radDist = sqrt((A.X - cen.X)*(A.X - cen.X) + (A.Y - cen.Y)*(A.Y - cen.Y));
    
    return {cen,radDist};
}

//Compute coordinates of the end of a ray
point endOfRay(ray A)
{
    point E;
    
    E.X = A.Length * cos(A.Angle * PI / 180.0) + A.Origin.X;
    E.Y = A.Length * sin(A.Angle * PI / 180.0) + A.Origin.Y;
    
    return E;
}

vector <point> endVector(cell A)
{
    vector <point> ret;
    
    for(int i = 0; i < A.Rays.size(); i++)
    {
        ret.push_back(endOfRay(A.Rays.at(i)));
    }
    
    return ret;
}


//Initialize a cell for a given number of rays at a specified center point in 2D space
void initCell(cell &A, point O, int numOfRays)
{
    A.Center = O;
    if(numOfRays < MAX_NUM_RAYS)
    {
        for(int i = 0; i < numOfRays; i++)
        {
            ray R;
            
            R.Origin    = A.Center;
            R.Angle     = i*360.0/numOfRays;
            R.Length    = MIN_RAY_LENGTH;
            
            A.Rays.push_back(R);
            A.Fixed.push_back(false);
        }
    }
    else
    {
        //do nothing, exception
    }
}

//Grow cells by extending rays that have not terminated
void inflateCell(cell &A, double delta)
{
    for(int i = 0; i < A.Rays.size(); i++)
    {
        //Check if specific ray has terminated
        if(! (A.Fixed.at(i)) )
        {
            A.Rays.at(i).Length += delta;
        }
        else
        {
            //Do Nothing
        }
    }
}

//Converts vector of point struct into interlaced vector of doubles
vector <double> pointToDoubleInter(vector <point> A)
{
    vector <double> ret;
    for(int i = 0; i < A.size(); i++)
    {
        ret.push_back(A.at(i).X);
        ret.push_back(A.at(i).Y);
    }
    
    return ret;
}



