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

#ifndef NUMBERRAIN_SCRIPTENGINE_H
#define NUMBERRAIN_SCRIPTENGINE_H

#include "../StringOperation.h"
#include "Script.h"
#include "../logging/Logger.h"
#include <map>

enum ComparisonOperator {
	EQUAL,
	NOT_EQUAL,
	LESS_THAN_OR_EQUAL_TO,
	GREATER_THAN_OR_EQUAL_TO,
	LESS_THAN,
	GREATER_THAN,
	
	INVALID_COMPARISON_OPERATOR
};

class ScriptEngine : public virtual StringOperation {
private:
	static std::map<std::string, ComparisonOperator> comparisonOperators;
	
	static Logger log;
	std::deque<int> loopStack;
	Script script;
	
	std::vector<std::string> scriptArgs;
	std::map<std::string, std::string> reservedVariables;
	std::map<std::string, std::string> variables;
	
	static ComparisonOperator getComparisonOperator(const std::string &oper);
	
	bool isValidType(const std::string &value, DataType type);
	
	bool isReservedVariable(const std::string &varName);
	
	bool variableExists(const std::string &varName);
	
	std::string getVariableValue(const std::string &varName);
	
	bool updateVariable(const std::string &varName, const std::string &value);
	
	void executeScriptCommand(const Command &command);
	
	void executeRealOperation(ScriptOperation operation, const std::vector<Real> &args);
	
	void executeIntegerOperation(ScriptOperation operation, const std::vector<Integer> &args);
	
	void executeVectorOperation(ScriptOperation operation, const std::vector<Vector> &args);
	
	void executeStringOperation(ScriptOperation operation, const std::vector<std::string> &args);
	
	void executeVoidOperation(ScriptOperation operation);
	
	void initializeConstants();

public:
	using StringOperation::StringOperation;
	
	long eval() override;
};


#endif //NUMBERRAIN_SCRIPTENGINE_H
