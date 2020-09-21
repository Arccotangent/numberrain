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

#include "Arccosine.h"

using namespace std;

Logger Arccosine::log = Logger("Arccosine");

long Arccosine::eval() {
	auto start = chrono::system_clock::now();
	
	Real adjacent = arguments[0];
	Real hypotenuse = arguments[1];
	log.i("Evaluating the arccosine of adjacent leg %s and hypotenuse %s", fmt(adjacent).c_str(),
	      fmt(hypotenuse).c_str());
	
	result = boost::multiprecision::acos(adjacent / hypotenuse);
	
	result *= (180 / pi);
	
	auto end = chrono::system_clock::now();
	
	return chrono::duration_cast<chrono::microseconds>(end - start).count();
}