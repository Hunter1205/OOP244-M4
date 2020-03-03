#ifndef AMA_IPRODUCT_H
#define AMA_IPRODUCT_H

/*Dennapa Harachai
Student ID 153369178
Section SFG
Date March 24,2019
Milestone 4 Winter 2019*/
//The iProduct class is an interface that exposes the Product hierarchy to client applications.

#include <iostream>

namespace ama {
	const int max_length_label = 30;
	const int max_length_sku = 7;
	const int max_length_name = 75;
	const int max_length_unit = 10;
	const int write_condensed = 0;
	const int write_table = 1;
	const int write_human = 2;
	const double tax_rate = 0.13; // 13%

	class iProduct {
	public:

		virtual std::ostream& write(std::ostream& os, int writeMode) const = 0;
		virtual std::istream& read(std::istream& is, bool interractive) = 0;
		virtual bool operator==(const char* sku) const = 0;
		virtual double total_cost() const = 0;
		virtual int qtyNeeded() const = 0;
		virtual int qtyAvailable() const = 0;
		virtual const char* name() const = 0;
		virtual int operator+=(int qty) = 0;
		virtual bool operator>(const iProduct& other) const = 0;
		virtual ~iProduct() = default;
	};
	iProduct* createInstance(char tag);

}

#endif // !ama_iproduct_h