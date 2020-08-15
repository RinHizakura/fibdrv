reset
set xlabel 'fib(n), n ='
set ylabel 'time(ns)'
set terminal png font " Times_New_Roman,12 "
set output 'runtime2.png'


plot \
"fast_fib.txt" using 1:2 with linespoints linewidth 2 title "fast fib", \
"fib_naive.txt" using 1:2 with linespoints linewidth 2 title "naive", \
"fast_fib_clz.txt" using 1:2 with linespoints linewidth 2 title "fast fib + clz", \
