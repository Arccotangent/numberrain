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

#include "MatrixAddition.h"

using namespace std;

Logger MatrixAddition::log = Logger("MatrixAddition");

long MatrixAddition::eval() {
	auto start = chrono::system_clock::now();
	
	Matrix sum = arguments[0];
	log.i("Adding matrices, starting with sum of:\n%s", fmt(sum).c_str());
	
	for (size_t i = 1; i < arguments.size(); i++) {
		Matrix arg = arguments[i];
		Matrix newSum = sum + arg;
		log.r("Sum is currently:\n%s\nafter argument %i:\n%s\n%s+\n%s=\n%s\n", fmt(sum).c_str(), i, fmt(arg).c_str(),
		      fmt(sum).c_str(), fmt(arg).c_str(), fmt(newSum).c_str());
		sum = newSum;
	}
	
	auto end = chrono::system_clock::now();
	
	result = sum;
	
	return chrono::duration_cast<chrono::microseconds>(end - start).count();
}
