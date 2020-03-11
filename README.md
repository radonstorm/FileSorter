# FileSorter

## A CSV file sorter written in ANSI C

This program is one of my assignment submissions for COMP1000 Unix & C Programming 2016

The purpose of this assignment was to demonstrate our understanding of memory management, file IO, the C standard library and Makefiles. To develop a deep understanding of these concepts we were confined to using the C89 ANSI C standard.

This program can sort a CSV text file into ascending or descending order on one column.

## Compiling

GCC compiler is used for all compilation. Only compiled/tested on linux.

From a terminal run `make` to compile the program.

## Usage

```bash
./FileSorter i input.txt o output.txt
i - specifies the input file
o - specifies output file
```

`testdata.txt` is available to see what format the program expects.
