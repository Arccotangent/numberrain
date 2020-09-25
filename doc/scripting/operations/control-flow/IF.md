# IF

`IF` is a control flow operation.

## Description

`IF` takes 3 arguments and executes code based on how they evaluate. If the given condition is true, the appropriate
code is executed.

The first and third arguments are real numbers, the second is an operator.

Valid operators are:

- `==` (equal)
- `!=` (not equal)
- `>=` (greater than or equal to)
- `<=` (less than or equal to)
- `>` (greater than)
- `<` (less than)

All `IF` statements must be ended by an `ENDIF` statement. Floating `IF` statements with no `ENDIF` statement will cause
your script to crash.

`IF` statements can be used together with `ELSEIF` and `ELSE`.

`ELSE` statements can be used to execute code if no other conditions are met.
`IF` blocks with an `ELSE` statement not at the end will ignore all blocks after the `ELSE` statement.

Both real numbers must be variables or constants - no expressions.

Complex conditions are currently unsupported. However, nested `IF` statements are supported, so logical operations such
as AND and OR can be emulated by nesting conditional statements or having multiple statements. Alternatively, `CMP` can
be used with jumping.

## Usage

`IF <a> <operator> <b>;`

## Examples

```
IF a < b;
PRINT "a is less than b.";
ELSE;
PRINT "a is not less than b.";
ENDIF;
```

```
IF a == b;
PRINT "a equals b.";
ELSE;
PRINT "a does not equal b.";
ENDIF;
```

### Examples of invalid statements

`IF (a < b) OR (a == b);` - Complex conditions currently unsupported.

`IF (a - 3) > b;` - First number being compared is an expression, not a single variable or constant.

Invalid because there is no `ENDIF` - thus no end to the `IF` statement:

```
IF a != b;
PRINT "a is not equal to b.";

# doing other stuff

END;
```
