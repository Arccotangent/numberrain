# Numberrain Scripting Guide

The following is a guide on how to develop basic Numberrain scripts.

## Example Script

This is the completed script (also in `example-scripts`):

```
# basics of Numberrain scripting
# adds 2 + 2

!PRECISION 50

BEGIN;

ADD 2 2; # add 2 + 2
ASSIGN sum; # store result in variable called sum

PRINT sum; # print value stored in sum

END;

```

### Line by Line Breakdown

`# basics of Numberrain scripting` - A comment. Everything after the # character in a certain line is a comment and therefore ignored by the script engine.

`# adds 2 + 2` - Another comment.

`!PRECISION 50` - Set the precision to 50 decimal digits.

`BEGIN;` - End the preoperation stage and start the main script.

`ADD 2 2;` - Add 2 + 2 and store the sum (4) in the result register.

`ASSIGN sum;` - Assign the value in the result register into a variable called `sum`.

`PRINT sum;` - Print the value stored in `sum`.

`END;` - End the script. Everything after an `END` instruction is ignored.

## Developing Your Own Scripts

Read the below information, then read the documentation in `doc/scripting/preoperations` and `doc/scripting/operations` as needed.

### Parts of a Script

Every Numberrain script is required to conform to a simple format, and all scripts operate in the same general way.

There are 2 stages of each script: the preoperation stage and the main script.

#### Preoperation Stage (or Setup Stage)

In the preoperation stage, initial setup for the rest of the script is done.

All preoperation commands start with an exclamation mark (`!`), must occupy a single line, and do not end with semicolons.

Examples of preoperations include setting the number precision.

#### Main Script Stage

Transitioning from the preoperation stage is done with a `BEGIN` operation.
Here, any operation can be executed.

This is where all actual calculations occur.

Every operation that has a result will store its result in the result register.
The result register can then be stored in a variable using the `ASSIGN` operation.

After the main script is complete, it should be ended with an `END` operation.
Everything after an `END` operation is ignored.
