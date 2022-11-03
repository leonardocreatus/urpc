reset
set multiplot

set size 0.33, 1
set origin 0, 0

set title "Testes de chamada de procedimento remoto s/ compressão" font "Arial, 12"
set xlabel "time (us)" font "Arial, 12"
set ylabel "size (bytes)" font "Arial, 12"
set logscale x 2
set format x "%.0s*10^{%T}"

plot    "result_without_compression_512_16_1.txt" u 2:1 t "Datagrama de 512 bytes" w p pt 7 lc 6 ps 1.2 smooth unique, \
        "result_without_compression_1024_16_1.txt" u 2:1 t "Datagrama de 1024 bytes" w p pt 7 lc 5 ps 1.2 smooth unique, \
        "result_without_compression_2048_16_1.txt" u 2:1 t "Datagrama de 2048 bytes" w p pt 7 lc 4 ps 1.2 smooth unique, \
        "result_without_compression_4096_16_1.txt" u 2:1 t "Datagrama de 4096 bytes" w p pt 7 lc 3 ps 1.2 smooth unique, \
        "result_without_compression_8192_16_1.txt" u 2:1 t "Datagrama de 8192 bytes" w p pt 7 lc 2 ps 1.2 smooth unique

set origin 0.33, 0

# set title "Testes de chamada de procedimento remoto s/ compressão" font "Arial, 12"
set xlabel "time (us)" font "Arial, 12"
set ylabel "size (bytes)" font "Arial, 12"
set logscale x 2
set format x "%.0s*10^{%T}"

plot    "result_without_compression_512_16_2.txt" u 2:1 t "Datagrama de 512 bytes" w p pt 7 lc 6 ps 1.2 smooth unique, \
        "result_without_compression_1024_16_2.txt" u 2:1 t "Datagrama de 1024 bytes" w p pt 7 lc 5 ps 1.2 smooth unique, \
        "result_without_compression_2048_16_2.txt" u 2:1 t "Datagrama de 2048 bytes" w p pt 7 lc 4 ps 1.2 smooth unique, \
        "result_without_compression_4096_16_2.txt" u 2:1 t "Datagrama de 4096 bytes" w p pt 7 lc 3 ps 1.2 smooth unique, \
        "result_without_compression_8192_16_2.txt" u 2:1 t "Datagrama de 8192 bytes" w p pt 7 lc 2 ps 1.2 smooth unique



set origin 0.66, 0

# set title "Testes de chamada de procedimento remoto s/ compressão" font "Arial, 12"
set xlabel "time (us)" font "Arial, 12"
set ylabel "size (bytes)" font "Arial, 12"
set logscale x 2
set format x "%.0s*10^{%T}"

plot    "result_without_compression_512_16_3.txt" u 2:1 t "Datagrama de 512 bytes" w p pt 7 lc 6 ps 1.2 smooth unique, \
        "result_without_compression_1024_16_3.txt" u 2:1 t "Datagrama de 1024 bytes" w p pt 7 lc 5 ps 1.2 smooth unique, \
        "result_without_compression_2048_16_3.txt" u 2:1 t "Datagrama de 2048 bytes" w p pt 7 lc 4 ps 1.2 smooth unique, \
        "result_without_compression_4096_16_3.txt" u 2:1 t "Datagrama de 4096 bytes" w p pt 7 lc 3 ps 1.2 smooth unique, \
        "result_without_compression_8192_16_3.txt" u 2:1 t "Datagrama de 8192 bytes" w p pt 7 lc 2 ps 1.2 smooth unique

unset multiplot 