# Examples

The following is a list of examples of what you can expect from Numberrain.

Elementary math operations are omitted.

## Vector Mathematics

Adding 2 vectors:

```
❯ numberrain vadd 1,1,1 2,3,4
Numberrain version 0.1-dev8 by Arccotangent
Loading configuration from file: /home/user/.numberrain/config.json
Precision was set to 50 digits.
Numberrain show work is ENABLED (can be overridden by scripts)
Operation: vadd
Arguments (vectors): {     1i + 1j + 1k     2i + 3j + 4k     }
===================================================================================
[INFO] [VectorAddition] Adding vectors, starting with sum of 0 (zero vector).
[WORK] [VectorAddition] Sum is currently 0, after argument 0 (1i + 1j + 1k): (0) + (1i + 1j + 1k) = 1i + 1j + 1k
[WORK] [VectorAddition] Sum is currently 1i + 1j + 1k, after argument 1 (2i + 3j + 4k): (1i + 1j + 1k) + (2i + 3j + 4k) = 3i + 4j + 5k
===================================================================================
Time: 85 microseconds
Final result: 3i + 4j + 5k
```

Vector-scalar multiplication:

```
❯ numberrain vsmul 5 1,2,3
Numberrain version 0.1-dev8 by Arccotangent
Loading configuration from file: /home/user/.numberrain/config.json
Precision was set to 50 digits.
Numberrain show work is ENABLED (can be overridden by scripts)
Operation: vsmul
Arguments (vectors): {     5i     1i + 2j + 3k     }
===================================================================================
[INFO] [VectorScalarMultiplication] Multiplying scalar A, 5, by vector B, (1i + 2j + 3k).
[WORK] [VectorScalarMultiplication] Vector/Scalar Product = ABx * i + ABy * j + ABz * k // yields a vector value
[WORK] [VectorScalarMultiplication] Product x = 5 * 1 = 5
[WORK] [VectorScalarMultiplication] Product y = 5 * 2 = 10
[WORK] [VectorScalarMultiplication] Product z = 5 * 3 = 15
[WORK] [VectorScalarMultiplication] Final Product = 5i + 10j + 15k
===================================================================================
Time: 69 microseconds
Final result: 5i + 10j + 15k
```

Vector dot product:

```
❯ numberrain vdot 1,1,1 2,2,2
Numberrain version 0.1-dev8 by Arccotangent
Loading configuration from file: /home/user/.numberrain/config.json
Precision was set to 50 digits.
Numberrain show work is ENABLED (can be overridden by scripts)
Operation: vdot
Arguments (vectors): {     1i + 1j + 1k     2i + 2j + 2k     }
===================================================================================
[INFO] [VectorDotProduct] Calculating dot product of vectors A and B: (1i + 1j + 1k) and (2i + 2j + 2k).
[WORK] [VectorDotProduct] Dot Product = AxBx + AyBy + AzBz // yields a scalar value
[WORK] [VectorDotProduct] AxBx = 1 * 2 = 2
[WORK] [VectorDotProduct] AyBy = 1 * 2 = 2
[WORK] [VectorDotProduct] AzBz = 1 * 2 = 2
[WORK] [VectorDotProduct] Dot Product = 2 + 2 + 2 = 6
===================================================================================
Time: 66 microseconds
Final result: 6
```

Vector cross product:

```
❯ numberrain vcross 1,2,3 4,5,6
Numberrain version 0.1-dev8 by Arccotangent
Loading configuration from file: /home/user/.numberrain/config.json
Precision was set to 50 digits.
Numberrain show work is ENABLED (can be overridden by scripts)
Operation: vcross
Arguments (vectors): {     1i + 2j + 3k     4i + 5j + 6k     }
===================================================================================
[INFO] [VectorCrossProduct] Calculating cross product, starting with vector (1i + 2j + 3k).
[WORK] [VectorCrossProduct] Vector Cross Product = (AyBz - AzBy) * i + (AzBx - AxBz) * j + (AxBy - AyBx) * k // yields a vector value
[WORK] [VectorCrossProduct] Cross product is currently 1i + 2j + 3k, after argument 1 (4i + 5j + 6k): (1i + 2j + 3k) X (4i + 5j + 6k) = -3i + 6j - 3k
[WORK] [VectorCrossProduct] Work:
[WORK] [VectorCrossProduct] 	Coefficient i = (2 * 6) - (3 * 5) = -3
[WORK] [VectorCrossProduct] 	Coefficient j = (3 * 4) - (1 * 6) = 6
[WORK] [VectorCrossProduct] 	Coefficient k = (1 * 5) - (2 * 4) = -3
===================================================================================
Time: 58 microseconds
Final result: -3i + 6j - 3k
```

## Linear Algebra

Console output for matrices is considerably verbose looking, but there isn't much of another way to represent matrices
in a reasonably user-friendly way that warrants implementing complex code.

Matrix addition:

```
❯ numberrain madd 1,2,3/4,5,6/7,8,9 1,1,1/1,1,1/1,1,1
Numberrain version 0.1-dev8 by Arccotangent
Loading configuration from file: /home/user/.numberrain/config.json
Precision was set to 50 digits.
Numberrain show work is ENABLED (can be overridden by scripts)
Operation: madd
Arguments (matrices): {
[ 1 2 3 ]
[ 4 5 6 ]
[ 7 8 9 ]

[ 1 1 1 ]
[ 1 1 1 ]
[ 1 1 1 ]

}
===================================================================================
[INFO] [MatrixAddition] Adding matrices, starting with sum of:
[ 1 2 3 ]
[ 4 5 6 ]
[ 7 8 9 ]

[WORK] [MatrixAddition] Sum is currently:
[ 1 2 3 ]
[ 4 5 6 ]
[ 7 8 9 ]

after argument 1:
[ 1 1 1 ]
[ 1 1 1 ]
[ 1 1 1 ]

[ 1 2 3 ]
[ 4 5 6 ]
[ 7 8 9 ]
+
[ 1 1 1 ]
[ 1 1 1 ]
[ 1 1 1 ]
=
[ 2 3 4  ]
[ 5 6 7  ]
[ 8 9 10 ]


===================================================================================
Time: 294 microseconds
Final result: 
[ 2 3 4  ]
[ 5 6 7  ]
[ 8 9 10 ]

```

Matrix subtraction:

```
❯ numberrain msub 1,2,3/4,5,6/7,8,9 1,1,1/1,1,1/1,1,1
Numberrain version 0.1-dev8 by Arccotangent
Loading configuration from file: /home/user/.numberrain/config.json
Precision was set to 50 digits.
Numberrain show work is ENABLED (can be overridden by scripts)
Operation: msub
Arguments (matrices): {
[ 1 2 3 ]
[ 4 5 6 ]
[ 7 8 9 ]

[ 1 1 1 ]
[ 1 1 1 ]
[ 1 1 1 ]

}
===================================================================================
[INFO] [MatrixSubtraction] Subtracting matrices, starting from:
[ 1 2 3 ]
[ 4 5 6 ]
[ 7 8 9 ]

[WORK] [MatrixSubtraction] Difference is currently:
[ 1 2 3 ]
[ 4 5 6 ]
[ 7 8 9 ]

after argument 1:
[ 1 1 1 ]
[ 1 1 1 ]
[ 1 1 1 ]

[ 1 2 3 ]
[ 4 5 6 ]
[ 7 8 9 ]
+
[ 1 1 1 ]
[ 1 1 1 ]
[ 1 1 1 ]
=
[ 0 1 2 ]
[ 3 4 5 ]
[ 6 7 8 ]


===================================================================================
Time: 238 microseconds
Final result: 
[ 0 1 2 ]
[ 3 4 5 ]
[ 6 7 8 ]
```

Matrix multiplication:

```
❯ numberrain mmul 1,2,3/4,5,6/7,8,9 1,1,1/1,1,1/1,1,1
Numberrain version 0.1-dev8 by Arccotangent
Loading configuration from file: /home/user/.numberrain/config.json
Precision was set to 50 digits.
Numberrain show work is ENABLED (can be overridden by scripts)
Operation: mmul
Arguments (matrices): {
[ 1 2 3 ]
[ 4 5 6 ]
[ 7 8 9 ]

[ 1 1 1 ]
[ 1 1 1 ]
[ 1 1 1 ]

}
===================================================================================
[INFO] [MatrixMultiplication] Multiplying matrices, starting with:
[ 1 2 3 ]
[ 4 5 6 ]
[ 7 8 9 ]

[WORK] [MatrixMultiplication] NOTICE: Matrix multiplication can get quite messy! Try to bear with us here.
[WORK] [MatrixMultiplication] The product of these two matrices will have dimensions 3 x 3
[WORK] [MatrixMultiplication] Product entry at coordinate 0, 0 = (1 * 1) + (4 * 1) + (7 * 1)
[WORK] [MatrixMultiplication] Product entry at coordinate 0, 1 = (1 * 1) + (4 * 1) + (7 * 1)
[WORK] [MatrixMultiplication] Product entry at coordinate 0, 2 = (1 * 1) + (4 * 1) + (7 * 1)
[WORK] [MatrixMultiplication] Product entry at coordinate 1, 0 = (2 * 1) + (5 * 1) + (8 * 1)
[WORK] [MatrixMultiplication] Product entry at coordinate 1, 1 = (2 * 1) + (5 * 1) + (8 * 1)
[WORK] [MatrixMultiplication] Product entry at coordinate 1, 2 = (2 * 1) + (5 * 1) + (8 * 1)
[WORK] [MatrixMultiplication] Product entry at coordinate 2, 0 = (3 * 1) + (6 * 1) + (9 * 1)
[WORK] [MatrixMultiplication] Product entry at coordinate 2, 1 = (3 * 1) + (6 * 1) + (9 * 1)
[WORK] [MatrixMultiplication] Product entry at coordinate 2, 2 = (3 * 1) + (6 * 1) + (9 * 1)
[WORK] [MatrixMultiplication] Product is currently:
[ 1 2 3 ]
[ 4 5 6 ]
[ 7 8 9 ]

after argument 1:
[ 1 1 1 ]
[ 1 1 1 ]
[ 1 1 1 ]

[ 1 2 3 ]
[ 4 5 6 ]
[ 7 8 9 ]
*
[ 1 1 1 ]
[ 1 1 1 ]
[ 1 1 1 ]
=
[ 12 12 12 ]
[ 15 15 15 ]
[ 18 18 18 ]


===================================================================================
Time: 334 microseconds
Final result: 
[ 12 12 12 ]
[ 15 15 15 ]
[ 18 18 18 ]
```

Calculating the determinant of a 4x4 matrix (Numberrain uses the recursive definition of the determinant - so it works
with any square matrix, but expect spam on large matrices like this one):

```
❯ numberrain mdet 1,2,3,4/1,4,9,16/1,8,27,64/1,16,81,256
Numberrain version 0.1-dev8 by Arccotangent
Loading configuration from file: /home/user/.numberrain/config.json
Precision was set to 50 digits.
Numberrain show work is ENABLED (can be overridden by scripts)
Operation: mdet
Arguments (matrices): {
[ 1 2  3  4   ]
[ 1 4  9  16  ]
[ 1 8  27 64  ]
[ 1 16 81 256 ]

}
===================================================================================
[INFO] [MatrixDeterminant] Calculating the determinant of matrix:
[ 1 2  3  4   ]
[ 1 4  9  16  ]
[ 1 8  27 64  ]
[ 1 16 81 256 ]

[WORK] [MatrixDeterminant] NOTICE: With larger matrices, the determinant calculation can get very messy.
[WORK] [MatrixDeterminant] This implementation uses the recursive definition for the determinant of an NxN matrix.
[WORK] [MatrixDeterminant] To calculate the determinant of matrix:
[ 1 2  3  4   ]
[ 1 4  9  16  ]
[ 1 8  27 64  ]
[ 1 16 81 256 ]

we must first calculate the determinant of submatrix 1:
[ 4  9  16  ]
[ 8  27 64  ]
[ 16 81 256 ]

[WORK] [MatrixDeterminant] **********************************************************************************
[WORK] [MatrixDeterminant] RECURSING - LEVEL 1 - determinant of 3x3 matrix
[WORK] [MatrixDeterminant] **********************************************************************************
[WORK] [MatrixDeterminant] To calculate the determinant of matrix:
[ 4  9  16  ]
[ 8  27 64  ]
[ 16 81 256 ]

we must first calculate the determinant of submatrix 1:
[ 27 64  ]
[ 81 256 ]

[WORK] [MatrixDeterminant] **********************************************************************************
[WORK] [MatrixDeterminant] RECURSING - LEVEL 2 - determinant of 2x2 matrix
[WORK] [MatrixDeterminant] **********************************************************************************
[WORK] [MatrixDeterminant] Determinant of 2x2 matrix = ad - bc: (27 * 256) - (64 * 81) = 1728
[WORK] [MatrixDeterminant] Determinant of submatrix was 1728
[WORK] [MatrixDeterminant] Determinant of 3x3 matrix is: 0
Next step, add 0 + (4 * 1728) = 6912
[WORK] [MatrixDeterminant] To calculate the determinant of matrix:
[ 4  9  16  ]
[ 8  27 64  ]
[ 16 81 256 ]

we must first calculate the determinant of submatrix 2:
[ 8  64  ]
[ 16 256 ]

[WORK] [MatrixDeterminant] **********************************************************************************
[WORK] [MatrixDeterminant] RECURSING - LEVEL 2 - determinant of 2x2 matrix
[WORK] [MatrixDeterminant] **********************************************************************************
[WORK] [MatrixDeterminant] Determinant of 2x2 matrix = ad - bc: (8 * 256) - (64 * 16) = 1024
[WORK] [MatrixDeterminant] Determinant of submatrix was 1024
[WORK] [MatrixDeterminant] Determinant of 3x3 matrix is: 6912
Next step, subtract 6912 - (9 * 1024) = -2304
[WORK] [MatrixDeterminant] To calculate the determinant of matrix:
[ 4  9  16  ]
[ 8  27 64  ]
[ 16 81 256 ]

we must first calculate the determinant of submatrix 3:
[ 8  27 ]
[ 16 81 ]

[WORK] [MatrixDeterminant] **********************************************************************************
[WORK] [MatrixDeterminant] RECURSING - LEVEL 2 - determinant of 2x2 matrix
[WORK] [MatrixDeterminant] **********************************************************************************
[WORK] [MatrixDeterminant] Determinant of 2x2 matrix = ad - bc: (8 * 81) - (27 * 16) = 216
[WORK] [MatrixDeterminant] Determinant of submatrix was 216
[WORK] [MatrixDeterminant] Determinant of 3x3 matrix is: -2304
Next step, add -2304 + (16 * 216) = 1152
[WORK] [MatrixDeterminant] Determinant of matrix:
[ 4  9  16  ]
[ 8  27 64  ]
[ 16 81 256 ]

is 1152
[WORK] [MatrixDeterminant] Determinant of submatrix was 1152
[WORK] [MatrixDeterminant] Determinant of 4x4 matrix is: 0
Next step, add 0 + (1 * 1152) = 1152
[WORK] [MatrixDeterminant] To calculate the determinant of matrix:
[ 1 2  3  4   ]
[ 1 4  9  16  ]
[ 1 8  27 64  ]
[ 1 16 81 256 ]

we must first calculate the determinant of submatrix 2:
[ 1 9  16  ]
[ 1 27 64  ]
[ 1 81 256 ]

[WORK] [MatrixDeterminant] **********************************************************************************
[WORK] [MatrixDeterminant] RECURSING - LEVEL 1 - determinant of 3x3 matrix
[WORK] [MatrixDeterminant] **********************************************************************************
[WORK] [MatrixDeterminant] To calculate the determinant of matrix:
[ 1 9  16  ]
[ 1 27 64  ]
[ 1 81 256 ]

we must first calculate the determinant of submatrix 1:
[ 27 64  ]
[ 81 256 ]

[WORK] [MatrixDeterminant] **********************************************************************************
[WORK] [MatrixDeterminant] RECURSING - LEVEL 2 - determinant of 2x2 matrix
[WORK] [MatrixDeterminant] **********************************************************************************
[WORK] [MatrixDeterminant] Determinant of 2x2 matrix = ad - bc: (27 * 256) - (64 * 81) = 1728
[WORK] [MatrixDeterminant] Determinant of submatrix was 1728
[WORK] [MatrixDeterminant] Determinant of 3x3 matrix is: 0
Next step, add 0 + (1 * 1728) = 1728
[WORK] [MatrixDeterminant] To calculate the determinant of matrix:
[ 1 9  16  ]
[ 1 27 64  ]
[ 1 81 256 ]

we must first calculate the determinant of submatrix 2:
[ 1 64  ]
[ 1 256 ]

[WORK] [MatrixDeterminant] **********************************************************************************
[WORK] [MatrixDeterminant] RECURSING - LEVEL 2 - determinant of 2x2 matrix
[WORK] [MatrixDeterminant] **********************************************************************************
[WORK] [MatrixDeterminant] Determinant of 2x2 matrix = ad - bc: (1 * 256) - (64 * 1) = 192
[WORK] [MatrixDeterminant] Determinant of submatrix was 192
[WORK] [MatrixDeterminant] Determinant of 3x3 matrix is: 1728
Next step, subtract 1728 - (9 * 192) = 0
[WORK] [MatrixDeterminant] To calculate the determinant of matrix:
[ 1 9  16  ]
[ 1 27 64  ]
[ 1 81 256 ]

we must first calculate the determinant of submatrix 3:
[ 1 27 ]
[ 1 81 ]

[WORK] [MatrixDeterminant] **********************************************************************************
[WORK] [MatrixDeterminant] RECURSING - LEVEL 2 - determinant of 2x2 matrix
[WORK] [MatrixDeterminant] **********************************************************************************
[WORK] [MatrixDeterminant] Determinant of 2x2 matrix = ad - bc: (1 * 81) - (27 * 1) = 54
[WORK] [MatrixDeterminant] Determinant of submatrix was 54
[WORK] [MatrixDeterminant] Determinant of 3x3 matrix is: 0
Next step, add 0 + (16 * 54) = 864
[WORK] [MatrixDeterminant] Determinant of matrix:
[ 1 9  16  ]
[ 1 27 64  ]
[ 1 81 256 ]

is 864
[WORK] [MatrixDeterminant] Determinant of submatrix was 864
[WORK] [MatrixDeterminant] Determinant of 4x4 matrix is: 1152
Next step, subtract 1152 - (2 * 864) = -576
[WORK] [MatrixDeterminant] To calculate the determinant of matrix:
[ 1 2  3  4   ]
[ 1 4  9  16  ]
[ 1 8  27 64  ]
[ 1 16 81 256 ]

we must first calculate the determinant of submatrix 3:
[ 1 4  16  ]
[ 1 8  64  ]
[ 1 16 256 ]

[WORK] [MatrixDeterminant] **********************************************************************************
[WORK] [MatrixDeterminant] RECURSING - LEVEL 1 - determinant of 3x3 matrix
[WORK] [MatrixDeterminant] **********************************************************************************
[WORK] [MatrixDeterminant] To calculate the determinant of matrix:
[ 1 4  16  ]
[ 1 8  64  ]
[ 1 16 256 ]

we must first calculate the determinant of submatrix 1:
[ 8  64  ]
[ 16 256 ]

[WORK] [MatrixDeterminant] **********************************************************************************
[WORK] [MatrixDeterminant] RECURSING - LEVEL 2 - determinant of 2x2 matrix
[WORK] [MatrixDeterminant] **********************************************************************************
[WORK] [MatrixDeterminant] Determinant of 2x2 matrix = ad - bc: (8 * 256) - (64 * 16) = 1024
[WORK] [MatrixDeterminant] Determinant of submatrix was 1024
[WORK] [MatrixDeterminant] Determinant of 3x3 matrix is: 0
Next step, add 0 + (1 * 1024) = 1024
[WORK] [MatrixDeterminant] To calculate the determinant of matrix:
[ 1 4  16  ]
[ 1 8  64  ]
[ 1 16 256 ]

we must first calculate the determinant of submatrix 2:
[ 1 64  ]
[ 1 256 ]

[WORK] [MatrixDeterminant] **********************************************************************************
[WORK] [MatrixDeterminant] RECURSING - LEVEL 2 - determinant of 2x2 matrix
[WORK] [MatrixDeterminant] **********************************************************************************
[WORK] [MatrixDeterminant] Determinant of 2x2 matrix = ad - bc: (1 * 256) - (64 * 1) = 192
[WORK] [MatrixDeterminant] Determinant of submatrix was 192
[WORK] [MatrixDeterminant] Determinant of 3x3 matrix is: 1024
Next step, subtract 1024 - (4 * 192) = 256
[WORK] [MatrixDeterminant] To calculate the determinant of matrix:
[ 1 4  16  ]
[ 1 8  64  ]
[ 1 16 256 ]

we must first calculate the determinant of submatrix 3:
[ 1 8  ]
[ 1 16 ]

[WORK] [MatrixDeterminant] **********************************************************************************
[WORK] [MatrixDeterminant] RECURSING - LEVEL 2 - determinant of 2x2 matrix
[WORK] [MatrixDeterminant] **********************************************************************************
[WORK] [MatrixDeterminant] Determinant of 2x2 matrix = ad - bc: (1 * 16) - (8 * 1) = 8
[WORK] [MatrixDeterminant] Determinant of submatrix was 8
[WORK] [MatrixDeterminant] Determinant of 3x3 matrix is: 256
Next step, add 256 + (16 * 8) = 384
[WORK] [MatrixDeterminant] Determinant of matrix:
[ 1 4  16  ]
[ 1 8  64  ]
[ 1 16 256 ]

is 384
[WORK] [MatrixDeterminant] Determinant of submatrix was 384
[WORK] [MatrixDeterminant] Determinant of 4x4 matrix is: -576
Next step, add -576 + (3 * 384) = 576
[WORK] [MatrixDeterminant] To calculate the determinant of matrix:
[ 1 2  3  4   ]
[ 1 4  9  16  ]
[ 1 8  27 64  ]
[ 1 16 81 256 ]

we must first calculate the determinant of submatrix 4:
[ 1 4  9  ]
[ 1 8  27 ]
[ 1 16 81 ]

[WORK] [MatrixDeterminant] **********************************************************************************
[WORK] [MatrixDeterminant] RECURSING - LEVEL 1 - determinant of 3x3 matrix
[WORK] [MatrixDeterminant] **********************************************************************************
[WORK] [MatrixDeterminant] To calculate the determinant of matrix:
[ 1 4  9  ]
[ 1 8  27 ]
[ 1 16 81 ]

we must first calculate the determinant of submatrix 1:
[ 8  27 ]
[ 16 81 ]

[WORK] [MatrixDeterminant] **********************************************************************************
[WORK] [MatrixDeterminant] RECURSING - LEVEL 2 - determinant of 2x2 matrix
[WORK] [MatrixDeterminant] **********************************************************************************
[WORK] [MatrixDeterminant] Determinant of 2x2 matrix = ad - bc: (8 * 81) - (27 * 16) = 216
[WORK] [MatrixDeterminant] Determinant of submatrix was 216
[WORK] [MatrixDeterminant] Determinant of 3x3 matrix is: 0
Next step, add 0 + (1 * 216) = 216
[WORK] [MatrixDeterminant] To calculate the determinant of matrix:
[ 1 4  9  ]
[ 1 8  27 ]
[ 1 16 81 ]

we must first calculate the determinant of submatrix 2:
[ 1 27 ]
[ 1 81 ]

[WORK] [MatrixDeterminant] **********************************************************************************
[WORK] [MatrixDeterminant] RECURSING - LEVEL 2 - determinant of 2x2 matrix
[WORK] [MatrixDeterminant] **********************************************************************************
[WORK] [MatrixDeterminant] Determinant of 2x2 matrix = ad - bc: (1 * 81) - (27 * 1) = 54
[WORK] [MatrixDeterminant] Determinant of submatrix was 54
[WORK] [MatrixDeterminant] Determinant of 3x3 matrix is: 216
Next step, subtract 216 - (4 * 54) = 0
[WORK] [MatrixDeterminant] To calculate the determinant of matrix:
[ 1 4  9  ]
[ 1 8  27 ]
[ 1 16 81 ]

we must first calculate the determinant of submatrix 3:
[ 1 8  ]
[ 1 16 ]

[WORK] [MatrixDeterminant] **********************************************************************************
[WORK] [MatrixDeterminant] RECURSING - LEVEL 2 - determinant of 2x2 matrix
[WORK] [MatrixDeterminant] **********************************************************************************
[WORK] [MatrixDeterminant] Determinant of 2x2 matrix = ad - bc: (1 * 16) - (8 * 1) = 8
[WORK] [MatrixDeterminant] Determinant of submatrix was 8
[WORK] [MatrixDeterminant] Determinant of 3x3 matrix is: 0
Next step, add 0 + (9 * 8) = 72
[WORK] [MatrixDeterminant] Determinant of matrix:
[ 1 4  9  ]
[ 1 8  27 ]
[ 1 16 81 ]

is 72
[WORK] [MatrixDeterminant] Determinant of submatrix was 72
[WORK] [MatrixDeterminant] Determinant of 4x4 matrix is: 576
Next step, subtract 576 - (4 * 72) = 288
[WORK] [MatrixDeterminant] Determinant of matrix:
[ 1 2  3  4   ]
[ 1 4  9  16  ]
[ 1 8  27 64  ]
[ 1 16 81 256 ]

is 288
===================================================================================
Time: 3103 microseconds
Final result: 
288
```

## Scripts

Ackermann function (specifically `ack(2, 2)` - the script for this is in the example-scripts folder):

```
❯ numberrain exec example-scripts/ackermann.nrs 2 2
Numberrain version 0.1-dev8 by Arccotangent
Loading configuration from file: /home/user/.numberrain/config.json
Precision was set to 50 digits.
Numberrain show work is ENABLED (can be overridden by scripts)
Operation: exec
Arguments (strings): {     example-scripts/ackermann.nrs     2     2     }
===================================================================================
Script file: example-scripts/ackermann.nrs
Script size: 815 bytes
Script precision set to 10 decimal digits.
Script execution has begun.
evaluating ack(2, 2) now...
[INFO] [Subtraction] Subtracting numbers, starting from 2.
[INFO] [Subtraction] Subtracting numbers, starting from 1.
[INFO] [Subtraction] Subtracting numbers, starting from 2.
[INFO] [Subtraction] Subtracting numbers, starting from 1.
[INFO] [Subtraction] Subtracting numbers, starting from 1.
[INFO] [Addition] Adding numbers, starting with sum of 1.
[INFO] [Subtraction] Subtracting numbers, starting from 1.
[INFO] [Addition] Adding numbers, starting with sum of 2.
[INFO] [Subtraction] Subtracting numbers, starting from 2.
[INFO] [Subtraction] Subtracting numbers, starting from 3.
[INFO] [Subtraction] Subtracting numbers, starting from 2.
[INFO] [Subtraction] Subtracting numbers, starting from 1.
[INFO] [Subtraction] Subtracting numbers, starting from 1.
[INFO] [Addition] Adding numbers, starting with sum of 1.
[INFO] [Subtraction] Subtracting numbers, starting from 1.
[INFO] [Addition] Adding numbers, starting with sum of 2.
[INFO] [Subtraction] Subtracting numbers, starting from 1.
[INFO] [Addition] Adding numbers, starting with sum of 3.
[INFO] [Subtraction] Subtracting numbers, starting from 1.
[INFO] [Addition] Adding numbers, starting with sum of 4.
[INFO] [Subtraction] Subtracting numbers, starting from 2.
[INFO] [Subtraction] Subtracting numbers, starting from 5.
[INFO] [Subtraction] Subtracting numbers, starting from 4.
[INFO] [Subtraction] Subtracting numbers, starting from 3.
[INFO] [Subtraction] Subtracting numbers, starting from 2.
[INFO] [Subtraction] Subtracting numbers, starting from 1.
[INFO] [Subtraction] Subtracting numbers, starting from 1.
[INFO] [Addition] Adding numbers, starting with sum of 1.
[INFO] [Subtraction] Subtracting numbers, starting from 1.
[INFO] [Addition] Adding numbers, starting with sum of 2.
[INFO] [Subtraction] Subtracting numbers, starting from 1.
[INFO] [Addition] Adding numbers, starting with sum of 3.
[INFO] [Subtraction] Subtracting numbers, starting from 1.
[INFO] [Addition] Adding numbers, starting with sum of 4.
[INFO] [Subtraction] Subtracting numbers, starting from 1.
[INFO] [Addition] Adding numbers, starting with sum of 5.
[INFO] [Subtraction] Subtracting numbers, starting from 1.
[INFO] [Addition] Adding numbers, starting with sum of 6.
ack(2, 2) = 7
Script execution has ended.
===================================================================================
Time: 1611 microseconds
Final result: Numberrain script terminated
```

Using the Chudnovsky algorithm to calculate Pi to high precision (console output was suppressed by the script - this is
also available in the example-scripts folder):

```
❯ numberrain exec example-scripts/chudnovsky-pi.nrs
Numberrain version 0.1-dev8 by Arccotangent
Loading configuration from file: /home/user/.numberrain/config.json
Precision was set to 50 digits.
Numberrain show work is ENABLED (can be overridden by scripts)
Operation: exec
Arguments (strings): {     example-scripts/chudnovsky-pi.nrs     }
===================================================================================
Script file: example-scripts/chudnovsky-pi.nrs
Script size: 1528 bytes
Script precision set to 100 decimal digits.
Script execution has begun.

we used 2 terms of the chudnovsky algorithm
calculated value for pi is 3.1415926535897346995917385065025408571403044963888211236033994378576235090161788143494518002735912954
real value for pi is       3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117068

Script execution has ended.
===================================================================================
Time: 1017 microseconds
Final result: Numberrain script terminated
```
