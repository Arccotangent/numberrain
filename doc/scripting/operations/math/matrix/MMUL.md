# MMUL

`MMUL` is a mathematical operation.

## Description

`MMUL` takes at least 2 matrix arguments and multiplies them from left to right. The final product is stored in the
result register.

Special Note A: While it is possible to pass more than 2 matrices to `MMUL`, all arguments must be compatible. Matrix
multiplication is not defined for all matrices. The matrices' "inner dimensions" have to be equal for matrix
multiplication to be possible.

Special Note B: Mind the order of the arguments. Matrix multiplication is not commutative.

Passing incompatible matrices to `MMUL` will cause your script to crash.

## Usage

`MMUL <matrix 1> <matrix 2> ... [matrix n];`
