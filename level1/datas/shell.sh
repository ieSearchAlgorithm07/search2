#!/bin/sh
./a.out 1000 > data1.txt
./a.out 2000 > data2.txt
./a.out 3000 > data3.txt
./a.out 4000 > data4.txt
./a.out 5000 > data5.txt
./a.out 6000 > data6.txt
./a.out 7000 > data7.txt
./a.out 8000 > data8.txt
./a.out 9000 > data9.txt
./a.out 10000 > data10.txt
gnuplot<<EOF
set xlabel "times"
set ylabel "error"
plot "data1.txt" with line title "seed=1000"
replot "data2.txt" with line title "seed=2000"
replot "data3.txt" with line title "seed=3000"
replot "data4.txt" with line title "seed=4000"
replot "data5.txt" with line title "seed=5000"
replot "data6.txt" with line title "seed=6000"
replot "data7.txt" with line title "seed=7000"
replot "data8.txt" with line title "seed=8000"
replot "data9.txt" with line title "seed=9000"
replot "data10.txt" with line title "seed=10000"
EOF
