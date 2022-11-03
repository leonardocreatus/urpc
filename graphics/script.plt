reset
# set xrange[0:900000]
#set yrange[]
set title "Testes de chamada de procedimento remoto s/ compressão" font "Arial, 12"
set xlabel "time (us)" font "Arial, 12"
set ylabel "size (bytes)" font "Arial, 12"
set logscale x 2
set format x "%.0s*10^{%T}"
#set xtics valor font "Arial, 12"
#set ytics valor font "Arial, 12"
#set mxtics valor
# set mytics 5
# v(x) = v0*exp(-x/tau)
# v0 = 500
# tau = 1
# fit v(x) "results.txt" u 1:2 via v0, tau
# set label "v0 = 500+-20" at 2, 170
# set label "tau = 43+-3 min" at 2, 120
plot "result_without_compression_512_16_1.txt" u 2:1 t "Envio de dados sem uso de compressão, 512 bytes por envio, 1ms de timeout e 16 janelas de envio paralelo " w p pt 7 lc 6 ps 1.2 smooth unique, \
    "result_without_compression_1024_16_1.txt" u 2:1 t "Envio de dados sem uso de compressão, 1024 bytes por envio, 1ms de timeout e 16 janelas de envio paralelo " w p pt 7 lc 5 ps 1.2 smooth unique, \
    "result_without_compression_2048_16_1.txt" u 2:1 t "Envio de dados sem uso de compressão, 2048 bytes por envio, 1ms de timeout e 16 janelas de envio paralelo " w p pt 7 lc 4 ps 1.2 smooth unique, \
    "result_without_compression_4096_16_1.txt" u 2:1 t "Envio de dados sem uso de compressão, 4096 bytes por envio, 1ms de timeout e 16 janelas de envio paralelo " w p pt 7 lc 3 ps 1.2 smooth unique, \
    "result_without_compression_8192_16_1.txt" u 2:1 t "Envio de dados sem uso de compressão, 8192 bytes por envio, 1ms de timeout e  janelas de envio paralelo " w p pt 7 lc 2 ps 1.2 smooth unique