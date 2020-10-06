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
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <boost/regex.h>

typedef boost::multiprecision::number<boost::multiprecision::gmp_int> Integer;
typedef boost::multiprecision::number<boost::multiprecision::gmp_float<0>> Real;
typedef std::vector<std::string> StringArray;

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

static StringArray parseArray(const std::string &value) {
	if (value[0] != '[' || value[value.length() - 1] != ']') {
		throw std::runtime_error("invalid array notation");
	}
	
	std::string newVal = value;
	std::string charsToRemove = "[]";
	newVal.erase(std::remove_if(newVal.begin(), newVal.end(), [charsToRemove](char ch) {
		return charsToRemove.find(ch) != std::string::npos;
	}), newVal.end());
	
	if (newVal.empty()) {
		std::cout << "[debug] array newVal is empty" << std::endl;
		return StringArray();
	}
	
	std::vector<std::string> elements;
	boost::algorithm::split(elements, newVal, boost::algorithm::is_any_of(","));
	
	StringArray arr;
	
	for (auto &elem : elements) {
		while (!elem.empty() && elem[0] == ' ') { //remove leading spaces in elements other than the first
			elem = elem.substr(1, elem.length() - 1);
		}
		
		if (elem.empty()) {
			throw std::runtime_error("empty array element");
		}
		
		arr.emplace_back(elem);
	}
	
	return arr;
}

static Vector parseVector(const std::string &value) {
	std::vector<std::string> parts;
	
	if (boost::algorithm::contains(value, "i")) {
		std::vector<std::string> parts2;
		boost::algorithm::split_regex(parts2, value, boost::regex("\\s"));
		
		bool negative = false;
		
		std::stringstream ss1;
		for (int i = 0; i < parts2.size(); i++) {
			if (!boost::regex_search(parts2[i], boost::regex("[0-9]+"))) {
				negative = parts2[i].find('-') != std::string::npos;
				continue;
			}
			
			if (negative)
				ss1 << "-";
			ss1 << parts2[i];
			if (i < parts2.size() - 1)
				ss1 << ",";
		}
		
		std::string newArg = ss1.str();
		std::string charsToRemove = "ijk ";
		
		newArg.erase(remove_if(newArg.begin(), newArg.end(), [charsToRemove](char ch) {
			return charsToRemove.find(ch) != std::string::npos;
		}), newArg.end());
		
		boost::algorithm::split(parts, newArg, boost::algorithm::is_any_of(","));
	} else {
		boost::algorithm::split(parts, value, boost::algorithm::is_any_of(","));
	}
	
	Real x = Real(parts[0]);
	Real y = parts.size() >= 2 ? Real(parts[1]) : 0.0;
	Real z = parts.size() >= 3 ? Real(parts[2]) : 0.0;
	
	return Vector(x, y, z);
}

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

static std::string fmt(const StringArray &arr) {
	if (arr.empty())
		return "[ ]";
	
	std::stringstream ss;
	
	ss << "[";
	
	for (size_t i = 0; i < arr.size(); i++) {
		ss << arr[i];
		
		if (i < arr.size() - 1)
			ss << ", ";
	}
	
	ss << "]";
	
	return ss.str();
}

#endif //NUMBERRAIN_STRUCTURES_H
