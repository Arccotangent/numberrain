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

#include "OperationDispatcher.h"
#include "ops.h"

using namespace std;

map<string, Oper> OperationDispatcher::opcodes = {
		{"add",    ADDITION},
		{"sub",    SUBTRACTION},
		{"mul",    MULTIPLICATION},
		{"div",    DIVISION},
		{"exp",    EXPONENTIATION},
		{"sqrt",   SQUARE_ROOT},
		{"fct",    FACTORIAL},
		{"mod",    MODULUS},
		{"gcd",    GREATEST_COMMON_DENOMINATOR},
		{"lcm",    LEAST_COMMON_MULTIPLE},
		{"ln",     NATURAL_LOGARITHM},
		{"log10",  BASE_10_LOGARITHM},
		{"logb",   CUSTOM_BASE_LOGARITHM},
		{"sin",    SINE},
		{"cos",    COSINE},
		{"tan",    TANGENT},
		{"arcsin", ARCSINE},
		{"arccos", ARCCOSINE},
		{"arctan", ARCTANGENT},
		{"vadd",   VECTOR_ADDITION},
		{"vsub",   VECTOR_SUBTRACTION},
		{"vsmul",  VECTOR_SCALAR_MULTIPLICATION},
		{"vdot",   VECTOR_DOT_PRODUCT},
		{"vcross", VECTOR_CROSS_PRODUCT},
		{"vptr",   VECTOR_POLAR_TO_RECTANGULAR},
		{"vrtp",   VECTOR_RECTANGULAR_TO_POLAR},
		{"exec",   EXECUTE_SCRIPT}
};

OperationDispatcher::OperationDispatcher(const string &operation) {
	this->operation = operation;
}

Oper OperationDispatcher::convert(const string &operation) {
	if (opcodes.find(operation) == opcodes.end()) {
		return INVALID_OPER;
	}
	
	return opcodes[operation];
}

bool OperationDispatcher::verify() {
	return convert(operation) != INVALID_OPER;
}

bool OperationDispatcher::checkArgCount(size_t argCount) {
	Oper oper = convert(operation);
	
	switch (oper) {
		case ADDITION:
		case SUBTRACTION:
		case MULTIPLICATION:
		case DIVISION:
		case EXPONENTIATION:
		case MODULUS:
		case GREATEST_COMMON_DENOMINATOR:
		case LEAST_COMMON_MULTIPLE:
		case VECTOR_ADDITION:
		case VECTOR_SUBTRACTION:
		case VECTOR_CROSS_PRODUCT:
			return argCount >= 2;
		case SQUARE_ROOT:
		case FACTORIAL:
		case NATURAL_LOGARITHM:
		case BASE_10_LOGARITHM:
		case SINE:
		case COSINE:
		case TANGENT:
		case VECTOR_RECTANGULAR_TO_POLAR:
			return argCount == 1;
		case CUSTOM_BASE_LOGARITHM:
		case ARCSINE:
		case ARCCOSINE:
		case ARCTANGENT:
		case VECTOR_DOT_PRODUCT:
		case VECTOR_SCALAR_MULTIPLICATION:
		case VECTOR_POLAR_TO_RECTANGULAR:
			return argCount == 2;
		case EXECUTE_SCRIPT:
			return argCount >= 1;
		default:
			return false;
	}
}

ArgType OperationDispatcher::getArgType() {
	Oper oper = convert(operation);
	
	switch (oper) {
		case ADDITION:
		case SUBTRACTION:
		case MULTIPLICATION:
		case DIVISION:
		case EXPONENTIATION:
		case SQUARE_ROOT:
		case NATURAL_LOGARITHM:
		case BASE_10_LOGARITHM:
		case CUSTOM_BASE_LOGARITHM:
		case SINE:
		case COSINE:
		case TANGENT:
		case ARCSINE:
		case ARCCOSINE:
		case ARCTANGENT:
			return REAL;
		case FACTORIAL:
		case MODULUS:
		case GREATEST_COMMON_DENOMINATOR:
		case LEAST_COMMON_MULTIPLE:
			return INTEGER;
		case VECTOR_ADDITION:
		case VECTOR_SUBTRACTION:
		case VECTOR_SCALAR_MULTIPLICATION:
		case VECTOR_DOT_PRODUCT:
		case VECTOR_CROSS_PRODUCT:
		case VECTOR_POLAR_TO_RECTANGULAR:
		case VECTOR_RECTANGULAR_TO_POLAR:
			return VECTOR;
		case EXECUTE_SCRIPT:
			return STRING;
		default:
			return INVALID_ARG_TYPE;
	}
}

RealOperation *OperationDispatcher::getRealOperation(const vector<Real> &arguments) {
	Oper oper = convert(operation);
	
	switch (oper) {
		case ADDITION:
			return new Addition(arguments);
		case SUBTRACTION:
			return new Subtraction(arguments);
		case MULTIPLICATION:
			return new Multiplication(arguments);
		case DIVISION:
			return new Division(arguments);
		case EXPONENTIATION:
			return new Exponentiation(arguments);
		case SQUARE_ROOT:
			return new SquareRoot(arguments);
		case NATURAL_LOGARITHM:
			return new NaturalLogarithm(arguments);
		case BASE_10_LOGARITHM:
			return new Base10Logarithm(arguments);
		case CUSTOM_BASE_LOGARITHM:
			return new CustomBaseLogarithm(arguments);
		case SINE:
			return new Sine(arguments);
		case COSINE:
			return new Cosine(arguments);
		case TANGENT:
			return new Tangent(arguments);
		case ARCSINE:
			return new Arcsine(arguments);
		case ARCCOSINE:
			return new Arccosine(arguments);
		case ARCTANGENT:
			return new Arctangent(arguments);
		default:
			return nullptr;
	}
}

IntegerOperation *OperationDispatcher::getIntegerOperation(const vector<Integer> &arguments) {
	Oper oper = convert(operation);
	
	switch (oper) {
		case FACTORIAL:
			return new Factorial(arguments);
		case MODULUS:
			return new Modulus(arguments);
		case GREATEST_COMMON_DENOMINATOR:
			return new GreatestCommonDenominator(arguments);
		case LEAST_COMMON_MULTIPLE:
			return new LeastCommonMultiple(arguments);
		default:
			return nullptr;
	}
}

VectorOperation *OperationDispatcher::getVectorOperation(const vector<Vector> &arguments) {
	Oper oper = convert(operation);
	
	switch (oper) {
		case VECTOR_ADDITION:
			return new VectorAddition(arguments);
		case VECTOR_SUBTRACTION:
			return new VectorSubtraction(arguments);
		case VECTOR_SCALAR_MULTIPLICATION:
			return new VectorScalarMultiplication(arguments);
		case VECTOR_DOT_PRODUCT:
			return new VectorDotProduct(arguments);
		case VECTOR_CROSS_PRODUCT:
			return new VectorCrossProduct(arguments);
		case VECTOR_POLAR_TO_RECTANGULAR:
			return new VectorPolarToRectangular(arguments);
		case VECTOR_RECTANGULAR_TO_POLAR:
			return new VectorRectangularToPolar(arguments);
		default:
			return nullptr;
	}
}

StringOperation *OperationDispatcher::getStringOperation(const vector<string> &arguments) {
	Oper oper = convert(operation);
	
	switch (oper) {
		case EXECUTE_SCRIPT:
			return new ScriptEngine(arguments);
		default:
			return nullptr;
	}
}
