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

#include "Factorial.h"

using namespace std;

Logger Factorial::log = Logger("Factorial");

long Factorial::eval() {
	auto start = chrono::system_clock::now();
	
	Integer res = 1;
	log.i("Evaluating %s!", fmt(arguments[0]).c_str());
	
	for (Integer i = 1; i <= arguments[0]; i++) {
		Integer newRes = res * i;
		log.r("Factorial so far is %s - multiplying by %s yields %s", fmt(res).c_str(), fmt(i).c_str(),
		      fmt(res).c_str());
		res = newRes;
	}
	
	log.i("Final factorial result is %s", fmt(res).c_str());
	
	auto end = chrono::system_clock::now();
	
	result = res;
	
	return chrono::duration_cast<chrono::microseconds>(end - start).count();
}
