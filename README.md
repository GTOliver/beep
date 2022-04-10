# Beep

Add noises to your code: for debugging or just to hear the rhythms
of your creations.

Beep can be turned off at compile-time without changing your code,
and keeps your release builds free of bloat.

## Usage

Link against the `beep` library, and run CMake with
`-DBEEP=ON`.

Include the `beep.h` header, which defines several macros.

Use the `BEEP()` macro throughout your code whenever you want to
emit an audible beep.

Before emitting any beeps, call the `BEEP_INIT()` macro, and call
`BEEP_TERMINATE()` when you're done.
