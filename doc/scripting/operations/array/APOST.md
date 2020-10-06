# APOST

`APOST` is an array operation.

## Description

`APOST` takes at least 2 arguments, the first being an array. All arguments after the first will be added to the end of
the specified array (appending).

The resulting array is stored in the result register.

## Usage

`APOST <array> <element 1> [element 2] ... [element n];`

## Examples

Append 2 elements to an array. The final `PRINT` statement will print `[1, 2, 3, 4, 5]`.

```
AC 1 2 3;
ASSIGN array; # create our array

APOST array 4 5;
ASSIGN array; # update array

PRINT array;
```
