# RESCHECK

`RESCHECK` is a special operation.

## Description

`RESCHECK` checks whether the result register is empty. It accepts no arguments.

`RESCHECK` will put a 0 in the result register if it is empty, and a 1 if it is not empty.

Note that `RESCHECK` will overwrite any previous value in the result register.

## Usage

`RESCHECK;`
