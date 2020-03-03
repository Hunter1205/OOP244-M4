#ifndef AMA_PRODUCT_H
#define AMA_PRODUCT_H

#include <iostream>
#include <cstring>
#include "ErrorState.h"
#include "iProduct.h"



namespace ama {


	class Product : public iProduct {
		char productType; // maybe const char
		char SKU[max_length_sku + 1];
		char ProdUnit[max_length_unit + 1];
		char productName[max_length_name];
		int quantity;
		int quantityInNeed;
		double priceBeforeTax;
		bool taxableProduct;
		ErrorState errMsgAddr;
	protected:
		void message(const char* pText);//
		bool isClear() const;//

	public:
		Product(char = 'N'); //
		Product(const char* sku, const char* addressPtr, const char* unit, double pricebfTax = 0.0, int qntyNeeded = 0, int qntyOnHand = 0, bool taxable = true);//
		Product(const Product& anotherItem); // copy constructor//
		~Product();//
		Product& operator=(const Product& anotherItem); // copy assignment operator //

		int operator+=(int cnt);//
		bool operator==(const char* sku) const;//
		bool operator> (const char* sku) const;//
		bool operator> (const iProduct& ) const; //
		int qtyAvailable() const;//
		int qtyNeeded() const;//
		const char* name() const;
		double total_cost() const;//
		bool isEmpty() const;//

		std::istream& read(std::istream& is, bool interractive);
		std::ostream& write(std::ostream& out, int writeMode) const;
	};
	iProduct* createInstance(char tag);
}


#endif // !AMA_PRODUCT_H


