//
//  Geometry.cpp
//  voronoi_0
//
//  Created by Ben Lewson on 3/10/17.
//  Copyright © 2017 Ben Lewson. All rights reserved.
//

#include "Geometry.hpp"

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