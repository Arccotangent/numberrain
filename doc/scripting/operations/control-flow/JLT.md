# JLT

`JLT` is a control flow operation.

## Description

`JLT` is a conditional jump that only executes if the last comparison resulted in "less than."
It takes 1 argument - the name of a label specified by `MARK`.

## Usage

`JLT <label name>;`

## Examples

`JLT label1;` - Jumps to a mark named `label1`, but only if the last comparison resulted in "less than."
