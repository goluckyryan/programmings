#include <iostream>
#include <stdio.h>
#include <cmath>
#include "../CppLibrary/constant.h"
#include "../CppLibrary/nuclei_mass.h"
#include "../CppLibrary/fourVector.h"
#include "../CppLibrary/RotMatrix4D.h"
#include "../CppLibrary/lorentzian.h"

using namespace std;

int main(){
    double TKEA = 250;  //kinetic energy pre nucleon
    double S1 = 0, S2 = 0; //Seperation energy
    double k1 = 12170, k1_theta = 0, k1_phi = 0;
    double k2 = 0, k2_theta = 0, k2_phi = 0;
    double theta_NN =90, phi_NN =0;

    // normal kinematics reaction  A(a, 2p+b)B
    FourVector vA, vB;
    FourVector va, vb; 
    FourVector v1, v2; 
    FourVector p1, p2; 
    // CM frame
    FourVector vA_c, vB_c;
    FourVector va_c, vb_c;
    FourVector v1_c, v2_c;
    FourVector p1_c, p2_c;

    FourVector cm, cm_c;

    Lorentzian L1, L2 ;
    RotMatrix4D Rot1, Rot2;

    double mass_vA[3], mass_vB[3];
    double mass_va[3], mass_vb[3];
    double mass_v1[3], mass_v2[3];
    double mass_p1[3], mass_p2[3];

    mass_vA[1]=25, mass_vA[2]=9, mass_vA[0]   = Nucleus_Mass(mass_vA[1],mass_vA[2]);
    mass_vB[1]=12, mass_vB[2]=6, mass_vB[0]   = Nucleus_Mass(mass_vB[1],mass_vB[2]);

    mass_p1[1]= 1, mass_p1[2]=1, mass_p1[0]   = Nucleus_Mass(mass_p1[1],mass_p1[2]);
    mass_p2[1]= 1, mass_p2[2]=1, mass_p2[0]   = Nucleus_Mass(mass_p2[1],mass_p2[2]);

	mass_va[1]= mass_vA[1]-mass_p1[1];
	mass_va[2]= mass_vA[2]-mass_p1[2];
    mass_va[0]= sqrt(pow(mass_vA[0]-mass_p1[0]+S1,2)-pow(k1,2));
    
	mass_vb[1]= mass_vB[1]-mass_p2[1];
	mass_vb[2]= mass_vB[2]-mass_p2[2];
    mass_vb[0]= sqrt(pow(mass_vB[0]-mass_p2[0]+S2,2)-pow(k2,2));
    
    vA.set(1, mass_vA, TKEA, 0, 0);
    vB.set(1, mass_vB, 0, 0, 0);
    va.set(2, mass_va, k1, k1_theta, k1_phi);
    vb.set(2, mass_vb, k2, k2_theta, k2_phi);
    v1 = vA-va;
    v2 = vB-vb;

    cm = (v1 + v2)/2;

    L1.set(-cm.beta, cm.angle[0]*rad2deg,cm.angle[1]*rad2deg);
    L2.set(cm.beta, cm.angle[0]*rad2deg,cm.angle[1]*rad2deg);

    cm_c = L1^cm;
    vA_c = L1^vA; vB_c = L1^vB;
    vb_c = L1^vb; vb_c = L1^vb;
    v1_c = L1^v1; v2_c = L1^v2;

	double Etotal = sqrt(1-pow(cm.beta,2))*(v2.energy+v1.energy);
	double k1c = sqrt((Etotal-mass_p1[0]-mass_p2[0])*(Etotal+mass_p1[0]-mass_p2[0])*(Etotal-mass_p1[0]+mass_p2[0])*(Etotal+mass_p1[0]+mass_p2[0]))/(2*Etotal);

    p1_c.set(2,mass_p1, k1c, 180-theta_NN, 180+phi_NN );
    p2_c.set(2,mass_p2, k1c, theta_NN, phi_NN);

    p1 = L2^p1_c; p2 = L2^p2_c;

    ///================================ Display
    cout << "========================================" << endl;
    printf("B(A, 2p+a)b \n");
    printf("S1: %5.1f MeV, S2: %5.1f MeV, T(A): %5.1f MeV \n",S1, S2,TKEA );
    printf("k1: %5.1f MeV/c, Theta(k1): %5.1f deg, Phi(k1): %5.1f deg \n",k1,k1_theta,k1_phi );
    printf("k2: %5.1f MeV/c, Theta(k2): %5.1f deg, Phi(k2): %5.1f deg \n",k2,k2_theta,k2_phi );
    printf("Theta(NN): %5.1f deg, Phi(NN): %5.1f deg \n",theta_NN,phi_NN );

    vA.printKinamatics(6,  "  A   ");
    vB.printKinamatics(0,  "  B   ");
    p1.printKinamatics(0,  " p1   ");
    p2.printKinamatics(0,  " p2   ");
    va.printKinamatics(0,  "  a   ");
    vb.printKinamatics(0,  "  b   ");
    v1.printKinamatics(0,  " A-a  ");
    v2.printKinamatics(0,  " B-b  ");
    cout << endl;
    (vA+vB).printKinamatics(0,  " sum  ");
    (p1+p2+va+vb).printKinamatics(0,  " sum  ");

	cout << endl;
    cm.printKinamatics(0,  " cm   ");

    cout << endl;

    cm_c.printKinamatics(0,  " cm_c ");
    vA_c.printKinamatics(0,  "  A_c ");
    vB_c.printKinamatics(0,  "  B_c ");
    p1_c.printKinamatics(0,  " p1_c ");
    p2_c.printKinamatics(0,  " p2_c ");
    va_c.printKinamatics(0,  "  a_c ");
    vb_c.printKinamatics(0,  "  b_c ");
    v1_c.printKinamatics(0,  " A-a_c");
    v2_c.printKinamatics(0,  " B-b_c");

    cout << endl;

	vA.print(" A   ", "\n");
	vB.print(" B   ", "\n");
	p1.print(" p1  ", "\n");
	p2.print(" p2  ", "\n");
	va.print(" a   ", "\n");
	vb.print(" b   ", "\n");
	v1.print(" A-a ", "\n");
	v2.print(" B-b ", "\n");
	cm.print(" cm  ", "\n");
	
    cout << endl;
    printf("E_cm : %9.2f, momt. : %9.2f \n",Etotal,k1c);
    cout << endl;

	cm_c.print(" cm_c  ", "\n");    
	vA_c.print(" A_c   ", "\n");
	vB_c.print(" B_c   ", "\n");
	p1_c.print(" p1_c  ", "\n");
	p2_c.print(" p2_c  ", "\n");
	va_c.print(" a_c   ", "\n");
	vb_c.print(" b_c   ", "\n");
	v1_c.print(" A-a_c ", "\n");
	v2_c.print(" B-b_c ", "\n");
	


    return 0;
}
