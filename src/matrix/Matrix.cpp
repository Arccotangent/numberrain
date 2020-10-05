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

Matrix::Matrix(const RealMatrix &matrix, bool isReal) {
	this->matrix = matrix;
	this->real = isReal;
}

bool Matrix::verifyDimensions(const RealMatrix &matrix, bool isReal) {
	size_t y = matrix.size();
	if (y == 0)
		return false;
	
	size_t initialX = matrix[0].size();
	bool allRowsSameLength = all_of(matrix.begin(), matrix.end(), [&](const vector<Real> &row) {
		return row.size() == initialX;
	});
	
	return isReal ? y == 1 && initialX == 1 : allRowsSameLength;
}

bool Matrix::dimensionsEqual(Dimensions a, Dimensions b) {
	return a.first == b.first && a.second == b.second;
}

Matrix *Matrix::createMatrix(const RealMatrix &matrix, bool isReal) {
	if (!verifyDimensions(matrix, isReal)) {
		return nullptr;
	}
	
	return new Matrix(matrix, isReal);
}

Matrix *Matrix::createMatrix(const Real &num) {
	RealMatrix mtx;
	
	vector<Real> row;
	row.emplace_back(num);
	
	mtx.emplace_back(row);
	
	return new Matrix(mtx, true);
}

bool Matrix::isReal() const {
	return real;
}

RealMatrix Matrix::getMatrix() const {
	return matrix;
}

Dimensions Matrix::getMatrixDimensions() const {
	if (matrix.empty()) {
		return {0, 0};
	}
	
	return {matrix[0].size(), matrix.size()};
}

Real Matrix::get(size_t x, size_t y) const {
	if (y >= matrix.size() || x >= matrix[y].size()) {
		throw runtime_error("Matrix coordinates out of bounds");
	}
	
	return matrix[y][x];
}

vector<Real> Matrix::operator[](size_t y) const {
	if (y >= matrix.size()) {
		throw runtime_error("Matrix coordinates out of bounds");
	}
	
	return matrix[y];
}

Matrix Matrix::operator+(const Matrix &other) const {
	if (!dimensionsEqual(this->getMatrixDimensions(), other.getMatrixDimensions())) {
		throw runtime_error("Attempted to add matrices of unequal dimensions!");
	}
	
	size_t xTotal = this->getMatrixDimensions().first;
	size_t yTotal = this->getMatrixDimensions().second;
	
	RealMatrix sum;
	
	for (size_t y = 0; y < yTotal; y++) {
		vector<Real> row;
		for (size_t x = 0; x < xTotal; x++) {
			row.emplace_back(get(x, y) + other.get(x, y));
		}
		
		sum.emplace_back(row);
	}
	
	Matrix *sumMatrix = createMatrix(sum, other.isReal());
	
	if (sumMatrix == nullptr) {
		throw runtime_error("Constructing sum matrix failed!");
	}
	
	return *sumMatrix;
}

Matrix Matrix::operator-(const Matrix &other) const {
	if (!dimensionsEqual(this->getMatrixDimensions(), other.getMatrixDimensions())) {
		throw runtime_error("Attempted to subtract matrices of unequal dimensions!");
	}
	
	size_t xTotal = this->getMatrixDimensions().first;
	size_t yTotal = this->getMatrixDimensions().second;
	
	RealMatrix difference;
	
	for (size_t y = 0; y < yTotal; y++) {
		vector<Real> row;
		for (size_t x = 0; x < xTotal; x++) {
			row.emplace_back(get(x, y) - other.get(x, y));
		}
		
		difference.emplace_back(row);
	}
	
	Matrix *differenceMatrix = createMatrix(difference, other.isReal());
	
	if (differenceMatrix == nullptr) {
		throw runtime_error("Constructing difference matrix failed!");
	}
	
	return *differenceMatrix;
}
