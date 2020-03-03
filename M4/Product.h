// TODO: add file header comments here
//Milestone 3
//Assignment Submission
//hahmad20@myseneca.ca
//Haasher Ahmad
//OOP244SFG
//136588167
//03/17/2019

#ifndef AMA_PRODUCT_H
#define AMA_PRODUCT_H

#include <iostream>
#include <fstream>
#include <limits>

#include "ErrorState.h"
#include "iProduct.h"

namespace ama{
	class Product : public iProduct{
	private:
	 	char productType;
		char _sku[max_length_sku + 1];
		char units[max_length_unit + 1];
		char names[max_length_name];
		int qty;
		int quantityNeeded;
		double prices;
		bool isTaxed;
		char tax;
		ErrorState error;

	protected:
		bool isClear() const;
		void message(const char* pText);
	
	public:
		//Safe Empty State
		Product(char='N');
		//recieves parameters, validates them, stores them in appropriate attributes
		Product(const char* sku, const char* name, const char* unit, double price = 0.0, int qtyN = 0, int qtyH = 0, bool tax = true);
		//Copy Constructor
		Product(const Product&);
		//Copy Assignment Constructor
		Product& operator=(const Product&);
		//Deconstructor
		~Product();

		//returns total of price with out/including tax
		double total_cost() const;
		//returns true/false if the object is in the empty state
		bool isEmpty() const;
		//returns quantity on hand value
		int qtyAvailable() const;
        //returns quantity needed value
		int qtyNeeded() const;
		//returns address of name. 
		//if the Product has no name, this query returns nullptr
		const char* name() const;

		//returns true/false if the string specified in the parameter
		//is equal to string stored in the SKU attribute of the current instance
		bool operator==(const char* sku) const;
		//returns true/false if the SKU attribute from the current instance
		//is greater than the string stored at the received address
		bool operator>(const char* sku) const;
		//returns true/false if the name of the current object is greater than
		//the name of the Product received as parameter object
		bool operator>(const iProduct& prod) const;
		//If int received is positive-valued, add it to the quantity on hand
		int operator+=(int cnt);

		std::istream& read(std::istream& in, bool interractive);
		std::ostream& write(std::ostream& os, int writeMode) const;
	};
	//dynamically create instances in the Product hierarchy
	iProduct* createInstance(char tag);
}
#endif