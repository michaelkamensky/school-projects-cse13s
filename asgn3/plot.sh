#!/usr/bin/bash

N="10 20 30 40 50 60 70 80 90 100 200 300 400 500 600 700 800 900 1000 2000 3000 4000 10000 50000 100000"
R="20 30 300 10000"
for n in $N; do
    for r in $R; do
        echo -n "$n $r "
        ./sorting -a -r $r -n $n -p0 | awk -f extract.awk
    done
done > plot.data

gnuplot << END
set terminal pdf
set output "sorting.pdf"
set title "Moves Performed"
set xlabel "Elements"
set ylabel "Moves"
set logscale x 10
set logscale y 10
# set size ratio -1
#set xrange[0:1]
#set yrange[0:0.01]
plot "plot.data" using 1:3 with lines linecolor rgb '#0000FF' title "quick", "plot.data" using 1:5 with lines linecolor rgb '#00FF00' title "shell", "plot.data" using 1:7 with lines linecolor rgb '#FF0000' title "heap","plot.data" using 1:9 with lines linecolor rgb '#00FFFF' title "batcher"
END

gnuplot << END
set terminal pdf
set output "sorting_comp.pdf"
set title "Compares Performed"
set xlabel "Elements"
set ylabel "Compares"
set logscale x 10
set logscale y 10
# set size ratio -1
#set xrange[0:1]
#set yrange[0:0.01]
plot "plot.data" using 1:4 with lines linecolor rgb '#0000FF' title "quick", "plot.data" using 1:6 with lines linecolor rgb '#00FF00' title "shell", "plot.data" using 1:8 with lines linecolor rgb '#FF0000' title "heap","plot.data" using 1:10 with lines linecolor rgb '#00FFFF' title "batcher"
END

