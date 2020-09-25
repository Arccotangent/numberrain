# DIE

`DIE` is a control flow operation.

## Description

`DIE` causes a script to exit prematurely.

It can be used to abort a script's execution (ie. if there is an error such as invalid arguments).

Unlike `END`, `DIE` does not cause everything after it to be ignored, so it can be used anywhere.

## Usage

`DIE;`

## Examples

A complete script showing an example of `DIE` usage:

```
!PRECISION 25

BEGIN;

IF argcount < 2;
PRINT "not enough arguments!";
# maybe print usage here
DIE;
ENDIF; # this is still required even though the script is terminating

# do stuff here

END;
```
