## the bash command is
# $ gnuplot -e "variable=value" -p plot_kp.gp

##### command line -e input ##################

#if (!exists("pngIO")) pngIO = 0 ; 
#print 'pngIO = '.pngIO

##### SETTING ################################
filename = "paraOut_23F_angk60_angNN60_Sp13.3.dat"

##### Plotting script ########################
reset #reset all graphic setting
print '============================================'
print 'file : ',filename
pngName = 'compare'.filename[9:strlen(filename)-4].'.png'

set term x11 size 900,600
set grid   #set graphic grid
set style data lines
set key autotitle columnhead
#set xrange [0:180]
#unset xrange
#unset xtics

#-------------- set mulit plot <row>, <col>
set multiplot layout 2, 1 title filename.' 289 MeV/nucleon'
set tmargin 0
#set bmargin 0
set lmargin 10
set rmargin 3
set grid

#--- 1st plot
set origin 0,0.47
set size 1, 0.47
unset xlabel
set ylabel 'DWIA'
set xtics 0, 20, 300.
set xrange[0:300]
set yrange[0:0.2]

# the sytex (A?B:C) is read as (if A then B else C)
plot filename using 1:($10*1.0) lc rgb "#FF0000" lw 2 title "1s1/2 x 1.0",\
           "" using 1:($12*3.0) lc rgb "#FF6600" lw 2 title "1p3/2 x 3.0",\
           "" using 1:($14*3.0) lc rgb "#999900" lw 2 title "1p1/2 x 3.0",\
           "" using 1:($16*9.0) lc rgb "#00FF00" lw 2 title "1d5/2 x 9.0",\
           "" using 1:($18*0.5) lc rgb "#00FFFF" lw 2 title "2s1/2 x 0.5",\
           "" using 1:($20*9.0) lc rgb "#0000FF" lw 2 title "1d3/2 x 9.0"

#--- 2nd plot
set origin 0,0
set size 1, 0.47
set xlabel 'k [MeV/c]'
set ylabel 'Ay'
set xtics 0,20,300.
set xrange [0:300]
set yrange [-1:1]
set ytics -1,0.2,1

plot  0 lc rgb "#000000", \
     filename using ($1):($11) lc rgb "#FF0000" lw 2, \
           "" using ($1):($13) lc rgb "#FF6600" lw 2, \
           "" using ($1):($15) lc rgb "#999900" lw 2, \
           "" using ($1):($17) lc rgb "#00FF00" lw 2, \
           "" using ($1):($19) lc rgb "#00FFFF" lw 2, \
           "" using ($1):($21) lc rgb "#0000FF" lw 2

unset multiplot


#---------- pause and wait for eneter to stop
pause mouse keypress " ==== press s to save, any for exit \n"
#print 'keypress ASCII = '.MOUSE_KEY

if (MOUSE_KEY == 115){
   set term png small size sizeX, sizeY
   set output pngName
   print 'png output -> '.pngName
   load "plot_k_angk_multi.gp"   
}
if (MOUSE_KEY != 115){
   print 'no output'
}
