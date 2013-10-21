#! /usr/bin/perl
use Tk;
use Math::Trig;

$c =299792458;
$amu = 931.494;
$deg2rad = 0.0174532925199;
$rad2deg = 57.2957795;

#A(a, 1+2)B

@mass = (20502.152, 938.27203, 938.27203, 938.27203, 0);
@A    = (22, 1, 1, 1, 0);
@Z    = (8, 1, 1, 1, 0);
@name = ("O","H", "H", "H", "");

@A[4] = @A[0]-@A[1];
@Z[4] = @Z[0]-@Z[1];
@mass_tmp = &Nmass(@A[4], @Z[4]);
@mass[4] = @mass_tmp[0];
@name[4] = @mass_tmp[1];


$reaction = "@A[0]@name[0](@A[1]@name[1], @A[2]@name[2]+@A[3]@name[3] )@A[4]@name[4]";

$mw = new MainWindow;
$mw -> title ("Knockout Reaction");
#$top = $mw->Toplevel();
#$frame = $mw->Frame(-borderwidth => 2, -relief => "groove");
# ----------------- buttons
$Cal_Rec        = $mw   -> Button(  -text => "Reaction",
                                        -font => "courierfont", 
                                        -command => \&Cal_Rec,
                                        -width => 10);                          
$Rec_Entry     	= $mw   -> Entry(   -textvariable => \$reaction,
				    -font => "{courierfont} 12",
                                    -width=>50);
$Cal_Rec -> grid($Rec_Entry,"-","-","-");
                        
           
$Z_Label     	= $mw   -> Label(   -text=>"Charge",
                                    -font=>"courierfont");
$A_Label     	= $mw   -> Label(   -text=>"Nucl. Mass",
                                    -font=>"courierfont");
$mass_Label     = $mw   -> Label(   -text=>"Mass [MeV]",
                                    -font=>"courierfont");
$name_Label     = $mw   -> Label(   -text=>"name",
                                    -font=>"courierfont");
                                    
$name_Label -> grid($mass_Label,$A_Label, $Z_Label);  


for( $row= 0; $row<5; $row++){
@name_Entry[$row]     = $mw   -> Entry(   -textvariable => \@name[$row],
				    -font => "{courierfont} 12",
                                    -width=>5);  
@mass_Entry[$row]     = $mw   -> Entry(   -textvariable => \@mass[$row],
				    -font => "{courierfont} 12",
                                    -width=>17);    
@Z_Entry[$row]     	= $mw   -> Entry(   -textvariable => \@Z[$row],
				    -font => "{courierfont} 12",
                                    -width=>5);
@A_Entry[$row]    	= $mw   -> Entry(   -textvariable => \@A[$row],
                                    -font => "{courierfont} 12",
                                    -width=>5);
                                                 
@name_Entry[$row] -> grid(@mass_Entry[$row],@A_Entry[$row], @Z_Entry[$row]); 

}

$S_Label     	= $mw   -> Label(   -text=>"S [MeV]",
                                    -font=>"courierfont");
$S_Entry    = $mw   -> Entry(   -textvariable => \$S,
				    -font => "{courierfont} 12",
                                    -width=>10); 
$T_Label     	= $mw   -> Label(   -text=>"T [MeV]",
                                    -font=>"courierfont");
$T_Entry    = $mw   -> Entry(   -textvariable => \$T,
				    -font => "{courierfont} 12",
                                    -width=>10); 
$S_Label -> grid($S_Entry, $T_Label, $T_Entry);
                                    
$k_Label     	= $mw   -> Label(   -text=>"k",
                                    -font=>"courierfont");
$theta_k_Label     = $mw   -> Label(   -text=>"theta_k [deg]",
                                    -font=>"courierfont");
$phi_k_Label     = $mw   -> Label(   -text=>"phi_k [deg]",
                                    -font=>"courierfont");
$k_Entry     = $mw   -> Entry(   -textvariable => \$k,
				    -font => "{courierfont} 12",
                                    -width=>10);    
$theta_k_Entry     	= $mw   -> Entry(   -textvariable => \$theta_k,
				    -font => "{courierfont} 12",
                                    -width=>10);
$phi_k_Entry    	= $mw   -> Entry(   -textvariable => \$phi_k,
                                    -font => "{courierfont} 12",
                                    -width=>10);
$k_Label -> grid($k_Entry, $theta_k_Label, $theta_k_Entry, $phi_k_Label, $phi_k_Entry);

$theta_NN_Label     = $mw   -> Label(   -text=>"theta_NN [deg]",
                                    -font=>"courierfont");
$phi_NN_Label     = $mw   -> Label(   -text=>"phi_NN [deg]",
                                    -font=>"courierfont");
$theta_NN_Entry     	= $mw   -> Entry(   -textvariable => \$theta_NN,
				    -font => "{courierfont} 12",
                                    -width=>10);
$phi_NN_Entry    	= $mw   -> Entry(   -textvariable => \$phi_NN,
                                    -font => "{courierfont} 12",
                                    -width=>10);     
$theta_NN_Label->grid($theta_NN_Entry, $phi_NN_Label, $phi_NN_Entry);                           


$E_Label     	= $mw   -> Label(   -text=>"Energy",
                                    -font=>"courierfont");
$px_Label     	= $mw   -> Label(   -text=>"Px",
                                    -font=>"courierfont");
$py_Label     = $mw   -> Label(   -text=>"Py",
                                    -font=>"courierfont");
$pz_Label     = $mw   -> Label(   -text=>"Pz",
                                    -font=>"courierfont");
                                    
$E_Label -> grid($px_Label,$py_Label, $pz_Label);  

for( $row= 0; $row<5; $row++){
@E_Entry[$row]     = $mw   -> Entry(   -textvariable => \@energy[$row],
				    -font => "{courierfont} 12",
                                    -width=>12);  
@px_Entry[$row]     = $mw   -> Entry(   -textvariable => \@px[$row],
				    -font => "{courierfont} 12",
                                    -width=>12);    
@py_Entry[$row]     	= $mw   -> Entry(   -textvariable => \@py[$row],
				    -font => "{courierfont} 12",
                                    -width=>12);
@pz_Entry[$row]    	= $mw   -> Entry(   -textvariable => \@pz[$row],
                                    -font => "{courierfont} 12",
                                    -width=>12);
                                                 
@E_Entry[$row] -> grid(@px_Entry[$row],@py_Entry[$row], @pz_Entry[$row]); 

}

MainLoop;

#*********************** functions *****************************
sub Cal_Rec {
	$row = 0;
	do {
	@A[$row] = @A_Entry[$row] -> get();
	@Z[$row] = @Z_Entry[$row] -> get();
	@mass_tmp = &Nmass(@A[$row], @Z[$row]);
	@mass[$row] = @mass_tmp[0];
	@name[$row] = @mass_tmp[1];
	$row++;
	}while ($row <4);
	
	@A[4] = @A[0]-@A[1];
	@Z[4] = @Z[0]-@Z[1];
	@mass_tmp = &Nmass(@A[4], @Z[4]);
	@mass[4] = @mass_tmp[0];
	@name[4] = @mass_tmp[1];

	$reaction = "@A[0]@name[0](@A[1]@name[1], @A[2]@name[2]+@A[3]@name[3] )@A[4]@name[4]";

	$S = $S_Entry -> get();
	$T = $T_Entry -> get();
	$k = $k_Entry -> get();
	$theta_k = $theta_k_Entry -> get();
	$phi_k = $phi_k_Entry -> get();
	$theta_NN = $theta_NN_Entry -> get();
	$phi_NN = $phi_NN_Entry -> get();
	
	@energy[0] = @mass[0];
	@px[0] = 0;
	@py[0] = 0;
	@pz[0] = 0;

	@energy[1] = @mass[1]+$T*@A[1];
	@px[1] = 0;
	@py[1] = 0;
	@pz[1] = sqrt(@energy[1]**2-@mass[1]**2);

	@energy[4] = sqrt((@mass[0]-@mass[1]+$S)**2-$k**2);
	@px[4] = $k*cos($phi_k*$deg2rad)*sin($theta_k*$deg2rad);
	@py[4] = $k*sin($phi_k*$deg2rad)*sin($theta_k*$deg2rad);
	@pz[4] = $k*cos($theta_k*$deg2rad);

	
	
}
sub Nmass{

	my @mass;
	
	$massData_file = "mass03.txt";
	open(Dat,"<",$massData_file) || die("could not open file!");
	@massData=<Dat>;
	close(Dat);
	
	$flag = 0;
	$line = 40;
		
	do{
		$A_tmp = substr($massData[$line-1],15 , 5);
		$Z_tmp = substr($massData[$line-1],10 , 5);

		
		if ( $_[0] == $A_tmp && $_[1] == $Z_tmp) {
			$m1_tmp = substr($massData[$line-1],96 , 3);
		    $m2_tmp = substr($massData[$line-1],99 ,13);
			@mass[0] = ( $m1_tmp + $m2_tmp/1e6)*$amu;
			@mass[1] = substr($massData[$line-1],19 ,3);
			$flag = 1;
		}
		
	    $line = $line + 1;
		
	}until($flag ==1 || $line > 3218);
	
	if ($flag == 0){
		@mass[0] ="no nucleus found!";
		@mass[1] ="";
	}

	return @mass;
	
}


