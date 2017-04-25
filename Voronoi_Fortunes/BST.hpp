//
//  BST.hpp
//  Voronoi_Fortunes
//
//  Created by Ben Lewson on 3/12/17.
//  Based on implementation from "Paul Programming" YouTube Channel
//

#ifndef BST_hpp
#define BST_hpp

#include <stdio.h>
#include <iostream>
#include <cstdlib>

class BST
{
    
private:
    
    struct node
    {
        //data value, left and right branches
        double key;
        node* left;
        node* right;
    };
    
    //Root of tree
    node* root;
    
    //Create a leaf node and return node pointer
    node* CreateLeaf(double key);
    
    //Adds leaf to tree
    void AddLeafPrivate(double key, node* ptr);
    
    
public:
    
    //Constructor
    BST();
    
    //Adds leaf to tree
    void AddLeaf(double key);
    
    
};

#endif /* BST_hpp */
