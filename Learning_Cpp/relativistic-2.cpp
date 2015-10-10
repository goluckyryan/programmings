#include <iostream>
#include <stdio.h>
#include <cmath>
#include "../CppLibrary/constant.h"
#include "../CppLibrary/fourVector.h"
#include "../CppLibrary/RotMatrix4D.h"
#include "../CppLibrary/lorentzian.h"

using namespace std;

int main(){
    double mass[3] = {mp_MeV, 1,  1};
    FourVector v1, v2, v1c, v2c, u1c, u2c, u1, u2;
    FourVector cm, cmc;
    Lorentzian L1, L2;
    double keA;
    
    cout << " Kinetic energy (MeV/A) : ";
    cin >> keA;


    v1.set(1, mass, keA, 0, 0);
    v2.set(4, mass, 0, 0, 0);
    
    cm = (v1+v2)/2;// center of momentum 4 vector

    L1.set(-cm.beta,cm.angle[0],cm.angle[1]);
    L2.set(cm.beta,cm.angle[0],cm.angle[1]);
    
    cmc = L1^cm;
    v1c=L1^v1;
    v2c=L1^v2;

    
    double scat_ang;
    
    cout << " scattering angle <=90 [deg] in Lab frame : ";
    cin >> scat_ang; 
    
    // 2 methods :
    //    a) seraching rotating angle
    //    b) by formula
    double delta1, delta2, test_ang1, test_ang2;
    RotMatrix4D rot;
    
    int trial;
    
    test_ang1 = 0;
    test_ang2 =180;
    
    rot.set(test_ang2,90,90);
    u1c = rot^v1c;
    u1  = L2^u1c;
    		
    delta2 = abs(u1.angle[0]*rad2deg - scat_ang);

    rot.set(test_ang1,90,90);
    u1c = rot^v1c;
    u1  = L2^u1c;
    
    delta1 = abs(u1.angle[0]*rad2deg - scat_ang);
    

    trial = 1;
  //  printf("%3d, (%10.5f,%10.5f), (%10.5f,%10.5f) \n",trial, delta1,delta2, test_ang1,test_ang2);
    
    do {
    
    	if(delta2 > delta1) {
    		test_ang2 = (test_ang1 + test_ang2)/2;
    
    		rot.set(test_ang2,90,90);
    		u1c = rot^v1c;
    		u1  = L2^u1c;
    		
    		delta2 = abs(u1.angle[0]*rad2deg - scat_ang);
    	}else{
    		test_ang1 = (test_ang1 + test_ang2)/2;
    		
    	    rot.set(test_ang1,90,90);
    		u1c = rot^v1c;
    		u1  = L2^u1c;
    
    		delta1 = abs(u1.angle[0]*rad2deg - scat_ang);
    		
    	}
    	
    	trial ++;
    	
  //  	printf("%3d, (%10.5f,%10.5f), (%10.5f,%10.5f) \n",trial, delta1,delta2, test_ang1,test_ang2);
    
    }while ((delta1> 0.005  || delta2 > 0.005 ) && trial < 50);
    
    u2c = rot^v2c;
   	u2  = L2^u2c;
    
    
    /*   emthod b
    double T,T1;
    
    T= v1.keA;
    
    T1 = T/((2*mp_MeV+T)/(2*mp_MeV)*pow(tan(scat_ang*deg2rad),2)+1);
    
    u1.set(1, mass, T1 , scat_ang,0); //set by keA
    
    u1c = L1^u1;
    
    RotMatrix4D rot (u1c.angle[0]*rad2deg, 90, 90);

    u2c= rot^v2c;

    u2 = L2^u2c;
    */
    
    

    /// Display
    v1.printKinamatics(5," v1  ");
    v2.printKinamatics(0," v2  ");
    cm.printKinamatics(0," cm  ");
    cout << "------- CM frame ----------" << endl;
    cmc.printKinamatics(0," cmc ");
    v1c.printKinamatics(0," v1c ");
    v2c.printKinamatics(0," v2c ");
    u1c.printKinamatics(0," u1c ");
    u2c.printKinamatics(0," u2c ");
    cout << "------- Lab     ----------" << endl;
    u1.printKinamatics(0," u1  ");
    u2.printKinamatics(0," u2  ");
    cout << "opening angle = " << (u1.angle[0]+u2.angle[0])*rad2deg << endl;
    
    L1.print();
    rot.print("rot");
    /*
    v1.print();cout << endl;
    v2.print();cout << endl;
    v1c.print();cout << endl;
    v2c.print();cout << endl;
    u1c.print();cout << endl;
    u2c.print();cout << endl;
    u1.print();cout << endl;
    u2.print();cout << endl;
    */
    return 0;
}
