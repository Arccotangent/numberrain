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

#ifndef NUMBERRAIN_MATRIX_H
#define NUMBERRAIN_MATRIX_H

#include "../Structures.h"
#include <vector>

typedef std::vector<std::vector<Real>> RealMatrix;
typedef std::pair<size_t, size_t> Dimensions;

class Matrix {
private:
	RealMatrix matrix;
	bool real = false;
	
	Matrix(const RealMatrix &matrix, bool isReal);
	
	static bool verifyDimensions(const RealMatrix &matrix, bool isReal);
	
	static bool dimensionsEqual(Dimensions a, Dimensions b);

public:
	Matrix() = default;
	
	static Matrix *createMatrix(const RealMatrix &matrix, bool isReal);
	
	static Matrix *createMatrix(const Real &num);
	
	[[nodiscard]] bool isReal() const;
	
	[[nodiscard]] RealMatrix getMatrix() const;
	
	[[nodiscard]] Dimensions getMatrixDimensions() const;
	
	[[nodiscard]] Real get(size_t x, size_t y) const;
	
	std::vector<Real> operator[](size_t y) const;
	
	Matrix operator+(const Matrix &other) const;
	
	Matrix operator-(const Matrix &other) const;
};

static Matrix *parseMatrix(const std::string &value) {
	RealMatrix matrixRaw;
	
	bool consoleFormatted = value.find('[') != std::string::npos;
	
	std::vector<std::string> rowStrings;
	boost::algorithm::split(rowStrings, value, boost::algorithm::is_any_of(consoleFormatted ? "\n" : "/"));
	
	std::string charsToRemove = "[]";
	
	for (auto &rowStr : rowStrings) {
		if (consoleFormatted) {
			rowStr.erase(std::remove_if(rowStr.begin(), rowStr.end(), [charsToRemove](char ch) {
				return charsToRemove.find(ch) != std::string::npos;
			}), rowStr.end());
			
			boost::replace_all(rowStr, " ", ",");
			boost::replace_all(rowStr, ",,", ",");
			
			if (rowStr.length() >= 2) {
				rowStr = rowStr.substr(1, rowStr.length() - 2);
			}
		}
		
		//std::cout << "[debug] parseMatrix rowStr = " << rowStr << std::endl;
		
		if (rowStr == "," || rowStr.empty())
			continue;
		
		std::vector<std::string> columnStrings;
		boost::algorithm::split(columnStrings, rowStr, boost::algorithm::is_any_of(","));
		
		std::vector<Real> row;
		for (const auto &columnStr : columnStrings) {
			row.emplace_back(Real(columnStr));
		}
		
		matrixRaw.emplace_back(row);
	}
	
	Matrix *matrix = Matrix::createMatrix(matrixRaw, matrixRaw.size() == 1 && matrixRaw[0].size() == 1);
	if (matrix == nullptr) {
		throw std::runtime_error("error occurred during matrix creation");
	}
	
	return matrix;
}

static std::string fmt(const Matrix &matrix) {
	if (matrix.isReal()) {
		return fmt(matrix[0][0]);
	}
	
	std::stringstream ss;
	
	Dimensions dim = matrix.getMatrixDimensions();
	
	if (dim.first == 0 || dim.second == 0) {
		return "[ ]";
	}
	
	std::vector<size_t> printColumns;
	
	printColumns.emplace_back(2);
	
	std::vector<std::vector<std::string>> numStrings;
	size_t longestNumLength;
	
	for (size_t x = 0; x < dim.first; x++) {
		longestNumLength = 0;
		
		for (size_t y = 0; y < dim.second; y++) {
			std::string numStr = fmt(matrix.get(x, y));
			
			if (numStr.length() > longestNumLength) {
				longestNumLength = numStr.length();
			}
		}
		
		printColumns.emplace_back(printColumns[printColumns.size() - 1] + longestNumLength + 1);
	}
	
	for (size_t y = 0; y < dim.second; y++) {
		std::vector<std::string> numStrLine;
		
		for (size_t x = 0; x < dim.first; x++) {
			std::string numStr = fmt(matrix.get(x, y));
			numStrLine.emplace_back(numStr);
		}
		
		numStrings.emplace_back(numStrLine);
	}
	
	std::stringstream spacingStream;
	
	for (size_t spaces = 0; spaces < longestNumLength; spaces++)
		spacingStream << " ";
	
	std::string spacing = spacingStream.str();
	
	std::vector<std::string> lines;
	
	size_t longestLineLength = 0;
	
	for (size_t y = 0; y < dim.second; y++) {
		std::stringstream lineStream;
		lineStream << "[ ";
		for (size_t x = 0; x < dim.first; x++) {
			while (lineStream.str().length() < printColumns[x]) {
				lineStream << " ";
			}
			lineStream << fmt(matrix.get(x, y));
		}
		
		std::string line = lineStream.str();
		lines.emplace_back(line);
		
		if (line.length() > longestLineLength) {
			longestLineLength = line.length();
		}
	}
	
	for (const auto &line : lines) {
		ss << line;
		if (line.length() < longestLineLength) {
			for (size_t i = 0; i < longestLineLength - line.length(); i++) {
				ss << " ";
			}
		}
		ss << " ]\n";
	}
	
	return ss.str();
}


#endif //NUMBERRAIN_MATRIX_H
