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

long Modulus::eval() {
	auto start = chrono::system_clock::now();
	
	Integer modulus = arguments[0];
	cout << "Evaluating modulus, starting from " << fmt(modulus) << "." << endl;
	
	for (size_t i = 1; i < arguments.size(); i++) {
		Integer arg = arguments[i];
		Integer newMod = modulus % arg;
		cout << "Modulus is currently " << fmt(modulus) << ", after argument " << i << " (" << fmt(arg) << "): "
		     << fmt(modulus) << " mod " << fmt(arg) << " = " << fmt(newMod) << endl;
		modulus = newMod;
	}
	
	auto end = chrono::system_clock::now();
	
	result = modulus;
	
	return chrono::duration_cast<chrono::microseconds>(end - start).count();
}
