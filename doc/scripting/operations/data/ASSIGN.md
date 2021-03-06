# ASSIGN

`ASSIGN` is a data control operation.

## Description

Every Numberrain script has a result register managed by the script engine.
This result register simply stores the result of the last operation executed that had a result.
That result can be stored in a variable using `ASSIGN`.

`ASSIGN` does not clear the result register.
Thus, it is possible to create many copies of the same value with successive `ASSIGN` statements.

Using `ASSIGN` on a variable name that already exists will overwrite the previous value in that variable.

Using `ASSIGN` before any result has been stored in the result register will create an empty variable.

## Usage

`ASSIGN <variable name>;`

## Examples

`ASSIGN var1;` - Stores the result register value in a variable called `var1`.
