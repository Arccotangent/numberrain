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

#include "Modulus.h"

using namespace std;

Logger Modulus::log = Logger("Modulus");

long Modulus::eval() {
	auto start = chrono::system_clock::now();
	
	Integer modulus = arguments[0];
	log.i("Evaluating modulus, starting from %s.", fmt(modulus).c_str());
	
	for (size_t i = 1; i < arguments.size(); i++) {
		Integer arg = arguments[i];
		Integer newMod = modulus % arg;
		log.r("Modulus is currently %s, after argument %i (%s): %s mod %s = %s", fmt(modulus).c_str(), i,
		      fmt(arg).c_str(), fmt(modulus).c_str(), fmt(arg).c_str(), fmt(newMod).c_str());
		modulus = newMod;
	}
	
	auto end = chrono::system_clock::now();
	
	result = modulus;
	
	return chrono::duration_cast<chrono::microseconds>(end - start).count();
}
