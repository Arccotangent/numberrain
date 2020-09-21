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

Logger VectorDotProduct::log = Logger("VectorDotProduct");

long VectorDotProduct::eval() {
	auto start = chrono::system_clock::now();
	
	Vector a = arguments[0];
	Vector b = arguments[1];
	log.i("Calculating dot product of vectors A and B: (%s) and (%s).", fmt(a).c_str(), fmt(b).c_str());
	log.r("Dot Product = AxBx + AyBy + AzBz // yields a scalar value");
	
	Real xProduct = a.x * b.x;
	log.r("AxBx = %s * %s = %s", fmt(a.x).c_str(), fmt(b.x).c_str(), fmt(xProduct).c_str());
	
	Real yProduct = a.y * b.y;
	log.r("AyBy = %s * %s = %s", fmt(a.y).c_str(), fmt(b.y).c_str(), fmt(yProduct).c_str());
	
	Real zProduct = a.z * b.z;
	log.r("AzBz = %s * %s = %s", fmt(a.z).c_str(), fmt(b.z).c_str(), fmt(zProduct).c_str());
	
	Real dotProduct = xProduct + yProduct + zProduct;
	log.r("Dot Product = %s + %s + %s = %s", fmt(xProduct).c_str(), fmt(yProduct).c_str(), fmt(zProduct).c_str(),
	      fmt(dotProduct).c_str());
	
	Vector dotProductVec(dotProduct);
	
	auto end = chrono::system_clock::now();
	
	result = dotProductVec;
	
	return chrono::duration_cast<chrono::microseconds>(end - start).count();
}