reset
# set multiplot

# set size 0.33, 1
# set origin 0, 0

set grid xtics nomxtics ytics nomytics noztics nomztics \

set title "Testes de chamada de procedimento remoto sem compressão, c/ variação de payload e perda de pacote" font "Arial, 12"
set ylabel "time (ms)" font "Arial, 12"
set xlabel "size (bytes)" font "Arial, 12"
set key outside

set format x '%.0s%c'
# set yrange [30000000:250000000]
# set logscale y
# set format x "%.0s*10^{%T}"


set style increment userstyles
unset style line
set style line 1  linetype 1 linecolor rgb "dark-red"  linewidth 2.000 pointtype 1 pointsize default pointinterval 0

plot    "loss_3%_1ms_16_512_1024-32768.dat" using 1:($2/1000000.) smooth bezier title "Atraso de 25ms" with linespoints pointinterval 4, \
        "loss_6%_1ms_16_512_1024-32768.dat" using 1:($2/1000000.) smooth bezier title "Atraso de 50ms" with linespoints pointinterval 4, \
        "loss_9%_1ms_16_512_1024-32768.dat" using 1:($2/1000000.) smooth bezier title "Atraso de 75ms" with linespoints pointinterval 4, \
        "loss_12%_1ms_16_512_1024-32768.dat" using 1:($2/1000000.) smooth bezier title "Atraso de 100ms" with linespoints pointinterval 4, \
        "loss_15%_1ms_16_512_1024-32768.dat" using 1:($2/1000000.) smooth bezier title "Atraso de 125ms" with linespoints pointinterval 4, \
        "loss_18%_1ms_16_512_1024-32768.dat" using 1:($2/1000000.) smooth bezier title "Atraso de 150ms" with linespoints pointinterval 4, \
        "loss_21%_1ms_16_512_1024-32768.dat" using 1:($2/1000000.) smooth bezier title "Atraso de 175ms" with linespoints pointinterval 4, \
        "loss_24%_1ms_16_512_1024-32768.dat" using 1:($2/1000000.) smooth bezier title "Atraso de 200ms" with linespoints pointinterval 4
        


# unset multiplot 