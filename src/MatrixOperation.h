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

#ifndef NUMBERRAIN_MATRIXOPERATION_H
#define NUMBERRAIN_MATRIXOPERATION_H

#include <vector>
#include <chrono>
#include <iostream>
#include "logging/Logger.h"
#include "Structures.h"
#include "matrix/Matrix.h"

class MatrixOperation {
protected:
	std::vector<Matrix> arguments;
	Matrix result;

public:
	explicit MatrixOperation(const std::vector<Matrix> &arguments);
	
	virtual long eval() = 0;
	
	[[nodiscard]] Matrix getResult() const;
};


#endif //NUMBERRAIN_MATRIXOPERATION_H
