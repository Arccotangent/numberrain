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

#ifndef NUMBERRAIN_LOGGER_H
#define NUMBERRAIN_LOGGER_H

#include <cstdio>
#include <string>
#include <cstdarg>
#include "../GlobalVars.h"

class Logger {
private:
	std::string tag;
	
	static std::string format(const char *msg, va_list args);

public:
	explicit Logger(const std::string &tag);
	
	void e(const char *msg, ...);
	
	void w(const char *msg, ...);
	
	void i(const char *msg, ...);
	
	void d(const char *msg, ...);
	
	void r(const char *msg, ...);
};


#endif //NUMBERRAIN_LOGGER_H
