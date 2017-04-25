//
//  BST.cpp
//  Voronoi_Fortunes
//
//  Created by Ben Lewson on 3/12/17.
//  Based on implementation from "Paul Programming" YouTube Channel
//

#include "BST.hpp"

BST::BST()
{
    //Ensure root points to nothing
    root = NULL;
}

BST::node* BST::CreateLeaf(double key)
{
    node* n =   new node;
    n->key =    key;
    
    //Leafs are terminal, so left and right are null
    n->left =   NULL;
    n->right =  NULL;
    
    return n;
}

void BST::AddLeaf(double key)
{
    //Safely calls private function from root
    AddLeafPrivate(key, root);
}

void BST::AddLeafPrivate(double key, node* ptr)
{
    if(root == NULL)
    {
        root = CreateLeaf(key);
    }
    else if(key < ptr->key)
    {
        if(ptr->left != NULL)
        {
            AddLeafPrivate(key, ptr->left);
        }
    }
}