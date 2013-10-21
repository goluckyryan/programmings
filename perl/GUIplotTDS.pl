#! /usr/bin/perl
use Tk;
use Tk::Font;
use Math::Trig;

# this is a GUI application which
# 1) choose the tdsXX.dat, and change the working directory 
# 2) use gunplot script "plot_tds.gp" 
# 3) can save the plot.


#last edit :  Wed Jun 13 16:25:40 2012  , ryan
###################
$out=0;
$lock =1;
$filename="filename";
$directory = "directory";
$comment = "comment";
$status = "status bar";
#$directory="/home/polp/data/2012/";
#chdir $directory;
#============================================================MainWindow
$mw = new MainWindow;
$mw -> title ("GUI Plot TDS");
$font       = $mw->Font(-family=> 'courierfont', 
                  -size  => 12);
$small_font = $mw->Font(-family=> 'Helvetica', 
                  -size  => 8);
#===========================================================Labels
$header		=$mw -> Label(-text => "plot with gnuplot",
			      -font => $font);
$footnote1	=$mw -> Label(-text => "if the range is not right, edit plot_tds.gp",
			      -font => $small_font);
$status_l	=$mw -> Label(-textvariable => \$status,
			       -font => $font,
			       -relief => 'ridge',
			       -justify => 'left',
			       -width => 30);				     		     
#===========================================================Entries 
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
$LOAD_b         = $mw   -> Button(  -text => "Load & Plot",
                                    -font => $font, 
                                    -command => \&Load,
                                    -width => 10);
$Save_b         = $mw   -> Button(  -text => "Save *.png",
                                    -font => $font, 
                                    -command => \&Save,
                                    -width => 10);
#===========================================================CheckButton
$Save_cb	= $mw	-> Checkbutton ( -text => "Save *.png", 
					 -variable => \$out,
					 -onvalue =>"1",
					 -offvalue => "0");
$lock_cb	= $mw	-> Checkbutton ( -text => "lock tds*.dat", 
					 -variable => \$lock,
					 -onvalue =>"1",
					 -offvalue => "0");
                                     
#===========================================================Layout 
$header -> grid("-");
$LOAD_b -> grid($Save_b);
$directory_e->grid("-");
$filename_e->grid($lock_cb);
$comment_e->grid("-");
$status_l->grid("-");
$footnote1->grid("-");


MainLoop;

#*********************** functions *****************************
sub Load{
	$types = [ ['tds data files', '.dat'], ['Saved Plot', '.png'], ['All Files','*']];
  	$tempfile = $mw-> getOpenFile( -filetypes => $types,
  			               -defaultextension => '.dat');
 	@fullfile = split('/',$tempfile) ;
 	#print "@fullfile";
 	$filename = $fullfile[-1];
 	$directory = substr($tempfile,0,length($tempfile)-length($filename));
 	chdir $directory;
	Plot(0);
}
sub Plot{
	if ((substr($filename,0,3) ne "tds")&& $lock==1){
		$status = "Not tds*.dat";
		return;
	}
	if ($comment eq "comment"){
		$comment="";
	}
	@temp = split(/\./,$filename);
	$short_filename = $temp[0];
	$plot =  "gnuplot -e \"folder=\'$directory\';filename=\'$filename\';out=\'$_[0]\';shortname=\'$short_filename\';comment=\'$comment\'\" -p /Users/mobileryan/Dropbox/C++_programs/perl/plot_tds.gp";
	system($plot);
	if ($_[0] == 1){
		$status = "Saved -> PS_$short_filename.png";
	}else{
		$status = "Loaded $filename and plotted." ;
	}
	
}

sub Save{
	Plot(1);	
}


