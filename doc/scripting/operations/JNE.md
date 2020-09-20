# JNE

`JNE` is a control flow operation.

## Description

`JNE` is a conditional jump that only executes if the last comparison did not result in "equal."
It takes 1 argument - the name of a label specified by `MARK`.

## Usage

`JNE <label name>;`

## Examples

`JNE label1;` - Jumps to a mark named `label1`, but only if the last comparison did not result in "equal."
