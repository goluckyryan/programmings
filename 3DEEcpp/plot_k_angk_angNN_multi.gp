set xrange [20:70]
set yrange [20:70]
set xlabel "ang1 [deg]"
set xtics 0, 10 , 70 font ",8" 
set ylabel "ang2 [deg]" offset -2,0, 0
set ytics 0, 10, 70 font ",8" 
#set dgrid3d 300/5,360/5,1

#set contour base #set contour at the base
#set cntrparam levels incremental -1, 0.1, 1
#set pm3d at b   #set color at base, no contour line
#set pm3d map  # set a 2D map
#unset pm3d

set pm3d at b
set view map
set dgrid 100,100

#set palette defined (-0.3 "black",-0.15 "blue",0 "white", 0.15 "green", 0.3 "red")
set palette defined ( 0.0  "#000000",\
                      0.1  "#FF00FF",\
                      0.2  "#0000FF",\
                      0.3  "#0066FF",\
                      0.4  "#00FFFF",\
                      0.5  "#00FF00",\
                      0.6  "#66CC00",\
                      0.7  "#FFFF00",\
                      0.8  "#FF6600",\
                      0.9  "#FF0000",\
                      1.0  "#FFFFFF" )

#========= multiplot
set multiplot layout 3, 2 title filename[9:strlen(filename)-4].comment
set tmargin 0
set bmargin 0
set lmargin 5
set rmargin 0

set cbrange [0:0.2]
set cbtics 0.05 font ",8" 
set format cb "%5.2f"
set title "DWIA 1s1/2 x 1  " ;splot filename using 5:7:($4>TGate?$12*1:1/0)   w pm3d title ""
set title "DWIA 1p3/2 x 4  " ;splot filename using 5:7:($4>TGate?$14*4:1/0)   w pm3d title ""
set title "DWIA 1p1/2 x 4  " ;splot filename using 5:7:($4>TGate?$16*4:1/0)   w pm3d title ""
set title "DWIA 1d5/2 x 9  " ;splot filename using 5:7:($4>TGate?$18*9:1/0)   w pm3d title ""
set title "DWIA 2s1/2 x 0.5" ;splot filename using 5:7:($4>TGate?$20*0.5:1/0) w pm3d title ""
set title "DWIA 1d3/2 x 9  " ;splot filename using 5:7:($4>TGate?$22*9:1/0)   w pm3d title "" 


#set cbrange [-1:1]
#set cbtics 0.2        
#set title "A00n0 1s1/2" ;splot filename using 1:2:($9>TdGate?$12:1/0) title "" pal
#set title "A00n0 1p3/2" ;splot filename using 1:2:($9>TdGate?$14:1/0) title "" pal
#set title "A00n0 1p1/2" ;splot filename using 1:2:($9>TdGate?$16:1/0) title "" pal
#set title "A00n0 1d5/2" ;splot filename using 1:2:($9>TdGate?$18:1/0) title "" pal
#set title "A00n0 2s1/2" ;splot filename using 1:2:($9>TdGate?$20:1/0) title "" pal
#set title "A00n0 1d3/2" ;splot filename using 1:2:($9>TdGate?$22:1/0) title "" pal
#
#set cbrange [-0.2:0]
#set cbtics 0.05
#set title "A00n0 1s1/2*2s1/2";splot filename using 1:2:($9>TdGate?$12*$20:0) title "" pal
#set title "A00n0 1p3/2*1p1/2";splot filename using 1:2:($9>TdGate?$14*$16:0) title "" pal
#set title "A00n0 1d5/2*1d3/2";splot filename using 1:2:($9>TdGate?$18*$22:0) title "" pal
#set cbrange [-0.1:0.1]
#set title "FOM s" ;splot filename using 1:2:($9>TdGate?($12-$20)*($11+$19)/2.:0) title "" pal
#set title "FOM 1p";splot filename using 1:2:($9>TdGate?($14-$16)*($13+$15)*2.:0) title "" pal
#set title "FOM 1d";splot filename using 1:2:($9>TdGate?($18-$22)*($17+$21)/2.*4.5:0) title "" pal


unset multiplot
