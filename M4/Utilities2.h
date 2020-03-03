#include <iostream>
#include "Product.h"


//helper functions

namespace ama {
	class Utilities : public iProduct {}; // optional
		double& operator+=(double& total, const iProduct& prod);
		std::ostream& operator<<(std::ostream& out, const iProduct& prod);
		std::istream& operator>>(std::istream& is, iProduct& prod);

		iProduct* createInstance(char tag);

}
