# numberrain

Numberrain is a command line calculator developed by a student for students.
It is currently capable of evaluating various basic operations while showing the steps of the calculation wherever appropriate.

Additionally, Numberrain is fully scriptable.
See example scripts in the `example-scripts/` directory for more information.

Numberrain is free software, released under the GNU AGPLv3.

## Compilation from Source

### Dependencies

- CMake >= 3.16.0
- Boost >= 1.70.0 (system, regex)
- GMP
- C++ compiler supporting C++17

Compiling on Linux:

```
git clone https://github.com/Arccotangent/numberrain.git
cd numberrain
mkdir build
cd build
cmake ..
make -j <number of cpu threads, or enter 4 if unsure>
sudo make install (optional, requires superuser)
./numberrain
```

Executable binaries for Linux (Windows soon) are attached to each tagged release on Github.

## Usage

Numberrain is run from the command line.

Windows: `numberrain <operation> [arguments]`

Linux: `./numberrain <operation> [arguments]`

Run Numberrain with no arguments to print the usage instructions.

### Examples

```
❯ ./numberrain add 2 2
Numberrain version 0.1 by Arccotangent
Operation: add
Arguments (real numbers): { 2 2 }
Adding numbers, starting with sum of 0.
Sum is currently 0, after argument 0 (2): 0 + 2 = 2
Sum is currently 2, after argument 1 (2): 2 + 2 = 4
===================================================================================
Time: 33 microseconds
Final result: 4
```

```
❯ ./numberrain mul 13 37
Numberrain version 0.1 by Arccotangent
Operation: mul
Arguments (real numbers): { 13 37 }
Multiplying numbers, starting from 13.
Product is currently 13, after argument 1 (37): 13 * 37 = 481
===================================================================================
Time: 12 microseconds
Final result: 481
```

## Main Features

Numberrain currently has the following operations built in:

- Four basic arithmetic operations
- Exponentiation
- Square roots
- Factorial
- Modulus (division remainder)
- Greatest common denominator & least common multiple
- Logarithms (base e, base 10, and custom bases)
- Trigonometric functions (sin, cos, tan, arcsin, arccos, arctan)
- Vector arithmetic (addition, subtraction, scalar multiplication)
- Other vector operations including dot and cross product
- Vector conversions (polar <-> rectangular)
- Shows steps taken to arrive at final result wherever appropriate
- Scripting

### Planned Features

The following is a list of planned features being considered to be added into Numberrain at some point in the future.
This list is always subject to change and some ideas may be removed without being implemented. This list is in no
particular order.

- Matrix operations (soon)
- Solving quadratic and cubic (maybe quartic or even nth-degree?) equations (somewhat soon)
- CAS & symbolic operations (not very soon)

## Performance

Numberrain is decently fast, being written in pure C++ (though it certainly isn't the fastest calculator out there). In
some cases, it can run over 50,000 operations per second on most modern CPUs.

Of course, some operations are more time consuming than others (eg. adding 2 numbers vs vector cross product). The
performance of scripts is not guaranteed. Some scripts may never terminate on their own, mostly because of a badly
written script or a bug in Numberrain's script engine.

## Bugs & Contributing

If you find a bug in Numberrain, please open an issue on the tracker.

If you know C++, feel free to open a pull request.
