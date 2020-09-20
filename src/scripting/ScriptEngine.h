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
#include <map>

class ScriptEngine : public virtual StringOperation {
private:
	std::deque<int> loopStack;
	Script script;
	
	int compRegister = 0; //0 = equal, -1 = less than, 1 = greater than
	
	std::vector<std::string> scriptArgs;
	std::map<std::string, std::string> reservedVariables;
	std::map<std::string, std::string> variables;
	
	bool variableExists(const std::string &varName);
	
	std::string getVariableValue(const std::string &varName);
	
	bool updateVariable(const std::string &varName, const std::string &value);
	
	void jumpToLabel(const std::string &labelName);
	
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
