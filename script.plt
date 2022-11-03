reset
# set multiplot

# set size 0.33, 1
# set origin 0, 0

set grid xtics nomxtics ytics nomytics noztics nomztics \

set title "Testes de chamada de procedimento remoto sem compressão, variando delay de 0ms a 250ms" font "Arial, 12"
set ylabel "time (us)" font "Arial, 12"
set xlabel "size (bytes)" font "Arial, 12"
set key outside
# set logscale x 2
# set format x "%.0s*10^{%T}"


set style increment userstyles
unset style line
set style line 1  linetype 1 linecolor rgb "dark-red"  linewidth 2.000 pointtype 1 pointsize default pointinterval 0

plot    "results.dat" using 1:2 smooth bezier title "Datagram 256 bytes" with linespoints pointinterval 4, \
        "results.dat" using 1:3 smooth bezier title "Datagram 512 bytes" with linespoints pointinterval 4, \
        "results.dat" using 1:4 smooth bezier title "Datagram 768 bytes" with linespoints pointinterval 4, \
        "results.dat" using 1:5 smooth bezier title "Datagram 1024 bytes" with linespoints pointinterval 4, \
        "results.dat" using 1:6 smooth bezier title "Datagram 1280 bytes" with linespoints pointinterval 4, \
        "results.dat" using 1:7 smooth bezier title "Datagram 1536 bytes" with linespoints pointinterval 4, \
        "results.dat" using 1:8 smooth bezier title "Datagram 1792 bytes" with linespoints pointinterval 4, \
        "results.dat" using 1:9 smooth bezier title "Datagram 2048 bytes" with linespoints pointinterval 4, \
        "results.dat" using 1:10 smooth bezier title "Datagram 2304 bytes" with linespoints pointinterval 4, \
        "results.dat" using 1:11 smooth bezier title "Datagram 2560 bytes" with linespoints pointinterval 4, \
        "results.dat" using 1:12 smooth bezier title "Datagram 2816 bytes" with linespoints pointinterval 4, \
        "results.dat" using 1:13 smooth bezier title "Datagram 3072 bytes" with linespoints pointinterval 4, \
        "results.dat" using 1:14 smooth bezier title "Datagram 3328 bytes" with linespoints pointinterval 4, \
        "results.dat" using 1:15 smooth bezier title "Datagram 3584 bytes" with linespoints pointinterval 4, \
        "results.dat" using 1:16 smooth bezier title "Datagram 3840 bytes" with linespoints pointinterval 4, \
        "results.dat" using 1:17 smooth bezier title "Datagram 4096 bytes" with linespoints pointinterval 4, \


# unset multiplot 