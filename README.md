# numberrain

Numberrain is a command line calculator developed by a student for students. It is currently capable of performing
various mathematical computations while showing the steps of the calculation wherever appropriate.

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
sudo install numberrain /usr/local/bin (optional, requires superuser)
./numberrain
```

Executable binaries for Linux (Windows soon) are attached to each tagged release on Github.

## Usage

Numberrain is run from the command line.

Windows: `numberrain <operation> [arguments]`

Linux: `./numberrain <operation> [arguments]`

Run Numberrain with no arguments to print the usage instructions.

### Examples

2 + 2:

```
❯ numberrain add 2 2
Numberrain version 0.1-dev8 by Arccotangent
Loading configuration from file: /home/user/.numberrain/config.json
Precision was set to 50 digits.
Numberrain show work is ENABLED (can be overridden by scripts)
Operation: add
Arguments (real numbers): { 2 2 }
===================================================================================
[INFO] [Addition] Adding numbers, starting with sum of 2.
[WORK] [Addition] Sum is currently 2, after argument 1 (2): 2 + 2 = 4
===================================================================================
Time: 17 microseconds
Final result: 4
```

13 * 37:

```
❯ numberrain mul 13 37
Numberrain version 0.1-dev8 by Arccotangent
Loading configuration from file: /home/user/.numberrain/config.json
Precision was set to 50 digits.
Numberrain show work is ENABLED (can be overridden by scripts)
Operation: mul
Arguments (real numbers): { 13 37 }
===================================================================================
[INFO] [Multiplication] Multiplying numbers, starting from 13.
[WORK] [Multiplication] Product is currently 13, after argument 1 (37): 13 * 37 = 481
===================================================================================
Time: 17 microseconds
Final result: 481
```

For more, see [EXAMPLES.md](EXAMPLES.md)

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
- Matrix operations (addition, subtraction, multiplication, determinant)
- Shows steps taken to arrive at final answer
- Scripting

### Planned Features

The following is a list of planned features being considered to be added into Numberrain at some point in the future.
This list is always subject to change and some ideas may be removed without being implemented. This list is in no
particular order.

- Importing code from other scripts (soon)
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
