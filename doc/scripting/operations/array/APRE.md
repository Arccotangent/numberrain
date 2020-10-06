# APRE

`APRE` is an array operation.

## Description

`APRE` takes at least 2 arguments, the first being an array. All arguments after the first will be added to the
beginning of the specified array (prepending).

The resulting array is stored in the result register.

## Usage

`APRE <array> <element 1> [element 2] ... [element n];`

## Examples

Prepend 2 elements to an array. The final `PRINT` statement will print `[-1, 0, 1, 2, 3]`.

```
AC 1 2 3;
ASSIGN array; # create our array

APRE array -1 0;
ASSIGN array; # update array

PRINT array;
```
