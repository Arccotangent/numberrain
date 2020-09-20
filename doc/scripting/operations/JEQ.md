# JEQ

`JEQ` is a control flow operation.

## Description

`JEQ` is a conditional jump that only executes if the last comparison resulted in "equal."
It takes 1 argument - the name of a label specified by `MARK`.

## Usage

`JEQ <label name>;`

## Examples

`JEQ label1;` - Jumps to a mark named `label1`, but only if the last comparison resulted in "equal."
