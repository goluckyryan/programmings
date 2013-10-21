## the bash command is
# $ gnuplot -e "tdsN="0";out=0" -p plot_tds.gp
#or
# $ gnuplot -e "tdsN="0"" -p plot_tds.gp

#last edit Wed Jun 13 15:23:18 2012 , ryan 

##### SETTING #########
#folder   = "./0104/"
#tdsN     = "0"
#out      = 0    # 0 for no output, 1 for output

##### Plot code ##########

cd folder

#filename = folder."tds".tdsN.".dat"
set term dumb size 30, 1 # this will plot a dummmy but can make the program more nice.

#----find range
	ismin(x) = (x<min)?min=x:0
	ismax(x) = (x>max)?max=x:0

	max=-3000
	min=3000

	plot filename u (ismin($1*1e6)+ismax($1*1e6)):2

	startx = 10*floor(min/10)
	endx = 10*ceil(max/10)

	tics(n)= startx + (endx-startx)/10*n
#-----find range end

outputfile = "PS_".shortname.".png"
if (out == 1) set term png small size 800,600 ;set output outputfile ; print "  output --> ".outputfile ;else print "  no output plot file" ; set term x11 size 800,600;

set multiplot title "Pulse Structure  (".filename.")  ".comment
set tmargin 0
set bmargin 0
set lmargin 6
set rmargin 2
unset xtics
set key left top
set xrange [startx:endx]
set xtics ("" tics(0), "" tics(1), "" tics(2), "" tics(3), "" tics(4), "" tics(5), "" tics(6), "" tics(7),"" tics(8),"" tics(9),"" tics(10)) 
unset xlabel
set grid

#  Field sweep
set size 1,0.2175
set origin 0.0,0.7325
set yrange [-2.5:2.5]
set ytics -2,1
plot filename u ($1*1e6):2 w l lc 1 title "Field Sweep"

#  Reflected Microwave
set size 1,0.2175
set origin 0.0,0.515
set yrange [*:*]
set ytics -2.1,0.2
plot filename u ($1*1e6):3 w l lc 3 title "Reflected Microwave"

#  Microwave trigger
set size 1,0.2175
set origin 0.0,0.2975
set yrange [-1:6]
set ytics 0,1,5
plot filename u ($1*1e6):4 w l lc 2 title "Microwave Trigger"

#  Laser Diode 
set size 1,0.217
set origin 0.0,0.08
set xlabel " Time [us]"
set xtics startx,(endx-startx)/10,endx
set yrange [0:10]
set ytics 1,2
plot filename u ($1*1e6):5 w l lc 6 title "Laser Diode"

unset multiplot

