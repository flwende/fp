set terminal epslatex standalone color ', 8' header '\renewcommand{\encodingdefault}{T1}\renewcommand{\familydefault}{phv}\renewcommand{\seriesdefault}{l}\renewcommand{\shapedefault}{n}'
set output 'blas2_n447_all_avx512.tex'

set size nosquare 0.9, 0.96
set multiplot

#set style fill pattern 9 border
set style fill solid border -1
set boxwidth 0.15

set key revers Left at graph 1.5, 0.93 samplen 1.0

set xrange [0.1:6.9]
set xtics ('8'1,'16'2,'32'3,'64'4,'128'5,'256'6) offset 0.0, 0.0 scale 1.5

set yrange [0:300]
set ytics ('0'0,'50'50,'100'100,'150'150,'200'200,'250'250,'300'300) offset 0.0, 0.0 scale 1.5
set ylabel 'GFLOPS'

set size nosquare 0.475, 0.482
set title '\textbf{gemv (n=447)}' offset 0.0, -0.5
set origin 0.0, 0.5
f(x) = 016.4452
plot f(x) with lines lt -1 title '\small IEEE $\textsl{FP}_\textsl{\tiny 11,52}$ (MKL reference)', \
'./blas2_gemv_avx512.txt' index 1 using (column(0)+0.70):8 with boxes lt -1 lc rgb '#2691cb' title '\small IEEE $\textsl{FP}_\textsl{\tiny 11,52}$', \
'./blas2_gemv_avx512.txt' index 2 using (column(0)+0.85):8 with boxes lt -1 lc rgb '#9fcdff' title '\small IEEE $\textsl{FP}_\textsl{\tiny 8,23}$', \
'./blas2_gemv_avx512.txt' index 3 using (column(0)+1.00):8 with boxes lt -1 lc rgb '#9988aa' title '\small $\textsl{FP}_\textsl{\tiny 8,7}$ (bfloat16)', \
'./blas2_gemv_avx512.txt' index 4 using (column(0)+1.15):8 with boxes lt -1 lc rgb '#699962' title '\small fixed 16 bit', \
'./blas2_gemv_avx512.txt' index 5 using (column(0)+1.30):8 with boxes lt -1 lc rgb '#8acd67' title '\small fixed 8 bit', \
'./blas2_gemv_avx512.txt' index 1 using (column(0)+0.70):8:9 with errorbars lt -1 notitle, \
'./blas2_gemv_avx512.txt' index 2 using (column(0)+0.85):8:9 with errorbars lt -1 notitle, \
'./blas2_gemv_avx512.txt' index 3 using (column(0)+1.00):8:9 with errorbars lt -1 notitle, \
'./blas2_gemv_avx512.txt' index 4 using (column(0)+1.15):8:9 with errorbars lt -1 notitle, \
'./blas2_gemv_avx512.txt' index 5 using (column(0)+1.30):8:9 with errorbars lt -1 notitle, \
f(x) with line lt -1 notitle

set xlabel 'block size $\tilde\textsl{\textit{n}}$'
set size nosquare 0.475, 0.520
set title '\textbf{spmv (n=447)}' offset 0.0, -0.5
set origin 0.0, 0.0
h(x) = 034.8417
plot './blas2_spmv_avx512.txt' index 1 using (column(0)+0.70):8 with boxes lt -1 lc rgb '#2691cb' notitle, \
'./blas2_spmv_avx512.txt' index 2 using (column(0)+0.85):8 with boxes lt -1 lc rgb '#9fcdff' notitle, \
'./blas2_spmv_avx512.txt' index 3 using (column(0)+1.00):8 with boxes lt -1 lc rgb '#9988aa' notitle, \
'./blas2_spmv_avx512.txt' index 4 using (column(0)+1.15):8 with boxes lt -1 lc rgb '#699962' notitle, \
'./blas2_spmv_avx512.txt' index 5 using (column(0)+1.30):8 with boxes lt -1 lc rgb '#8acd67' notitle, \
'./blas2_spmv_avx512.txt' index 1 using (column(0)+0.70):8:9 with errorbars lt -1 notitle, \
'./blas2_spmv_avx512.txt' index 2 using (column(0)+0.85):8:9 with errorbars lt -1 notitle, \
'./blas2_spmv_avx512.txt' index 3 using (column(0)+1.00):8:9 with errorbars lt -1 notitle, \
'./blas2_spmv_avx512.txt' index 4 using (column(0)+1.15):8:9 with errorbars lt -1 notitle, \
'./blas2_spmv_avx512.txt' index 5 using (column(0)+1.30):8:9 with errorbars lt -1 notitle, \
h(x) with line lt -1 notitle

unset ylabel
set size nosquare 0.450, 0.520
set title '\textbf{tpsv (n=447)}' offset 0.0, -0.5
set origin 0.47, 0.0
h(x) = 017.7979
plot './blas2_tpsv_avx512.txt' index 1 using (column(0)+0.70):8 with boxes lt -1 lc rgb '#2691cb' notitle, \
'./blas2_tpsv_avx512.txt' index 2 using (column(0)+0.85):8 with boxes lt -1 lc rgb '#9fcdff' notitle, \
'./blas2_tpsv_avx512.txt' index 3 using (column(0)+1.00):8 with boxes lt -1 lc rgb '#9988aa' notitle, \
'./blas2_tpsv_avx512.txt' index 4 using (column(0)+1.15):8 with boxes lt -1 lc rgb '#699962' notitle, \
'./blas2_tpsv_avx512.txt' index 5 using (column(0)+1.30):8 with boxes lt -1 lc rgb '#8acd67' notitle, \
'./blas2_tpsv_avx512.txt' index 1 using (column(0)+0.70):8:9 with errorbars lt -1 notitle, \
'./blas2_tpsv_avx512.txt' index 2 using (column(0)+0.85):8:9 with errorbars lt -1 notitle, \
'./blas2_tpsv_avx512.txt' index 3 using (column(0)+1.00):8:9 with errorbars lt -1 notitle, \
'./blas2_tpsv_avx512.txt' index 4 using (column(0)+1.15):8:9 with errorbars lt -1 notitle, \
'./blas2_tpsv_avx512.txt' index 5 using (column(0)+1.30):8:9 with errorbars lt -1 notitle, \
h(x) with line lt -1 notitle

unset xlabel
set size nosquare 0.45, 0.482
set title '\textbf{tpmv (n=447)}' offset 0.0, -0.5
set origin 0.47, 0.5
g(x) = 017.8063
plot './blas2_tpmv_avx512.txt' index 1 using (column(0)+0.70):8 with boxes lt -1 lc rgb '#2691cb' notitle, \
'./blas2_tpmv_avx512.txt' index 2 using (column(0)+0.85):8 with boxes lt -1 lc rgb '#9fcdff' notitle, \
'./blas2_tpmv_avx512.txt' index 3 using (column(0)+1.00):8 with boxes lt -1 lc rgb '#9988aa' notitle, \
'./blas2_tpmv_avx512.txt' index 4 using (column(0)+1.15):8 with boxes lt -1 lc rgb '#699962' notitle, \
'./blas2_tpmv_avx512.txt' index 5 using (column(0)+1.30):8 with boxes lt -1 lc rgb '#8acd67' notitle, \
'./blas2_tpmv_avx512.txt' index 1 using (column(0)+0.70):8:9 with errorbars lt -1 notitle, \
'./blas2_tpmv_avx512.txt' index 2 using (column(0)+0.85):8:9 with errorbars lt -1 notitle, \
'./blas2_tpmv_avx512.txt' index 3 using (column(0)+1.00):8:9 with errorbars lt -1 notitle, \
'./blas2_tpmv_avx512.txt' index 4 using (column(0)+1.15):8:9 with errorbars lt -1 notitle, \
'./blas2_tpmv_avx512.txt' index 5 using (column(0)+1.30):8:9 with errorbars lt -1 notitle, \
g(x) with line lt -1 notitle

unset multiplot
set output
