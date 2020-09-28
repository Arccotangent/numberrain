# FUNCTION

`FUNCTION` is an operation allowing the definition of callable functions in scripts.

## Description

`FUNCTION` is the statement used to define callable functions. It accepts a minimum of 2 arguments.

The first argument is the return data type - what kind of data the function will insert in the result register upon
completion. The second argument is the function name. Any arguments after that are arguments to the function itself.

Valid return types are:

- `VOID` (returning nothing)
- `REAL` (returning a real number)
- `INT` (returning an integer)
- `VECTOR` (returning a vector)
- `STRING` (returning a string)

Arguments are specified by name and data type separated by a colon.

Argument names will temporarily overwrite any variables with the same names. Any overwritten variables will be restored
to their previous values after the function returns. Function argument variables will be deleted after the function
returns.

All functions must be terminated by an `ENDFUNC` statement.

Return values are stored in the result register after the function is completed. The value can then be stored in a
variable using `ASSIGN`.

Nested functions and variable argument functions are not currently supported.

## Usage

`FUNCTION <return type> <name> [argument 1] [argument 2] ... [argument n];`

## Examples

A function that adds 2 numbers:

```
FUNCTION REAL add a:REAL b:REAL;
	ADD a b;
	ASSIGN sum;
	
	RETURN sum;
ENDFUNC;
```

A function implementing the Pythagorean theorem:

```
FUNCTION REAL pythag leg1:REAL leg2:REAL;
	EXP leg1 2; # square first leg
	ASSIGN leg1squared;
	
	EXP leg2 2; # square second leg
	ASSIGN leg2squared;
	
	ADD leg1squared leg2squared; # add squares
	ASSIGN hypotSquared;
	
	SQRT hypotSquared; # calculate the sum's square root
	ASSIGN hypot;
	
	RETURN hypot; # hypotenuse length
ENDFUNC;
```
