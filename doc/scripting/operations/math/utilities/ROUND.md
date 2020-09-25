# ROUND

`ROUND` is a mathematical operation.

## Description

`ROUND` accepts 1 real number argument and rounds it up or down depending on its decimal component.
If the number's first decimal digit is 5 or greater, `ROUND` will round it up.
Otherwise, it will round down.
If the argument is an integer, `ROUND` has no effect.

Passing vectors directly to `ROUND` will cause your script to crash.
At the moment, rounding vector coefficients must be done individually, then reconstruct the vector using `VC`.

## Usage

`ROUND <number>;`

## Examples

`ROUND 3.1;` - Rounds down to `3` and stores the result in the result register.

`ROUND 3.9;` - Rounds up to `4` and stores the result in the result register.
