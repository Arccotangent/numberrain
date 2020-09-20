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

long VectorScalarMultiplication::eval() {
	auto start = chrono::system_clock::now();
	
	Real a = arguments[0].x;
	Vector b = arguments[1];
	cout << "Multiplying scalar A, " << fmt(a) << ", by vector B, (" << fmt(b) << ")." << endl;
	cout << "Vector/Scalar Product = ABx * i + ABy * j + ABz * k // yields a vector value" << endl;
	
	Real newX = a * b.x;
	cout << "Product x = " << fmt(a) << " * " << fmt(b.x) << " = " << fmt(newX) << endl;
	
	Real newY = a * b.y;
	cout << "Product y = " << fmt(a) << " * " << fmt(b.y) << " = " << fmt(newY) << endl;
	
	Real newZ = a * b.z;
	cout << "Product z = " << fmt(a) << " * " << fmt(b.z) << " = " << fmt(newZ) << endl;
	
	Vector product(newX, newY, newZ);
	cout << "Final Product = " << fmt(product) << endl;
	
	auto end = chrono::system_clock::now();
	
	result = product;
	
	return chrono::duration_cast<chrono::microseconds>(end - start).count();
}
