#!/usr/bin/bash

# Defult is 1000 
numpoints=1000

# If argument is supplied then it is used as number of points
if [ $# != 0 ]; then
    numpoints=$1
fi 
./monte_carlo -n $numpoints | grep -v "Iteration" | awk '{ print( $3, $4, $5); }' > all.data
grep -E "*.1$" < all.data > inside_circle.data
grep -E "*.0$" < all.data > outside_circle.data  


# gnuplot < test2.plot
gnuplot << END
set terminal pdf
set output "fig2.pdf"
# set title "Monte Carlo Graph"
# set xlabel "x"
# set ylabel "y"
set size ratio -1
set xrange[0:1]
set yrange[0:1]
f1(x) = sqrt(1-(x**2))
plot "inside_circle.data" with points pointtype 7 pointsize .2 linecolor rgb '#0000FF' notitle, "outside_circle.data" with points pointtype 7 pointsize .2 linecolor rgb '#FF0000' notitle, f1(x) linecolor rgb '#000000' notitle

END

