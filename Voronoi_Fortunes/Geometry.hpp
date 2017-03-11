//
//  Geometry.hpp
//  voronoi_0
//
//  Created by Ben Lewson on 3/10/17.
//  Copyright © 2017 Ben Lewson. All rights reserved.
//

#ifndef Geometry_hpp
#define Geometry_hpp

#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <map>

//Constants
const double MAX_LENGTH_OF_LINE = 1000.0;

//Structs
struct node
{
    int data;
    node* left;//less than data
    node* right;//greater than data
};

struct point
{
    double  X;
    double  Y;
};

struct line
{
    point   Start;
    point   End;
};

struct line_slope
{
    point   Start;
    double  Slope;
    double  Length;
};

struct triangle
{
    point   points[3];
    line    lines[3];
};

//Functions

//Safe Division, stops divide by zero errors
double sDiv(double x, double y);

//Changes line (points form) to line_slope
line_slope toSlopeForm(line AB);

//Changes line_slope to line (points form)
line toPointForm(line_slope CD);

//Changes Focus and Directrix form of parabola to standard form coefficients
void directrixConversion(double pointX, double pointY, double sweepX, double &k_i, double &a_i, double &c_i);

//Determinant form of line intersection
point detInter(line AB, line CD);

point circCenter(point A, point B, point C);



#endif /* Geometry_hpp */
