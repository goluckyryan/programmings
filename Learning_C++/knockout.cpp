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
    double S = 0; //Seperation energy
    double TKEA = 250;  //kinetic energy pre nucleon
    double k = 0, k_theta = 0, k_phi = 0;
    double theta_NN =90, phi_NN =0;

    cout << "S [MeV] : ";
    cin >> S;
    cout << "T(a) [MeV] : ";
    cin >> TKEA;
    cout << "(k, theta(k), phi(k)) :";
    cin >> k >> k_theta >> k_phi;
   // cout << "(theta "

    // normal kinematics reaction  A(a, b+c)B
    FourVector v1, v2; //v1 = A, v2 = a
    FourVector resi; //recoil residual
    FourVector Neo; //effective orbital nucleon
    FourVector p1, p2; //p1 = b, p2 = c
    // CM frame
    FourVector v1_c, v2_c, Neo_c, resi_c;
    FourVector p1_c, p2_c;
    // Lab Frame
    FourVector v1_L, v2_L, Neo_L, resi_L;
    FourVector p1_L, p2_L;

    FourVector cm, cm_c, cm_L;

    Lorentzian L1, L2, L2inv;
    RotMatrix4D Rot1, Rot2;

    double mass_v1[3];
    double mass_v2[3];
    double mass_resi[3];
    double mass_p1[3];
    double mass_p2[3];

    mass_v1[1]=22, mass_v1[2]=8, mass_v1[0]   = Nucleus_Mass(mass_v1[1],mass_v1[2]);
    mass_v2[1]= 1, mass_v2[2]=1, mass_v2[0]   = Nucleus_Mass(mass_v2[1],mass_v2[2]);

    mass_p1[1]= 1, mass_p1[2]=1, mass_p1[0]   = Nucleus_Mass(mass_p1[1],mass_p1[2]);
    mass_p2[1]= 1, mass_p2[2]=1, mass_p2[0]   = Nucleus_Mass(mass_p2[1],mass_p2[2]);

    mass_resi[1]= mass_v1[1] - mass_p1[1];
    mass_resi[2]= mass_v1[2] - mass_p1[2];
    mass_resi[0]= sqrt(pow(mass_v1[0]-mass_p1[0]+S,2)-pow(k,2));

    v1.set(1, mass_v1, 0, 0, 0);
    v2.set(1, mass_v2, TKEA, 0, 0);
    resi.set(2,mass_resi,k, k_theta, k_phi);
    Neo = v1-resi;

    cm = (Neo + v2)/2;

    L1.set(-cm.beta, cm.angle[0]*rad2deg,cm.angle[1]*rad2deg);
    L2.set(cm.beta, cm.angle[0]*rad2deg,cm.angle[1]*rad2deg);
    L2inv.set(-v2.beta, v2.angle[0]*rad2deg,v2.angle[1]*rad2deg);

    cm_c = L1^cm;
    v1_c = L1^v1;
    v2_c = L1^v2;
    Neo_c = L1^Neo;

	double Etotal = sqrt(1-pow(cm.beta,2))*(v2.energy+Neo.energy);
	double k1c = sqrt((Etotal-mass_p1[0]-mass_p2[0])*(Etotal+mass_p1[0]-mass_p2[0])*(Etotal-mass_p1[0]+mass_p2[0])*(Etotal+mass_p1[0]+mass_p2[0]))/(2*Etotal);

    p1_c.set(2,mass_p1, k1c, 180-theta_NN, 180+phi_NN );
    p2_c.set(2,mass_p2, k1c, theta_NN, phi_NN);
    resi_c = v1_c + v2_c - p1_c - p2_c;

    p1 = L2^p1_c;
    p2 = L2^p2_c;

    v1_L = L2inv^v1;
    v2_L = L2inv^v2;
    Neo_L = L2inv^Neo;
    p1_L = L2inv^p1;
    p2_L = L2inv^p2;
    resi_L = L2inv^resi;

    ///================================ Display
    cout << "========================================" << endl;
    printf("A(a, b+c)B \n");
    printf("S: %5.1f MeV, T(a): %5.1f MeV \n",S,TKEA );
    printf("k: %5.1f MeV/c, Theta(k): %5.1f deg, Phi(k): %5.1f deg \n",k,k_theta,k_phi );
    printf("Theta(NN): %5.1f deg, Phi(NN): %5.1f deg \n",theta_NN,phi_NN );

    v1.printKinamatics(6,  " v1   ");
    resi.printKinamatics(0," resi ");
    cout << "\e[32m" ;
    Neo.printKinamatics(0, " Neo  "); cout << "\e[m";
    v2.printKinamatics(0,  " v2   ");
    p1.printKinamatics(0, " p1   ");
    p2.printKinamatics(0, " p2   ");

    cm.printKinamatics(0,  " cm   ");

    cout << endl;

    cm_c.printKinamatics(0,  " cm_c ");
    resi_c.printKinamatics(0, "resi_c");
    Neo_c.printKinamatics(0, "Neo_c ");
    v1_c.printKinamatics(0,  " v1_c ");
    v2_c.printKinamatics(0,  " v2_c ");
    p2_c.printKinamatics(0,  " p2_c ");
    p1_c.printKinamatics(0,  " p1_c ");
//    (Neo_c+v2_c).print("","\n");
//    (p1_c+p2_c).print("","\n");

    cout << endl;

    v1_L.printKinamatics(0,  " v1_L ");
    resi_L.printKinamatics(0, "resi_L");
    Neo_L.printKinamatics(0, " Neo_L");
    v2_L.printKinamatics(0,  " v2_L ");
    p2_L.printKinamatics(0,  " p2_L ");
    p1_L.printKinamatics(0,  " p1_L ");

    cout << endl;

    v1.print(  " v1  ","\n");
    resi.print("resi ","\n");
    Neo.print( " Neo ","\n");
    v2.print(  " v2  ","\n");
    p1.print(  " p1  ","\n");
    p2.print(  " p2  ","\n");
    cout << endl;
    printf("E_cm : %9.2f, momt. : %9.2f \n",Etotal,k1c);
    v1_c.print(  " v1_c  ","\n");
    resi_c.print("resi_c ","\n");
    Neo_c.print( " Neo_c ","\n");
    v2_c.print(  " v2_c  ","\n");
    p1_c.print(  " p1_c  ","\n");
    p2_c.print(  " p2_c  ","\n");
    cout << endl;
    v1_L.print(  " v1_L  ","\n");
    resi_L.print("resi_L ","\n");
    Neo_L.print( " Neo_L ","\n");
    v2_L.print(  " v2_L  ","\n");
    p1_L.print(  " p1_L  ","\n");
    p2_L.print(  " p2_L  ","\n");

    return 0;
}
