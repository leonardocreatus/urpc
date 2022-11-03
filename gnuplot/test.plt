set multiplot                       # multiplot mode (prompt changes to 'multiplot')
set size 0.5, 1

set origin 0.5,0.0
plot sin(x), log(x)

set origin 0.0,0.0
plot sin(x), log(x), cos(x)

unset multiplot 