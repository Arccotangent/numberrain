# Numberrain Scripting

Numberrain is scriptable using a scripting language bearing a similar structure and style as assembly language.

The scripting language has limited functionality for the time being.

## Features

- Turing-complete
    - Looping and conditional jumps
- Accept an arbitrary number of command line arguments
- Access to (almost) every function of Numberrain CLI
    - Basically an API to Numberrain math engine
- Some useful tools exclusive to scripts 

## Limitations

- No (built-in) function functionality (yet)
    - However, it is possible to implement "pseudo-functions" using jumps and the `NOP` and `MARK` operations for the time being
- No import functionality (yet)

## Technical Specifications

- Interpreted language
- Single-threaded // not capable of concurrency

### Known Issues

- Setting precision not far above ~120 digits breaks it, throwing a memory allocation error (at least on my machine)
- Currently no way to disable work being shown which can easily spam out the console (fix planned soon) 
