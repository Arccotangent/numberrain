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

#include "MatrixMultiplication.h"

using namespace std;

Logger MatrixMultiplication::log = Logger("MatrixMultiplication");

long MatrixMultiplication::eval() {
	auto start = chrono::system_clock::now();
	
	Matrix product = arguments[0];
	log.i("Multiplying matrices, starting with:\n%s", fmt(product).c_str());
	log.r("NOTICE: Matrix multiplication can get quite messy! Try to bear with us here.");
	
	for (size_t i = 1; i < arguments.size(); i++) {
		Matrix arg = arguments[i];
		
		size_t aX = product.getMatrixDimensions().first;
		size_t aY = product.getMatrixDimensions().second;
		size_t bX = arg.getMatrixDimensions().first;
		size_t bY = arg.getMatrixDimensions().second;
		
		if (aY != bX) {
			log.e("Matrix dimensions do not match! Multiplication of these two matrices is impossible.");
			log.e("Matrix 1 dimensions (x, y) = %i x %i", aX, aY);
			log.e("Matrix 2 dimensions (x, y) = %i x %i", bX, bY);
			log.e("Matrix 1's y must match matrix 2's x.");
			log.e("Remember matrix multiplication is not commutative.");
			log.e("Zeroing out product and aborting.");
			
			product = Matrix();
			break;
		}
		
		size_t n = aY; //or bX
		
		log.r("The product of these two matrices will have dimensions %i x %i", aX, bY);
		
		RealMatrix prodMtx;
		prodMtx.reserve(arg.getMatrixDimensions().second);
		
		for (size_t x = 0; x < aX; x++) {
			vector<Real> row;
			
			for (size_t y = 0; y < bY; y++) {
				stringstream ss;
				ss << "Product entry at coordinate " << x << ", " << y << " = ";
				
				Real prodEntry = 0;
				
				for (size_t pos = 0; pos < n; pos++) {
					Real entryA = product.get(x, pos);
					Real entryB = arg.get(pos, y);
					
					if (pos > 0) {
						ss << " + ";
					}
					
					ss << "(" << entryA << " * " << entryB << ")";
					
					prodEntry += entryA * entryB;
				}
				
				log.r(ss.str().c_str());
				row.emplace_back(prodEntry);
			}
			
			prodMtx.emplace_back(row);
		}
		
		Matrix *newProd = Matrix::createMatrix(prodMtx, false);
		
		if (newProd == nullptr) {
			log.e("Error occurred while creating new product matrix!");
			log.e("Zeroing out product and aborting.");
			
			product = Matrix();
			break;
		}
		
		log.r("Product is currently:\n%s\nafter argument %i:\n%s\n%s*\n%s=\n%s\n", fmt(product).c_str(), i,
		      fmt(arg).c_str(),
		      fmt(product).c_str(), fmt(arg).c_str(), fmt(*newProd).c_str());
		product = *newProd;
	}
	
	auto end = chrono::system_clock::now();
	
	result = product;
	
	return chrono::duration_cast<chrono::microseconds>(end - start).count();
}
