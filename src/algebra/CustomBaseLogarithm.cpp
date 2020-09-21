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

Logger CustomBaseLogarithm::log = Logger("CustomBaseLogarithm");

long CustomBaseLogarithm::eval() {
	auto start = chrono::system_clock::now();
	
	Real base = arguments[0];
	Real num = arguments[1];
	
	log.i("Evaluating log_%s(%s)", fmt(base).c_str(), fmt(num).c_str());
	
	log.r("Change of base formula: log_base(num) = log10(num) / log10(base)");
	log.r("Evaluating log10(%s) / log10(%s)", fmt(num).c_str(), fmt(base).c_str());
	
	result = boost::multiprecision::log10(num) / boost::multiprecision::log10(base);
	
	log.i("Final result is %s", fmt(result).c_str());
	
	auto end = chrono::system_clock::now();
	
	return chrono::duration_cast<chrono::microseconds>(end - start).count();
}
