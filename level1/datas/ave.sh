#!/bin/sh
sort -n data1.txt data2.txt data3.txt data4.txt data5.txt data6.txt data7.txt data8.txt data9.txt data10.txt > data.txt
gnuplot<<EOF
set xlabel "ave_times"
set ylabel "ave_error"
plot "data.txt" smooth unique
EOF
