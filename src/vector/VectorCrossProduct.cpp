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

Logger VectorCrossProduct::log = Logger("VectorCrossProduct");

long VectorCrossProduct::eval() {
	auto start = chrono::system_clock::now();
	
	Vector crossProduct = arguments[0];
	log.i("Calculating cross product, starting with vector (%s).", fmt(crossProduct).c_str());
	log.r("Vector Cross Product = (AyBz - AzBy) * i + (AzBx - AxBz) * j + (AxBy - AyBx) * k // yields a vector value");
	
	for (size_t i = 1; i < arguments.size(); i++) {
		Vector arg = arguments[i];
		Real iCoeff = (crossProduct.y * arg.z) - (crossProduct.z * arg.y);
		Real jCoeff = (crossProduct.z * arg.x) - (crossProduct.x * arg.z);
		Real kCoeff = (crossProduct.x * arg.y) - (crossProduct.y * arg.x);
		Vector newCrossProd(iCoeff, jCoeff, kCoeff);
		log.r("Cross product is currently %s, after argument %i (%s): (%s) X (%s) = %s", fmt(crossProduct).c_str(), i,
		      fmt(arg).c_str(), fmt(crossProduct).c_str(), fmt(arg).c_str(), fmt(newCrossProd).c_str());
		
		log.r("Work:");
		log.r("\tCoefficient i = (%s * %s) - (%s * %s) = %s", fmt(crossProduct.y).c_str(), fmt(arg.z).c_str(),
		      fmt(crossProduct.z).c_str(), fmt(arg.y).c_str(), fmt(iCoeff).c_str());
		log.r("\tCoefficient j = (%s * %s) - (%s * %s) = %s", fmt(crossProduct.z).c_str(), fmt(arg.x).c_str(),
		      fmt(crossProduct.x).c_str(), fmt(arg.z).c_str(), fmt(jCoeff).c_str());
		log.r("\tCoefficient k = (%s * %s) - (%s * %s) = %s", fmt(crossProduct.x).c_str(), fmt(arg.y).c_str(),
		      fmt(crossProduct.y).c_str(), fmt(arg.x).c_str(), fmt(kCoeff).c_str());
		
		crossProduct = newCrossProd;
	}
	
	auto end = chrono::system_clock::now();
	
	result = crossProduct;
	
	return chrono::duration_cast<chrono::microseconds>(end - start).count();
}
