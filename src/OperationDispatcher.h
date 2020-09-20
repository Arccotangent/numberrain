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

#ifndef NUMBERRAIN_OPERATIONDISPATCHER_H
#define NUMBERRAIN_OPERATIONDISPATCHER_H

#include <string>
#include <vector>
#include "RealOperation.h"
#include "IntegerOperation.h"
#include "VectorOperation.h"
#include "StringOperation.h"
#include "Structures.h"

enum Oper {
	ADDITION,
	SUBTRACTION,
	MULTIPLICATION,
	DIVISION,
	EXPONENTIATION,
	SQUARE_ROOT,
	FACTORIAL,
	MODULUS,
	GREATEST_COMMON_DENOMINATOR,
	LEAST_COMMON_MULTIPLE,
	
	NATURAL_LOGARITHM,
	BASE_10_LOGARITHM,
	CUSTOM_BASE_LOGARITHM,
	
	SINE,
	COSINE,
	TANGENT,
	ARCSINE,
	ARCCOSINE,
	ARCTANGENT,
	
	VECTOR_ADDITION,
	VECTOR_SUBTRACTION,
	VECTOR_SCALAR_MULTIPLICATION,
	VECTOR_DOT_PRODUCT,
	VECTOR_CROSS_PRODUCT,
	VECTOR_POLAR_TO_RECTANGULAR,
	VECTOR_RECTANGULAR_TO_POLAR,
	
	EXECUTE_SCRIPT,
	
	INVALID_OPER
};

enum ArgType {
	REAL,
	INTEGER,
	VECTOR,
	STRING,
	
	INVALID_ARG_TYPE
};

class OperationDispatcher {
private:
	static std::map<std::string, Oper> opcodes;
	
	std::string operation;
	
	static Oper convert(const std::string &operation);

public:
	explicit OperationDispatcher(const std::string &operation);
	
	bool verify();
	
	bool checkArgCount(size_t argCount);
	
	ArgType getArgType();
	
	RealOperation *getRealOperation(const std::vector<Real> &arguments);
	
	IntegerOperation *getIntegerOperation(const std::vector<Integer> &arguments);
	
	VectorOperation *getVectorOperation(const std::vector<Vector> &arguments);
	
	StringOperation *getStringOperation(const std::vector<std::string> &arguments);
};


#endif //NUMBERRAIN_OPERATIONDISPATCHER_H
