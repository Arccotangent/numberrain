# CALL

`CALL` is a control flow operation.

## Description

`CALL` allows for functions defined with `FUNCTION` to be executed. It accepts a minimum of 1 argument.

The first argument is the function name. All arguments after that are arguments passed to the function.

The return value of a function, if any, will be automatically placed in the result register. It can then be stored in a
variable using `ASSIGN`. Functions returning nothing (`VOID` return type) will clear the result register.

`RESCHECK` can be used to check the result register.

Calling functions with an incorrect number of arguments will cause your script to crash.

## Usage

`CALL <function name> [argument 1] [argument 2] ... [argument n];`

## Examples

Assuming that function examples in [FUNCTION.md](FUNCTION.md) are defined.
