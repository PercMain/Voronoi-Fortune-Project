//
//  main.cpp
//  Voronoi_Fortunes
//
//  Created by Ben Lewson on 3/11/17.
//  Copyright © 2017 Ben Lewson. All rights reserved.
//

#include "Geometry.hpp"
#include "SvgPacker.hpp"

using namespace std;

SvgPacker svg;

//Initial Data
vector <point> points =
{
     {101.6, 110.6}
    ,{200.9, 207.2}
    ,{285.0, 97.5}
};

/*
 double minX = 0.0, maxX = 400.0, minY = 0.0, maxY = 400.0;
 
 double sweep = 0.0;
 */

//Main Loop
int main(int argc, const char * argv[]) {
    
    circle circ = circFromPoints(points.at(0), points.at(1), points.at(2));
    
    for(int i = 0; i < points.size(); i++)
    {
        cout << points.at(i).X << " " << points.at(i).Y << "\n";
        svg.addToWork(svg.circle(1, points.at(i).X, points.at(i).Y));
    }
    
    printf("\nCenter = %.3f,%.3f\nRadius = %.3f\n", circ.Center.X, circ.Center.Y,circ.Radius);
    
    svg.addToWork(svg.circle(circ.Radius, circ.Center.X, circ.Center.Y));
    svg.addToWork(svg.circle(1, circ.Center.X, circ.Center.Y));
    
    svg.addToWork(svg.line(points.at(0).X, points.at(0).Y, points.at(1).X, points.at(1).Y));
    svg.addToWork(svg.line(points.at(1).X, points.at(1).Y, points.at(2).X, points.at(2).Y));
    
    svg.addToWork(svg.fileFooter());
    
    cout << svg.WorkingContent;
    
    return 0;
}

