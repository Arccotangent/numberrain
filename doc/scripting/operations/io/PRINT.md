# PRINT

`PRINT` is an I/O operation.

## Description

`PRINT` is an I/O operation that prints all arguments to the console.
It takes at least 1 argument.

`PRINT` does not separate arguments with spaces like before, therefore it is recommended to use quoted text whenever possible.

`PRINT` accepts both unquoted and quoted text.
However, note that `PRINT` will print the value of any argument that happens to be a used variable name unless it is quoted.

So if there is a variable called `sum` with `5` in it, the statement `PRINT the sum is sum;` will print `the 5 is 5`, but `PRINT "the sum is " sum;` will print `the sum is 5`.  

## Usage

`PRINT <text/variable 1> [text/variable 2] ... [text/variable n];`

## Examples

`PRINT test print statement;` - Prints `testprintstatement` to the console.

`PRINT "test print statement";` - Prints `test print statement` to the console.

`PRINT "the sum is " sum;` - Prints `the sum is 5` to the console, assuming the variable `sum` exists and contains the value `5`.
