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

#include "Exponentiation.h"

using namespace std;

Logger Exponentiation::log = Logger("Exponentiation");

long Exponentiation::eval() {
	auto start = chrono::system_clock::now();
	
	Real res = arguments[arguments.size() - 1];
	log.i("Evaluating exponents, starting with %s.", fmt(res).c_str());
	
	for (size_t i = arguments.size() - 2; i >= 0; i--) {
		Real arg = arguments[i];
		Real newRes = pow(arg, res);
		log.r("Result is currently %s, after argument %i (%s): %s^%s = %s", fmt(res).c_str(), i, fmt(arg).c_str(),
		      fmt(arg).c_str(), fmt(res).c_str(), fmt(newRes).c_str());
		res = newRes;
		
		if (i == 0)
			break;
	}
	
	auto end = chrono::system_clock::now();
	
	result = res;
	
	return chrono::duration_cast<chrono::microseconds>(end - start).count();
}
