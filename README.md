# Edit Distance Calculator
Written by: Cristopher Hernandez - 5276

This program is meant to calculate the edit distance between two words.
It displays the edit distance matrix, as well as the alignment.
This program was originally compiled and tested on windows using mingw-32, 
a windows implementation of the GNU compiler suite. However, it should also
work with the Linux version of g++. The provided makefile has commands for 
either implementation.

A guide to installing mingw can be found here: http://www.mingw.org/wiki/Getting_Started

## Build

### Linux

Compile:
```
make
```
Delete:
```
make clean
```

### Windows (requires mingw32)

Compile:
```
mingw32-make
```
Delete:
```
mingw32-make clean
```

## Run

Execute the compiled file on a terminal/command line (like so: "./edit_dist") and it will prompt for two words to calculate the alignment for.
