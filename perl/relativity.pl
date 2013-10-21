#! /usr/bin/perl
use Tk;
use Math::Trig;

$c =299792458;
$amu = 931.494;
$length =1;

$mass=938.27203;
$A = 1;
$Z = 1;
$name = " H";

$mw = new MainWindow;
$mw -> title ("Relativistic Calculation");
#$top = $mw->Toplevel();
#$frame = $mw->Frame(-borderwidth => 2, -relief => "groove");
# ----------------- buttons
$Cal_mass             = $mw   -> Button(  -text => "call Mass",
                                        -font => "courierfont", 
                                        -command => \&Cal_mass,
                                        -width => 10);
                                        
$Cal_T             = $mw   -> Button(  -text => "K.E. Cal",
                                        -font => "courierfont", 
                                        -command => \&Cal_T,
                                        -width => 10);
                                        
$Cal_momt         = $mw   -> Button(  -text => "momt. Cal",
                                        -font => "courierfont", 
                                        -command => \&Cal_momt,
                                        -width => 10);
                                        
$Cal_gamma         = $mw   -> Button(  -text => "Gamma Cal",
                                        -font => "courierfont", 
                                        -command => \&Cal_gamma,
                                        -width => 10);
                                        
$Cal_beta          = $mw   -> Button(  -text => "beta Cal",
                                        -font => "courierfont", 
                                        -command => \&Cal_beta,
                                        -width => 10);     
                                                                          
$Cal_ToF            = $mw   -> Button(  -text => "ToF + len Cal",
                                        -font => "courierfont", 
                                        -command => \&Cal_ToF,
                                        -width => 10);

$Cal_Brho            = $mw   -> Button(  -text => "Brho Cal",
                                        -font => "courierfont", 
                                        -command => \&Cal_Brho,
                                        -width => 10);                                        

# ----------------- Label and entry
$Z_Label     	= $mw   -> Label(   -text=>"Charge",
                                    -font=>"courierfont");
$A_Label     	= $mw   -> Label(   -text=>"Nucl. Mass",
                                    -font=>"courierfont")
                        -> grid($Z_Label);


$Z_Entry     	= $mw   -> Entry(   -textvariable => \$Z,
				                            -font => "{courierfont} 12",
                                            -width=>10);
$A_Entry     	= $mw   -> Entry(   -textvariable => \$A,
				                            -font => "{courierfont} 12",
                                            -width=>10)
                        ->grid($Z_Entry);
                        
                        
$name_Entry     	= $mw   -> Entry(   -textvariable => \$name,
				                            -font => "{courierfont} 12",
                                            -width=>10);                        

$mass_Label     	= $mw   -> Label(   -text=>"Mass [MeV]",
                                        -font=>"courierfont")
                            -> grid($name_Entry);       
$mass_Entry     	= $mw   -> Entry(   -textvariable => \$mass,
				                            -font => "{courierfont} 12",
                                            -width=>17)
                            ->grid($Cal_mass);      


$T_Label     	= $mw   -> Label(   -text=>"K.E. [MeV/u]",
                                 -font=>"courierfont")
                        -> grid();
$T_Entry     	= $mw   -> Entry(   -textvariable => \$T,
				                            -font => "{courierfont} 12",
                                            -width=>17)
                       -> grid($Cal_T);
                       
$momt_Label     	= $mw   -> Label(   -text=>"momt. [MeV/c]",
                                 -font=>"courierfont")
                            -> grid();
$momt_Entry     	= $mw   -> Entry(   -textvariable => \$momt,
				                            -font => "{courierfont} 12",
                                            -width=>17)
                            -> grid($Cal_momt);


$gamma_Label  	= $mw   -> Label(   -text=>"Gamma",
                                    -font=>"courierfont") 
                        -> grid();
                         
$gamma_Entry 	 = $mw   -> Entry(   -textvariable => \$gamma,
				     -font => "{courierfont} 12",
                                     -width=>17);
$gamma_Entry->grid($Cal_gamma);


$beta_Label  	= $mw   -> Label(   -text=>"beta",
                                    -font=>"courierfont") 
                        -> grid();
$beta_Entry  	= $mw   -> Entry(   -font => "{courierfont} 12",
				    -textvariable => \$beta,
                                    -width=>17);
$beta_Entry->grid($Cal_beta);

$length_Label  	= $mw   -> Label(   -text=>"length [m]",
                                    -font=>"courierfont") 
                        -> grid();
$length_Entry  	= $mw   -> Entry(   -font => "{courierfont} 12",
				    -textvariable => \$length,
                                    -width=>17)
                        -> grid();
                        
$ToF_Label   	 = $mw   -> Label(   -text=>"ToF [ns]",
                                        -font=>"courierfont") 
                         -> grid();
$ToF_Entry     	= $mw    -> Entry(   -textvariable => \$ToF,
					 -font => "{courierfont} 12",
                                        -width=>17);
$ToF_Entry->grid($Cal_ToF);
		     
$Brho_Label   	 = $mw   -> Label(   -text=>"Brho [Tm]",
                                        -font=>"courierfont") 
                         -> grid();
$Brho_Entry     	= $mw    -> Entry(   -textvariable => \$Brho,
					 -font => "{courierfont} 12",
                                        -width=>17);
$Brho_Entry->grid($Cal_Brho);

MainLoop;

#*********************** functions *****************************
sub Cal_mass {
	$A = $A_Entry -> get();
	$Z = $Z_Entry -> get();
	&Nmass($A,$Z);
}

sub Cal_T {
	$T = $T_Entry -> get();
	$length = $length_Entry -> get();
	$A = $A_Entry -> get();
	$Z = $Z_Entry -> get();
	&Nmass($A,$Z);
	$gamma=($T*$A+$mass)/$mass;
	$beta=sqrt(1-(1/$gamma)**2);
	$momt=$mass*$gamma*$beta;
	&ToF_function($beta,$length);
	$Brho = $mass*$beta*$gamma/$Z/$c*1e6;
#	printf "K.E. : %6.2f ; Gamma : %6.4f ; Beta : %6.4f ; Brho : %6.2f\n",$T,$gamma,$beta,$Brho;
}

sub Cal_momt {
	$momt = $momt_Entry -> get();
	$length = $length_Entry -> get();
	$A = $A_Entry -> get();
	$Z = $Z_Entry -> get();
	&Nmass($A,$Z);
	$T = (sqrt($mass**2+$momt**2)-$mass)/$A;
	$gamma=($T*$A+$mass)/$mass;
	$beta=sqrt(1-(1/$gamma)**2);
	&ToF_function($beta,$length);
	$Brho = $mass*$beta*$gamma/$Z/$c*1e6;
#	printf "K.E. : %6.2f ; Gamma : %6.4f ; Beta : %6.4f ; Brho : %6.2f\n",$T,$gamma,$beta,$Brho;
}

sub Cal_gamma {
	$gamma = $gamma_Entry -> get();
	$length = $length_Entry -> get();
	$A = $A_Entry -> get();
	$Z = $Z_Entry -> get();
	&Nmass($A,$Z);
	if ($gamma < 1 ){
		$gamma = 1;
	}
	$T = $mass*($gamma-1)/$A;
	$beta=sqrt(1-(1/$gamma)**2);
	$momt=$mass*$gamma*$beta;
	&ToF_function($beta,$length);
	$Brho = $mass*$beta*$gamma/$Z/$c*1e6;
#	printf "K.E. : %6.2f ; Gamma : %6.4f ; Beta : %6.4f ; Brho : %6.2f\n",$T,$gamma,$beta,$Brho;

}

sub Cal_beta {
	$beta = $beta_Entry -> get();
	$length = $length_Entry -> get();
	$A = $A_Entry -> get();
	$Z = $Z_Entry -> get();
	&Nmass($A,$Z);
	if ($beta >= 1){
		$beta = "   >= 1 !!!";
		$gamma = " ";
		$T = "";
	}else {
		$gamma = 1/sqrt(1-($beta)**2);
		$T = $mass*($gamma-1)/$A;
		$momt=$mass*$gamma*$beta;
		&ToF_function($beta,$length);
	    $Brho = $mass*$beta*$gamma/$Z/$c*1e6;
#		printf "K.E. : %6.2f ; Gamma : %6.4f ; Beta : %6.4f ; Brho : %6.2f\n",$T,$gamma,$beta,$Brho;
	}
}

sub Cal_ToF {
	$ToF = $ToF_Entry -> get();
	$length = $length_Entry -> get();
	$A = $A_Entry -> get();
	$Z = $Z_Entry -> get();
	&Nmass($A,$Z);
	$beta_check = $length*1000000000/($c*$ToF);
	if ($beta_check > 1){
		$beta ="  > 1 !!!!  ";
		$gamma = " ";
		$T = "";
	}else{
		$beta = $beta_check;
		$gamma = 1/sqrt(1-($beta)**2);
		$T = $mass*($gamma-1)/$A;
		$momt=$mass*$gamma*$beta;
	    $Brho = $mass*$beta*$gamma/$Z/$c*1e6;
#		printf "K.E. : %6.2f ; Gamma : %6.4f ; Beta : %6.4f ; Brho : %6.2f\n",$T,$gamma,$beta,$Brho;
	}
}

sub Cal_Brho {

	$Brho = $Brho_Entry -> get();
	$length = $length_Entry -> get();
	$A = $A_Entry -> get();
	$Z = $Z_Entry -> get();
	&Nmass($A,$Z);
	$T   = (sqrt(($Brho*$Z*$c/1e6)**2+$mass**2)-$mass)/$A;
	$gamma=($T*$A+$mass)/$mass;
	$beta=sqrt(1-(1/$gamma)**2);
	$momt=$mass*$gamma*$beta;
	&ToF_function($beta,$length);
#	printf "K.E. : %6.2f ; Gamma : %6.4f ; Beta : %6.4f ; Brho : %6.2f\n",$T,$gamma,$beta,$Brho;
}


sub ToF_function{
	if ($_[0] == 0){
	    $ToF = "INFINITY";
	}else{
	    $ToF = $_[1]*1000000000/($c*$_[0]);
	}
}
	
	
sub Nmass{
	$massData_file = "mass03.txt";
	open(Dat,"<",$massData_file) || die("could not open file!");
	@massData=<Dat>;
	close(Dat);
	
	$flag = 0;
	$line = 40;
	
	#print "$_[0], $_[1] \n";
	
	do{
		$A_tmp = substr($massData[$line-1],15 , 5);
		$Z_tmp = substr($massData[$line-1],10 , 5);


	#	print $massData[$line-1];
	#	print "$line,  $A_tmp, $Z_tmp \n";
		
		if ( $_[0] == $A_tmp && $_[1] == $Z_tmp) {
			$m1_tmp = substr($massData[$line-1],96 , 3);
		    $m2_tmp = substr($massData[$line-1],99 ,13);
			$mass = ( $m1_tmp + $m2_tmp/1e6)*$amu;
			$name = substr($massData[$line-1],19 ,3);
			$flag = 1;
		}
		
	    $line = $line + 1;
		
	}until($flag ==1 || $line > 3218);
	
	if ($flag == 0){
		$mass ="no nucleus found!";
		$name ="";
	}
	
	
}

