#!/bin/bash

echo "set terminal png
set output '$1'
set terminal png font arial 25 size 1600,1200
plot 'tmp1' using 1 with linespoints title 'AST_SGOT', \
     'tmp2' using 1 with linespoints title 'ALT_SGPT', \
     'tmp3' using 1 with linespoints title 'ALP', \
     'tmp4' using 1 with linespoints title 'Bilirubin_Total', \
     'tmp5' using 1 with linespoints title 'Bilirubin_Direct', \
     'tmp6' using 1 with linespoints title 'Bilirubin_Indirect', \
     'tmp7' using 1 with linespoints title 'Protein_Total', \
     'tmp8' using 1 with linespoints title 'Albumin', \
     'tmp9' using 1 with linespoints title 'A_G_Ratio'" | gnuplot
