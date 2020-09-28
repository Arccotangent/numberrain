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

#include "ScriptReader.h"
#include <boost/algorithm/string.hpp>
#include <fstream>

using namespace std;

map<string, ScriptOperation> ScriptReader::opcodes = {
		{"BEGIN",  BEGIN_EXEC},
		
		{"ADD",    S_ADD},
		{"SUB",    S_SUBTRACT},
		{"MUL",    S_MULTIPLY},
		{"DIV",    S_DIVIDE},
		{"EXP",    S_EXPONENT},
		{"SQRT",   S_SQRT},
		{"FCT",    S_FACTORIAL},
		{"MOD",    S_MODULUS},
		{"GCD",    S_GREATEST_COMMON_DENOMINATOR},
		{"LCM",    S_LEAST_COMMON_MULTIPLE},
		{"ABS",    S_ABSOLUTE_VALUE},
		
		{"LN",     S_LN},
		{"LOG10",  S_LOG10},
		{"LOGB",   S_LOGB},
		
		{"SIN",    S_SINE},
		{"COS",    S_COSINE},
		{"TAN",    S_TANGENT},
		{"ARCSIN", S_ARCSINE},
		{"ARCCOS", S_ARCCOSINE},
		{"ARCTAN", S_ARCTANGENT},
		
		{"VADD",   S_VECTOR_ADD},
		{"VSUB",   S_VECTOR_SUBTRACT},
		{"VSMUL",  S_VECTOR_SCALAR_MULTIPLY},
		{"VDOT",   S_VECTOR_DOT_PRODUCT},
		{"VCROSS", S_VECTOR_CROSS_PRODUCT},
		{"VPTR",   S_VECTOR_POLAR_TO_RECTANGULAR},
		{"VRTP",   S_VECTOR_RECTANGULAR_TO_POLAR},
		
		{"VC",          S_VECTOR_CONSTRUCT},
		{"VX",          S_VECTOR_GET_X},
		{"VY",          S_VECTOR_GET_Y},
		{"VZ",          S_VECTOR_GET_Z},
		
		{"FLOOR",       S_FLOOR},
		{"CEIL",        S_CEIL},
		{"ROUND",       S_ROUND},
		{"DROUND",      S_DROUND},
		
		{"ASSIGN",      S_ASSIGN},
		{"PRINT",       S_PRINT},
		
		{"FOR",         S_FOR},
		{"ENDFOR",      S_ENDFOR},
		
		{"DISABLEWORK", S_DISABLEWORK},
		{"ENABLEWORK",  S_ENABLEWORK},
		
		{"IF",          S_IF},
		{"ELSEIF",      S_ELSEIF},
		{"ELSE",        S_ELSE},
		{"ENDIF",       S_ENDIF},
		
		{"FUNCTION",    S_FUNCTION},
		{"RETURN",      S_RETURN},
		{"ENDFUNC",     S_ENDFUNC},
		{"CALL",        S_CALL},
		
		{"NOP",         S_NOP},
		{"RESCHECK",    S_RESCHECK},
		
		{"DIE",         S_DIE},
		
		{"END",         END_EXEC}
};

map<string, PreScriptOperation> ScriptReader::preOpcodes = {
		{"PRECISION", PRECISION}
};

ScriptOperation ScriptReader::getOpcode(const string &opcode) {
	if (opcodes.find(opcode) == opcodes.end()) {
		return INVALID_OP;
	}
	
	return opcodes[opcode];
}

PreScriptOperation ScriptReader::getPreOpcode(const string &opcode) {
	if (preOpcodes.find(opcode) == preOpcodes.end()) {
		return INVALID_PREOP;
	}
	
	return preOpcodes[opcode];
}

ScriptReader::ScriptReader(const string &filename) {
	this->filename = filename;
}

bool ScriptReader::verifyAccessibility() {
	return filesystem::is_regular_file(filename) &&
	       ((filesystem::status(filename).permissions() & filesystem::perms::owner_read) != filesystem::perms::none);
}

Script ScriptReader::readScript() {
	Script script;
	
	ifstream in(filename);
	if (!in.good()) {
		script.invalidate();
		return script;
	}
	
	cout << "Script file: " << filename << endl;
	cout << "Script size: " << filesystem::file_size(filename) << " bytes" << endl;
	
	string buf;
	size_t line = 0;
	
	while (getline(in, buf)) {
		line++;
		
		if (buf.empty())
			continue;
		
		if (buf[0] == '#')
			continue;
		
		if (buf[0] != '!') {
			break;
		}
		
		vector<string> parts;
		boost::algorithm::split(parts, buf.substr(1), boost::algorithm::is_any_of(" "));
		
		PreScriptOperation preop = getPreOpcode(parts[0]);
		if (preop == INVALID_PREOP) {
			cout << "[LINE " << line << "] Script error: Invalid preoperation: '" << parts[0] << "'." << endl;
			script.invalidate();
			return script;
		}
		
		ArgList args(parts.begin() + 1, parts.end());
		
		bool success = script.addPreCommand(preop, args);
		if (!success) {
			cout << "[LINE " << line << "] Script error: Processing precommand failed." << endl;
			script.invalidate();
			return script;
		}
	}
	
	line++;
	
	stringstream scriptStr;
	scriptStr << buf;
	scriptStr << in.rdbuf();
	
	string scriptData = scriptStr.str();
	scriptStr.clear();
	
	ScriptOperation opBuffer = INVALID_OP;
	ArgList argListBuffer;
	
	stringstream commandBuffer;
	
	bool comment = false;
	bool quote = false;
	bool began = false;
	bool ended = false;
	size_t cursor = 0;
	
	while (cursor < scriptData.length() - 1) {
		if (ended)
			break;
		
		char nextChar = scriptData[cursor];
		
		cursor++;
		
		if (nextChar == '\t') //ignore tabs for indentation
			continue;
		
		if (comment && nextChar != '\n')
			continue;
		
		switch (nextChar) {
			case '#': {
				if (!quote)
					comment = true;
				break;
			}
			case '"': {
				if (opBuffer == INVALID_OP) {
					cout << "[LINE " << line << " ] Script error: Quote outside of argument." << endl;
					script.invalidate();
					return script;
				}
				
				if (!quote) {
					if (commandBuffer.str().length() > 0) {
						cout << "[LINE " << line << "] Script error: Floating quote." << endl;
						script.invalidate();
						return script;
					}
					
					commandBuffer << nextChar;
				} else {
					commandBuffer << nextChar;
					
					buf = commandBuffer.str();
					//cout << "[debug] read quoted argument '" << buf << "'" << endl;
					argListBuffer.emplace_back(buf);
					commandBuffer.str("");
				}
				
				quote = !quote;
				break;
			}
			case ' ': {
				buf = commandBuffer.str();
				
				if (buf.empty())
					break;
				
				if (opBuffer == INVALID_OP) {
					//cout << "[debug] read operation " << buf << endl;
					
					opBuffer = getOpcode(buf);
					
					switch (opBuffer) {
						case INVALID_OP: {
							cout << "[LINE " << line << "] Script error: Invalid operation '" << buf << "'." << endl;
							script.invalidate();
							return script;
						}
						case BEGIN_EXEC: {
							if (began) {
								cout << "[LINE " << line << "] Script error: Multiple BEGIN operations." << endl;
								script.invalidate();
								return script;
							}
							
							began = true;
							break;
						}
						case END_EXEC: {
							ended = true;
							
							break;
						}
						default: {
							if (!began) {
								cout << "[LINE " << line
								     << "] Script error: BEGIN operation not first main script operation." << endl;
								script.invalidate();
								return script;
							}
							break;
						}
					}
					commandBuffer.str("");
				} else {
					if (!quote) {
						//cout << "[debug] read argument '" << buf << "'" << endl;
						argListBuffer.emplace_back(buf);
						commandBuffer.str("");
					} else {
						commandBuffer << " ";
					}
				}
				
				break;
			}
			case ';': {
				buf = commandBuffer.str();
				
				if (opBuffer == INVALID_OP) {
					//cout << "[debug] read operation " << buf << " at semicolon" << endl;
					
					opBuffer = getOpcode(buf);
					switch (opBuffer) {
						case INVALID_OP: {
							cout << "[LINE " << line << "] Script error: Invalid operation '" << buf << "'." << endl;
							script.invalidate();
							return script;
						}
						case BEGIN_EXEC: {
							if (began) {
								cout << "[LINE " << line << "] Script error: Multiple BEGIN operations." << endl;
								script.invalidate();
								return script;
							}
							
							began = true;
							break;
						}
						case END_EXEC: {
							ended = true;
							
							break;
						}
						default: {
							if (!began) {
								cout << "[LINE " << line
								     << "] Script error: BEGIN operation not first main script operation." << endl;
								script.invalidate();
								return script;
							}
							break;
						}
					}
					
					if (Script::getOpType(opBuffer) != VOID_SCR) {
						cout << "[LINE " << line << "] Script error: Floating semicolon." << endl;
						script.invalidate();
						return script;
					}
				} else {
					if (quote) {
						cout << "[LINE " << line << "] Script error: Unterminated quote." << endl;
						script.invalidate();
						return script;
					}
					
					//cout << "[debug] read argument '" << buf << "' at semicolon" << endl;
					argListBuffer.emplace_back(buf);
				}
				
				commandBuffer.str("");
				
				//cout << "[debug] have " << argListBuffer.size() << " arguments for last op" << endl;
				bool success = script.addCommand(opBuffer, argListBuffer);
				opBuffer = INVALID_OP;
				
				argListBuffer.clear();
				
				if (!success) {
					cout << "[LINE " << line << "] Script error: Processing command failed." << endl;
					script.invalidate();
					return script;
				}
				break;
			}
			case '\n': {
				if (comment)
					comment = false;
				
				line++;
				break;
			}
			default: {
				commandBuffer << nextChar;
				break;
			}
		}
	}
	
	script.lockRO();
	return script;
}
