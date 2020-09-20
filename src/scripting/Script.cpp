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

map<PreScriptOperation, pair<int, CountRuleType>> Script::preOpArgCounts = {
		{PRECISION,     {1,  EQUAL}},
		{INVALID_PREOP, {-1, LESS_THAN}}
};

map<ScriptOperation, pair<int, CountRuleType>> Script::opArgCounts = {
		{BEGIN_EXEC,                      {0,  EQUAL}},
		{S_ADD,                           {2,  GREATER_THAN_OR_EQUAL_TO}},
		{S_SUBTRACT,                      {2,  GREATER_THAN_OR_EQUAL_TO}},
		{S_MULTIPLY,                      {2,  GREATER_THAN_OR_EQUAL_TO}},
		{S_DIVIDE,                        {2,  GREATER_THAN_OR_EQUAL_TO}},
		{S_EXPONENT,                      {2,  GREATER_THAN_OR_EQUAL_TO}},
		{S_SQRT,                          {1,  EQUAL}},
		{S_FACTORIAL,                     {1,  EQUAL}},
		{S_MODULUS,                       {2,  GREATER_THAN_OR_EQUAL_TO}},
		{S_GREATEST_COMMON_DENOMINATOR,   {2,  GREATER_THAN_OR_EQUAL_TO}},
		{S_LEAST_COMMON_MULTIPLE,         {2,  GREATER_THAN_OR_EQUAL_TO}},
		{S_LN,                            {1,  EQUAL}},
		{S_LOG10,                         {1,  EQUAL}},
		{S_LOGB,                          {2,  EQUAL}},
		{S_SINE,                          {1,  EQUAL}},
		{S_COSINE,                        {1,  EQUAL}},
		{S_TANGENT,                       {1,  EQUAL}},
		{S_ARCSINE,                       {2,  EQUAL}},
		{S_ARCCOSINE,                     {2,  EQUAL}},
		{S_ARCTANGENT,                    {2,  EQUAL}},
		{S_VECTOR_ADD,                    {2,  GREATER_THAN_OR_EQUAL_TO}},
		{S_VECTOR_SUBTRACT,               {2,  GREATER_THAN_OR_EQUAL_TO}},
		{S_VECTOR_SCALAR_MULTIPLY,        {2,  EQUAL}},
		{S_VECTOR_DOT_PRODUCT,            {2,  EQUAL}},
		{S_VECTOR_CROSS_PRODUCT,          {2,  GREATER_THAN_OR_EQUAL_TO}},
		{S_VECTOR_POLAR_TO_RECTANGULAR,   {2,  EQUAL}},
		{S_VECTOR_RECTANGULAR_TO_POLAR,   {1,  EQUAL}},
		{S_VECTOR_GET_X,                  {1,  EQUAL}},
		{S_VECTOR_GET_Y,                  {1,  EQUAL}},
		{S_VECTOR_GET_Z,                  {1,  EQUAL}},
		{S_PRINT,                         {1,  GREATER_THAN_OR_EQUAL_TO}},
		{S_ASSIGN,                        {1,  EQUAL}},
		{S_FOR,                           {4,  EQUAL}},
		{S_ENDFOR,                        {0,  EQUAL}},
		{S_COMPARE,                       {2,  EQUAL}},
		{S_MARK,                          {1,  EQUAL}},
		{S_JUMP_UNCONDITIONAL,            {1,  EQUAL}},
		{S_JUMP_EQUAL,                    {1,  EQUAL}},
		{S_JUMP_NOT_EQUAL,                {1,  EQUAL}},
		{S_JUMP_LESS_THAN,                {1,  EQUAL}},
		{S_JUMP_LESS_THAN_OR_EQUAL_TO,    {1,  EQUAL}},
		{S_JUMP_GREATER_THAN,             {1,  EQUAL}},
		{S_JUMP_GREATER_THAN_OR_EQUAL_TO, {1,  EQUAL}},
		{S_NOP,                           {1,  EQUAL}},
		{END_EXEC,                        {0,  EQUAL}},
		{INVALID_OP,                      {-1, LESS_THAN}}
};

map<ScriptOperation, OperationType> Script::opTypes = {
		{BEGIN_EXEC,                      VOID_SCR},
		{S_ADD,                           REAL_SCR},
		{S_SUBTRACT,                      REAL_SCR},
		{S_MULTIPLY,                      REAL_SCR},
		{S_DIVIDE,                        REAL_SCR},
		{S_EXPONENT,                      REAL_SCR},
		{S_SQRT,                          REAL_SCR},
		{S_FACTORIAL,                     INTEGER_SCR},
		{S_MODULUS,                       INTEGER_SCR},
		{S_GREATEST_COMMON_DENOMINATOR,   INTEGER_SCR},
		{S_LEAST_COMMON_MULTIPLE,         INTEGER_SCR},
		{S_LN,                            REAL_SCR},
		{S_LOG10,                         REAL_SCR},
		{S_LOGB,                          REAL_SCR},
		{S_SINE,                          REAL_SCR},
		{S_COSINE,                        REAL_SCR},
		{S_TANGENT,                       REAL_SCR},
		{S_ARCSINE,                       REAL_SCR},
		{S_ARCCOSINE,                     REAL_SCR},
		{S_ARCTANGENT,                    REAL_SCR},
		{S_VECTOR_ADD,                    VECTOR_SCR},
		{S_VECTOR_SUBTRACT,               VECTOR_SCR},
		{S_VECTOR_SCALAR_MULTIPLY,        VECTOR_SCR},
		{S_VECTOR_DOT_PRODUCT,            VECTOR_SCR},
		{S_VECTOR_CROSS_PRODUCT,          VECTOR_SCR},
		{S_VECTOR_POLAR_TO_RECTANGULAR,   VECTOR_SCR},
		{S_VECTOR_RECTANGULAR_TO_POLAR,   VECTOR_SCR},
		{S_VECTOR_GET_X,                  VECTOR_SCR},
		{S_VECTOR_GET_Y,                  VECTOR_SCR},
		{S_VECTOR_GET_Z,                  VECTOR_SCR},
		{S_PRINT,                         STRING_SCR},
		{S_ASSIGN,                        STRING_SCR},
		{S_FOR,                           STRING_SCR},
		{S_ENDFOR,                        VOID_SCR},
		{S_COMPARE,                       REAL_SCR},
		{S_MARK,                          STRING_SCR},
		{S_JUMP_UNCONDITIONAL,            STRING_SCR},
		{S_JUMP_EQUAL,                    STRING_SCR},
		{S_JUMP_NOT_EQUAL,                STRING_SCR},
		{S_JUMP_LESS_THAN,                STRING_SCR},
		{S_JUMP_LESS_THAN_OR_EQUAL_TO,    STRING_SCR},
		{S_JUMP_GREATER_THAN,             STRING_SCR},
		{S_JUMP_GREATER_THAN_OR_EQUAL_TO, STRING_SCR},
		{S_NOP,                           STRING_SCR},
		{END_EXEC,                        VOID_SCR},
		{INVALID_OP,                      INVALID_OP_TYPE}
};

OperationType Script::getOpType(ScriptOperation operation) {
	if (opTypes.find(operation) == opTypes.end()) {
		return INVALID_OP_TYPE;
	}
	
	return opTypes[operation];
}

bool Script::checkPreOpArgCount(PreScriptOperation operation, uint32_t argCount) {
	if (preOpArgCounts[operation].first < 0) {
		return false;
	}
	
	pair<int, CountRuleType> rule = preOpArgCounts[operation];
	
	switch (rule.second) {
		case EQUAL:
			return argCount == rule.first;
		case LESS_THAN:
			return argCount < rule.first;
		case LESS_THAN_OR_EQUAL_TO:
			return argCount <= rule.first;
		case GREATER_THAN:
			return argCount > rule.first;
		case GREATER_THAN_OR_EQUAL_TO:
			return argCount >= rule.first;
		default:
			return false;
	}
}

bool Script::checkOpArgCount(ScriptOperation operation, uint32_t argCount) {
	if (opArgCounts[operation].first < 0) {
		return false;
	}
	
	pair<int, CountRuleType> rule = opArgCounts[operation];
	
	switch (rule.second) {
		case EQUAL:
			return argCount == rule.first;
		case LESS_THAN:
			return argCount < rule.first;
		case LESS_THAN_OR_EQUAL_TO:
			return argCount <= rule.first;
		case GREATER_THAN:
			return argCount > rule.first;
		case GREATER_THAN_OR_EQUAL_TO:
			return argCount >= rule.first;
		default:
			return false;
	}
}

void Script::lockRO() {
	writable = false;
}

void Script::invalidate() {
	valid = false;
}

bool Script::isValid() const {
	return valid;
}

bool Script::markExists(const string &name) {
	return labelMarks.find(name) != labelMarks.end();
}

int Script::getMarkPosition(const string &name) {
	if (!markExists(name)) {
		return (int) commands.size() - 1;
	}
	
	return labelMarks[name];
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
	
	if (operation == S_MARK) {
		labelMarks.emplace(arguments[0], commands.size());
		return true;
	}
	
	commands.emplace_back(operation, arguments);
	
	return true;
}

Command Script::nextCommand() {
	if (!valid || cursor < 0) {
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

void Script::jump(uint32_t position) {
	cursor = position;
}
