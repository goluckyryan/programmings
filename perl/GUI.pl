#!/usr/local/bin/perl
use Tk;
# Main Window
my $mw = new MainWindow;
$mw -> title ("Capture External Program Output");

#Frame setting
my $top = $mw -> Frame()
	      -> pack(-side => 'top', -fill => 'x');
my $left1 = $top -> Frame()
                 -> pack(-side => 'left', -pady => 5 , -padx => 5);
my $left2 = $top -> Frame()
                 -> pack(-side => 'left', -pady => 5 , -padx => 5);
my $left3 = $top -> Frame()
                 -> pack(-side => 'left', -pady => 5 , -padx => 5);

# Lable and Entry 
my $MA_Label = $left1 -> Label(-text=>"MA",-font=>"courierfont") 
                      -> pack(-expand => 1, -fill => "both");
my $MA_Entry = $left1 -> Entry(-text => "22", -width=>5)
		      -> pack(-expand => 1, -fill => "both");

my $TiL_Label = $left1 -> Label(-text=>"TiL",-font=>"courierfont") 
                       -> pack(-expand => 1, -fill => "both");
my $TiL_Entry = $left1 -> Entry(-text => "261",-width=>5)
		       -> pack(-expand => 1, -fill => "both");

my $k_Label = $left2 -> Label(-text=>"k",-font=>"courierfont") 
                     -> pack(-expand => 1, -fill => "both");
my $k_Entry = $left2 -> Entry(-text => "100",-width=>5)
		     -> pack(-expand => 1, -fill => "both");
my $thk_Label = $left2 -> Label(-text=>"theta k",-font=>"courierfont") 
                       -> pack(-expand => 1, -fill => "both");
my $thk_Entry = $left2 -> Entry(-text => "90",-width=>5)
		       -> pack(-expand => 1, -fill => "both");

my $thNN_Label = $left3 -> Label(-text=>"theta_NN",-font=>"courierfont") 
                        -> pack(-expand => 1, -fill => "both");
my $thNN_Entry = $left3 -> Entry(-text => "90",-width=>5)
		        -> pack(-expand => 1, -fill => "both");
my $S_Label = $left3 -> Label(-text=>"S",-font=>"courierfont") 
                     -> pack(-expand => 1, -fill => "y");
my $S_Entry = $left3 -> Entry(-text => "10",-width=>5)
		     -> pack(-expand => 1, -fill => "x");

my $T1L_Label = $mw -> Label(-text=>"T1L",-font=>"courierfont") 
                     -> pack(-expand => 1, -fill => "y");
my $T1L_Entry = $mw -> Entry(-textvariable => \$data[2],-width=>5)
		     -> pack(-expand => 1, -fill => "x");



# calculate
my $knockout = $mw -> Button(-text => "Run", -font => "courierfont", -command => \&program)
                   -> pack();
my $button = $mw -> Button(-text => "Quit", -font=>"courierfont",-command => sub{ print "Bye!\n";exit(0);})
                 -> pack();

MainLoop;

sub exitProgram {
        $mw->messageBox(-message=>"Goodbye !! ",-font=>"courierfont");
        exit;
}

sub program {
	$MA = $MA_Entry -> get();
	$TiL = $TiL_Entry -> get();
	$thk = $thk_Entry -> get();
	$k = $k_Entry -> get();
	$thNN = $thNN_Entry -> get();
	$S = $S_Entry -> get();
        @data = `./test.o $MA $TiL $k $thk $thNN $S `;
	#print @data;
	print $data[2];
        #print $data[6]."\n";

}
