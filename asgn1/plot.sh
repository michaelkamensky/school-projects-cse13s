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

numpoints=65536

./monte_carlo -n $numpoints | grep -v "Iteration" | awk '{ print( $1, $2-3.141592653589793238); }' > fig3_1.data
sleep 2
./monte_carlo -n $numpoints | grep -v "Iteration" | awk '{ print( $1, $2-3.141592653589793238); }' > fig3_2.data
sleep 2
./monte_carlo -n $numpoints | grep -v "Iteration" | awk '{ print( $1, $2-3.141592653589793238); }' > fig3_3.data
sleep 2
./monte_carlo -n $numpoints | grep -v "Iteration" | awk '{ print( $1, $2-3.141592653589793238); }' > fig3_4.data
sleep 2
./monte_carlo -n $numpoints | grep -v "Iteration" | awk '{ print( $1, $2-3.141592653589793238); }' > fig3_5.data

gnuplot << END
set terminal pdf
set output "fig3.pdf"
set title "Monte Carlo Error Estimation"
# set xlabel "x"
set ylabel "Error"
set yrange[-1:1]
# set size ratio -1
set grid
set logscale x 4
plot "fig3_1.data" with lines linecolor rgb '#0000FF' notitle, "fig3_2.data" with lines linecolor rgb '#FF0000' notitle, "fig3_3.data" with lines linecolor rgb '#00FF00' notitle, "fig3_4.data" with lines linecolor rgb '#FFFF00' notitle, "fig3_5.data" with lines linecolor rgb '#00FFFF' notitle

END

