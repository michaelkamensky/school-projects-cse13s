# The Game of Life (Assignment 4)

## Description
This is a project that runs the game of life. The game works by having a 2d grid of alive and dead cells. Each generation or iteration of the program checks every cell. If an alive cell has two or three live neighbors it lives. If a deadcell has exactly three cells it becomes alive. All other cells become dead. Then the program runs through the many iterations of generations of the board. The project can take an input file and can retrun an out put file, and has a toroidal mode and ncurses mode.

This is a response to [assignment 4](https://git.ucsc.edu/cse13s/winter2023-section01/resources/-/blob/main/asgn4/asgn4.pdf) in [Cse13s course](https://git.ucsc.edu/cse13s/winter2023-section01/resources)

## Installation
First you need to compile all appropirate c files to create sorting: run make as follows
```
make clean && make
```

## Usage
To run this program run life as follows
```
./life                                           
```
You can use indvidual tests using additional options.
The opitions can be seen with -h command:
```
SYNOPSIS
   Runs the game of life

USAGE
   ./life [options]

OPTIONS
    -t : Specify that the Game of Life is to be played on a toroidal universe.
    -s : Silence ncurses.
    -n generations : Specify the number of generations that the universe goes through. The default number of generations is 100.
    -i input : Specify the input file to read in order to populate the universe. By default the input should be stdin
    -o output :  Specify the output file to print the final state of the universe to. By default the output should be stdout.
    -h : display program help and usage.
```
## Support
Please contact mkamensk@ucsc.edu if you need help or provide feedback for this project

## Author
Michael V. Kamensky

