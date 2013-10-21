#!/usr/local/bin/perl
use Tk;
# Main Window
$mw = new MainWindow;
$mw -> title ("using Configure to change the botton");


# Lable and Entry 
$button = $mw->Button(	-text 	=> "ADD",
			-command => \&change);
$stop_b = $mw->Button(	-text 	=> "Minus",
			-command => \&change);
		

#Display setting
$button->grid();

MainLoop;

sub change {
	$n=$n+1;
        $button-> configure(	-text => $n);
        if ($n==10){
        	$stop_b->grid();
        	$button-> configure(-width => 20);
        }
}

