# CMP

`CMP` is a control flow operation.

## Description

`CMP` takes 2 real number arguments and compares them.
The result is stored in the comparison register.

`CMP` does not accept vectors.

## Usage

`CMP <number 1> <number 2>;`

## Examples

`CMP 2 5;` - Compares `2` and `5` and stores the result in the comparison register.
In this case, the result would be "less than" because 2 is less than 5.
