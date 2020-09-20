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

long Exponentiation::eval() {
	auto start = chrono::system_clock::now();
	
	Real res = arguments[arguments.size() - 1];
	cout << "Evaluating exponents, starting with " << fmt(res) << "." << endl;
	
	for (size_t i = arguments.size() - 2; i >= 0; i--) {
		Real arg = arguments[i];
		Real newRes = pow(arg, res);
		cout << "Result is currently " << fmt(res) << ", after argument " << i << "(" << fmt(arg) << "): " << fmt(arg)
		     << "^" << fmt(res) << " = " << fmt(newRes) << endl;
		res = newRes;
		
		if (i == 0)
			break;
	}
	
	auto end = chrono::system_clock::now();
	
	result = res;
	
	return chrono::duration_cast<chrono::microseconds>(end - start).count();
}
