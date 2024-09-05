# requirement: gnuplot version>5.4
# Please open the data file to check the data:   bulkek.dat
set terminal pdf enhanced color font ",24"
set palette defined ( 0  "green", 5 "yellow", 10 "red" )
set output 'bulkek.pdf' 
set style data linespoints
unset key
set pointsize 0.8
#set xtics font ",24"
#set ytics font ",24"
#set ylabel font ",24"
set ylabel offset 0.5,0
set border lw 2
set xrange [0:    4.01504]
emin=   -7.556535
emax=   11.916805
set ylabel "Energy (eV)"
set yrange [ emin : emax ]
set xtics ("M  "    0.00000,"K  "    0.84848,"G  "    2.54543,"M  "    4.01504)
set arrow from    0.84848, emin to    0.84848, emax nohead lw 2
set arrow from    2.54543, emin to    2.54543, emax nohead lw 2
# please comment the following lines to plot the fatband 
plot 'bulkek.dat' u 1:2  w lp lw 2 pt 7  ps 0.2 lc rgb 'black', 0 w l lw 2 dt 2
 
# uncomment the following lines to plot the fatband 
#plot 'bulkek.dat' u 1:2:3  w lp lw 2 pt 7  ps 0.2 lc palette, 0 w l lw 2 dt 2
# uncomment the following lines to plot the spin if necessary
#plot 'bulkek.dat' u 1:2 w lp lw 2 pt 7  ps 0.2, \
#plot 'bulkek.dat' u 1:2:($3/6):($4/6) w vec
