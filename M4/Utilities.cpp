// TODO: add file header comments here
//Milestone 3
//Assignment Submission
//hahmad20@myseneca.ca
//Haasher Ahmad
//OOP244SFG
//136588167
//03/17/2019

#include <iostream>
#include <cstring>

#include "Product.h"
#include "ErrorState.h"
#include "Utilities.h"

using namespace std;

namespace ama{
  	double& operator+=(double& total, const iProduct& cost){
		//Adds total cost of the product into the first parameter 
		//and returns result
		return total += cost.total_cost();
	}

 	std::ostream& operator<<(std::ostream& out, const iProduct& b){
		//Writes into the first parameter, in a human readable format
		return b.write(out, write_human);
	}

	std::istream& operator>>(std::istream& in, iProduct& b){
		//Reads from the first parameter a product in interactive mode
		return b.read(in, true);
	}

	iProduct* createInstance(char tag){
		if(tag == 'N' || tag == 'n'){
			//dynamically create instances in the Product hierarchy
			return new Product('N');
		}else{
			return nullptr;
		}
	}
}