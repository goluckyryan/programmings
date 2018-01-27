#! /usr/bin/perl
use Tk;
use Tk::Font;
use Math::Trig;

# this is a GUI application which
# 1) choose the iseXX.dat, and change the working directory 
# 2a) call FFTW to do FFT
# 2b) use gunplot script "plot_fid+FTamp.gp" 
# 3) can save the plot.

# inculde FFTW_batch to transform number of files and plots
# include Background substraction

#last edit :  2012-06-13 03:43:34 , ryan
###################
$out=0;
$lock =1;
$filename="filename";
$directory = "directory";
$comment = "comment";
#$directory="/home/polp/data/2012/";
#chdir $directory;
#============================================================MainWindow
$mw = new MainWindow;
$mw -> title ("GUI Fouier Transform");
$font       = $mw->Font(-family=> 'courierfont', 
                  -size  => 12);
$small_font = $mw->Font(-family=> 'Helvetica', 
                  -size  => 8);
#===========================================================Labels
$start_l	=$mw -> Label(-text => "Start row",
			      -font => $font);
$end_l		=$mw -> Label(-text => "End row",
			      -font => $font);
$header		=$mw -> Label(-text => "use FFTW and gnuplot",
			      -font => $font);
$footnote1	=$mw -> Label(-text => "if the range is not right, edit plot_fid+FTamp.gp",
			      -font => $small_font);
$footnote2	=$mw -> Label(-text => "batch transform : FFTW_batch",
			      -font => $small_font);
#===========================================================Entries 
$start_e 	=$mw -> Entry( -text => "1500",
			       -font => $font,
			       -width => 5,
			       -justify =>'center');
$end_e		=$mw -> Entry( -text => "4999",
			       -font => $font,
			       -width => 5,
			       -justify =>'center');
$filename_e		=$mw -> Entry( -textvariable => \$filename,
			       -font => $font,
			       -width => 15,
			       -justify =>'center');
$directory_e		=$mw -> Entry( -textvariable => \$directory,
			       -font => $font,
			       -width => 30);			
$comment_e		=$mw -> Entry( -textvariable => \$comment,
			       -font => $font,
			       -width => 30);	     

#===========================================================Buttons 
$LOAD_b         = $mw   -> Button(  -text => "Load",
                                    -font => $font, 
                                    -command => \&Load,
                                    -width => 10);
$FFTW_b         = $mw   -> Button(  -text => "FFTW & Plot",
                                    -font => $font, 
                                    -command => \&FFTW,
                                    -width => 10);
#===========================================================CheckButton
$Save_cb	= $mw	-> Checkbutton ( -text => "Save *.png", 
					 -variable => \$out,
					 -onvalue =>"1",
					 -offvalue => "0");
$lock_cb	= $mw	-> Checkbutton ( -text => "lock ise*.dat", 
					 -variable => \$lock,
					 -onvalue =>"1",
					 -offvalue => "0");
                                     
#===========================================================Layout 
$header -> grid("-");
$LOAD_b -> grid();
$directory_e->grid("-");
$filename_e->grid($lock_cb);
$start_l-> grid($start_e);
$end_l->grid($end_e);
$FFTW_b->grid($Save_cb);
$comment_e->grid("-");
$footnote1->grid("-");
$footnote2->grid("-");


MainLoop;

#*********************** functions *****************************
sub Load{
	$types = [ ['data files', '.dat'], ['Saved Plot', '.png'], ['All Files','*']];
  	$tempfile = $mw-> getOpenFile( -filetypes => $types,
  			               -defaultextension => '.dat');
 	@fullfile = split('/',$tempfile) ;
 	#print "@fullfile";
 	$filename = $fullfile[-1];
 	$directory = substr($tempfile,0,length($tempfile)-length($filename));
 	chdir $directory;
}

sub FFTW {
	if ((substr($filename,0,3) ne "ise")&& $lock==1){
		$filename = "Not ise*.dat";
		return;
	}
	if ($comment eq "comment"){
		$comment="";
	}
	$start = $start_e -> get();
	$end = $end_e -> get();
	@temp = split(/\./,$filename);
#	$num = substr($temp[0],3);
	$short_filename = $temp[0];
	$FFT = "/Users/mobileryan/Dropbox/C++_programs/FFTW/FFTW.o $filename $start $end 1";
	$plot =  "gnuplot -e \"folder=\'$directory\';filename1=\'$filename\';shortname=\'$short_filename\';start=$start;end=$end;out=$out;comment=\'$comment\'\" -p /Users/mobileryan/Dropbox/C++_programs/FFTW/plot_fid+FTamp.gp";
	system($FFT);
	system($plot);
}


