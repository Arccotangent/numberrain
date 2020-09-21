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

#include "GreatestCommonDenominator.h"

using namespace std;

Logger GreatestCommonDenominator::log = Logger("GreatestCommonDenominator");

long GreatestCommonDenominator::eval() {
	auto start = chrono::system_clock::now();
	
	Integer a = arguments[0];
	Integer b = arguments[1];
	log.i("Evaluating greatest common denominator, starting from %s and %s.", fmt(a).c_str(), fmt(b).c_str());
	
	for (size_t i = 1; i < arguments.size(); i++) {
		b = arguments[i];
		Integer newGCD = gcd(a, b);
		log.r("GCD is currently %s, after argument %i (%s): gcd(%s, %s) = %s", fmt(a).c_str(), i, fmt(b).c_str(),
		      fmt(a).c_str(), fmt(b).c_str(), fmt(newGCD).c_str());
		a = newGCD;
	}
	
	auto end = chrono::system_clock::now();
	
	result = a;
	
	return chrono::duration_cast<chrono::microseconds>(end - start).count();
}
