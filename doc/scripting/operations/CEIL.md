# CEIL

`CEIL` is a mathematical operation.

## Description

`CEIL` accepts 1 real number argument and rounds it up.
If the argument is an integer, `CEIL` has no effect.

Passing vectors directly to `CEIL` will cause your script to crash.
At the moment, rounding vector coefficients must be done individually, then reconstruct the vector using `VC`.

## Usage

`CEIL <number>;`

## Examples

`CEIL 3.1;` - Rounds up to `4` and stores the result in the result register.

`CEIL 3.9;` - Same result as above.
