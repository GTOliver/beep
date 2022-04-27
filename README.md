# Beep

Add noises to your code: for debugging or just to hear the rhythms of your creations.

Beep can be turned off at compile-time without changing your code.

## Usage

This project can be used either using the C or C++ APIs, or via the macros which wrap around the C API. The benefit of
using the macros is that they can be turned off at compile-time.

### Beep Macros

To use the beep macros, include the `beep.h` header and link against the `beep::beep` target. The CMake
option `-DBEEP=ON` must be provided to enable the beeps.

Use the `BEEP()` macro throughout your code whenever you want to emit an audible beep.

Before emitting any beeps, call the `BEEP_INIT()` macro, and call
`BEEP_TERMINATE()` when you're done.

### Beep C API

To use the C API, link against the `beep::beepc` target and include the `beepc.h` header.

### Beep C++ API

The C++ API can be used by linking against the `beep:beeppp` target and including the `beeppp.h` header.
