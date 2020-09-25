# VRTP

`VRTP` is a mathematical operation.

## Description

`VRTP` takes 1 vector argument and converts it to an angle and magnitude.
Only x and y are considered (z is ignored).

The angle is in degrees counterclockwise from the +x axis.

The result is returned as a vector, with x being the angle and y being the magnitude.
Use `VX` and `VY` to extract them.

## Usage

`VRTP <vector>;`

## Examples

`VPTR 4,7;` - Calculates angle and magnitude of (4i + 7j) and stores the result in the result register.
