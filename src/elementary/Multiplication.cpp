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

long Multiplication::eval() {
	auto start = chrono::system_clock::now();
	
	Real product = arguments[0];
	cout << "Multiplying numbers, starting from " << fmt(product) << "." << endl;
	
	for (size_t i = 1; i < arguments.size(); i++) {
		Real arg = arguments[i];
		Real newProd = product * arg;
		cout << "Product is currently " << fmt(product) << ", after argument " << i << " (" << fmt(arg) << "): "
		     << fmt(product) << " * " << fmt(arg) << " = " << fmt(newProd) << endl;
		product = newProd;
	}
	
	auto end = chrono::system_clock::now();
	
	result = product;
	
	return chrono::duration_cast<chrono::microseconds>(end - start).count();
}