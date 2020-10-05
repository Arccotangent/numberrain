# FOR

`FOR` is a control flow operation.

## Description

`FOR` is an implementation of the common for loop in other programming languages.

All of the following criteria must be met for a valid for loop:

- End of iteration code signaled by an `ENDFOR` operation
- Start, end, and step are integers

If any of these criteria are not met, the script will either crash or never finish.

Using a step value of 0 will result in an infinite loop.

If any loop is infinite, the only way for the loop to terminate is by using a `BREAK` statement.

For loop features and specifications:

- Placeholder variable (1st argument) deleted after loop completion
- Executes from start (inclusive) to end (exclusive)
- Step value (4th argument) is added to placeholder variable on every iteration

Nested loops are supported.

## Usage

`FOR <var> <start> <end> <step>;`

## Examples

A for loop that prints out all integers from 0-4 inclusive.

```
FOR i 0 5 1;
	PRINT i;
ENDFOR;
```

A for loop that prints the first 5 perfect squares. Note that the `end` argument is set to 6, not 5.

```
FOR i 1 6 1;
	EXP i 2;
	PRINT result; # special variable for direct access to result register
ENDFOR;
```
