# FOR

`FOR` is a control flow operation.

## Description

`FOR` is an implementation of the common for loop in other programming languages.

All of the following criteria must be met for a valid for loop:
- End of iteration code signaled by an `ENDFOR` operation
- Finite amount of iterations
- Start, end, and step are integers

If any of these criteria are not met, the script will either crash or never finish.

If a for loop (or any loop such as a comparison/jump based loop) is infinite, the only way to break out is by jumping.

For loop features and specifications:
- Placeholder variable (1st argument) deleted after loop completion
- Executes from start (inclusive) to end (exclusive)
- Step value (4th argument) is added to placeholder variable on every iteration

Nested loops are supported.

## Usage

`FOR <var> <start> <end> <step>;`

## Example

`FOR i 0 5 1;` - Executes 5 times, stepping up by 1 every time (0, 1, 2, 3, 4) in a variable named `i`.

`FOR x 0 10 2;` - Executes 5 times, stepping up by 2 every time (0, 2, 4, 6, 8) in a variable named `x`.
