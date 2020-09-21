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
#include "../ops.h"
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <boost/regex.h>

using namespace std;

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
	
	return varName == "argcount" || variables.find(varName) != variables.end() ||
	       reservedVariables.find(varName) != reservedVariables.end();
}

string ScriptEngine::getVariableValue(const string &varName) {
	if (boost::algorithm::starts_with(varName, "arg_")) {
		string tentativeIndex = varName.substr(4);
		
		if (variableExists(tentativeIndex)) {
			tentativeIndex = getVariableValue(tentativeIndex);
		}
		
		long argIndex = strtol(tentativeIndex.c_str(), nullptr, 10);
		
		if (argIndex < scriptArgs.size() && argIndex >= 0) {
			return scriptArgs[argIndex];
		}
	}
	
	if (varName == "argcount")
		return to_string(scriptArgs.size());
	
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
	if (boost::algorithm::starts_with(varName, "arg_")) {
		return false;
	}
	
	if (reservedVariables.find(varName) != reservedVariables.end()) {
		return false;
	}
	
	variables.erase(varName);
	variables.emplace(varName, value);
	
	return true;
}

void ScriptEngine::jumpToLabel(const string &labelName) {
	if (!script.markExists(labelName)) {
		cout << "SCRIPT ERROR: Label '" << labelName << "' does not exist." << endl;
		script.invalidate();
		return;
	}
	
	int labelPos = script.getMarkPosition(labelName);
	
	script.jump(labelPos);
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
		case STRING_SCR: {
			vector<string> arguments;
			
			for (auto &argStr : args) {
				if (variableExists(argStr) && command.first !=
				                              S_ASSIGN) { //ASSIGN is a special case here, substituting variables would make reassignment impossible
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
		case S_COMPARE: {
			Real a = args[0];
			Real b = args[1];
			
			if (a == b)
				compRegister = 0;
			else if (a < b)
				compRegister = -1;
			else
				compRegister = 1;
			
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

void ScriptEngine::executeStringOperation(ScriptOperation operation, const vector<string> &args) {
	switch (operation) {
		case S_PRINT: {
			for (auto &arg : args) {
				cout << arg;
				cout << " ";
			}
			cout << endl;
			break;
		}
		case S_ASSIGN: {
			string varName = args[0];
			boost::regex digits("^[0-9]");
			
			if (boost::regex_match(varName, digits)) {
				cout << "SCRIPT ERROR: variable names cannot start with a number." << endl;
				script.invalidate();
				return;
			}
			
			updateVariable(varName, result);
			break;
		}
		case S_FOR: {
			string loopVarName = args[0];
			Integer loopVarValue;
			Integer loopEndValue;
			Integer loopStep;
			
			if (reservedVariables.find(loopVarName) != reservedVariables.end()) {
				cout << "SCRIPT ERROR: FOR loop attempted to redefine a reserved variable ('" << loopVarName << "')."
				     << endl;
				script.invalidate();
				return;
			}
			
			//TODO improve this 3x if
			
			if (variableExists(args[1])) {
				loopVarValue = Integer(getVariableValue(args[1]));
			} else {
				loopVarValue = Integer(args[1]);
			}
			
			if (variableExists(args[2])) {
				loopEndValue = Integer(getVariableValue(args[2]));
			} else {
				loopEndValue = Integer(args[2]);
			}
			
			if (variableExists(args[3])) {
				loopStep = Integer(getVariableValue(args[3]));
			} else {
				loopStep = Integer(args[3]);
			}
			
			bool loopVarPreExisting = variables.find(loopVarName) != variables.end();
			string loopVarPreValue;
			if (loopVarPreExisting) {
				loopVarPreValue = variables[loopVarName];
			}
			
			Command buf;
			
			loopStack.emplace_back(script.getPosition());
			
			uint32_t resetPos;
			
			while ((loopStep > 0 && loopVarValue < loopEndValue) || (loopStep < 0 && loopVarValue > loopEndValue)) {
				if (!script.isValid()) {
					cout << "SCRIPT ERROR: End of FOR loop iteration code not marked by ENDFOR." << endl;
					script.invalidate();
					return;
				}
				
				updateVariable(loopVarName, fmt(loopVarValue));
				
				Command command = script.nextCommand();
				
				if (command.first == S_ENDFOR) {
					resetPos = script.getPosition();
					loopVarValue += loopStep;
					script.jump(loopStack.back());
					continue;
				}
				
				executeScriptCommand(command);
			}
			
			loopStack.pop_back();
			script.jump(resetPos);
			
			variables.erase(loopVarName);
			
			if (loopVarPreExisting) {
				variables[loopVarName] = loopVarPreValue;
			}
			break;
		}
		case S_MARK: {
			break;
		}
		case S_JUMP_UNCONDITIONAL: {
			string label = args[0];
			jumpToLabel(label);
			break;
		}
		case S_JUMP_EQUAL: {
			if (compRegister != 0) {
				break;
			}
			
			string label = args[0];
			jumpToLabel(label);
			break;
		}
		case S_JUMP_NOT_EQUAL: {
			if (compRegister == 0) {
				break;
			}
			
			string label = args[0];
			jumpToLabel(label);
			break;
		}
		case S_JUMP_LESS_THAN: {
			if (compRegister != -1) {
				break;
			}
			
			string label = args[0];
			jumpToLabel(label);
			break;
		}
		case S_JUMP_LESS_THAN_OR_EQUAL_TO: {
			if (compRegister == 1) {
				break;
			}
			
			string label = args[0];
			jumpToLabel(label);
			break;
		}
		case S_JUMP_GREATER_THAN: {
			if (compRegister != 1) {
				break;
			}
			
			string label = args[0];
			jumpToLabel(label);
			break;
		}
		case S_JUMP_GREATER_THAN_OR_EQUAL_TO: {
			if (compRegister == -1) {
				break;
			}
			
			string label = args[0];
			jumpToLabel(label);
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
		case S_ENDFOR: {
			//should never be executed
			cout << "For loop ended." << endl;
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
			{"euler_gamma",  fmt(boost::math::constants::euler<Real>())}
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
		
		executeScriptCommand(command);
	}
	
	auto stop = chrono::system_clock::now();
	
	result = "Numberrain script terminated";
	
	return chrono::duration_cast<chrono::microseconds>(stop - start).count();
}
