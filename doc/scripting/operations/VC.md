# VC

`VC` is a special operation.

## Description

`VC` takes 1-3 arguments in (x, y, z) order, constructs a vector from them, and stores the vector in the result register.
It can be used to construct vectors from variables.

The y and z parameters are optional and default to 0 if omitted.

`VC` can be thought of as the vector equivalent of `NOP`.

## Usage

`VC <x> [y] [z];`

## Examples

`VC 5 1;` - Stores a vector with value `(5i + j)` in the result register.

`VC 2 3 4;` - Stores a vector with value `(2i + 3j + 4k)` in the result register.
