# Variables in Numberrain Scripting

Numberrain scripts support basic variables.

## Usage

All variables are assigned their values by means of an `ASSIGN` statement. There is currently no `=` operator like in
most programming and scripting languages.

`ASSIGN var;` - Copies the value in the result register into a variable named `var`.

Variables can then be used in any operations taking arguments.
A few examples:

```
ADD var1 var2;
MUL var1 var2 var3;
GCD a b;
```

If a certain variable does not exist but is still being accessed by a script, the script will crash.

## Scope

Apart from iteration variables in for loops, there is only a global scope. Any variables created will be available for
the rest of the script, regardless of conditions.

There is currently no way to delete variables.

## Variable Names

Variables can have any name provided that the name meets these criteria:

- Does not start with a number
- Does not contain a colon
- Does not match a reserved variable name (see [RESERVED-VARIABLES.md](RESERVED-VARIABLES.md))

## Data Types

The script engine represents all variable values are represented as strings in memory and converts them to the
appropriate internal data structure when needed.

The formatting of variables in memory is identical to the format in which data is printed to the console.

Internally, this has the advantage of being able to store all variables in one map. However, for computationally
expensive scripts, it does add a bit of overhead as variables are parsed every time they are used.

## Current Limitations

Anything other than single variables is currently unsupported.
This includes arrays, maps, etc.
The only exception to this rule is the read-only array of command line arguments.

### Arrays/Lists

Currently, the only array variable that exists is that corresponding to command line arguments.
It is not currently possible to create arbitrary arrays in a script.

The current array syntax will likely change in the future to a more conventional and familiar format (eg. `array[index]`).
Such a format will also make n-dimensional arrays a possibility as opposed to the current limitation of 1 dimension.

User-defined arrays are being worked on and will be implemented in the near future.

### Maps/Dictionaries

Maps are a more difficult variable type to implement into Numberrain scripting given the current syntax form and the internal workings of the script engine.
As such, they are not planned to be implemented in the near future, but will be added at some point.
