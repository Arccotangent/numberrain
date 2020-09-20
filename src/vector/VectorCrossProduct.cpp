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

#include "VectorCrossProduct.h"

using namespace std;

long VectorCrossProduct::eval() {
	auto start = chrono::system_clock::now();
	
	Vector crossProduct = arguments[0];
	cout << "Calculating cross product, starting with vector (" << fmt(crossProduct) << ")." << endl;
	cout << "Vector Cross Product = (AyBz - AzBy) * i + (AzBx - AxBz) * j + (AxBy - AyBx) * k // yields a vector value"
	     << endl;
	
	for (size_t i = 1; i < arguments.size(); i++) {
		Vector arg = arguments[i];
		Real iCoeff = (crossProduct.y * arg.z) - (crossProduct.z * arg.y);
		Real jCoeff = (crossProduct.z * arg.x) - (crossProduct.x * arg.z);
		Real kCoeff = (crossProduct.x * arg.y) - (crossProduct.y * arg.x);
		Vector newCrossProd(iCoeff, jCoeff, kCoeff);
		cout << "Cross product is currently " << fmt(crossProduct) << ", after argument " << i << " (" << fmt(arg)
		     << "): (" << fmt(crossProduct) << ") X (" << fmt(arg) << ") = " << fmt(newCrossProd) << endl;
		
		cout << "Work:" << endl;
		cout << "\tCoefficient i = (" << fmt(crossProduct.y) << " * " << fmt(arg.z) << ") - (" << fmt(crossProduct.z)
		     << " * " << fmt(arg.y) << ") = " << fmt(iCoeff) << endl;
		cout << "\tCoefficient j = (" << fmt(crossProduct.z) << " * " << fmt(arg.x) << ") - (" << fmt(crossProduct.x)
		     << " * " << fmt(arg.z) << ") = " << fmt(jCoeff) << endl;
		cout << "\tCoefficient k = (" << fmt(crossProduct.x) << " * " << fmt(arg.y) << ") - (" << fmt(crossProduct.y)
		     << " * " << fmt(arg.x) << ") = " << fmt(kCoeff) << endl;
		
		crossProduct = newCrossProd;
	}
	
	auto end = chrono::system_clock::now();
	
	result = crossProduct;
	
	return chrono::duration_cast<chrono::microseconds>(end - start).count();
}
