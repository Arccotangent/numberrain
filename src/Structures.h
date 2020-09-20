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

#ifndef NUMBERRAIN_STRUCTURES_H
#define NUMBERRAIN_STRUCTURES_H

#include <sstream>
#include <boost/multiprecision/gmp.hpp>

typedef boost::multiprecision::number<boost::multiprecision::gmp_int> Integer;
typedef boost::multiprecision::number<boost::multiprecision::gmp_float<0>> Real;

struct Vector;

const Real pi = boost::math::constants::pi<Real>();
const Real e = boost::math::constants::e<Real>();
const Real golden_ratio = boost::math::constants::phi<Real>();
const Real euler_gamma = boost::math::constants::euler<Real>();

static std::string fmt(const Real &real);

static std::string fmt(const Vector &vector);

struct Vector {
	Real x = 0.0;
	Real y = 0.0;
	Real z = 0.0;
	bool scalar = false;
	
	Vector() = default;
	
	Vector(Real x, Real y, Real z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	
	Vector(Real _scalar) {
		this->x = _scalar;
		this->scalar = true;
	}
	
	Vector(const Vector &vec) {
		this->x = vec.x;
		this->y = vec.y;
		this->z = vec.z;
		this->scalar = vec.scalar;
	}
	
	Vector operator+(Vector &other) const {
		Vector nVec;
		
		nVec.x = this->x + other.x;
		nVec.y = this->y + other.y;
		nVec.z = this->z + other.z;
		
		return nVec;
	}
	
	Vector operator-(Vector &other) const {
		Vector nVec;
		
		nVec.x = this->x - other.x;
		nVec.y = this->y - other.y;
		nVec.z = this->z - other.z;
		
		return nVec;
	}
	
	bool operator==(Vector &other) const {
		return this->x == other.x && this->y == other.y && this->z == other.z && this->scalar == other.scalar;
	}
	
	std::string str() const {
		if (scalar) {
			return fmt(x);
		}
		
		std::stringstream ss;
		
		if (x != 0) {
			ss << fmt(x);
			ss << "i";
		}
		
		Real absY = boost::multiprecision::abs(y);
		
		if (y < 0) {
			ss << (ss.str().empty() ? "-" : " - ");
			ss << fmt(absY);
			ss << "j";
		} else if (y > 0) {
			ss << (ss.str().empty() ? "" : " + ");
			ss << fmt(absY);
			ss << "j";
		}
		
		Real absZ = boost::multiprecision::abs(z);
		
		if (z < 0) {
			ss << (ss.str().empty() ? "-" : " - ");
			ss << fmt(absZ);
			ss << "k";
		} else if (z > 0) {
			ss << (ss.str().empty() ? "" : " + ");
			ss << fmt(absZ);
			ss << "k";
		}
		
		if (ss.str().empty()) {
			return "0";
		}
		
		return ss.str();
	}
};

static std::string fmt(const Real &real) {
	std::string str = real.str(boost::multiprecision::mpf_float::default_precision(), std::ios::fixed);
	
	if (str.find('.') != str.npos) {
		int index = str.length() - 1;
		
		while (str[index] == '0' || str[index] == '.') {
			index--;
			
			if (str[index] == '.') {
				index--;
				break;
			}
		}
		
		if (index < str.length() - 1) {
			return str.substr(0, index + 1);
		}
	}
	
	return str;
}

static std::string fmt(const Vector &vec) {
	return vec.str();
}

#endif //NUMBERRAIN_STRUCTURES_H
