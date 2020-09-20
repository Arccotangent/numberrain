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

#include "VectorDotProduct.h"

using namespace std;

long VectorDotProduct::eval() {
	auto start = chrono::system_clock::now();
	
	Vector a = arguments[0];
	Vector b = arguments[1];
	cout << "Calculating dot product of vectors A and B: (" << fmt(a) << ") and (" << fmt(b) << ")." << endl;
	cout << "Dot Product = AxBx + AyBy + AzBz // yields a scalar value" << endl;
	
	Real xProduct = a.x * b.x;
	cout << "AxBx = " << fmt(a.x) << " * " << fmt(b.x) << " = " << fmt(xProduct) << endl;
	
	Real yProduct = a.y * b.y;
	cout << "AyBy = " << fmt(a.y) << " * " << fmt(b.y) << " = " << fmt(yProduct) << endl;
	
	Real zProduct = a.z * b.z;
	cout << "AzBz = " << fmt(a.z) << " * " << fmt(b.z) << " = " << fmt(zProduct) << endl;
	
	Real dotProduct = xProduct + yProduct + zProduct;
	cout << "Dot Product = " << fmt(xProduct) << " + " << fmt(yProduct) << " + " << fmt(zProduct) << " = "
	     << fmt(dotProduct) << endl;
	
	Vector dotProductVec(dotProduct);
	
	auto end = chrono::system_clock::now();
	
	result = dotProductVec;
	
	return chrono::duration_cast<chrono::microseconds>(end - start).count();
}