# WHILE

`WHILE` is a control flow operation.

## Description

`WHILE` is an implementation of the common while loop in other programming languages.

All of the following criteria must be met for a valid while loop:

- End of iteration code signaled by an `ENDWHILE` operation
- Condition must eventually become false

If any of these criteria are not met, the script will either crash or never finish.

Using a condition that is always true will result in an infinite loop.

If any loop is infinite, the only way for the loop to terminate is by using a `BREAK` statement.

While loop features and specifications:

- No placeholder variable
- Executes continuously until the condition becomes false

Nested loops are supported.

## Usage

`WHILE <condition>;`

## Example

A while loop that continuously subtracts 1 from `n` until `n` is zero (the condition is made false). If `n` is
non-positive, the loop never executes.

```
WHILE n > 0;
	SUB n 1;
	ASSIGN n;
ENDWHILE;
```

A similar, but invalid while loop - the condition will never become false and there is no way to break out.

```
WHILE n > 0;
	ADD n 1;
	ASSIGN n;
ENDWHILE;
```
