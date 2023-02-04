# Sorting: Putting your affairs in order (Assignment 3)

## Description
This is a project that uses multiple c functions that sort a random array and order from least to greatest value. The sorting algorithms that are used include Shell sort, Batchers merge sort, Quick sort and Heap sort. The program tracks the number of compares and moves each sortring algorithm does.

This is a response to [assignment3](https://git.ucsc.edu/cse13s/winter2023-section01/resources/-/blob/main/asgn3/asgn3.pdf) in [Cse13s course](https://git.ucsc.edu/cse13s/winter2023-section01/resources)

## Installation
First you need to compile all appropirate c files to create sorting: run make as follows
```
make clean && make
```

## Usage
To run this program with all tests run sorting as follows
```
./sorting -a
```
You can use indvidual tests using additional options.
The opitions can be seen with -H command:
```
SYNOPSIS
   Sorts a random array using four different sorting algorithms

USAGE
   ./sorting [options]

OPTIONS
    -a : Employs all sorting algorithms
    -h : Enables Heap Sort
    -b : Enables Batcher Sort
    -s : Enables Shell Sort
    -q : Enables Quicksort
    -r seed : Set the random seed to seed. The default seed is 13371453
    -n size : Set the array size to size. The default size is 100
    -p elements : Print out elements number of elements from the array.The default is 100
    -H display program help and usage.
```
To generate the graph data and pdf files run plot.sh:
```
./plot.sh
```

## Support
Please contact mkamensk@ucsc.edu if you need help or provide feedback for this project

## Roadmap
A possible addiotion could be more sorting algorithms, such as insert sort, or bubble  sort.

## Author
Michael V. Kamensky
