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

#include "Script.h"

using namespace std;

//format = {OPERATION, {minArgs, maxArgs}}
//-1 minArgs means invalid operation (since actual minimum is zero // cannot have negative argument count)
//-1 maxArgs means no maximum
map<PreScriptOperation, pair<int, int>> Script::preOpArgCounts = {
		{PRECISION,     {1,  1}},
		{INVALID_PREOP, {-1, -1}}
};

map<ScriptOperation, pair<int, int>> Script::opArgCounts = {
		{BEGIN_EXEC,                    {0, 0}},
		{S_ADD,                         {2, -1}},
		{S_SUBTRACT,                    {2, -1}},
		{S_MULTIPLY,                    {2, -1}},
		{S_DIVIDE,                      {2, -1}},
		{S_EXPONENT,                    {2, -1}},
		{S_SQRT,                        {1, 1}},
		{S_FACTORIAL,                   {1, 1}},
		{S_MODULUS,                     {2, -1}},
		{S_GREATEST_COMMON_DENOMINATOR, {2, -1}},
		{S_LEAST_COMMON_MULTIPLE,       {2, -1}},
		{S_ABSOLUTE_VALUE,              {1, 1}},
		{S_LN,                          {1, 1}},
		{S_LOG10,                       {1, 1}},
		{S_LOGB,                        {2, 2}},
		{S_SINE,                        {1, 1}},
		{S_COSINE,                      {1, 1}},
		{S_TANGENT,                     {1, 1}},
		{S_ARCSINE,                     {2, 2}},
		{S_ARCCOSINE,                   {2, 2}},
		{S_ARCTANGENT,                  {2, 2}},
		{S_VECTOR_ADD,                  {2, -1}},
		{S_VECTOR_SUBTRACT,               {2,  -1}},
		{S_VECTOR_SCALAR_MULTIPLY,        {2,  2}},
		{S_VECTOR_DOT_PRODUCT,            {2,  2}},
		{S_VECTOR_CROSS_PRODUCT,          {2,  -1}},
		{S_VECTOR_POLAR_TO_RECTANGULAR, {2,  2}},
		{S_VECTOR_RECTANGULAR_TO_POLAR, {1,  2}},
		{S_VECTOR_CONSTRUCT,            {1,  3}},
		{S_VECTOR_GET_X,                {1,  1}},
		{S_VECTOR_GET_Y,                {1,  1}},
		{S_VECTOR_GET_Z,                {1,  1}},
		{S_PRINT,                       {1,  -1}},
		{S_ASSIGN,                      {1,  1}},
		{S_FOR,                         {4,  4}},
		{S_ENDFOR,                      {0,  0}},
		{S_FLOOR,                       {1,  1}},
		{S_CEIL,                        {1,  1}},
		{S_ROUND,                       {1,  1}},
		{S_DROUND,                      {2,  2}},
		{S_DISABLEWORK,                 {0,  0}},
		{S_ENABLEWORK,                  {0,  0}},
		{S_IF,                          {3,  3}},
		{S_ELSEIF,                      {3,  3}},
		{S_ELSE,                        {0,  0}},
		{S_ENDIF,                       {0,  0}},
		{S_FUNCTION,                    {2,  -1}},
		{S_RETURN,                      {1,  1}},
		{S_ENDFUNC,                     {0,  0}},
		{S_CALL,                        {1,  -1}},
		{S_NOP,                         {1,  1}},
		{S_DIE,                         {0,  0}},
		{S_RESCHECK,                    {0,  0}},
		{END_EXEC,                      {0,  0}},
		{INVALID_OP,                    {-1, -1}}
};

map<ScriptOperation, OperationType> Script::opTypes = {
		{BEGIN_EXEC,                    VOID_SCR},
		{S_ADD,                         REAL_SCR},
		{S_SUBTRACT,                    REAL_SCR},
		{S_MULTIPLY,                    REAL_SCR},
		{S_DIVIDE,                      REAL_SCR},
		{S_EXPONENT,                    REAL_SCR},
		{S_SQRT,                        REAL_SCR},
		{S_FACTORIAL,                   INTEGER_SCR},
		{S_MODULUS,                     INTEGER_SCR},
		{S_GREATEST_COMMON_DENOMINATOR, INTEGER_SCR},
		{S_LEAST_COMMON_MULTIPLE,       INTEGER_SCR},
		{S_ABSOLUTE_VALUE,              REAL_SCR},
		{S_LN,                          REAL_SCR},
		{S_LOG10,                       REAL_SCR},
		{S_LOGB,                        REAL_SCR},
		{S_SINE,                        REAL_SCR},
		{S_COSINE,                      REAL_SCR},
		{S_TANGENT,                     REAL_SCR},
		{S_ARCSINE,                     REAL_SCR},
		{S_ARCCOSINE,                   REAL_SCR},
		{S_ARCTANGENT,                  REAL_SCR},
		{S_VECTOR_ADD,                  VECTOR_SCR},
		{S_VECTOR_SUBTRACT,               VECTOR_SCR},
		{S_VECTOR_SCALAR_MULTIPLY,        VECTOR_SCR},
		{S_VECTOR_DOT_PRODUCT,            VECTOR_SCR},
		{S_VECTOR_CROSS_PRODUCT,          VECTOR_SCR},
		{S_VECTOR_POLAR_TO_RECTANGULAR, VECTOR_SCR},
		{S_VECTOR_RECTANGULAR_TO_POLAR, VECTOR_SCR},
		{S_VECTOR_CONSTRUCT,            REAL_SCR},
		{S_VECTOR_GET_X,                VECTOR_SCR},
		{S_VECTOR_GET_Y,                VECTOR_SCR},
		{S_VECTOR_GET_Z,                VECTOR_SCR},
		{S_FLOOR,                       REAL_SCR},
		{S_CEIL,                        REAL_SCR},
		{S_ROUND,                       REAL_SCR},
		{S_DROUND,                      REAL_SCR},
		{S_PRINT,                       STRING_SCR},
		{S_ASSIGN,                      STRING_SCR},
		{S_FOR,                         STRING_SCR},
		{S_ENDFOR,                      VOID_SCR},
		{S_DISABLEWORK,                 VOID_SCR},
		{S_ENABLEWORK,                  VOID_SCR},
		{S_IF,                          STRING_SCR},
		{S_ELSEIF,                      STRING_SCR},
		{S_ELSE,                        VOID_SCR},
		{S_ENDIF,                       VOID_SCR},
		{S_FUNCTION,                    STRING_SCR},
		{S_RETURN,                      STRING_SCR},
		{S_ENDFUNC,                     VOID_SCR},
		{S_CALL,                        STRING_SCR},
		{S_NOP,                         STRING_SCR},
		{S_RESCHECK,                    VOID_SCR},
		{S_DIE,                         VOID_SCR},
		{END_EXEC,                      VOID_SCR},
		{INVALID_OP,                    INVALID_OP_TYPE}
};

map<string, DataType> Script::dataTypeCodes = {
		{"VOID",   DT_VOID},
		{"REAL",   DT_REAL},
		{"INT",    DT_INTEGER},
		{"VECTOR", DT_VECTOR},
		{"STRING", DT_STRING}
};

OperationType Script::getOpType(ScriptOperation operation) {
	if (opTypes.find(operation) == opTypes.end()) {
		return INVALID_OP_TYPE;
	}
	
	return opTypes[operation];
}

DataType Script::getDataType(const string &code) {
	if (dataTypeCodes.find(code) == dataTypeCodes.end()) {
		return INVALID_DATA_TYPE;
	}
	
	return dataTypeCodes[code];
}

bool Script::checkPreOpArgCount(PreScriptOperation operation, uint32_t argCount) {
	if (preOpArgCounts[operation].first < 0) {
		return false;
	}
	
	pair<int, int> argCountBounds = preOpArgCounts[operation];
	
	if (argCountBounds.first < 0) {
		return false;
	}
	
	if (argCountBounds.second < 0) {
		return argCount >= argCountBounds.first;
	} else {
		return argCount >= argCountBounds.first && argCount <= argCountBounds.second;
	}
}

bool Script::checkOpArgCount(ScriptOperation operation, uint32_t argCount) {
	if (opArgCounts[operation].first < 0) {
		return false;
	}
	
	pair<int, int> argCountBounds = opArgCounts[operation];
	
	if (argCountBounds.first < 0) {
		return false;
	}
	
	if (argCountBounds.second < 0) {
		return argCount >= argCountBounds.first;
	} else {
		return argCount >= argCountBounds.first && argCount <= argCountBounds.second;
	}
}

void Script::lockRO() {
	writable = false;
	if (functionInsertionMode) {
		cout << "ERROR: Function '" << activeFunction << "' is never terminated by ENDFUNC" << endl;
		invalidate();
	}
}

void Script::invalidate() {
	valid = false;
}

bool Script::isValid() const {
	return valid;
}

bool Script::functionExists(const string &name) {
	return functions.find(name) != functions.end();
}

Function Script::getFunction(const string &name) {
	if (!functionExists(name)) {
		Function invalid;
		invalid.startPosition = -1;
		
		return invalid;
	}
	
	return functions[name];
}

void Script::executePreCommands() {
	while (!preCommands.empty()) {
		Precommand precommand = preCommands.front();
		preCommands.pop_front();
		
		switch (precommand.first) {
			case PRECISION: {
				int digits = (int) strtol(precommand.second[0].c_str(), nullptr, 10);
				
				boost::multiprecision::mpf_float::default_precision(digits);
				cout << "Script precision set to " << digits << " decimal digits." << endl;
				break;
			}
			default: {
				cout << "PRE-SCRIPT ERROR: Encountered invalid precommand." << endl;
				invalidate();
				break;
			}
		}
	}
}

bool Script::addPreCommand(PreScriptOperation operation, const ArgList &arguments) {
	if (!writable || !valid)
		return false;
	
	if (operation == INVALID_PREOP) {
		invalidate();
		return false;
	}
	
	if (!checkPreOpArgCount(operation, arguments.size())) {
		cout << "Invalid argument count for this precommand!" << endl;
		invalidate();
		return false;
	}
	
	preCommands.emplace_back(operation, arguments);
	
	return true;
}

bool Script::addCommand(ScriptOperation operation, const ArgList &arguments) {
	if (!writable || !valid)
		return false;
	
	if (operation == INVALID_OP && valid) {
		invalidate();
		return false;
	}
	
	if (!checkOpArgCount(operation, arguments.size())) {
		cout << "Invalid argument count for this command!" << endl;
		invalidate();
		return false;
	}
	
	switch (operation) {
		case S_FUNCTION: {
			if (functionInsertionMode) {
				cout << "Nested functions are not supported" << endl;
				return false;
			}
			
			string retCode = arguments[0];
			string name = arguments[1];
			
			if (functionExists(name)) {
				cout << "Multiple definition of function " << name << endl;
				return false;
			}
			
			DataType retType = getDataType(retCode);
			if (retType == INVALID_DATA_TYPE) {
				cout << "Invalid return type '" << retCode << "' for function " << name << endl;
				return false;
			}
			
			Function func;
			func.startPosition = commands.size();
			func.returnType = retType;
			
			for (int i = 2; i < arguments.size(); i++) {
				vector<string> parts;
				string arg = arguments[i];
				
				boost::algorithm::split(parts, arg, boost::algorithm::is_any_of(":"));
				
				if (parts.size() != 2) {
					cout << "Invalid argument specification '" << arg << "' for function " << name << endl;
					return false;
				}
				
				string argName = parts[0];
				
				if (func.argExists(argName)) {
					cout << "Multiple definition of argument '" << argName << "' in function " << name << endl;
					return false;
				}
				
				DataType argType = getDataType(parts[1]);
				
				if (argType == INVALID_DATA_TYPE) {
					cout << "Invalid data type for argument '" << argName << "' in function " << name << endl;
					return false;
				}
				
				func.args.emplace_back(pair<string, DataType>(argName, argType));
			}
			
			functions.emplace(name, func);
			functionInsertionMode = true;
			activeFunction = name;
			break;
		}
		case S_ENDFUNC: {
			if (!functionInsertionMode) {
				cout << "Floating ENDFUNC statement" << endl;
				return false;
			}
			
			functions[activeFunction].endPosition = commands.size();
			functionInsertionMode = false;
			activeFunction = "";
			break;
		}
		default: {
			break;
		}
	}
	
	commands.emplace_back(operation, arguments);
	
	return true;
}

Command Script::nextCommand() {
	if (!valid || cursor < 0 || cursor >= commands.size()) {
		return Command(INVALID_OP, ArgList());
	}
	
	auto command = commands[cursor];
	cursor++;
	
	valid = cursor < commands.size();
	
	return command;
}

int Script::getPosition() const {
	return cursor;
}

void Script::jump(int position) {
	if (position < 0) {
		cursor = (int) commands.size() - 1;
		valid = false;
	}
	
	cursor = position;
}
