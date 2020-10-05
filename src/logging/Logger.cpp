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

#include "Logger.h"

using namespace std;

Logger::Logger(const string &tag) {
	this->tag = tag;
}

std::string Logger::format(const char *msg, va_list args) {
	va_list args2;
	va_copy(args2, args);
	
	size_t size = vsnprintf(nullptr, 0, msg, args) + 1;
	auto *str = (char *) malloc(size);
	vsnprintf(str, size, msg, args2);
	
	return std::string(str);
}

void Logger::e(const char *msg, ...) {
	va_list args;
	va_start(args, msg);
	
	std::string formatted = format(msg, args);
	
	printf("[ERROR] [%s] %s\n", tag.c_str(), formatted.c_str());
	va_end(args);
}

void Logger::w(const char *msg, ...) {
	va_list args;
	va_start(args, msg);
	
	std::string formatted = format(msg, args);
	
	printf("[WARN] [%s] %s\n", tag.c_str(), formatted.c_str());
	va_end(args);
}

void Logger::i(const char *msg, ...) {
	if (!GlobalVars::getInstance()->shouldLogToConsole())
		return;
	
	va_list args;
	va_start(args, msg);
	
	std::string formatted = format(msg, args);
	
	printf("[INFO] [%s] %s\n", tag.c_str(), formatted.c_str());
	va_end(args);
}

void Logger::d(const char *msg, ...) {
	va_list args;
	va_start(args, msg);
	
	std::string formatted = format(msg, args);
	
	printf("[DEBUG] [%s] %s\n", tag.c_str(), formatted.c_str());
	va_end(args);
}

void Logger::r(const char *msg, ...) {
	if (!GlobalVars::getInstance()->shouldShowWork() || !GlobalVars::getInstance()->shouldLogToConsole())
		return;
	
	va_list args;
	va_start(args, msg);
	
	std::string formatted = format(msg, args);
	
	printf("[WORK] [%s] %s\n", tag.c_str(), formatted.c_str());
	va_end(args);
}