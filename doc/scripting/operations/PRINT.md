# PRINT

`PRINT` is an I/O operation.

## Description

`PRINT` is an I/O operation that prints all arguments to the console, separated by spaces.
It takes at least 1 argument.

`PRINT` accepts both unquoted and quoted text.
However, note that `PRINT` will print the value of any argument that happens to be a used variable name unless it is quoted.
So if there is a variable called `sum` with `5` in it, the statement `PRINT the sum is sum;` will print `the 5 is 5`, but `PRINT "the sum is" sum;` will print `the sum is 5`.  

## Usage

`PRINT <text/variable 1> [text/variable 2] ... [text/variable n];`

## Examples

`PRINT test print statement;` - Prints `test print statement` to the console.
