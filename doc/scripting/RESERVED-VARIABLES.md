# Reserved Variables in Numberrain Scripts

Some variable names in scripts are reserved. Reserved variable values are constant and can be only accessed by scripts.
If a script tries to modify a reserved variable value, it will crash.

A complete list of the reserved variable names can be found below.

## Reserved Variable Name/Value List

These variables are all read-only.

`pi` - Pi, Archimedes' constant, ratio of circle circumference to diameter ~= 3.14159...

`e` - Euler's number, base of the natural logarithm ~= 2.71818...

`golden_ratio` - Golden ratio ~= 1.61803...

`euler_gamma` - Euler-Mascheroni constant ~= 0.57721...

`arg_0`, `arg_1`, ... `arg_n` - Command line arguments passed into script (starts from 0)

`argcount` - Amount of command line arguments

`result` - The result register
