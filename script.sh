#!/bin/bash

echo "set terminal png
set output '$1'
set terminal png size 1000,1000
plot 'tmp1' using 1 with linespoints title 'Glucose_Fasting', \
     'tmp2' using 1 with linespoints title 'Glucose_PP', \
     'tmp3' using 1 with linespoints title 'Cholesterol_Total', \
     'tmp4' using 1 with linespoints title 'Triglycerides', \
     'tmp5' using 1 with linespoints title 'HDL_Cholesterol', \
     'tmp6' using 1 with linespoints title 'LDL_Cholesterol', \
     'tmp7' using 1 with linespoints title 'Uric_Acid', \
     'tmp8' using 1 with linespoints title 'Creatinine', \
     'tmp9' using 1 with linespoints title 'HbA1c', \
     'tmp10' using 1 with linespoints title 'Microalbumin_Urine'" | gnuplot
