#!/bin/bash

echo "set terminal png
set output '$1'
set terminal png font arial 25 size 1600,1200
plot 'tmp1' using 1 with linespoints title 'Apolipoprotein_A1', \
     'tmp2' using 1 with linespoints title 'Apolipoprotein_B', \
     'tmp3' using 1 with linespoints title 'Lipoprotein_A', \
     'tmp4' using 1 with linespoints title 'S_Homocysteine', \
     'tmp5' using 1 with linespoints title 'S_Fibrinogen'" | gnuplot
