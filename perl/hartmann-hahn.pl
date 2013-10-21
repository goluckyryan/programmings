#! /usr/bin/perl
use Tk;
use Math::Trig;

$ge=28024.95;
$gp=42.5764;
$x=503;
$y=418;
$z=-921;

$Hallupdate="2012 April 23rd"; # this is the date for last Hall Voltage Check
@Hall2NMR=(0.41553,-0.00016); # this is the Hall Volatge - NMR freq convertor, the 1st one is slope, 2nd is intercept

$mw = new MainWindow;
$mw -> title ("Hartmann-Hahn Condition");
#$top = $mw->Toplevel();
#$frame = $mw->Frame(-borderwidth => 2, -relief => "groove");
$CalMag             = $mw   -> Button(  -text => "Mag Cal",
                                        -font => "courierfont", 
                                        -command => \&CalMag,
                                        -width => 10);
                                        
$CalHV             = $mw   -> Button(  -text => "HV Cal",
                                        -font => "courierfont", 
                                        -command => \&CalHV,
                                        -width => 10);
$CalESR             = $mw   -> Button(  -text => "ESR Cal",
                                        -font => "courierfont", 
                                        -command => \&CalESR,
                                        -width => 10);
$CalNMR             = $mw   -> Button(  -text => "NMR Cal",
                                        -font => "courierfont", 
                                        -command => \&CalNMR,
                                        -width => 10);

$MagField_Label     = $mw   -> Label(   -text=>"Mag Field [mT]",
                                        -font=>"courierfont")
                            -> grid();
$MagField_Entry     = $mw   -> Entry(   -textvariable => \$H,
										-font => "{courierfont} 12",
                                        -width=>10);
$MagField_Entry-> grid($CalMag);

$HallVoltage_Label  = $mw   -> Label(   -text=>"Hall Voltage* [mV]",
                                        -font=>"courierfont") 
                            -> grid();
$HallVoltage_Entry  = $mw   -> Entry(   -textvariable => \$HV,
										-font => "{courierfont} 12",
                                        -width=>10);
$HallVoltage_Entry->grid($CalHV);


$ESR_Label          = $mw   -> Label(   -text=>"ESR freq [MHz]",
                                        -font=>"courierfont") 
                            -> grid();
$ESR_Entry          = $mw   -> Entry(   -font => "{courierfont} 12",
										-textvariable => \$ESR,
                                        -width=>10);
$ESR_Entry->grid($CalESR);

$NMR_Label          = $mw   -> Label(   -text=>"NMR freq [MHz]",
                                        -font=>"courierfont") 
                            -> grid();
$NMR_Entry          = $mw   -> Entry(   -textvariable => \$NMR,
										-font => "{courierfont} 12",
                                        -width=>10);
$NMR_Entry->grid($CalNMR);
		     
$Remark_Label       = $mw   -> Label(   -text=>"*the data is from $Hallupdate",
                                        -font=>"courierfont 8") 
                            -> grid();






MainLoop;

#*********************** functions *****************************

sub CalMag {
	$H = $MagField_Entry -> get();
	&u_energy($H);
    print "Triplet level [MHz] : @energy\n";
    $ESR=$energy[1]-$energy[2];
    $NMR=$H*$gp/1000;
    $HV=($NMR-$Hall2NMR[1])/$Hall2NMR[0];
}

sub CalHV {
	$HV = $HallVoltage_Entry -> get();
	$NMR = $HV*$Hall2NMR[0]+$Hall2NMR[1];
	&nmr($NMR);
	&u_energy($H);
    print "Triplet level [MHz] : @energy\n";
    $ESR=$energy[1]-$energy[2];
}

sub CalESR {
	$ESR = $ESR_Entry -> get();
	&field($ESR);
	&u_energy($H);
    print "Triplet level [MHz] : @energy\n";
    $NMR=$H*$gp/1000;
    $HV=($NMR+0.00016)/0.41553;
}

sub CalNMR {
	$NMR = $NMR_Entry -> get();
	&nmr($NMR);
	&u_energy($H);
    print "Triplet level [MHz] : @energy\n";
    $ESR=$energy[1]-$energy[2];
    $HV=($NMR+0.00016)/0.41553;
}


sub u_energy{
    $energy[0]=($y+$z)/2+sqrt((($y-$z)/2)**2+($ge*$_[0]/1000)**2);
    $energy[1]=$x;
    $energy[2]=($y+$z)/2-sqrt((($y-$z)/2)**2+($ge*$_[0]/1000)**2);
}

sub field{
    $H = sqrt (644.2824075927322-1.921319306936577*$_[0]+0.0012732400973724773*($_[0])**2);
}

sub nmr{
    $H = $_[0]/$gp*1000;
}

