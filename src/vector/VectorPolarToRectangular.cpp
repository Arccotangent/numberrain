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

#include "VectorPolarToRectangular.h"

using namespace std;

long VectorPolarToRectangular::eval() {
	auto start = chrono::system_clock::now();
	
	Real angle = arguments[0].x;
	Real magnitude = arguments[1].x;
	
	Vector vec;
	
	Real usedAngle = angle;
	
	while (usedAngle > 180) {
		usedAngle -= 180;
	}
	
	Real radians = usedAngle * (pi / 180);
	
	vec.x = magnitude * boost::multiprecision::cos(radians);
	vec.y = magnitude * boost::multiprecision::sin(radians);
	
	if (angle >= 90 && angle <= 270) {
		vec.x = -vec.x;
	}
	
	if (angle >= 180 && angle <= 360) {
		vec.y = -vec.y;
	}
	
	cout << "Vector x = " << fmt(magnitude) << " * cos(" << fmt(angle) << ") = " << fmt(vec.x) << endl;
	cout << "Vector y = " << fmt(magnitude) << " * sin(" << fmt(angle) << ") = " << fmt(vec.y) << endl;
	
	auto end = chrono::system_clock::now();
	
	result = vec;
	
	return chrono::duration_cast<chrono::microseconds>(end - start).count();
}
