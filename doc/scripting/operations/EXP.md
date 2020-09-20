# EXP

`EXP` is a mathematical operation.

## Description

`EXP` takes at least 2 inputs, raises them to the next argument's power, then stores the final result in the result register.
From there, the result can be assigned to a variable using `ASSIGN`.

`EXP` uses right-associative exponentiation, that is, exponents are evaluated from right to left.

## Usage

`EXP <number 1> <number 2> ... <number n>;`

## Examples

`EXP 2 31;` - Evaluates 2^31 and stores the result in the result register.

`EXP 3 3 3;` - Evaluates 3^(3^3) and stores the result in the result register.
