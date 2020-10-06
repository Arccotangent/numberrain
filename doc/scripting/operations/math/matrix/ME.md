# ME

`ME` is a special operation.

## Description

`ME` takes 3 arguments, 1 matrix and 2 integers, and extracts the value at the specified coordinates from the matrix.
The value is stored in the result register.

Row and column index counting starts from 0.

## Usage

`ME <matrix> <x> <y>;`

## Examples

`ME matrix 0 0;` - Extract the value at the very top left of `matrix`.
