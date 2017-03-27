#!/bin/bash

echo "set terminal png
set output '$1'
set terminal png font arial 25 size 1600,1200
plot 'tmp1' using 1 with linespoints title 'Glucose_Fasting', \
     'tmp2' using 1 with linespoints title 'Urea', \
     'tmp3' using 1 with linespoints title 'Creatinine', \
     'tmp4' using 1 with linespoints title 'Uric_Acid', \
     'tmp5' using 1 with linespoints title 'Calcium', \
     'tmp6' using 1 with linespoints title 'Phosphorus', \
     'tmp7' using 1 with linespoints title 'Sodium', \
     'tmp8' using 1 with linespoints title 'Potassium', \
     'tmp9' using 1 with linespoints title 'Chloride', \
     'tmp10' using 1 with linespoints title 'Bicarbonate', \
     'tmp11' using 1 with linespoints title 'ALP', \
     'tmp12' using 1 with linespoints title 'Protein_Total', \
     'tmp13' using 1 with linespoints title 'Albumin', \
     'tmp14' using 1 with linespoints title 'A_G_Ratio'" | gnuplot
