#!/usr/bin/bash


make clean
make MYCFLAGS="-DTRACE_PI"
./mathlib-test -r | grep -v "diff" | awk '{ print( $1, $2-3.141592653589793); }' > euler.data
./mathlib-test -b | grep -v "diff" | awk '{ print( $1, $2-3.141592653589793); }' > bbp.data
./mathlib-test -v | grep -v "diff" | awk '{ print( $1, $2-3.141592653589793); }' > viete.data
./mathlib-test -m | grep -v "diff" | awk '{ print( $1, $2-3.141592653589793); }' > madhava.data
make clean
make MYCFLAGS="-DTRACE_E"
./mathlib-test -e | grep -v "diff" | awk '{ print( $1, $2-2.718281828459045); }' > e.data
make clean
make MYCFLAGS="-DTRACE_SQRT"
./mathlib-test -n | grep -v "diff" | awk '{ print( $1, $2-1.414213562373095); }' > newton.data

gnuplot << END
set terminal pdf
set output "pi.pdf"
set title "Pi Calculation Error"
set xlabel "terms"
set ylabel "error"
#set logscale y 10
# set size ratio -1
#set xrange[0:1]
#set yrange[0:0.01]
plot "bbp.data" with lines linecolor rgb '#0000FF', "viete.data" with lines linecolor rgb '#FF0000',"madhava.data" with lines linecolor rgb '#00FF00'

END

gnuplot << END
set terminal pdf
set output "pi_euler.pdf"
set title "Pi Euler Calculation Error"
set xlabel "terms"
set ylabel "error"
#set logscale y 10
# set size ratio -1
#set xrange[0:1]
#set yrange[0:0.01]
plot "euler.data" with lines linecolor rgb '#0000FF'

END

gnuplot << END
set terminal pdf
set output "e.pdf"
set title "E Calculation Error"
set xlabel "terms"
set ylabel "error"
#set logscale y 10
# set size ratio -1
#set xrange[0:1]
#set yrange[0:0.01]
plot "e.data" with lines linecolor rgb '#0000FF'

END

gnuplot << END
set terminal pdf
set output "sqrt.pdf"
set title "Square Root of Two Newton Calculation Error"
set xlabel "terms"
set ylabel "error"
#set logscale y 10
# set size ratio -1
#set xrange[0:1]
#set yrange[0:0.01]
plot "newton.data" with lines linecolor rgb '#0000FF'

END




