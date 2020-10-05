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

#include "MatrixDeterminant.h"

using namespace std;

Logger MatrixDeterminant::log = Logger("MatrixDeterminant");
bool MatrixDeterminant::invalidated = false;

Real MatrixDeterminant::calcDet(const Matrix &matrix, unsigned int levels) {
	if (invalidated)
		return 0;
	
	size_t size = matrix.getMatrixDimensions().first;
	
	if (levels > 0) {
		log.r("**********************************************************************************");
		log.r("RECURSING - LEVEL %i - determinant of %ix%i matrix", levels, size, size);
		log.r("**********************************************************************************");
	}
	
	if (size == 2) {
		//base case - determinant of a 2x2 matrix = ad - bc
		Real a = matrix[0][0];
		Real b = matrix[0][1];
		Real c = matrix[1][0];
		Real d = matrix[1][1];
		
		Real det = (a * d) - (b * c);
		
		log.r("Determinant of 2x2 matrix = ad - bc: (%s * %s) - (%s * %s) = %s", fmt(a).c_str(), fmt(d).c_str(),
		      fmt(b).c_str(), fmt(c).c_str(), fmt(det).c_str());
		return det;
	}
	
	Real det = 0;
	bool add = true;
	
	for (size_t column = 0; column < size; column++) {
		Real coeff = matrix.get(column, 0);
		
		RealMatrix subMatrix;
		subMatrix.reserve(size - 1);
		
		for (size_t y = 1; y < size; y++) {
			vector<Real> row;
			
			for (size_t x = 0; x < size; x++) {
				if (x == column)
					continue;
				row.emplace_back(matrix.get(x, y));
			}
			
			subMatrix.emplace_back(row);
		}
		
		Matrix *subMtx = Matrix::createMatrix(subMatrix, false);
		if (subMtx == nullptr) {
			log.e("Error occurred while creating submatrix!");
			log.e("Zeroing out determinant and aborting.");
			
			invalidated = true;
			log.e("Your determinant will be incorrect.");
			return 0;
		}
		
		log.r("To calculate the determinant of matrix:\n%s\nwe must first calculate the determinant of submatrix %i:\n%s",
		      fmt(matrix).c_str(), column + 1, fmt(*subMtx).c_str());
		
		Real subDet = calcDet(*subMtx, levels + 1);
		log.r("Determinant of submatrix was %s", fmt(subDet).c_str());
		Real detBuf = coeff * subDet;
		
		if (!add)
			detBuf *= -1;
		
		Real newDet = det + detBuf;
		
		if (add) {
			log.r("Determinant of %ix%i matrix is: %s\nNext step, add %s + (%s * %s) = %s", size, size,
			      fmt(det).c_str(), fmt(det).c_str(), fmt(coeff).c_str(), fmt(subDet).c_str(), fmt(newDet).c_str());
		} else {
			log.r("Determinant of %ix%i matrix is: %s\nNext step, subtract %s - (%s * %s) = %s", size, size,
			      fmt(det).c_str(), fmt(det).c_str(), fmt(coeff).c_str(), fmt(subDet).c_str(), fmt(newDet).c_str());
		}
		
		det = newDet;
		
		add = !add;
	}
	
	log.r("Determinant of matrix:\n%s\nis %s", fmt(matrix).c_str(), fmt(det).c_str());
	
	return det;
}

long MatrixDeterminant::eval() {
	auto start = chrono::system_clock::now();
	
	Matrix matrix = arguments[0];
	if (matrix.getMatrixDimensions().first != matrix.getMatrixDimensions().second) {
		log.e("This matrix is not a square matrix! Calculating the determinant is impossible.");
		result = Matrix();
		
		auto end = chrono::system_clock::now();
		return chrono::duration_cast<chrono::microseconds>(end - start).count();
	}
	
	log.i("Calculating the determinant of matrix:\n%s", fmt(matrix).c_str());
	log.r("NOTICE: With larger matrices, the determinant calculation can get very messy.");
	log.r("This implementation uses the recursive definition for the determinant of an NxN matrix.");
	
	Real determinant = calcDet(matrix, 0);
	
	if (invalidated) {
		log.w("Something went wrong during the calculation process - this determinant is incorrect.");
	}
	
	Matrix *determinantMtx = Matrix::createMatrix(determinant);
	
	auto end = chrono::system_clock::now();
	
	if (determinantMtx == nullptr) {
		log.e("Error occurred while creating result matrix!");
		return chrono::duration_cast<chrono::microseconds>(end - start).count();
	}
	
	result = *determinantMtx;
	
	return chrono::duration_cast<chrono::microseconds>(end - start).count();
}

