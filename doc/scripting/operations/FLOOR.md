# FLOOR

`FLOOR` is a mathematical operation.

## Description

`FLOOR` accepts 1 real number argument and rounds it down.
If the argument is an integer, `FLOOR` has no effect.

Passing vectors directly to `FLOOR` will cause your script to crash.
At the moment, rounding vector coefficients must be done individually, then reconstruct the vector using `VC`.

## Usage

`FLOOR <number>;`

## Examples

`FLOOR 3.1;` - Rounds down to `3` and stores the result in the result register.

`FLOOR 3.9;` - Same result as above.
