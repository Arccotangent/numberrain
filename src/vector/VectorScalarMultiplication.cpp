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

#include "VectorScalarMultiplication.h"

using namespace std;

Logger VectorScalarMultiplication::log = Logger("VectorScalarMultiplication");

long VectorScalarMultiplication::eval() {
	auto start = chrono::system_clock::now();
	
	Real a = arguments[0].x;
	Vector b = arguments[1];
	log.i("Multiplying scalar A, %s, by vector B, (%s).", fmt(a).c_str(), fmt(b).c_str());
	log.r("Vector/Scalar Product = ABx * i + ABy * j + ABz * k // yields a vector value");
	
	Real newX = a * b.x;
	log.r("Product x = %s * %s = %s", fmt(a).c_str(), fmt(b.x).c_str(), fmt(newX).c_str());
	
	Real newY = a * b.y;
	log.r("Product y = %s * %s = %s", fmt(a).c_str(), fmt(b.y).c_str(), fmt(newY).c_str());
	
	Real newZ = a * b.z;
	log.r("Product z = %s * %s = %s", fmt(a).c_str(), fmt(b.z).c_str(), fmt(newZ).c_str());
	
	Vector product(newX, newY, newZ);
	log.r("Final Product = %s", fmt(product).c_str());
	
	auto end = chrono::system_clock::now();
	
	result = product;
	
	return chrono::duration_cast<chrono::microseconds>(end - start).count();
}
