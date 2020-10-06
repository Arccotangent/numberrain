# MIDENT

`MIDENT` is a special operation.

## Description

`MIDENT` takes 1 integer argument and returns the identity matrix at the given size. The identity matrix is stored in
the result register.

Passing non-positive values to `MIDENT` will cause your script to crash.

## Usage

`MIDENT <size>;`

## Examples

`MIDENT 2;` - Generate the 2x2 identity matrix and store it in the result register
