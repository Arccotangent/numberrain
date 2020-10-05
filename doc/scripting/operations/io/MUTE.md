# MUTE

`MUTE` is an I/O operation.

## Description

`MUTE` disables all console logging by operations (including showing work). It can be useful when performing large
amounts of work that spam out the console. It can also be useful for suppressing console output produced by work that is
non-essential to the script (ie. loop variable incrementing or work that doesn't need to be shown).

`MUTE` disables all console logging by operations regardless of the user's configuration.

`MUTE` does not suppress script logging.
`PRINT` statements will continue to print to console.

`MUTE` (and the corresponding config option) does not suppress the text printed to the console when Numberrain starts
and finishes.

`MUTE` does not specifically disable showing work. Rather, the option set by mute disables showing work as well as
regular console output. So if one calls `MUTE` with work enabled, then calls `UNMUTE`, work will still be enabled.

Pro Tip: Printing to the console takes time. By disabling console output with `MUTE`, one can significantly speed up
their scripts. However, users won't be able to see what your script is doing until it uses `UNMUTE`.

## Usage

`MUTE;`
