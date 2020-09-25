# ELSE

`ELSE` is a control flow operation.

## Description

`ELSE` takes no arguments. The code contained within an `ELSE` block is evaluated if and only if all other conditions in
an `IF` block are not met.

`ELSE` statements must always be the last statements in `IF` blocks.
`IF` blocks with an `ELSE` statement not at the end will ignore all blocks after the `ELSE` statement.

Complex conditions are currently unsupported. However, nested `IF` statements are supported, so logical operations such
as AND and OR can be emulated by nesting conditional statements or having multiple statements. Alternatively, `CMP` can
be used with jumping.

## Usage

`ELSE;`

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
ELSEIF a < b;
PRINT "a is less than b.";
ELSE;
PRINT "no other conditions were met";
ENDIF;
```

### Examples of invalid statements

`ELSE` statement is not the last statement in the `IF` block.

```
IF a == b;
PRINT "a equals b.";
ELSE;
PRINT "no other conditions were met";
ELSEIF a > b;
PRINT "a is greater than b.";
ENDIF;
```
