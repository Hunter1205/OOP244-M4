/*
Dennapa Harachai
Student ID 153369178
Email dharachai@myseneca.ca
March 24,2019

Milestone 4 Winter 2019
*/

#include <iostream>
#include <cstring>
#include "Utilities.h"

//helper functions implemetation

namespace ama {

	double& operator+=(double& total, const iProduct& prod) {
		return total += prod.total_cost();
	}

	std::ostream& operator<<(std::ostream& out, const iProduct& prod) {
		return prod.write(out, write_human);
	}

	std::istream& operator>>(std::istream& is, iProduct& prod) {
		return prod.read(is, true);
	}

	iProduct* createInstance(char tag) {
		if (tag == 'N' || tag == 'n') {
			return new Product('N');
		}	
		else {
			return nullptr;
		}
	}
}