# ADELETE

`ADELETE` is an array operation.

## Description

`ADELETE` takes 2-3 arguments, the first being an array, and the others being indices. The elements between the given
indices are deleted from the array.

The resulting array is stored in the result register.

Passing -1 as any index argument will be interpreted as "without bound."
If -1 is the only argument, then all elements are deleted, emptying the array.

Passing 1 argument (`a`) will delete the element at index `a`.

Passing 2 arguments (`a` and `b`) will delete all elements between `a` and `b` inclusive. If both `a` and `b` are -1,
then all elements are deleted, emptying the array.

## Usage

`APRE <array> <index 1> <index 2>;`

## Examples

Delete multiple elements from an array (example 1). The final `PRINT` statement will print `[5, 6, 7]`.

```
AC 1 2 3 4 5 6 7;
ASSIGN array; # create our array

ADELETE array -1 3; # delete the first 4 elements
ASSIGN array;

PRINT array;
```

Delete multiple elements from an array (example 2). The final `PRINT` statement will print `[1, 2, 3]`.

```
AC 1 2 3 4 5 6 7;
ASSIGN array; # create our array

ADELETE array 3 -1; # delete everything after index 3, including index 3 itself
ASSIGN array;

PRINT array;
```

Delete a single element from an array. The final `PRINT` statement will print `[1, 2, 3, 5, 6, 7]`.

```
AC 1 2 3 4 5 6 7;
ASSIGN array; # create our array

ADELETE array 3; # remove the element at index 3 (4th element)
ASSIGN array;

PRINT array;
```

Delete all elements from an array. The final `PRINT` statement will print `[ ]`.

```
AC 1 2 3 4 5 6 7;
ASSIGN array; # create our array

ADELETE array -1; # delete all elements
ASSIGN array;

PRINT array;
```
