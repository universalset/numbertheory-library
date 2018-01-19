# numbertheory-library

## Brian's number theory library.

This is a personal number theory library that I mostly use for Project Euler hacking.  More stuff will be added as I find it useful.

### What's with the X versions?

The library files ending in **x** contain code that works for larger numbers.  This includes code for arbitrary-precision integers as well as functions whose inputs and outputs are 64-bit integers, but where using solely 64-bit integers in intermediary calculations could result in overflow.
The non-X code requires no additional libraries (beyond the STL); the X versions use the boost multiprecision data types.

### What's currently in the library?

The library currently consists of two parts:
- modarith (and modarithx), which contains a bunch of basic modular arithmetic functions such as gcd, modular exponentiation, a method for computing modular inverses, and a modular system solver (a la Chinese Remainder Theorem)
- primes, which contains material related to prime numbers such as various sieves, prime counting function (miller-rabin primality testing to be added soon).

