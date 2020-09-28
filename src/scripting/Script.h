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
#include <boost/algorithm/string.hpp>
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
	S_ABSOLUTE_VALUE,
	
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
	
	S_IF,
	S_ELSEIF,
	S_ELSE,
	S_ENDIF,
	
	S_FUNCTION,
	S_RETURN,
	S_ENDFUNC,
	S_CALL,
	
	S_NOP,
	S_RESCHECK,
	
	S_DIE,
	
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

enum DataType {
	DT_VOID,
	DT_REAL,
	DT_INTEGER,
	DT_VECTOR,
	DT_STRING,
	
	INVALID_DATA_TYPE
};

typedef std::vector<std::string> ArgList;

typedef std::pair<PreScriptOperation, ArgList> Precommand;
typedef std::pair<ScriptOperation, ArgList> Command;

struct Function {
	int startPosition;
	int endPosition;
	std::vector<std::pair<std::string, DataType>> args;
	DataType returnType;
	
	bool argExists(const std::string &name) {
		return std::any_of(args.begin(), args.end(), [&](std::pair<std::string, DataType> &arg) {
			return arg.first == name;
		});
	}
};

class Script {
private:
	static Logger log;
	static std::map<PreScriptOperation, std::pair<int, int>> preOpArgCounts;
	static std::map<ScriptOperation, std::pair<int, int>> opArgCounts;
	static std::map<ScriptOperation, OperationType> opTypes;
	static std::map<std::string, DataType> dataTypeCodes;
	
	bool functionInsertionMode = false;
	std::string activeFunction;
	std::map<std::string, Function> functions;
	
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
	
	static DataType getDataType(const std::string &code);
	
	void lockRO();
	
	void invalidate();
	
	[[nodiscard]] bool isValid() const;
	
	bool functionExists(const std::string &name);
	
	Function getFunction(const std::string &name);
	
	void executePreCommands();
	
	bool addPreCommand(PreScriptOperation operation, const ArgList &arguments);
	
	bool addCommand(ScriptOperation operation, const ArgList &arguments);
	
	Command nextCommand();
	
	[[nodiscard]] int getPosition() const;
	
	void jump(int position);
};


#endif //NUMBERRAIN_SCRIPT_H
