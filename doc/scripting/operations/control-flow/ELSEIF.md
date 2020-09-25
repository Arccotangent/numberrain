# ELSEIF

`ELSEIF` is a control flow operation.

## Description

`ELSEIF` takes 3 arguments and executes code based on how they evaluate. If the given condition is true, the appropriate
code is executed.

The first and third arguments are real numbers, the second is an operator.

Valid operators are:

- `==` (equal)
- `!=` (not equal)
- `>=` (greater than or equal to)
- `<=` (less than or equal to)
- `>` (greater than)
- `<` (less than)

All `ELSEIF` statements must be between `IF` and `ENDIF` statements. Floating `ELSEIF` statements will cause your script
to crash.

`ELSE` statements can be used to execute code if no other conditions are met.

Both real numbers must be variables or constants - no expressions.

Complex conditions are currently unsupported. However, nested `IF` statements are supported, so logical operations such
as AND and OR can be emulated by nesting conditional statements or having multiple statements. Alternatively, `CMP` can
be used with jumping.

## Usage

`ELSEIF <a> <operator> <b>;`

## Examples

```
IF a < b;
PRINT "a is less than b.";
ELSEIF a > b;
PRINT "a is greater than b.";
ENDIF;
```

```
IF a == b;
PRINT "a equals b.";
ELSEIF a < b;
PRINT "a is less than b.";
ENDIF;
```

### Examples of invalid statements

`ELSEIF (a < b) OR (a == b);` - Complex conditions currently unsupported.

`ELSEIF (a - 3) > b;` - First number being compared is an expression, not a single variable or constant.
