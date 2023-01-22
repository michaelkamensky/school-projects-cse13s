# Monte Carlo Pi Estimation Bash Script Project (Assignment 1)

## Description
This is a project that uses a bash script to run a program monte_carlo and plot the appropriate results on a graph using gnuplot. The two figures that we want to print out are the random points and their location in the Monte Carlo program, with the dots in the inside of the circle being Blue while the dots on the outside being Red. Finally there is a second graph that shows the error estimation of pi based on multiple simulations of the Monte Carlo program and the amount of error.

This is a response to [assignment1](https://git.ucsc.edu/cse13s/winter2023-section01/resources/-/blob/main/asgn1/asgn1.pdf) in [Cse13s course](https://git.ucsc.edu/cse13s/winter2023-section01/resources) 

## Installation
First you need to compile monte_carlo program: run make as follows
```
make clean && make
```

## Usage
To run this program run plot.sh as follows
```
./plot.sh
```
The script generates fig2.pdf and fig3.pdf. By default the script generates 1000 points for fig2.pdf. That number can changed by passing an optional argument as an int. For example 
```
./plot.sh 100
```

## Support
Please contact mkamensk@ucsc.edu if you need help or provide feedback for this project

## Roadmap
It would be nice to add more command line options to the script. For example:
- specify the number of points for fig3. 
- have an option to specify output files instead of the default fig2.pdf and fig3.pdf

## Author
Michael V. Kamensky


