/*
This file is part of Numberrain.

Numberrain is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as
published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

Numberrain is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with Numberrain.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Multiplication.h"

using namespace std;

Logger Multiplication::log = Logger("Multiplication");

long Multiplication::eval() {
	auto start = chrono::system_clock::now();
	
	Real product = arguments[0];
	log.i("Multiplying numbers, starting from %s.", fmt(product).c_str());
	
	for (size_t i = 1; i < arguments.size(); i++) {
		Real arg = arguments[i];
		Real newProd = product * arg;
		log.r("Product is currently %s, after argument %i (%s): %s * %s = %s", fmt(product).c_str(), i,
		      fmt(arg).c_str(), fmt(product).c_str(), fmt(arg).c_str(), fmt(newProd).c_str());
		product = newProd;
	}
	
	auto end = chrono::system_clock::now();
	
	result = product;
	
	return chrono::duration_cast<chrono::microseconds>(end - start).count();
}