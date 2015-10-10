#! /usr/bin/perl -w
use Tk;
use Math::Trig;

# this is a GUI application which
# 1) load the iseXX.dat
# 2) draw the FID signal
# 3) load system program FFTW.o and do fourier transform
# 4) draw the FTiseXX.dat

###################
$mw = new MainWindow;
$mw -> title ("GUI Fouier Transform");
#===========================================================Entries 
$start_e 	=$mw -> Entry( -text => "900",
			       -font => "courierfont",
			       -width => 5);
$end_e		=$mw -> Entry( -text => "4999",
			       -font => "courierfont",
			       -width => 5);
$filename_e		=$mw -> Entry( -textvariable => \$openfile,
			       -font => "courierfont",
			       -width => 15);


#===========================================================Buttons 
$LOAD_b         = $mw   -> Button(  -text => "Load",
                                    -font => "courierfont", 
                                    -command => \&Load,
                                    -width => 10);
$FFTW_b         = $mw   -> Button(  -text => "FFTW",
                                    -font => "courierfont", 
                                    -command => \&FFTW,
                                    -width => 10);
#===========================================================Canvas
$FID_c		= $mw 	-> Canvas (-relief=>"sunken", -background=>"white"); 

$FID_c -> create('rectangle',10,150,100,250, -dash=>[6,4,2,4,2,4]);
                                     
#===========================================================Layout 
$LOAD_b -> grid($filename_e);
$start_e-> grid($end_e, $FFTW_b);
$FID_c ->grid();


MainLoop;

#*********************** functions *****************************
sub Load{
	$types = [ ['data files', '.dat'], ['All Files',   '*'],];
  	$openfile = $mw-> getOpenFile( -filetypes => $types,
  			               -defaultextension => '.dat');
 	@fullfile = split('/',$tempfile) ;
 	$filename = $fullfile[-1];
}

sub FFTW {
	$start = $start_e -> get();
	$end = $end_e -> get();
	system("./FFTW.o $filename $start $end 1");

}

