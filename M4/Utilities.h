// TODO: add file header comments here
//Milestone 3
//Assignment Submission
//hahmad20@myseneca.ca
//Haasher Ahmad
//OOP244SFG
//136588167
//03/17/2019

#ifndef AMA_UTILITIES_H
#define AMA_UTILITIES_H

#include <iostream>

#include "Product.h"

namespace ama{
    //Writes into the first parameter, in a human readable format
    std::ostream& operator<<(std::ostream&, const iProduct&);
    //Reads from the first parameter a product in interactive mode
    std::istream& operator>>(std::istream&, iProduct&);
    //Adds total cost of the product into the first parameter and returns result
    double& operator+=(double&, const iProduct&);
    //dynamically create instances in the Product hierarchy
    iProduct* createInstance(char tag);
}
#endif