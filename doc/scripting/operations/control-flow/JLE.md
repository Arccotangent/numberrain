# JLE

`JLE` is a control flow operation.

## Description

`JLE` is a conditional jump that only executes if the last comparison resulted in "less than" or "equal."
It takes 1 argument - the name of a label specified by `MARK`.

## Usage

`JLE <label name>;`

## Examples

`JLE label1;` - Jumps to a mark named `label1`, but only if the last comparison resulted in "less than" or "equal."
