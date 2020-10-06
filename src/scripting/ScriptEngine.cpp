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

#include "ScriptEngine.h"
#include "ScriptReader.h"
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <boost/regex.h>

using namespace std;

map<string, ComparisonOperator> ScriptEngine::comparisonOperators = {
		{"==", EQUAL},
		{"!=", NOT_EQUAL},
		{"<=", LESS_THAN_OR_EQUAL_TO},
		{">=", GREATER_THAN_OR_EQUAL_TO},
		{"<",  LESS_THAN},
		{">",  GREATER_THAN}
};

ComparisonOperator ScriptEngine::getComparisonOperator(const string &oper) {
	if (comparisonOperators.find(oper) == comparisonOperators.end()) {
		return INVALID_COMPARISON_OPERATOR;
	}
	
	return comparisonOperators[oper];
}

bool ScriptEngine::isValidType(const string &value, DataType type) {
	switch (type) {
		case DT_REAL: {
			try {
				auto val = Real(value);
				return true;
			} catch (exception &e) {
				return false;
			}
		}
		case DT_INTEGER: {
			try {
				auto val = Integer(value);
				return true;
			} catch (exception &e) {
				return false;
			}
		}
		case DT_VECTOR: {
			try {
				parseVector(value);
				return true;
			} catch (exception &e) {
				return false;
			}
		}
		case DT_MATRIX: {
			try {
				parseMatrix(value);
				return true;
			} catch (exception &e) {
				return false;
			}
		}
		case DT_ARRAY: {
			try {
				parseArray(value);
				return true;
			} catch (exception &e) {
				return false;
			}
		}
		case DT_STRING:
		case DT_VOID:
			return true;
		default: {
			return false;
		}
	}
}

bool ScriptEngine::isReservedVariable(const string &varName) {
	return reservedVariables.find(varName) != reservedVariables.end() || varName == "result" ||
	       boost::algorithm::starts_with(varName, "arg_");
}

bool ScriptEngine::variableExists(const string &varName) {
	if (boost::algorithm::starts_with(varName, "arg_")) {
		string tentativeIndex = varName.substr(4);
		
		if (variableExists(tentativeIndex)) {
			tentativeIndex = getVariableValue(tentativeIndex);
		}
		
		long argIndex = strtol(tentativeIndex.c_str(), nullptr, 10);
		
		if (argIndex < scriptArgs.size() && argIndex >= 0) {
			return true;
		}
	}
	
	return varName == "result" || variables.find(varName) != variables.end() ||
	       reservedVariables.find(varName) != reservedVariables.end();
}

string ScriptEngine::getVariableValue(const string &varName) {
	if (varName == "result")
		return result;
	
	if (boost::algorithm::starts_with(varName, "arg_")) {
		string tentativeIndex = varName.substr(4);
		
		if (variableExists(tentativeIndex)) {
			tentativeIndex = getVariableValue(tentativeIndex);
		}
		
		long argIndex = strtol(tentativeIndex.c_str(), nullptr, 10);
		
		if (argIndex < scriptArgs.size() && argIndex >= 0) {
			string value = scriptArgs[argIndex];
			//cout << "[debug] argument at index " << argIndex << " is " << value << endl;
			return value;
		}
	}
	
	if (!variableExists(varName)) {
		return "";
	}
	
	if (variables.find(varName) != variables.end()) {
		return variables[varName];
	} else {
		return reservedVariables[varName];
	}
}

bool ScriptEngine::updateVariable(const string &varName, const string &value) {
	if (isReservedVariable(varName)) {
		return false;
	}
	
	variables.erase(varName);
	variables.emplace(varName, value);
	
	return true;
}

void ScriptEngine::executeScriptCommand(const Command &command) {
	ArgList args = command.second;
	
	OperationType type = Script::getOpType(command.first);
	
	switch (type) {
		case REAL_SCR: {
			vector<Real> arguments;
			
			for (auto &argStr : args) {
				Real arg;
				
				if (variableExists(argStr)) {
					arg = Real(getVariableValue(argStr));
				} else {
					arg = Real(argStr);
				}
				
				arguments.emplace_back(arg);
			}
			
			executeRealOperation(command.first, arguments);
			break;
		}
		case INTEGER_SCR: {
			vector<Integer> arguments;
			
			for (auto &argStr : args) {
				Integer arg;
				
				if (variableExists(argStr)) {
					arg = Integer(variables[argStr]);
				} else {
					arg = Integer(argStr);
				}
				
				arguments.emplace_back(arg);
			}
			
			executeIntegerOperation(command.first, arguments);
			break;
		}
		case VECTOR_SCR: {
			vector<Vector> arguments;
			
			for (auto &argStr : args) {
				Vector vec;
				
				vector<string> parts;
				
				if (variableExists(argStr)) {
					vector<string> parts2;
					boost::algorithm::split_regex(parts2, getVariableValue(argStr), boost::regex("\\s"));
					
					bool negative = false;
					
					stringstream ss1;
					for (int i = 0; i < parts2.size(); i++) {
						if (!boost::regex_search(parts2[i], boost::regex("[0-9]+"))) {
							negative = parts2[i].find('-') != string::npos;
							continue;
						}
						
						if (negative)
							ss1 << "-";
						ss1 << parts2[i];
						if (i < parts2.size() - 1)
							ss1 << ",";
					}
					
					string newArg = ss1.str();
					string charsToRemove = "ijk ";
					
					newArg.erase(remove_if(newArg.begin(), newArg.end(), [charsToRemove](char ch) {
						return charsToRemove.find(ch) != string::npos;
					}), newArg.end());
					
					boost::algorithm::split(parts, newArg, boost::algorithm::is_any_of(","));
				} else {
					boost::algorithm::split(parts, argStr, boost::algorithm::is_any_of(","));
				}
				
				Real x = Real(parts[0]);
				Real y = parts.size() >= 2 ? Real(parts[1]) : 0.0;
				Real z = parts.size() >= 3 ? Real(parts[2]) : 0.0;
				
				vec = Vector(x, y, z);
				
				arguments.emplace_back(vec);
			}
			
			executeVectorOperation(command.first, arguments);
			break;
		}
		case MATRIX_SCR: {
			vector<Matrix> arguments;
			
			for (auto &argStr : args) {
				if (!variableExists(argStr)) {
					if (!isValidType(argStr, DT_MATRIX)) {
						cout << "SCRIPT ERROR: invalid matrix" << endl;
						script.invalidate();
						return;
					}
				}
				
				Matrix *matrix = parseMatrix(variableExists(argStr) ? getVariableValue(argStr) : argStr);
				if (matrix == nullptr) {
					cout << "SCRIPT ERROR: error occurred while creating matrix: " << argStr << endl;
					script.invalidate();
					return;
				}
				
				arguments.emplace_back(*matrix);
			}
			
			executeMatrixOperation(command.first, arguments);
			break;
		}
		case ARRAY_SCR: {
			vector<StringArray> arguments;
			
			for (auto &argStr : args) {
				if (!variableExists(argStr)) {
					if (!isValidType(argStr, DT_ARRAY)) {
						cout << "SCRIPT ERROR: invalid array notation or empty array element" << endl;
						script.invalidate();
						return;
					}
				}
				
				arguments.emplace_back(parseArray(variableExists(argStr) ? getVariableValue(argStr) : argStr));
			}
			
			executeArrayOperation(command.first, arguments);
			break;
		}
		case STRING_SCR: {
			vector<string> arguments;
			
			for (auto &argStr : args) {
				//some special cases:
				//ASSIGN is a special case because interpreting variables would make reassignment impossible
				//WHILE is a special case because we don't want the variable to be interpreted - it should be changing on each iteration
				if (variableExists(argStr) && command.first !=
				                              S_ASSIGN && command.first != S_WHILE) {
					if ((argStr[0] == '"') != (argStr[argStr.length() - 1] == '"')) {
						cout << "RUNTIME ERROR (PRINT): Unterminated quotes in word" << endl;
					} else if (argStr[0] == '"' && argStr[argStr.length() - 1] == '"') {
						arguments.emplace_back(argStr.substr(1, argStr.length() - 2));
					} else {
						arguments.emplace_back(getVariableValue(argStr));
					}
				} else {
					if ((argStr[0] == '"') != (argStr[argStr.length() - 1] == '"')) {
						cout << "RUNTIME ERROR (PRINT): Unterminated quotes in word" << endl;
					} else if (argStr[0] == '"' && argStr[argStr.length() - 1] == '"') {
						arguments.emplace_back(argStr.substr(1, argStr.length() - 2));
					} else {
						arguments.emplace_back(argStr);
					}
				}
			}
			
			executeStringOperation(command.first, arguments);
			break;
		}
		case VOID_SCR: {
			executeVoidOperation(command.first);
			break;
		}
		default: {
			cout << "SCRIPT ERROR: encountered invalid operation type - skipping (this is a bug, please report it!)"
			     << endl;
			script.invalidate();
			break;
		}
	}
}

void ScriptEngine::executeRealOperation(ScriptOperation operation, const vector<Real> &args) {
	switch (operation) {
		case S_ADD: {
			auto *op = new Addition(args);
			
			op->eval();
			result = fmt(op->getResult());
			break;
		}
		case S_SUBTRACT: {
			auto *op = new Subtraction(args);
			
			op->eval();
			result = fmt(op->getResult());
			break;
		}
		case S_MULTIPLY: {
			auto *op = new Multiplication(args);
			
			op->eval();
			result = fmt(op->getResult());
			break;
		}
		case S_DIVIDE: {
			auto *op = new Division(args);
			
			op->eval();
			result = fmt(op->getResult());
			break;
		}
		case S_EXPONENT: {
			auto *op = new Exponentiation(args);
			
			op->eval();
			result = fmt(op->getResult());
			break;
		}
		case S_SQRT: {
			auto *op = new SquareRoot(args);
			
			op->eval();
			result = fmt(op->getResult());
			break;
		}
		case S_ABSOLUTE_VALUE: {
			result = fmt(boost::multiprecision::abs(args[0]));
			break;
		}
		case S_LN: {
			auto *op = new NaturalLogarithm(args);
			
			op->eval();
			result = fmt(op->getResult());
			break;
		}
		case S_LOG10: {
			auto *op = new Base10Logarithm(args);
			
			op->eval();
			result = fmt(op->getResult());
			break;
		}
		case S_LOGB: {
			auto *op = new CustomBaseLogarithm(args);
			
			op->eval();
			result = fmt(op->getResult());
			break;
		}
		case S_SINE: {
			auto *op = new Sine(args);
			
			op->eval();
			result = fmt(op->getResult());
			break;
		}
		case S_COSINE: {
			auto *op = new Cosine(args);
			
			op->eval();
			result = fmt(op->getResult());
			break;
		}
		case S_TANGENT: {
			auto *op = new Tangent(args);
			
			op->eval();
			result = fmt(op->getResult());
			break;
		}
		case S_ARCSINE: {
			auto *op = new Arcsine(args);
			
			op->eval();
			result = fmt(op->getResult());
			break;
		}
		case S_ARCCOSINE: {
			auto *op = new Arccosine(args);
			
			op->eval();
			result = fmt(op->getResult());
			break;
		}
		case S_ARCTANGENT: {
			auto *op = new Arctangent(args);
			
			op->eval();
			result = fmt(op->getResult());
			break;
		}
		case S_VECTOR_CONSTRUCT: {
			Vector vec;
			
			vec.x = args[0];
			vec.y = args.size() >= 2 ? args[1] : 0.0;
			vec.z = args.size() >= 3 ? args[2] : 0.0;
			
			result = fmt(vec);
			break;
		}
		case S_FLOOR: {
			result = fmt(boost::multiprecision::floor(args[0]));
			break;
		}
		case S_CEIL: {
			result = fmt(boost::multiprecision::ceil(args[0]));
			break;
		}
		case S_ROUND: {
			result = fmt(boost::multiprecision::round(args[0]));
			break;
		}
		case S_DROUND: {
			Real coeff = boost::multiprecision::pow(Real(10), args[1]);
			Real toRound = args[0] * coeff;
			Real rounded = boost::multiprecision::round(toRound);
			rounded /= coeff;
			
			result = fmt(rounded);
			break;
		}
		default: {
			cout
					<< "SCRIPT ERROR: attempted to execute operation with real numbers, yet it accepts something else (this is a bug, please report it!)"
					<< endl;
			script.invalidate();
			break;
		}
	}
}

void ScriptEngine::executeIntegerOperation(ScriptOperation operation, const vector<Integer> &args) {
	switch (operation) {
		case S_FACTORIAL: {
			auto *op = new Factorial(args);
			
			op->eval();
			result = fmt(op->getResult());
			break;
		}
		case S_MODULUS: {
			auto *op = new Modulus(args);
			
			op->eval();
			result = fmt(op->getResult());
			break;
		}
		case S_GREATEST_COMMON_DENOMINATOR: {
			auto *op = new GreatestCommonDenominator(args);
			
			op->eval();
			result = fmt(op->getResult());
			break;
		}
		case S_LEAST_COMMON_MULTIPLE: {
			auto *op = new LeastCommonMultiple(args);
			
			op->eval();
			result = fmt(op->getResult());
			break;
		}
		case S_MATRIX_IDENTITY_GENERATOR: {
			Integer size = args[0];
			
			if (size < 1) {
				cout << "SCRIPT ERROR: attempted to generate an identity matrix smaller than 1x1" << endl;
				script.invalidate();
				break;
			}
			
			RealMatrix mtxRaw;
			
			for (Integer y = 0; y < size; y++) {
				vector<Real> row;
				for (Integer x = 0; x < size; x++) {
					row.emplace_back(x == y ? 1 : 0);
				}
				mtxRaw.emplace_back(row);
			}
			
			Matrix *mtx = Matrix::createMatrix(mtxRaw, false);
			if (mtx == nullptr) {
				cout << "SCRIPT ERROR: error occurred while creating identity matrix" << endl;
				script.invalidate();
				break;
			}
			
			result = fmt(*mtx);
			break;
		}
		default: {
			cout
					<< "SCRIPT ERROR: attempted to execute operation with integers, yet it accepts something else (this is a bug, please report it!)"
					<< endl;
			script.invalidate();
			break;
		}
	}
}

void ScriptEngine::executeVectorOperation(ScriptOperation operation, const vector<Vector> &args) {
	switch (operation) {
		case S_VECTOR_ADD: {
			auto *op = new VectorAddition(args);
			
			op->eval();
			result = fmt(op->getResult());
			break;
		}
		case S_VECTOR_SUBTRACT: {
			auto *op = new VectorSubtraction(args);
			
			op->eval();
			result = fmt(op->getResult());
			break;
		}
		case S_VECTOR_SCALAR_MULTIPLY: {
			auto *op = new VectorScalarMultiplication(args);
			
			op->eval();
			result = fmt(op->getResult());
			break;
		}
		case S_VECTOR_DOT_PRODUCT: {
			auto *op = new VectorDotProduct(args);
			
			op->eval();
			result = fmt(op->getResult());
			break;
		}
		case S_VECTOR_CROSS_PRODUCT: {
			auto *op = new VectorCrossProduct(args);
			
			op->eval();
			result = fmt(op->getResult());
			break;
		}
		case S_VECTOR_POLAR_TO_RECTANGULAR: {
			auto *op = new VectorPolarToRectangular(args);
			
			op->eval();
			result = fmt(op->getResult());
			break;
		}
		case S_VECTOR_RECTANGULAR_TO_POLAR: {
			auto *op = new VectorRectangularToPolar(args);
			
			op->eval();
			result = fmt(op->getResult());
			break;
		}
		case S_VECTOR_GET_X: {
			result = fmt(args[0].x);
			break;
		}
		case S_VECTOR_GET_Y: {
			result = fmt(args[0].y);
			break;
		}
		case S_VECTOR_GET_Z: {
			result = fmt(args[0].z);
			break;
		}
		default: {
			cout
					<< "SCRIPT ERROR: attempted to execute operation with vectors, yet it accepts something else (this is a bug, please report it!)"
					<< endl;
			script.invalidate();
			break;
		}
	}
}

void ScriptEngine::executeMatrixOperation(ScriptOperation operation, const vector<Matrix> &args) {
	switch (operation) {
		case S_MATRIX_X_QUERY: {
			result = to_string(args[0].getMatrixDimensions().first);
			break;
		}
		case S_MATRIX_Y_QUERY: {
			result = to_string(args[0].getMatrixDimensions().second);
			break;
		}
		case S_MATRIX_ADDITION: {
			size_t x = args[0].getMatrixDimensions().first;
			size_t y = args[0].getMatrixDimensions().second;
			
			for (size_t i = 0; i < args.size(); i++) {
				size_t tx = args[i].getMatrixDimensions().first;
				size_t ty = args[i].getMatrixDimensions().second;
				if (tx != x || ty != y) {
					cout << "SCRIPT ERROR: incompatible matrix dimensions for addition at matrix argument " << i
					     << " - expected " << x << "x" << y << ", got " << tx << "x" << ty << endl;
					script.invalidate();
					return;
				}
			}
			
			auto *op = new MatrixAddition(args);
			
			op->eval();
			result = fmt(op->getResult());
			break;
		}
		case S_MATRIX_SUBTRACTION: {
			size_t x = args[0].getMatrixDimensions().first;
			size_t y = args[0].getMatrixDimensions().second;
			
			for (size_t i = 0; i < args.size(); i++) {
				size_t tx = args[i].getMatrixDimensions().first;
				size_t ty = args[i].getMatrixDimensions().second;
				if (tx != x || ty != y) {
					cout << "SCRIPT ERROR: incompatible matrix dimensions for subtraction at matrix argument " << i
					     << " - expected " << x << "x" << y << ", got " << tx << "x" << ty << endl;
					script.invalidate();
					return;
				}
			}
			
			auto *op = new MatrixSubtraction(args);
			
			op->eval();
			result = fmt(op->getResult());
			break;
		}
		case S_MATRIX_MULTIPLICATION: {
			size_t aX = args[0].getMatrixDimensions().first;
			size_t aY = args[0].getMatrixDimensions().second;
			size_t bX = args[1].getMatrixDimensions().first;
			size_t bY = args[1].getMatrixDimensions().second;
			
			//cout << "[debug] matrix 1 = " << endl << fmt(args[0]) << endl;
			//cout << "[debug] matrix 2 = " << endl << fmt(args[1]) << endl;
			
			if (aY != bX) {
				cout
						<< "SCRIPT ERROR: incompatible matrix dimensions for multiplication (first 2 matrices) - first matrix Y ("
						<< aY << ") must equal second matrix X (" << bX << ")" << endl;
				script.invalidate();
				break;
			}
			
			size_t newX = aX;
			size_t newY = bY;
			
			for (size_t i = 2; i < args.size(); i++) {
				size_t argX = args[i].getMatrixDimensions().first;
				size_t argY = args[i].getMatrixDimensions().second;
				
				if (newY != argX) {
					cout << "SCRIPT ERROR: incompatible matrix dimensions for multiplication at matrix argument " << i
					     << " - inner dimensions are unequal - first matrix Y = " << newY << ", second matrix X = "
					     << argX << endl;
					script.invalidate();
					return;
				}
				
				newY = argY;
			}
			
			auto *op = new MatrixMultiplication(args);
			
			op->eval();
			result = fmt(op->getResult());
			break;
		}
		case S_MATRIX_DETERMINANT: {
			if (args[0].getMatrixDimensions().first != args[0].getMatrixDimensions().second) {
				cout << "SCRIPT ERROR: attempted to take the determinant of a non-square matrix" << endl;
				script.invalidate();
				break;
			}
			
			auto *op = new MatrixDeterminant(args);
			
			op->eval();
			result = fmt(op->getResult());
			break;
		}
		default: {
			cout
					<< "SCRIPT ERROR: attempted to execute operation with matrices, yet it accepts something else (this is a bug, please report it!)"
					<< endl;
			script.invalidate();
			break;
		}
	}
}

void ScriptEngine::executeArrayOperation(ScriptOperation operation, const vector<StringArray> &args) {
	switch (operation) {
		case S_ARRAY_LENGTH_QUERY: {
			result = to_string(args[0].size());
			break;
		}
		default: {
			cout
					<< "SCRIPT ERROR: attempted to execute operation with arrays, yet it accepts something else (this is a bug, please report it!)"
					<< endl;
			script.invalidate();
			break;
		}
	}
}

void ScriptEngine::executeStringOperation(ScriptOperation operation, const vector<string> &args) {
	switch (operation) {
		case S_PRINT: {
			for (auto &arg : args) {
				cout << arg;
			}
			cout << endl;
			break;
		}
		case S_ASSIGN: {
			string varName = args[0];
			boost::regex digits("^[0-9]");
			
			if (isReservedVariable(varName)) {
				cout << "SCRIPT ERROR: variable name '" << varName << "' is a reserved variable" << endl;
				script.invalidate();
				return;
			}
			
			if (boost::regex_match(varName, digits)) {
				cout << "SCRIPT ERROR: variable names cannot start with a number" << endl;
				script.invalidate();
				return;
			}
			
			if (boost::contains(varName, "/")) {
				cout << "SCRIPT ERROR: variable names cannot contain slashes" << endl;
				script.invalidate();
				return;
			}
			
			updateVariable(varName, result);
			
			//cout << "[debug] updated variable " << varName << " with value " << result << " from result register" << endl;
			break;
		}
		case S_FOR: {
			string loopVarName = args[0];
			vector<Integer> loopSpecs; //0 = loopVarValue, 1 = loopEndValue, 2 = loopStep
			
			if (reservedVariables.find(loopVarName) != reservedVariables.end()) {
				cout << "SCRIPT ERROR: FOR loop attempted to redefine a reserved variable ('" << loopVarName << "')"
				     << endl;
				script.invalidate();
				return;
			}
			
			int initialPos = script.getPosition();
			int levels = 1;
			
			Command command;
			while (levels > 0) {
				if (!script.isValid()) {
					cout
							<< "SCRIPT ERROR: end of FOR loop not marked by ENDFOR - check if there are enough ENDFORs if using nested FOR loops"
							<< endl;
					script.invalidate();
					return;
				}
				
				command = script.nextCommand();
				
				if (command.first == S_FOR) {
					levels++;
					//cout << "[debug] entered nested for - levels = " << levels << endl;
				} else if (command.first == S_ENDFOR) {
					levels--;
					//cout << "[debug] exited for - levels = " << levels << endl;
				}
			}
			
			int endForPos = script.getPosition();
			
			loopEndStack.emplace_front(endForPos);
			script.jump(initialPos);
			
			for (int i = 1; i < 4; i++) {
				if (variableExists(args[i])) {
					loopSpecs.emplace_back(Integer(getVariableValue(args[i])));
				} else {
					loopSpecs.emplace_back(args[i]);
				}
			}
			
			bool loopVarPreExisting = variables.find(loopVarName) != variables.end();
			string loopVarPreValue;
			if (loopVarPreExisting) {
				loopVarPreValue = variables[loopVarName];
			}
			
			while ((loopSpecs[2] > 0 && loopSpecs[0] < loopSpecs[1]) ||
			       (loopSpecs[2] < 0 && loopSpecs[0] > loopSpecs[1]) ||
			       loopSpecs[2] == 0) {
				if (!script.isValid()) {
					cout
							<< "SCRIPT ERROR: script invalidated before end of FOR loop (catch 1) - there are likely other errors - check above"
							<< endl;
					script.invalidate();
					return;
				}
				
				updateVariable(loopVarName, fmt(loopSpecs[0]));
				
				command = script.nextCommand();
				
				if (command.first == S_ENDFOR) {
					loopSpecs[0] += loopSpecs[2];
					script.jump(initialPos);
					continue;
				}
				
				executeScriptCommand(command);
				
				if (cont) {
					loopSpecs[0] += loopSpecs[2];
					script.jump(initialPos);
					cont = false;
					continue;
				}
				
				if (ignore)
					break;
			}
			
			variables.erase(loopVarName);
			
			if (loopVarPreExisting) {
				variables[loopVarName] = loopVarPreValue;
			}
			
			if (ignore)
				break;
			
			script.jump(loopEndStack.front());
			loopEndStack.pop_front();
			break;
		}
		case S_WHILE: {
			int initialPos = script.getPosition();
			int levels = 1;
			
			Command command;
			while (levels > 0) {
				if (!script.isValid()) {
					cout
							<< "SCRIPT ERROR: end of WHILE loop not marked by ENDWHILE - check if there are enough ENDWHILEs if using nested WHILE loops"
							<< endl;
					script.invalidate();
					return;
				}
				
				command = script.nextCommand();
				
				if (command.first == S_WHILE) {
					levels++;
					//cout << "[debug] entered nested while - levels = " << levels << endl;
				} else if (command.first == S_ENDWHILE) {
					levels--;
					//cout << "[debug] exited while - levels = " << levels << endl;
				}
			}
			
			int endWhilePos = script.getPosition();
			
			loopEndStack.emplace_front(endWhilePos);
			script.jump(initialPos);
			
			ComparisonOperator oper = getComparisonOperator(args[1]);
			if (oper == INVALID_COMPARISON_OPERATOR) {
				cout << "SCRIPT ERROR: invalid comparison operator (while, catch 1): " << args[1] << endl;
				script.invalidate();
				return;
			}
			
			bool keepGoing = true;
			command = script.nextCommand();
			
			Real a;
			Real b;
			
			while (keepGoing) {
				if (!script.isValid()) {
					cout
							<< "SCRIPT ERROR: script invalidated before end of WHILE loop (catch 1) - there are likely other errors - check above"
							<< endl;
					script.invalidate();
					return;
				}
				
				if (variableExists(args[0])) {
					a = Real(getVariableValue(args[0]));
				} else {
					a = Real(args[0]);
				}
				
				if (variableExists(args[2])) {
					b = Real(getVariableValue(args[2]));
				} else {
					b = Real(args[2]);
				}
				
				//cout << "[debug] a = " << fmt(a) << endl;
				//cout << "[debug] b = " << fmt(b) << endl;
				
				switch (oper) {
					case EQUAL: {
						keepGoing = a == b;
						break;
					}
					case NOT_EQUAL: {
						keepGoing = a != b;
						break;
					}
					case LESS_THAN: {
						keepGoing = a < b;
						break;
					}
					case GREATER_THAN: {
						keepGoing = a > b;
						break;
					}
					case LESS_THAN_OR_EQUAL_TO: {
						keepGoing = a <= b;
						break;
					}
					case GREATER_THAN_OR_EQUAL_TO: {
						keepGoing = a >= b;
						break;
					}
					default: {
						cout << "SCRIPT ERROR: invalid comparison operator (while, catch 2)" << endl;
						script.invalidate();
						return;
					}
				}
				
				if (ignore)
					break;
				
				while (command.first != S_ENDWHILE) {
					if (!script.isValid()) {
						cout
								<< "SCRIPT ERROR: script invalidated before end of WHILE loop (catch 2) - there are likely other errors - check above"
								<< endl;
						script.invalidate();
						return;
					}
					
					executeScriptCommand(command);
					
					if (cont) {
						script.jump(initialPos);
						command = script.nextCommand();
						cont = false;
						continue;
					}
					
					if (ignore)
						break;
					
					command = script.nextCommand();
				}
				
				if (ignore)
					break;
				
				script.jump(initialPos);
				command = script.nextCommand();
			}
			
			if (ignore)
				break;
			
			script.jump(loopEndStack.front());
			loopEndStack.pop_front();
			break;
		}
		case S_IF: {
			int initialPos = script.getPosition();
			int endIfPos;
			
			int levels = 1;
			
			Command command = script.nextCommand();
			while (levels > 0) {
				if (!script.isValid()) {
					cout
							<< "SCRIPT ERROR: end of IF block not marked by ENDIF - check if there are enough ENDIFs if using nested IF blocks"
							<< endl;
					script.invalidate();
					return;
				}
				
				command = script.nextCommand();
				
				if (command.first == S_IF) {
					levels++;
					//cout << "[debug] entered nested if - levels = " << levels << endl;
				} else if (command.first == S_ENDIF) {
					levels--;
					//cout << "[debug] exited if - levels = " << levels << endl;
				}
			}
			
			endIfPos = script.getPosition();
			script.jump(initialPos);
			
			ComparisonOperator oper = getComparisonOperator(args[1]);
			if (oper == INVALID_COMPARISON_OPERATOR) {
				cout << "SCRIPT ERROR: invalid comparison operator (if, catch 1): " << args[1] << endl;
				script.invalidate();
				return;
			}
			
			Real a;
			Real b;
			
			if (variableExists(args[0])) {
				a = Real(getVariableValue(args[0]));
			} else {
				a = Real(args[0]);
			}
			
			if (variableExists(args[2])) {
				b = Real(getVariableValue(args[2]));
			} else {
				b = Real(args[2]);
			}
			
			command = script.nextCommand();
			bool conditionMet = false;
			
			while (command.first != S_ENDIF && !conditionMet) {
				if (!script.isValid()) {
					cout
							<< "SCRIPT ERROR: script invalidated before end of IF block (catch 1) - there are likely other errors - check above"
							<< endl;
					script.invalidate();
					return;
				}
				
				bool goToNextCondition;
				int condPos = script.getPosition();
				
				if (command.first == S_ELSE) {
					goToNextCondition = false;
				} else {
					switch (oper) {
						case EQUAL: {
							goToNextCondition = a != b;
							break;
						}
						case NOT_EQUAL: {
							goToNextCondition = a == b;
							break;
						}
						case LESS_THAN: {
							goToNextCondition = a >= b;
							break;
						}
						case GREATER_THAN: {
							goToNextCondition = a <= b;
							break;
						}
						case LESS_THAN_OR_EQUAL_TO: {
							goToNextCondition = a > b;
							break;
						}
						case GREATER_THAN_OR_EQUAL_TO: {
							goToNextCondition = a < b;
							break;
						}
						default: {
							cout << "SCRIPT ERROR: invalid comparison operator (if, catch 2)" << endl;
							script.invalidate();
							return;
						}
					}
				}
				
				if (goToNextCondition) {
					command = script.nextCommand();
					
					while (command.first != S_ELSEIF && command.first != S_ELSE && command.first != S_ENDIF) {
						if (!script.isValid()) {
							cout
									<< "SCRIPT ERROR: script invalidated before end of IF block (catch 2) - there are likely other errors - check above"
									<< endl;
							script.invalidate();
							return;
						}
						
						command = script.nextCommand();
						condPos = script.getPosition() - 1;
					}
					
					if (command.first == S_ELSEIF) {
						oper = getComparisonOperator(command.second[1]);
						if (oper == INVALID_COMPARISON_OPERATOR) {
							cout << "SCRIPT ERROR: invalid comparison operator: " << command.second[1] << endl;
							script.invalidate();
							return;
						}
						
						if (variableExists(command.second[0])) {
							a = Real(getVariableValue(command.second[0]));
						} else {
							a = Real(command.second[0]);
						}
						
						if (variableExists(command.second[2])) {
							b = Real(getVariableValue(command.second[2]));
						} else {
							b = Real(command.second[2]);
						}
					}
					
					script.jump(condPos);
					if (endIfPos - condPos >= 2) {
						command = script.nextCommand();
					}
					
					continue;
				}
				
				if (command.first != S_IF && command.first != S_ELSEIF && command.first != S_ELSE) {
					condPos--;
				}
				
				script.jump(condPos);
				command = script.nextCommand();
				conditionMet = true;
				
				while (command.first != S_ELSEIF && command.first != S_ELSE && command.first != S_ENDIF &&
				       script.isValid()) {
					executeScriptCommand(command);
					
					if (ignore || cont)
						break;
					
					command = script.nextCommand();
				}
			}
			
			if (ignore)
				break;
			
			script.jump(endIfPos);
			break;
		}
		case S_ELSEIF: {
			cout << "SCRIPT ERROR: floating ELSEIF statement" << endl;
			script.invalidate();
			break;
		}
		case S_FUNCTION: {
			script.jump(script.getFunction(args[1]).endPosition);
			break;
		}
		case S_CALL: {
			string functionName = args[0];
			if (!script.functionExists(functionName)) {
				cout << "SCRIPT ERROR: function '" << functionName << "' is undefined" << endl;
				script.invalidate();
				break;
			}
			
			int origPos = script.getPosition();
			Function func = script.getFunction(functionName);
			
			if (func.startPosition < 0) {
				cout << "SCRIPT ERROR: invalid function " << functionName << endl;
				script.invalidate();
				break;
			}
			
			if (args.size() - 1 != func.args.size()) {
				cout << "SCRIPT ERROR: wrong number of arguments passed to function " << functionName << " - expected "
				     << func.args.size() << ", received " << args.size() - 1 << endl;
				script.invalidate();
				break;
			}
			
			map<string, string> variableBackup;
			
			for (int i = 1; i < args.size(); i++) {
				pair<string, DataType> arg = func.args[i - 1];
				
				if (isReservedVariable(arg.first)) {
					cout << "SCRIPT ERROR: argument '" << arg.first << "' attempts to overwrite a reserved variable"
					     << endl;
					script.invalidate();
					return;
				}
				
				if (!isValidType(args[i], arg.second)) {
					cout << "SCRIPT ERROR: argument " << i - 1 << " passed to function " << functionName
					     << " is the wrong data type" << endl;
					script.invalidate();
					return;
				}
				
				if (variableExists(arg.first)) {
					variableBackup.emplace(arg.first, getVariableValue(arg.first));
				}
				
				updateVariable(arg.first, args[i]);
			}
			
			script.jump(func.startPosition + 1);
			Command cmd = script.nextCommand();
			
			while (cmd.first != S_ENDFUNC) {
				if (cmd.first == S_RETURN) {
					if (func.returnType == DT_VOID) {
						break;
					} else {
						if (variableExists(cmd.second[0])) {
							result = getVariableValue(cmd.second[0]);
						} else {
							result = cmd.second[0];
						}
					}
					
					if (!isValidType(result, func.returnType)) {
						cout << "SCRIPT ERROR: function '" << functionName << "' returned the incorrect data type"
						     << endl;
					}
					break;
				}
				
				executeScriptCommand(cmd);
				cmd = script.nextCommand();
			}
			
			for (const auto &var : func.args) {
				if (variableBackup.find(var.first) != variableBackup.end()) {
					updateVariable(var.first, variableBackup[var.first]);
				} else {
					variables.erase(var.first);
				}
			}
			
			script.jump(origPos);
			break;
		}
		case S_MATRIX_CONSTRUCT: {
			Matrix *mtx = nullptr;
			
			if (args[0].find('[') == string::npos) {
				if (!variableExists(args[0])) {
					if (!isValidType(args[0], DT_MATRIX)) {
						cout << "SCRIPT ERROR: invalid matrix" << endl;
						script.invalidate();
						return;
					}
				}
				
				mtx = parseMatrix(variableExists(args[0]) ? getVariableValue(args[0]) : args[0]);
			} else {
				RealMatrix mtxRaw;
				mtxRaw.reserve(args.size());
				
				for (auto &arg : args) {
					vector<Real> row;
					
					if (!variableExists(arg)) {
						if (!isValidType(arg, DT_ARRAY)) {
							cout << "SCRIPT ERROR: invalid array for matrix construction: " << arg << endl;
							script.invalidate();
							return;
						}
					}
					
					StringArray arr = parseArray(variableExists(arg) ? getVariableValue(arg) : arg);
					
					for (auto &numStr : arr) {
						string num = variableExists(numStr) ? getVariableValue(numStr) : numStr;
						if (!isValidType(num, DT_REAL)) {
							cout << "SCRIPT ERROR: attempted to pass in non-real number argument '" << num
							     << "' to matrix construction." << endl;
							script.invalidate();
							return;
						}
						
						row.emplace_back(Real(num));
					}
					
					mtxRaw.emplace_back(row);
				}
				
				mtx = Matrix::createMatrix(mtxRaw, false);
			}
			
			if (mtx == nullptr) {
				cout << "SCRIPT ERROR: error occurred while constructing matrix" << endl;
				script.invalidate();
				break;
			}
			
			result = fmt(*mtx);
			break;
		}
		case S_ARRAY_CONSTRUCT: {
			StringArray arr;
			
			for (const auto &arg : args) {
				if (arg.empty())
					continue;
				
				if (isValidType(arg, DT_ARRAY)) {
					cout << "SCRIPT ERROR: attempted to create nested array" << endl;
					script.invalidate();
					return;
				}
				
				string argFormatted;
				
				if (isValidType(arg, DT_VECTOR)) {
					Vector vec = parseVector(arg);
					
					if (vec.y == 0 && vec.z == 0) {
						argFormatted = arg;
					} else {
						argFormatted = fmt(vec);
					}
				} else if (isValidType(arg, DT_MATRIX)) {
					argFormatted = fmt(*parseMatrix(arg));
				} else {
					argFormatted = arg;
				}
				
				arr.emplace_back(argFormatted);
			}
			
			result = fmt(arr);
			break;
		}
		case S_ARRAY_EXTRACT: {
			StringArray arr = parseArray(args[0]);
			size_t index = strtoul(args[1].c_str(), nullptr, 10);
			
			if (index >= arr.size()) {
				cout << "SCRIPT ERROR: array extraction index out of bounds" << endl;
				script.invalidate();
				break;
			}
			
			result = arr[index];
			break;
		}
		case S_ARRAY_PREPEND: {
			StringArray arr = parseArray(args[0]);
			StringArray newArr;
			
			for (size_t i = 1; i < args.size(); i++) {
				if (args[i].empty())
					continue;
				
				string argFormatted;
				
				if (isValidType(args[i], DT_VECTOR)) {
					Vector vec = parseVector(args[i]);
					
					if (vec.y == 0 && vec.z == 0) {
						argFormatted = args[i];
					} else {
						argFormatted = fmt(vec);
					}
				} else if (isValidType(args[i], DT_MATRIX)) {
					argFormatted = fmt(*parseMatrix(args[i]));
				} else {
					argFormatted = args[i];
				}
				
				newArr.emplace_back(argFormatted);
			}
			
			for (auto &elem : arr) {
				newArr.emplace_back(elem);
			}
			
			result = fmt(newArr);
			break;
		}
		case S_ARRAY_APPEND: {
			StringArray arr = parseArray(args[0]);
			StringArray newArr;
			
			for (auto &elem : arr) {
				newArr.emplace_back(elem);
			}
			
			for (size_t i = 1; i < args.size(); i++) {
				if (args[i].empty())
					continue;
				
				string argFormatted;
				
				if (isValidType(args[i], DT_VECTOR)) {
					Vector vec = parseVector(args[i]);
					
					if (vec.y == 0 && vec.z == 0) {
						argFormatted = args[i];
					} else {
						argFormatted = fmt(vec);
					}
				} else if (isValidType(args[i], DT_MATRIX)) {
					argFormatted = fmt(*parseMatrix(args[i]));
				} else {
					argFormatted = args[i];
				}
				
				newArr.emplace_back(argFormatted);
			}
			
			result = fmt(newArr);
			break;
		}
		case S_ARRAY_DELETE: {
			StringArray arr = parseArray(args[0]);
			StringArray newArr;
			
			if (args.size() == 2) {
				long element = strtol(args[1].c_str(), nullptr, 10);
				if (element < 0) {
					result = fmt(newArr);
					break;
				}
				
				if (element >= arr.size()) {
					cout << "SCRIPT ERROR: array deletion index out of bounds" << endl;
					script.invalidate();
					break;
				}
				
				newArr = arr;
				newArr.erase(newArr.begin() + element);
			} else {
				long a = strtol(args[1].c_str(), nullptr, 10);
				long b = strtol(args[1].c_str(), nullptr, 10);
				
				if (a < 0 && b < 0) {
					result = fmt(newArr);
					break;
				}
				
				if (b >= arr.size()) {
					cout << "SCRIPT ERROR: maximum array deletion index out of bounds" << endl;
					script.invalidate();
					break;
				}
				
				newArr = arr;
				newArr.erase(newArr.begin() + a, newArr.begin() + b);
			}
			
			result = fmt(newArr);
			break;
		}
		case S_NOP: {
			result = args[0];
			break;
		}
		default: {
			cout
					<< "SCRIPT ERROR: attempted to execute operation with strings, yet it accepts something else (this is a bug, please report it!)"
					<< endl;
			script.invalidate();
			break;
		}
	}
}

void ScriptEngine::executeVoidOperation(ScriptOperation operation) {
	switch (operation) {
		case BEGIN_EXEC: {
			cout << "Script execution has begun." << endl;
			break;
		}
		case S_BREAK: {
			if (loopEndStack.empty()) {
				cout << "SCRIPT ERROR: Floating BREAK statement." << endl;
				script.invalidate();
				break;
			}
			
			ignore = true;
			script.jump(loopEndStack.front());
			loopEndStack.pop_front();
			break;
		}
		case S_CONTINUE: {
			if (loopEndStack.empty()) {
				cout << "SCRIPT ERROR: Floating CONTINUE statement." << endl;
				script.invalidate();
				break;
			}
			
			cont = true;
			break;
		}
		case S_ENDFOR: {
			//should never be executed - mainly for debugging
			cout << "For loop ended." << endl;
			break;
		}
		case S_ENDWHILE: {
			//should never be executed - mainly for debugging
			cout << "While loop ended." << endl;
			break;
		}
		case S_ELSE: {
			cout << "SCRIPT ERROR: Floating ELSE statement." << endl;
			script.invalidate();
			break;
		}
		case S_ENDIF: {
			break;
		}
		case S_MUTE: {
			GlobalVars::getInstance()->setLogToConsole(false);
			break;
		}
		case S_UNMUTE: {
			GlobalVars::getInstance()->setLogToConsole(true);
			break;
		}
		case S_DISABLEWORK: {
			GlobalVars::getInstance()->setShowWork(false);
			break;
		}
		case S_ENABLEWORK: {
			GlobalVars::getInstance()->setShowWork(true);
			break;
		}
		case S_RESCHECK: {
			result = result.empty() ? "0" : "1";
			break;
		}
		case S_ENDFUNC: {
			break;
		}
		case S_DIE: {
			script.invalidate();
			break;
		}
		case END_EXEC: {
			cout << "Script execution has ended." << endl;
			break;
		}
		default: {
			cout
					<< "SCRIPT ERROR: attempted to execute operation with no arguments, yet it expects some (this is a bug, please report it!)"
					<< endl;
			script.invalidate();
			break;
		}
	}
}

void ScriptEngine::initializeConstants() {
	reservedVariables = {
			{"pi",           fmt(boost::math::constants::pi<Real>())},
			{"e",            fmt(boost::math::constants::e<Real>())},
			{"golden_ratio", fmt(boost::math::constants::phi<Real>())},
			{"euler_gamma",  fmt(boost::math::constants::euler<Real>())},
			{"argcount",     to_string(arguments.size() - 1)}
	};
}

long ScriptEngine::eval() {
	string file = arguments[0];
	
	auto start = chrono::system_clock::now();
	
	ScriptReader reader(file);
	bool accessible = reader.verifyAccessibility();
	
	if (!accessible) {
		cout << "ERROR: The file '" << file << "' is either not accessible, does not exist, or is not a file." << endl;
		result = "Numberrain script failed";
		return chrono::duration_cast<chrono::microseconds>(chrono::system_clock::now() - start).count();
	}
	
	script = reader.readScript();
	
	if (!script.isValid()) {
		cout << "ERROR: Script is invalid." << endl;
		result = "Numberrain script failed";
		return chrono::duration_cast<chrono::microseconds>(chrono::system_clock::now() - start).count();
	}
	
	for (int i = 1; i < arguments.size(); i++) {
		scriptArgs.emplace_back(arguments[i]);
	}
	
	script.executePreCommands();
	
	initializeConstants();
	
	while (script.isValid()) {
		Command command = script.nextCommand();
		
		ignore = false;
		cont = false;
		executeScriptCommand(command);
	}
	
	auto stop = chrono::system_clock::now();
	
	result = "Numberrain script terminated";
	
	return chrono::duration_cast<chrono::microseconds>(stop - start).count();
}
