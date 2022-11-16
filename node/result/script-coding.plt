reset
# set multiplot

# set size 0.33, 1
# set origin 0, 0

set grid xtics nomxtics ytics nomytics noztics nomztics \

set title "Testes de chamada de procedimento remoto com compressão, c/ variação de payload e datagrama" font "Arial, 12"
set ylabel "time (ms)" font "Arial, 12"
set xlabel "size (bytes)" font "Arial, 12"
set key box at graph 0.25, 0.95

set format x '%.0s%c'
# set yrange [30000000:250000000]
# set logscale y
# set format x "%.0s*10^{%T}"


set style increment userstyles
unset style line
set style line 1  linetype 1 linecolor rgb "dark-red"  linewidth 2.000 pointtype 1 pointsize default pointinterval 0

plot    "with_coding_1_16_1024-65536.dat" using 1:($2/1000000.) smooth bezier title "Datagrama de 256 bytes" with linespoints pointinterval 4, \
        "with_coding_1_16_1024-65536.dat" using 1:($3/1000000.) smooth bezier title "Datagrama de 512 bytes" with linespoints pointinterval 4, \
        "with_coding_1_16_1024-65536.dat" using 1:($4/1000000.) smooth bezier title "Datagrama de 768 bytes" with linespoints pointinterval 4, \
        "with_coding_1_16_1024-65536.dat" using 1:($5/1000000.) smooth bezier title "Datagrama de 1024 bytes" with linespoints pointinterval 4, \
        "with_coding_1_16_1024-65536.dat" using 1:($6/1000000.) smooth bezier title "Datagrama de 1280 bytes" with linespoints pointinterval 4, \
        "with_coding_1_16_1024-65536.dat" using 1:($7/1000000.) smooth bezier title "Datagrama de 1536 bytes" with linespoints pointinterval 4, \
        "with_coding_1_16_1024-65536.dat" using 1:($8/1000000.) smooth bezier title "Datagrama de 1792 bytes" with linespoints pointinterval 4, \
        "with_coding_1_16_1024-65536.dat" using 1:($9/1000000.) smooth bezier title "Datagrama de 2048 bytes" with linespoints pointinterval 4
        


# unset multiplot 