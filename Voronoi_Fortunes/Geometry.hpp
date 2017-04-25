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


#define MIN_RAY_LENGTH  0.01
#define MAX_NUM_RAYS    10000

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

struct ray
{
    point   Origin;
    double  Angle;
    double  Length;
};

struct cell
{
    point               Center;
    std::vector <ray>   Rays;
    std::vector <bool>  Fixed;
    
};

struct triangle
{
    point   points[3];
    line    lines[3];
};

struct circle
{
    point   Center;
    double  Radius;
};

//Functions

//Safe Division, stops divide by zero errors
double sDiv(double x, double y);

//Simple pythagorean distance
double dist(point A, point B);

//Changes line (points form) to line_slope
line_slope toSlopeForm(line AB);

//Changes line_slope to line (points form)
line toPointForm(line_slope CD);

//Changes Focus and Directrix form of parabola to standard form coefficients
void directrixConversion(double pointX, double pointY, double sweepX, double &k_i, double &a_i, double &c_i);

//Determinant form of line intersection
point detInter(line AB, line CD);

point circCenter(point A, point B, point C);

circle circFromPoints(point A, point B, point C);

point endOfRay(ray A);

std::vector <point> endVector(cell A);

void initCell(cell &A, point O, int numOfRays);

void inflateCell(cell &A, double delta);

std::vector <double> pointToDoubleInter(std::vector <point> A);

#endif /* Geometry_hpp */
