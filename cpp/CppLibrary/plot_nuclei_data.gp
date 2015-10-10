filename = "nuclei_data.txt"

set key autotitle columnhead
set xlabel "N"
set xtics 0, 2, 40
set ylabel "Sp [MeV]"
set ytics -6, 2, 30

set grid

plot filename u 1:($2==0?1/0:$3)   w l,\
           '' u 1:($3==0?1/0:$4)   w l,\
           '' u 1:($4==0?1/0:$5)   w l,\
           '' u 1:($5==0?1/0:$6)   w l,\
           '' u 1:($6==0?1/0:$7)   w l,\
           '' u 1:($7==0?1/0:$8)   w l,\
           '' u 1:($8==0?1/0:$9)   w l
           