//
//  main.cpp
//  Voronoi_Fortunes
//
//  Created by Ben Lewson on 3/11/17.
//  Copyright © 2017 Ben Lewson. All rights reserved.
//

#include "Geometry.hpp"
#include "SvgPacker.hpp"
#include "BST.hpp"

using namespace std;

SvgPacker svg;


//Initial Data
vector <point> points =
{
     {101.6, 110.6}
    ,{200.9, 207.2}
    ,{285.0, 97.5}
};

vector <point> seeds =
{
     {10,10}
    ,{15.7,11}
    ,{9.1,16.8}
    ,{14.4,16.1}
};

cell T;

point Origin = {20,20};

int n_rays = 360;

//Main Loop
int main(int argc, const char * argv[]) {
    
    
    //Proving out circle finding code
    
    /*
    circle circ = circFromPoints(points.at(0), points.at(1), points.at(2));
    
    for(int i = 0; i < points.size(); i++)
    {
        cout << points.at(i).X << " " << points.at(i).Y << "\n";
        svg.addToWork(svg.circle(1, points.at(i).X, points.at(i).Y));
    }
    
    printf("\nCenter = %.3f,%.3f\nRadius = %.3f\n\n", circ.Center.X, circ.Center.Y,circ.Radius);
    
    svg.addToWork(svg.circle(circ.Radius, circ.Center.X, circ.Center.Y));
    svg.addToWork(svg.circle(1, circ.Center.X, circ.Center.Y,"red"));
    
    svg.addToWork(svg.line(points.at(0).X, points.at(0).Y, points.at(1).X, points.at(1).Y));
    svg.addToWork(svg.line(points.at(1).X, points.at(1).Y, points.at(2).X, points.at(2).Y));
    svg.addToWork(svg.line(points.at(0).X, points.at(0).Y, points.at(2).X, points.at(2).Y));
    */
    
    
    initCell(T, Origin, n_rays);
    
    for(int i = 0; i < 4000; i++)
    {
        for(int j = 0; j < T.Rays.size(); j++)
        {
            if(endOfRay(T.Rays.at(j)).X < 10 || endOfRay(T.Rays.at(j)).Y < 10)
            {
                T.Fixed.at(j) = true;
            }
        }
        inflateCell(T, 0.01);
    }
    
    //A lot happens here, this is bad code but it makes me feel good inside
    //Because I'm a monster
    svg.addToWork(svg.polygon(pointToDoubleInter(endVector(T))));
    
    svg.addToWork(svg.fileFooter());
    
    cout << svg.WorkingContent;
    
    
    return 0;
}

