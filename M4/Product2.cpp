/*
Dennapa Harachai
Student ID 153369178
Email dharachai@myseneca.ca
March 24,2019

Milestone 3 Winter 2019
*/

#define _CRT_SECURE_NO_WARNINGS


#include <iostream>
#include <string>
#include <iomanip>
#include "Product.h"
#include "Utilities.h"
#include "iProduct.h"


using namespace std;

namespace ama {

	Product::Product(char type){//: productType(type){ //constructor optionally receives a character that identifies the product type. The default value is 'N'.
		productType = type;
		SKU[0] = '\0';
		ProdUnit[0] = '\0';
		productName[0] = '\0';
		quantity = 0;
		quantityInNeed = 0;
		priceBeforeTax = 0.0;
		taxableProduct = true;
	}

	Product::Product(const char* mySku, const char* addressPtr, const char* unit, double pricebfTax, int qntyNeeded, int qntyOnHand, bool taxable) {


		strncpy(SKU, mySku, max_length_sku);
		SKU[max_length_sku] = '\0';
		strncpy(productName, addressPtr, max_length_name);
		productName[max_length_name] = '\0';
		strncpy(ProdUnit, unit, max_length_unit);
		ProdUnit[max_length_unit] = '\0';

		quantity = qntyOnHand;
		quantityInNeed = qntyNeeded;
		priceBeforeTax = pricebfTax;
		taxableProduct = taxable;

	}

	Product::~Product() {	}



	Product::Product(const Product& anotherItem) {//: productType('N'){ //copy constructor
		productType = 'N';
		anotherItem.name();
		strncpy(SKU, anotherItem.SKU, max_length_sku);
		SKU[max_length_sku] = '\0';
		strncpy(ProdUnit, anotherItem.ProdUnit, max_length_unit);
		ProdUnit[max_length_unit] = '\0';

		quantity = anotherItem.quantity;
		quantityInNeed = anotherItem.quantityInNeed;
		priceBeforeTax = anotherItem.priceBeforeTax;
		taxableProduct = anotherItem.taxableProduct;
		errMsgAddr.message(anotherItem.errMsgAddr.message());
		//*this = anotherItem; another way to write is function

	}

	const char* Product::name() const {
		//returns the address of the C-style null-terminated string that holds the name of the Good. If the Good has no name, this query returns nullptr
		return productName[0] == '\0' || productName == nullptr ? nullptr : productName;
	}

	void Product::message(const char* pText) {
		errMsgAddr = pText;
	}

	bool Product::isClear() const {
		//This query returns true if the ErrorState attribute contains no error message; false otherwise.
		return (errMsgAddr.message() == nullptr) ? true : false; // call isEmpty() in ErrorState
	}

	Product &Product ::operator=(const Product& anotherItem) {
		// copy assignment operator
		if (this != &anotherItem) { // ** golden rule!! check for self-assignment first
			strncpy(SKU, anotherItem.SKU, max_length_sku);
			SKU[max_length_sku] = '\0';
			strncpy(productName, anotherItem.productName, max_length_name);
			productName[max_length_name] = '\0';
			strncpy(ProdUnit, anotherItem.ProdUnit, max_length_unit);
			ProdUnit[max_length_unit] = '\0';
			quantity = anotherItem.quantity;
			quantityInNeed = anotherItem.quantityInNeed;
			priceBeforeTax = anotherItem.priceBeforeTax;
			taxableProduct = anotherItem.taxableProduct;
			errMsgAddr.message(anotherItem.errMsgAddr.message());
		}
		return *this;


	}

	std::istream &Product::read(std::istream& in, bool interractive) {
		/*reads data from the stream, and stores it in the attributes.
		Depending on the second parameter, this function prompts the user asking for values, or doesn’t interact with the user.
		*/

		if (interractive) {
			char readInput[max_length_label];
			cout.setf(ios::right);
			cout.width(max_length_label);
			cout << "Sku: ";
			in.getline(SKU, max_length_sku);
			cout.width(max_length_label);
			cout << "Name (no spaces): ";
			in.getline(productName, max_length_name);
			cout.width(max_length_label);
			cout << "Unit: ";
			in.getline(ProdUnit, max_length_unit);
			cout.width(max_length_label);
			cout << "Taxed? (y/n): ";
			in >> readInput;
			// If the tax input is not valid, set an error message.
			if (readInput[0] != 'Y' && readInput[0] != 'y' && readInput[0] != 'N' && readInput[0] != 'n')
			{
				in.setstate(ios::failbit);
				message("Only (Y)es or (N)o are acceptable!");
			}
			else
			{
				cout.width(max_length_label);
				cout << "Price: ";
				in >> priceBeforeTax;
				// If the price input is not valid, set an error message.
				if (priceBeforeTax <= 0.0)
				{
					in.setstate(ios::failbit);
					message("Invalid Price Entry!");
				}
				else
				{
					// If the quantity on hand input is not valid, set an error message.
					cout.width(max_length_label);
					cout << "Quantity on hand: ";
					in >> quantity;
					if (qtyAvailable() <= 0)
					{
						in.setstate(ios::failbit);
						message("Invalid Quantity Available Entry!");
					}
					else
					{
						// If the quantity needed input is not valid, set an error message.
						cout.width(max_length_label);
						cout << "Quantity needed: ";
						in >> quantityInNeed;
						if (qtyNeeded() <= 0)
						{
							in.setstate(ios::failbit);
							message("Invalid Quantity Needed Entry!");
						}
					}
				}
			}
		}
		// If no errors have occured, receive input from stream and set it to current instance attributes.
		else
		{
			in.getline(SKU, max_length_sku, ',');
			in.getline(productName, max_length_name, ',');
			in.getline(ProdUnit, max_length_unit, ',');
			in >> priceBeforeTax;
			in.ignore();
			in >> taxableProduct;
			in.ignore();
			in >> quantity;
			in.ignore();
			in >> quantityInNeed;
		}
		in.ignore(); // Catching extra newline inputted.
		return in;
	}


	std::ostream& Product::write(std::ostream& os, int writeMode) const {
		if (!isClear()) { // if there is error msg, display it
			os << errMsgAddr.message();
		}

		else if (isEmpty()) {
			//do nothing if current obj is in SES
		}
		else if (writeMode == write_table) {
			os << " ";
			os.width(max_length_sku);
			os.setf(ios::right);
			os << SKU << " | ";
			os.unsetf(ios::right);
			os.setf(ios::left);
			//hold = productName[13];
			//productName[13] = '\0';
			if (strlen(productName) > 16) {
				char tempName[max_length_name] = { '\0' };
				os.width(13);
				strncpy(tempName, productName, 13);
				os << tempName << "..." << " | ";
			}
			else {
				os << productName << " | ";
			}
			os.unsetf(ios::left);
			os.width(10);
			os.setf(ios::left);
			os << ProdUnit << " | ";
			os.unsetf(ios::left);
			os.width(7);
			os.setf(ios::right);
			os << std::fixed;
			os.precision(2);
			os << priceBeforeTax << " | ";
			os.unsetf(ios::right);
			os.width(3);
			os.setf(ios::right);
			os << (taxableProduct ? "yes" : "no") << " | ";
			os.unsetf(ios::right);
			os.width(6);
			os.setf(ios::right);
			os << quantity << " | ";
			os.unsetf(ios::right);
			os.width(6);
			os.setf(ios::right);
			os << quantityInNeed << " |";
		}
		else if (writeMode == write_human) {
			os.width(max_length_label);
			os.setf(ios::right);
			os << "Sku: " << SKU << endl;
			os.width(max_length_label);
			os.setf(ios::right);
			os << "Name: " << productName << endl;
			os.width(max_length_label);
			os.setf(ios::right);
			os.setf(ios::fixed);
			os.precision(2);
			os << "Price: " << priceBeforeTax << endl;
			if (taxableProduct) {
				os.width(max_length_label);
				os.setf(ios::right);
				os.setf(ios::fixed);
				os.precision(2);
				os << "Price after Tax: " << priceBeforeTax * (1 + tax_rate) << endl;
			}
			else {
				os.width(max_length_label);
				os.setf(ios::right);
				os.setf(ios::fixed);
				os.precision(2);
				os << "Price after Tax: " << priceBeforeTax << endl;
			}
			os.width(max_length_label);
			os.setf(ios::right);
			os << "Quantity Available: " << quantity << " " << ProdUnit << endl;
			os.width(max_length_label);
			os.setf(ios::right);
			os << "Quantity Needed: " << quantityInNeed << " " << ProdUnit << endl;
		}
		else if (writeMode == write_condensed) {
			os << productType << "," << SKU << ","
				<< productName << "," << ProdUnit << ","
				<< priceBeforeTax << "," << taxableProduct << ","
				<< quantity << "," << quantityInNeed;
		}
		return os;
	}

	bool Product ::operator==(const char* sku) const {
		/*returns true if the string specified in the parameter
		is the same as the string stored in the SKU attribute of the current instance;
		false otherwise.*/
		return strcmp(sku, SKU) == 0;
	}

	double Product::total_cost() const {

		double total;
		if (taxableProduct) {
			total = priceBeforeTax * (1 + tax_rate);
		}
		else {
			total = priceBeforeTax;
		}
		return static_cast<double>(quantity * total);

	}

	int Product::qtyAvailable() const {
		//return quantity on hand
		return quantity;
	}

	bool Product::isEmpty() const {
		//returns true if the object is in the empty state; false otherwise.
		return (productName[0] == '\0') ? true : false;
	}

	int Product::qtyNeeded() const {
		// return the value of the attribute storing how many units of product are needed.
		return quantityInNeed;
	}

	bool Product::operator>(const char *sku) const {
		/*returns true if the SKU attribute from the current instance is greater than the string stored at the received address*/
		return (strcmp(SKU, sku) > 0) ? true : false;
	}

	bool Product:: operator> (const iProduct& anotherItem) const {
		/*returns true if the name of the current object is greater than
		the name of the Product received as parameter object*/
		return (strcmp(name(), anotherItem.name()) > 0) ? true : false; // check this one again 
	}

	int Product::operator+=(int cnt) {
		/*
		If the integer received is positive-valued,add it to the quantity on hand. */
		return cnt > 0 ? quantity += cnt : quantity;
	}

}

