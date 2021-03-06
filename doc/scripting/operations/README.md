# Numberrain Scripting Operations

All Numberrain scripting operations must be written in capital letters and terminated by a semicolon.

Numberrain will fail to recognize operations that are not in all caps and terminated by a semicolon, and your script will not run.

## List of Operations

The following is a list of operations supported by the scripting engine.

### Elementary Mathematics

- `ADD` (Addition)
- `SUB` (Subtraction)
- `MUL` (Multiplication)
- `DIV` (Division)
- `EXP` (Exponentiation)
- `SQRT` (Square root)
- `FCT` (Factorial)
- `MOD` (Modulus aka division remainder)
- `GCD` (Greatest common denominator aka greatest common factor (GCF))
- `LCM` (Least common multiple)
- `ABS` (Store the absolute value of the argument in the result register) (scripting exclusive)

### Algebra

- `LN` (Natural logarithm (base e))
- `LOG10` (Base 10 logarithm)
- `LOGB` (Custom base logarithm)

### Trigonometry

- `SIN` (Sine)
- `COS` (Cosine)
- `TAN` (Tangent)
- `ARCSIN` (Arcsine aka inverse sine)
- `ARCCOS` (Arccosine aka inverse cosine)
- `ARCTAN` (Arctangent aka inverse tangent)

### Vectors

- `VADD` (Vector addition)
- `VSUB` (Vector subtraction)
- `VSMUL` (Vector/scalar multiplication)
- `VDOT` (Vector dot product)
- `VCROSS` (Vector cross product)
- `VPTR` (Vector conversion - polar to rectangular)
- `VRTP` (Vector conversion - rectangular to polar)

### Matrices

- `MIDENT` (Identity matrix generator) (scripting exclusive)
- `MADD` (Matrix addition)
- `MSUB` (Matrix subtraction)
- `MMUL` (Matrix multiplication)
- `MDET` (Matrix determinant)

### Arrays (scripting exclusive)

- `AC` (Construct array)
- `ADELETE` (Delete elements from array)
- `AE` (Extract element from array)
- `ALEN` (Retrieve length of array)
- `APOST` (Append to array)
- `APRE` (Prepend to array)

### Utilities (scripting exclusive)

- `NOP` (Store a value in the result register)
- `ASSIGN` (Copy a value from the result register to a named variable)
- `VC` (Construct vector - useful for variables)
- `VX` (Extract vector's x value)
- `VY` (Extract vector's y value)
- `VZ` (Extract vector's z value)
- `MC` (Construct matrix - useful for variables)
- `ME` (Extract element from matrix)
- `MX` (Retrieve amount of columns in matrix)
- `MY` (Retrieve amount of rows in matrix)
- `FLOOR` (Round a real number down)
- `CEIL` (Round a real number up)
- `ROUND` (Round a real number up or down using the 5/4 rule)
- `DROUND` (Same as `ROUND`, but allows to round to a specified precision in decimal digits)

### Miscellaneous (scripting exclusive)

- `BEGIN` and `END` (Begin and end a script)
- `FOR` and `ENDFOR` (For loops)
- `WHILE` and `ENDWHILE` (While loops)
- `BREAK` (Breaking out of a loop)
- `CONTINUE` (Skip to the next iteration of a loop)
- `DISABLEWORK` (Disable showing work)
- `ENABLEWORK` (Enable showing work)
- `IF`, `ELSEIF`, `ELSE`, `ENDIF` (Conditional execution)
- `FUNCTION`, `RETURN`, `ENDFUNC`, `CALL` (Functions)
