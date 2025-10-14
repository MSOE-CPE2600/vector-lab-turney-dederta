# Vector Calculator (minimat)

## Overview
minimat is a command-line vector calculator modeled after MatLab.
It allows users to define, manipulate, and save 3D vectors.

## Features
- Add, list, and delete vectors dynamically
- Vector math: additon, subtraction, scalar multiplication, cross product, dot product
- File I/O:
    - 'load filename' - load vectors from file
    - 'save filename' - save vectors to file
- Auto-fill random data: 'fill N' - gerate N random vectors

## Commands
- 'var = x y z' or 'var = x, y, z' - assign a vector
- 'var = var1 (op) var2' - Add/Subtract/Cross/Dot vectors
- 'var1 (op) var2' - Vector operations without assignment
- 'var' - prints out a vectors data
- 'list' - lists out all current vectors
- 'clear' - clears all saved vectors
- 'load filename' loads vectors from a .csv file
- 'save filename' saves vectors to a .csv file
- 'fill n' - fills with n random vectors
- 'quit' - cleanly exits the program

## Compilation
Build using make, or manually with gcc minimat.c vector.c -o minimat

## Author
Ashlyn Dedert