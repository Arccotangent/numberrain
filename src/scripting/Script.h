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

#ifndef NUMBERRAIN_SCRIPT_H
#define NUMBERRAIN_SCRIPT_H

#include <map>
#include <deque>
#include <vector>
#include <string>
#include "../Structures.h"
#include "../logging/Logger.h"

enum PreScriptOperation {
	PRECISION,
	
	INVALID_PREOP
};

enum ScriptOperation {
	BEGIN_EXEC,
	
	S_ADD,
	S_SUBTRACT,
	S_MULTIPLY,
	S_DIVIDE,
	S_EXPONENT,
	S_SQRT,
	S_FACTORIAL,
	S_MODULUS,
	S_GREATEST_COMMON_DENOMINATOR,
	S_LEAST_COMMON_MULTIPLE,
	
	S_LN,
	S_LOG10,
	S_LOGB,
	
	S_SINE,
	S_COSINE,
	S_TANGENT,
	S_ARCSINE,
	S_ARCCOSINE,
	S_ARCTANGENT,
	
	S_VECTOR_ADD,
	S_VECTOR_SUBTRACT,
	S_VECTOR_SCALAR_MULTIPLY,
	S_VECTOR_DOT_PRODUCT,
	S_VECTOR_CROSS_PRODUCT,
	S_VECTOR_POLAR_TO_RECTANGULAR,
	S_VECTOR_RECTANGULAR_TO_POLAR,
	
	S_VECTOR_CONSTRUCT,
	S_VECTOR_GET_X,
	S_VECTOR_GET_Y,
	S_VECTOR_GET_Z,
	
	S_FLOOR,
	S_CEIL,
	S_ROUND,
	S_DROUND,
	
	S_ASSIGN,
	S_PRINT,
	
	S_FOR,
	S_ENDFOR,
	
	S_DISABLEWORK,
	S_ENABLEWORK,
	
	S_COMPARE,
	S_MARK,
	S_JUMP_UNCONDITIONAL,
	S_JUMP_EQUAL,
	S_JUMP_NOT_EQUAL,
	S_JUMP_LESS_THAN,
	S_JUMP_LESS_THAN_OR_EQUAL_TO,
	S_JUMP_GREATER_THAN,
	S_JUMP_GREATER_THAN_OR_EQUAL_TO,
	
	S_NOP,
	
	END_EXEC,
	
	INVALID_OP
};

enum OperationType {
	VOID_SCR,
	REAL_SCR,
	INTEGER_SCR,
	VECTOR_SCR,
	STRING_SCR,
	
	INVALID_OP_TYPE
};

typedef std::vector<std::string> ArgList;

typedef std::pair<PreScriptOperation, ArgList> Precommand;
typedef std::pair<ScriptOperation, ArgList> Command;

class Script {
private:
	static Logger log;
	static std::map<PreScriptOperation, std::pair<int, int>> preOpArgCounts;
	static std::map<ScriptOperation, std::pair<int, int>> opArgCounts;
	static std::map<ScriptOperation, OperationType> opTypes;
	
	std::map<std::string, int> labelMarks;
	
	std::deque<Precommand> preCommands;
	std::deque<Command> commands;
	
	bool writable = true;
	bool valid = true;
	
	int cursor = 0;
	
	static bool checkPreOpArgCount(PreScriptOperation operation, uint32_t argCount);
	
	static bool checkOpArgCount(ScriptOperation operation, uint32_t argCount);

public:
	Script() = default;
	
	static OperationType getOpType(ScriptOperation op);
	
	void lockRO();
	
	void invalidate();
	
	[[nodiscard]] bool isValid() const;
	
	bool markExists(const std::string &name);
	
	int getMarkPosition(const std::string &name);
	
	void executePreCommands();
	
	bool addPreCommand(PreScriptOperation operation, const ArgList &arguments);
	
	bool addCommand(ScriptOperation operation, const ArgList &arguments);
	
	Command nextCommand();
	
	int getPosition() const;
	
	void jump(uint32_t position);
};


#endif //NUMBERRAIN_SCRIPT_H
