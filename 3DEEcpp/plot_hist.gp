## the bash command is
# $ gnuplot -e "variable=value" -p plot_kp.gp

##### SETTING ################################
#file = "xsec_23F_Sp13.3_Tc030_ang010_phi004.dat"
file = "paraOut_23F_Sp13.3_Tc002_ang002.dat"

set xrange [20:70]

binwidth=5
bin(x,width)=width*floor(x/width)

plot file u (bin(($9),binwidth)):19 smooth freq with boxes


#plot file u (bin(($9),binwidth)):15 smooth freq with boxes,\
#     file u (bin(($11),binwidth)):15 smooth freq with boxes

#plot file u (bin(($9>45?$9:1./0.),binwidth)):12 smooth freq with boxes,\
#     file u (bin(($9>45?$11:1./0.),binwidth)):12 smooth freq with boxes
