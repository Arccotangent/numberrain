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
			string value = scriptArgs[argIndex];
			//cout << "[debug] argument at index " << argIndex << " is " << value << endl;
			return value;
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
			
			//cout << "[debug] updated variable " << varName << " with value " << result << " from result register" << endl;
			break;
		}
		case S_FOR: {
			string loopVarName = args[0];
			vector<Integer> loopSpecs; //0 = loopVarValue, 1 = loopEndValue, 2 = loopStep
			
			if (reservedVariables.find(loopVarName) != reservedVariables.end()) {
				cout << "SCRIPT ERROR: FOR loop attempted to redefine a reserved variable ('" << loopVarName << "')."
				     << endl;
				script.invalidate();
				return;
			}
			
			for (int i = 1; i < 4; i++) {
				if (variableExists(args[i])) {
					loopSpecs.emplace_back(Integer(getVariableValue(args[i])));
				} else {
					loopSpecs.emplace_back(args[i]);
				}
			}
			
			/*if (loopSpecs[2] == 0) {
				cout << "SCRIPT ERROR: For loop will never end (step is zero)." << endl;
				script.invalidate();
				return;
			}
			
			if (loopSpecs[0] < loopSpecs[1] && loopSpecs[2] < 0) {
				cout << "SCRIPT ERROR: For loop will never end (start < end, step is negative)." << endl;
				script.invalidate();
				return;
			}
			
			if (loopSpecs[0] > loopSpecs[1] && loopSpecs[2] > 0) {
				cout << "SCRIPT ERROR: For loop will never end (start > end, step is positive)." << endl;
				script.invalidate();
				return;
			}*/
			
			bool loopVarPreExisting = variables.find(loopVarName) != variables.end();
			string loopVarPreValue;
			if (loopVarPreExisting) {
				loopVarPreValue = variables[loopVarName];
			}
			
			Command buf;
			
			loopStack.emplace_back(script.getPosition());
			
			int resetPos;
			
			while ((loopSpecs[2] > 0 && loopSpecs[0] < loopSpecs[1]) ||
			       (loopSpecs[2] < 0 && loopSpecs[0] > loopSpecs[1])) {
				if (!script.isValid()) {
					cout << "SCRIPT ERROR: End of FOR loop iteration code not marked by ENDFOR." << endl;
					script.invalidate();
					return;
				}
				
				updateVariable(loopVarName, fmt(loopSpecs[0]));
				
				Command command = script.nextCommand();
				
				if (command.first == S_ENDFOR) {
					resetPos = script.getPosition();
					loopSpecs[0] += loopSpecs[2];
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
		case S_IF: {
			int initialPos = script.getPosition();
			int endifPos;
			
			int levels = 1;
			
			Command command = script.nextCommand();
			while (levels > 0) {
				if (!script.isValid()) {
					cout
							<< "SCRIPT ERROR: End of IF block not marked by ENDIF - check if there are enough ENDIFs if using nested IF blocks."
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
			
			endifPos = script.getPosition();
			script.jump(initialPos);
			
			ComparisonOperator oper = getComparisonOperator(args[1]);
			if (oper == INVALID_COMPARISON_OPERATOR) {
				cout << "SCRIPT ERROR: Invalid comparison operator (catch 1): " << args[1] << endl;
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
							<< "SCRIPT ERROR: Script invalidated before end of IF block (catch 1) - there are likely other errors - check above."
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
							cout << "SCRIPT ERROR: Invalid comparison operator: (catch 2)." << endl;
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
									<< "SCRIPT ERROR: Script invalidated before end of IF block (catch 2) - there are likely other errors - check above."
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
							cout << "SCRIPT ERROR: Invalid comparison operator: " << command.second[1] << endl;
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
					if (endifPos - condPos >= 2) {
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
					
					command = script.nextCommand();
				}
			}
			
			script.jump(endifPos);
			break;
		}
		case S_ELSEIF: {
			cout << "SCRIPT ERROR: Floating ELSEIF statement." << endl;
			script.invalidate();
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
			//should never be executed - mainly for debugging
			cout << "For loop ended." << endl;
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
		case S_DISABLEWORK: {
			GlobalVars::getInstance()->setShowWork(false);
			break;
		}
		case S_ENABLEWORK: {
			GlobalVars::getInstance()->setShowWork(true);
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
