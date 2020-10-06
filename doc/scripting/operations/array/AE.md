# AE

`AE` is an array operation.

## Description

`AE` takes 2 arguments, an array and an integer, and extracts the element at the given position from the array. The
value is stored in the result register.

Index counting starts at 0.

Passing an index that is out of bounds (eg. attempting to extract the 5th element in a 3 element array) will cause your
script to crash.

By extension, using `AE` on an empty array will cause your script to crash.

## Usage

`AE <array> <index>;`

## Examples

`AE myArray 0;` - Retrieve the first element from `myArray` and store it in the result register.
