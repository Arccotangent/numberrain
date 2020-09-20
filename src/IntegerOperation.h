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

#ifndef NUMBERRAIN_INTEGEROPERATION_H
#define NUMBERRAIN_INTEGEROPERATION_H

#include <vector>
#include <chrono>
#include <iostream>
#include "Structures.h"

class IntegerOperation {
protected:
	std::vector<Integer> arguments;
	Integer result = 0;

public:
	explicit IntegerOperation(const std::vector<Integer> &arguments);
	
	virtual long eval() = 0;
	
	[[nodiscard]] Integer getResult() const;
};


#endif //NUMBERRAIN_INTEGEROPERATION_H
