# MDET

`MDET` is a mathematical operation.

## Description

`MDET` takes 1 matrix argument and calculates its determinant. The determinant is stored in the result register.

Matrices passed to `MDET` must be square because determinants are defined for only square matrices. Passing a non-square
matrix to `MDET` will cause your script to crash.

## Usage

`MDET <matrix>;`
