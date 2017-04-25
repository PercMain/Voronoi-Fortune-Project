//
//  SvgPacker.h
//  Voronoi_Fortunes
//
//  Created by Ben Lewson on 4/26/16.
//  Copyright (c) 2016 Ben Lewson. All rights reserved.
//

#ifndef SvgPacker_hpp
#define SvgPacker_hpp

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>
#include <math.h>

#define PI 3.14159265


using namespace std;

class SvgPacker
{
public:
    //Constructor
    SvgPacker();
    
    //
    // Tag and content generation
    //
    
    //SVG boiler plate info.
    string fileHeader();
    string fileFooter();
    
    //Rotation transform opening tag and wrapper, takes angle and center of rotation
    string rotationHeader(double angle, double x, double y);
    string rotationWrap(string content, double angle, double x, double y);
    
    //pattern tag opening and wrapper. Takes width and height of base pattern
    string patternHeader(double width, double height);
    string patternWrap(string content, double width, double height);
    
    //returns <defs> or </defs> from true or false respectively. Wraps content
    string defsTag(bool openClose);
    string defsWrap(string content);
    
    //Creates line element from start and stop coordinates
    string line(double xStart, double yStart, double xStop, double yStop);
    
    //Creates circle element from radius and center coordinates
    string circle(double radius, double xCenter, double yCenter, string color = "none");
    
    //Creates arc element from radius, center coordinates, and angular limits
    string arc(double radius, double xCenter, double yCenter, double angleStart, double angleStop);
    
    //Creates quadratic bezier curve from start, stop and control point coordinates
    string quadBezier(double xStart, double yStart, double xStop, double yStop, double xControl, double yControl);
    
    //Creates polyline from coordinate vector
    string poly(vector<double> xy);
    
    //Creates closed polygon from coordinate vector
    string polygon(vector<double> xy);
    
    //Creates a rotational pattern
    string rotationPattern(string content, int numberOfInstances, double xCenter, double yCenter);
    
    //Creates dashed perimeter circle
    string dashedCircle(double radius, double xCenter, double yCenter, double arcLength, int numberOfArcs, bool centerOnGap);
    
    //
    // Tag and content arrangement
    //
    
    //Adds to working file content before output to file
    void addToWork(string addition);
    
    //Internal string storage for any function. Make null after return
    void addToTemp(string addition);
    
    //
    // Public data
    //
    
    //Temporary storage for file content before output to file
    string WorkingContent;
    
private:
    
    string _TempContent;
};

#endif /* defined(__Voronoi_Fortunes__SvgPacker__) */


