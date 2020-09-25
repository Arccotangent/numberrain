# VSMUL

`VSMUL` is a mathematical operation.

## Description

`VSMUL` takes 2 arguments (a scalar and a vector) and multiplies the vector by the scalar.

Internally, both arguments are vectors, but the first "scalar" argument's y and z are ignored (only its x is used).

## Usage

`VSMUL <scalar> <vector>;`

## Examples

`VSMUL 4 2,2,2;` - Multiplies (2i + 2j + 2k) * 4 and stores the result in the result register.
