# Numberrain Scripting

Numberrain is scriptable using a scripting language bearing a similar structure and style as assembly language.

The scripting language has limited functionality for the time being.

## Features

- Turing-complete
	- Looping and conditional branching
- Accept an arbitrary number of command line arguments
- Access to (almost) every function of Numberrain CLI
	- Basically an API to Numberrain math engine
- Some useful tools and utilities exclusive to scripts
- Functions

## Limitations

- No import functionality (yet)
- Scripts can be indented, but only with tabs due to technical restrictions (at least for now)
	- Indenting with spaces will cause errors
	- It is unlikely that indenting with spaces will be supported any time soon

## Technical Specifications

- Interpreted language
- Single-threaded // not capable of concurrency

### Known Issues

- Setting precision not far above ~120 digits breaks it, throwing a memory allocation error (at least on my machine)
