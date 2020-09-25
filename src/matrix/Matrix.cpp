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

#include "Matrix.h"

using namespace std;

Matrix::Matrix(const RealMatrix &matrix) {
	this->matrix = matrix;
}

bool Matrix::verifyDimensions(const RealMatrix &matrix) {
	size_t y = matrix.size();
	if (y == 0)
		return false;
	
	size_t initialX = matrix[0].size();
	bool allRowsSameLength = all_of(matrix.begin(), matrix.end(), [&](const vector<Real> &row) {
		return row.size() == initialX;
	});
	
	return allRowsSameLength;
}

Matrix *Matrix::createMatrix(const RealMatrix &matrix) {
	if (!verifyDimensions(matrix)) {
		return nullptr;
	}
	
	return new Matrix(matrix);
}

RealMatrix Matrix::getMatrix() {
	return matrix;
}

Dimensions Matrix::getMatrixDimensions() {
	return {matrix[0].size(), matrix.size()};
}

Real Matrix::getElementAt(size_t x, size_t y) {
	if (y >= matrix.size() || x >= matrix[y].size()) {
		throw runtime_error("Matrix coordinates out of bounds");
	}
	
	return matrix[y][x];
}
