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

#include "CustomBaseLogarithm.h"

using namespace std;

long CustomBaseLogarithm::eval() {
	auto start = chrono::system_clock::now();
	
	Real base = arguments[0];
	Real num = arguments[1];
	
	cout << "Evaluating log_" << fmt(base) << "(" << fmt(num) << ")" << endl;
	
	cout << "Change of base formula: log_base(num) = log10(num) / log10(base)" << endl;
	cout << "Evaluating log10(" << fmt(num) << ") / log10(" << fmt(base) << ")" << endl;
	
	result = boost::multiprecision::log10(num) / boost::multiprecision::log10(base);
	
	cout << "Final result is " << fmt(result) << endl;
	
	auto end = chrono::system_clock::now();
	
	return chrono::duration_cast<chrono::microseconds>(end - start).count();
}
