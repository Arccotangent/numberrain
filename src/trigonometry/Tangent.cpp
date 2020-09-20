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

#include "Tangent.h"

using namespace std;

long Tangent::eval() {
	auto start = chrono::system_clock::now();
	
	Real theta = arguments[0];
	cout << "Evaluating the tangent of angle " << fmt(theta) << " degrees." << endl;
	
	Real usedAngle = theta;
	
	while (usedAngle > 180) {
		usedAngle -= 180;
	}
	
	Real radians = usedAngle * (pi / 180);
	
	result = boost::multiprecision::abs(boost::multiprecision::tan(radians));
	
	if ((theta >= 90 && theta <= 180) || (theta >= 270 && theta <= 360)) {
		result = -result;
	}
	
	auto end = chrono::system_clock::now();
	
	return chrono::duration_cast<chrono::microseconds>(end - start).count();
}