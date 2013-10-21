## the bash command is
# $ gnuplot -e "iseN='X'" -p plot_fid+FTamp.gp
#  X is the file number

# last update : Sun Jun 10 16:49:19 2012 Ryan

##### SETTING #########################
folder   = "./"
#iseN     = "0"  # the order of ise file, for ise9.dat, iseN="9" 
extitle  = ""   # extra title 
fid      = 200  #fid range in us
ft       = 100  #FT range in kHz
#out      = 0    # 0 for no output, 1 for output
#start    = 00   #FFT start rows
#end      = 3999 #FFT end rows
FFTpath  = "~/Dropbox/C++_programs/FFTW/FFTW.o"

##### Plotting script ########################

cd folder # change folder

FTgen = FFTpath." ise".iseN.".dat ".start." ".end." 1"
system(FTgen)

filename1 = "ise".iseN.".dat"
filename2 = "FTise".iseN.".dat"
outputfile = "ise".iseN."_FID_FTamp.png"

if (out == 1) set term png small size 900,400 ; set output outputfile ; print " ##### output --> ".outputfile ;else print " ##### no output plot file" ; set term x11 size 900,400;

##### this section is for output. if no output, this will run but overwrite by later code.
##### since gnuplot not support parentless 
set multiplot
set grid

#  FID signal
set title "FID signal (".folder."ise".iseN.".dat | ".start."-".end." ) ".extitle
set size 0.66,1
set origin 0,0
set xrange [0:fid]
set xtics 0,fid/10,fid
set xlabel "Time [us]"
set yrange [*:*]
plot filename1 u ($1*1e6):2 w l lc 3 title "Cos", filename1 u ($1*1e6):3 w l lc 1 title "Sin"

#  FT amp
set title "Fourier Spectrum"
set size 0.34,1
set origin 0.66,0
set xrange [-ft:ft]
set xtics -ft,ft/4,ft
set xlabel "Freqeuncy [kHz]"
set yrange [0:*]
plot filename2 u ($1*1000):($2) w lp lc 4 title "" 

unset multiplot

### quick display ####################################
set term x11 size 900,400
set multiplot
set grid

#  FID signal
set title "FID signal (".folder."ise".iseN.".dat | ".start."-".end." ) ".extitle
set size 0.66,1
set origin 0,0
set xrange [0:fid]
set xtics 0,fid/10,fid
set xlabel "Time [us]"
set yrange [*:*]
plot filename1 u ($1*1e6):2 w l lc 3 title "Cos", filename1 u ($1*1e6):3 w l lc 1 title "Sin"

#  FT amp
set title "Fourier Spectrum"
set size 0.34,1
set origin 0.66,0
set xrange [-ft:ft]
set xtics -ft,ft/4,ft
set xlabel "Freqeuncy [kHz]"
set yrange [0:*]
plot filename2 u ($1*1000):($2) w lp lc 4 title "" 

unset multiplot

