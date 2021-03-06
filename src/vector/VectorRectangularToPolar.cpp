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

#include "VectorRectangularToPolar.h"

using namespace std;

Logger VectorRectangularToPolar::log = Logger("VectorRectangularToPolar");

long VectorRectangularToPolar::eval() {
	auto start = chrono::system_clock::now();
	
	Real angle;
	
	if (arguments[0].x == 0) {
		if (arguments[0].y > 0) {
			angle = 90;
		} else if (arguments[0].y < 0) {
			angle = 270;
		} else {
			angle = 0;
		}
	} else {
		angle = boost::multiprecision::atan(arguments[0].y / arguments[0].x);
		angle *= (180 / pi);
	}
	
	/*if (arguments[0].x < 0) {
		angle += 180;
	}
	
	if (arguments[0].x > 0 && arguments[0].y < 0) {
		angle += 360;
	}*/
	
	Real magnitude = boost::multiprecision::hypot(boost::multiprecision::abs(arguments[0].x),
	                                              boost::multiprecision::abs(arguments[0].y));
	
	log.r("Angle = arctan(%s / %s) = %s deg", fmt(arguments[0].y).c_str(), fmt(arguments[0].x).c_str(),
	      fmt(angle).c_str());
	log.r("Magnitude = sqrt((%s)^2 + (%s)^2)", fmt(boost::multiprecision::abs(arguments[0].x)).c_str(),
	      fmt(boost::multiprecision::abs(arguments[0].y)).c_str());
	
	log.r("The answer is returned as a vector.");
	log.r("The format is: angle * i, magnitude * j, 0 * k");
	
	Vector vec(angle, magnitude, 0);
	
	auto end = chrono::system_clock::now();
	
	result = vec;
	
	return chrono::duration_cast<chrono::microseconds>(end - start).count();
}
