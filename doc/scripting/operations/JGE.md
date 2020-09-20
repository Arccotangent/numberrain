# JGE

`JGE` is a control flow operation.

## Description

`JGE` is a conditional jump that only executes if the last comparison resulted in "greater than" or "equal."
It takes 1 argument - the name of a label specified by `MARK`.

## Usage

`JGE <label name>;`

## Examples

`JGE label1;` - Jumps to a mark named `label1`, but only if the last comparison resulted in "greater than" or "equal."
