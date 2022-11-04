reset
# set multiplot

# set size 0.33, 1
# set origin 0, 0

set grid xtics nomxtics ytics nomytics noztics nomztics \

set title "Testess de chamada de procedimento remoto sem compressão, variando payload de 0ms a 250ms" font "Arial, 12"
set ylabel "time (us)" font "Arial, 12"
set xlabel "size (bytes)" font "Arial, 12"
set key outside
# set ydata time
set format y '%.6f'
# set logscale x 2
# set format x "%.0s*10^{%T}"


set style increment userstyles
unset style line
set style line 1  linetype 1 linecolor rgb "dark-red"  linewidth 2.000 pointtype 1 pointsize default pointinterval 0

plot    "delay/result-delay-25-250ms.dat" using 1:2 smooth bezier title "Delay de 0ms" with linespoints pointinterval 4, \
        "delay/result-delay-25-250ms.dat" using 1:3 smooth bezier title "Delay de 25ms" with linespoints pointinterval 4, \
        "delay/result-delay-25-250ms.dat" using 1:4 smooth bezier title "Delay de 50ms" with linespoints pointinterval 4, \
        "delay/result-delay-25-250ms.dat" using 1:5 smooth bezier title "Delay de 75ms" with linespoints pointinterval 4, \
        "delay/result-delay-25-250ms.dat" using 1:6 smooth bezier title "Delay de 100ms" with linespoints pointinterval 4, \
        "delay/result-delay-25-250ms.dat" using 1:7 smooth bezier title "Delay de 125ms" with linespoints pointinterval 4, \
        "delay/result-delay-25-250ms.dat" using 1:8 smooth bezier title "Delay de 150ms" with linespoints pointinterval 4, \
        "delay/result-delay-25-250ms.dat" using 1:9 smooth bezier title "Delay de 175ms" with linespoints pointinterval 4, \
        "delay/result-delay-25-250ms.dat" using 1:10 smooth bezier title "Delay de 200ms" with linespoints pointinterval 4, \
        "delay/result-delay-25-250ms.dat" using 1:11 smooth bezier title "Delay de 225ms" with linespoints pointinterval 4, \
        "delay/result-delay-25-250ms.dat" using 1:12 smooth bezier title "Delay de 250ms" with linespoints pointinterval 4, \


# unset multiplot 