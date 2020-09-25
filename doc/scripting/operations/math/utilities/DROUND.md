# DROUND

`DROUND` is a mathematical operation.

## Description

`DROUND` accepts 2 real number arguments, and rounds the first argument to the precision specified by the second in decimal digits.
If the number's first applicable decimal digit is 5 or greater, `DROUND` will round it up.
Otherwise, it will round down.
If the argument is an integer, `DROUND` has no effect.

The second argument of `DROUND` is truncated (rounded down), so passing decimal arguments will not cause errors.
For example, passing 2.6 as the second argument will be interpreted as 2.

Passing a negative number as the second argument will still work, but it will round to the nearest ten, hundred, etc.
So passing -1 rounds to the nearest ten, -2 rounds to the nearest hundred, and so on.

Passing vectors directly to `DROUND` will cause your script to crash.
At the moment, rounding vector coefficients must be done individually, then reconstruct the vector using `VC`.

## Usage

`DROUND <number> <precision>;`

## Examples

`DROUND 3.141592 2;` - Rounds down to `3.14` (2 decimal digits) and stores the result in the result register.

`DROUND 2.718182 4;` - Rounds up to `2.7182` (4 decimal digits) and stores the result in the result register.
