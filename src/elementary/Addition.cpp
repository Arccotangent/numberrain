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

#include "Addition.h"

using namespace std;

Logger Addition::log = Logger("Addition");

long Addition::eval() {
	auto start = chrono::system_clock::now();
	
	Real sum = arguments[0];
	log.i("Adding numbers, starting with sum of %s.", fmt(sum).c_str());
	
	for (size_t i = 1; i < arguments.size(); i++) {
		Real arg = arguments[i];
		Real newSum = sum + arg;
		log.r("Sum is currently %s, after argument %i (%s): %s + %s = %s", fmt(sum).c_str(), i, fmt(arg).c_str(),
		      fmt(sum).c_str(), fmt(arg).c_str(), fmt(newSum).c_str());
		sum = newSum;
	}
	
	auto end = chrono::system_clock::now();
	
	result = sum;
	
	return chrono::duration_cast<chrono::microseconds>(end - start).count();
}
