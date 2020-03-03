// TODO: add file header comments here
//Milestone 3
//Assignment Submission
//hahmad20@myseneca.ca
//Haasher Ahmad
//OOP244SFG
//136588167
//03/17/2019

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cstring>

#include "ErrorState.h"
#include "Product.h"
#include "Utilities.h"

using namespace std;

namespace ama{
	Product::Product(char type) : productType(type){ 
		//Safe Empty State which optionally receives 
		//a product type with default value of 'N'
		_sku[0] = '\0';
		units[0] = '\0';
		names[0] = '\0' ;
		qty = 0;
		quantityNeeded = 0;
		prices = 0.0;
		isTaxed = true;
	}

	Product::Product(const char* mySku, const char* addressPtr, const char* unit, double pricebfTax, int qntyNeeded, int qntyOnHand, bool taxable){
		strncpy(_sku, mySku, max_length_sku);
		_sku[max_length_sku] = '\0';
		strncpy(names, addressPtr, max_length_name);
		names[max_length_name] = '\0';
		strncpy(units, unit, max_length_unit);
		units[max_length_unit] = '\0';

		qty = qntyOnHand;
		quantityNeeded = qntyNeeded;
		prices = pricebfTax;
		isTaxed = taxable;
	}

	//Deconstructor
	Product::~Product(){}

	Product::Product(const Product& prod) : productType('N'){ 
		//copy constructor
		prod.name();
		strncpy(_sku, prod._sku, max_length_sku);
		_sku[max_length_sku] = '\0';
		strncpy(units, prod.units, max_length_unit);
		units[max_length_unit] = '\0';

		qty = prod.qty;
		quantityNeeded = prod.quantityNeeded;
		prices = prod.prices;
		isTaxed = prod.isTaxed;
		error.message(prod.error.message());
	}

	Product &Product::operator=(const Product& prod){
		//copy assignment operator
		if(this != &prod){ 
			strncpy(_sku, prod._sku, max_length_sku);
			_sku[max_length_sku] = '\0';
			strncpy(names, prod.names, max_length_name);
			names[max_length_name] = '\0';
			strncpy(units, prod.units, max_length_unit);
			units[max_length_unit] = '\0';
			qty = prod.qty;
			quantityNeeded = prod.quantityNeeded;
			prices = prod.prices;
			isTaxed = prod.isTaxed;
			error.message(prod.error.message());
		}
		return *this;
	}

	const char* Product::name() const{
		//returns address of name. 
		//if the Product has no name, this query returns nullptr
		return (names[0] == '\0' || names == nullptr) ? nullptr : names;
	}

	void Product::message(const char* pText){
		error = pText;
	}

	bool Product::isClear() const{
		//returns true/false if there are no error message
		return (error.message() == nullptr) ? true : false;
	}

	double Product::total_cost() const{
		double total;
		if(isTaxed){
			//returns total of price including tax
			total = prices * (1 + tax_rate);
		}else{
			//returns total of price without tax
			total = prices;
		}
		return static_cast<double>(qty * total);
	}

	int Product::qtyAvailable() const{
		//return quantity on hand value
		return qty;
	}

	int Product::qtyNeeded() const{
		//return quantity needed value
		return quantityNeeded;
	}

	bool Product::isEmpty() const{
		//returns true/false if the object is in the empty state
		return (names[0] == '\0') ? true : false;
	}

	int Product::operator+=(int cnt){
		//If int received is positive-valued
		//add it to the quantity on hand
		return cnt > 0 ? qty += cnt : qty;
	}

	bool Product::operator==(const char* sku) const{
		//returns true/false if the string specified in the parameter
		//is equal to string stored in the SKU attribute of the current instance
		return (strcmp(_sku, sku) == 0) ? true : false;
	}

	bool Product::operator>(const char* sku) const{
		//returns true/false if the SKU attribute 
		//from the current instance is greater than 
		//the string stored at the received address
		return (strcmp(_sku, sku) > 0) ? true : false;
	}

	bool Product::operator>(const iProduct& prod) const{
		//returns true/false if the name of the current object is greater than
		//the name of the Product received as parameter object
		return (strcmp(name(), prod.name()) > 0) ? true : false;
	}

	std::ostream& Product::write(std::ostream& os, int writeMode) const{
		if(!isClear()){ 
			//Displays any error message
			os << error.message();
		}else if(isEmpty()){
			//do nothing
		}else if(writeMode == write_table){
			//Write Table Formatting
			os << " ";
			os.width(max_length_sku);
			os.setf(ios::right);
			os << _sku << " | ";
			os.unsetf(ios::right);
			os.setf(ios::left);
			//checks if names length is greater than 16
			//outputs only 13 characters of name with 3 dots
			if(strlen(names) > 16){
				char temp[max_length_name] = { '\0' };
				os.width(13);
				strncpy(temp, names, 13);
				os << temp << "..." <<" | ";
			}else{
				os << names << " | ";
			}
			os.unsetf(ios::left);
			os.width(10);
			os.setf(ios::left);
			os << units << " | ";
			os.unsetf(ios::left);
			os.width(7);
			os.setf(ios::right);
			os << std::fixed;
			os.precision(2);
			os << prices << " | ";
			os.unsetf(ios::right);
			os.width(3);
			os.setf(ios::right);
			os << (isTaxed ? "yes" : "no") << " | ";
			os.unsetf(ios::right);
			os.width(6);
			os.setf(ios::right);
			os << qty << " | ";
			os.unsetf(ios::right);
			os.width(6);
			os.setf(ios::right);
			os << quantityNeeded << " |";
		}else if(writeMode == write_human){
			//Human Writing Formatting
			os.width(max_length_label);
			os.setf(ios::right);
			os << "Sku: " << _sku << endl;
			os.width(max_length_label);
			os.setf(ios::right);
			os << "Name: " << names << endl;
			os.width(max_length_label);
			os.setf(ios::right);
			os.setf(ios::fixed);
			os.precision(2);
			os << "Price: " << prices << endl;
			if(isTaxed){
				os.width(max_length_label);
				os.setf(ios::right);
				os.setf(ios::fixed);
				os.precision(2);
				os << "Price after Tax: " << prices * (1 + tax_rate) << endl;
			}else{
				os.width(max_length_label);
				os.setf(ios::right);
				os.setf(ios::fixed);
				os.precision(2);
				os << "Price after Tax: " << prices << endl;
			}
			os.width(max_length_label);
			os.setf(ios::right);
			os << "Quantity Available: " << qty << " " << units << endl;
			os.width(max_length_label);
			os.setf(ios::right);
			os << "Quantity Needed: " << quantityNeeded << " " << units << endl;
		}else if (writeMode == write_condensed){
			//Condensed Writing Formatting
			os << productType << "," << _sku << ","
				<< names << "," << units << ","
				<< prices << "," << isTaxed << ","
				<< qty << "," << quantityNeeded;
		}
		return os;
	}

	//reads data from the stream, and stores it in the attributes
	std::istream& Product::read(std::istream& in, bool interractive){
		//If bool is true/false function does or doesn't interact with the user
		if(interractive){
			char input[max_length_label];
			
			cout.setf(ios::right);
			cout.width(max_length_label);
			
			cout << "Sku: ";
			in.getline(_sku, max_length_sku);
			cout.width(max_length_label);
			
			cout << "Name (no spaces): ";
			in.getline(names, max_length_name);
			cout.width(max_length_label);
			
			cout << "Unit: ";
			in.getline(units, max_length_unit);
			cout.width(max_length_label);

			cout << "Taxed? (y/n): ";
			in >> input;
			//Sets error message if the tax input not valid
			if(input[0] != 'Y' && input[0] != 'y' && input[0] != 'N' && input[0] != 'n'){
				in.setstate(ios::failbit);
				message("Only (Y)es or (N)o are acceptable!");
			}else{
				cout.width(max_length_label);
				cout << "Price: ";
				in >> prices;
				//set an error message if the price input not valid
				if(prices <= 0.0){
					in.setstate(ios::failbit);
					message("Invalid Price Entry!");
				}else{
					//set an error message if the quantity input not valid
					cout.width(max_length_label);
					cout << "Quantity on hand: ";
					in >> qty;
					if(qtyAvailable() <= 0){
						in.setstate(ios::failbit);
						message("Invalid Quantity Available Entry!");
					}else{
						//set an error message if the quantity needed input not valid
						cout.width(max_length_label);
						cout << "Quantity needed: ";
						in >> quantityNeeded;
						if(qtyNeeded() <= 0){
							in.setstate(ios::failbit);
							message("Invalid Quantity Needed Entry!");
						}
					}
				}
			}
		}else{
			//If no errors, receives input from stream and 
			//sets it to current instance attributes
			in.getline(_sku, max_length_sku, ',');
			in.getline(names, max_length_name, ',');
			in.getline(units, max_length_unit, ',');
			in >> prices;
			in.ignore();
			in >> isTaxed;
			in.ignore();
			in >> qty;
			in.ignore();
			in >> quantityNeeded;
		}
		in.ignore(); // Catching extra newline inputted.
		return in;
	}
}