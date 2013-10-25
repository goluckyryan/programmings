/*  Knockout of O(p,2p)R

The Lorentz Tranform on aribtary direction is well discrpted in Goldstien P .281

k(vector): momentum of a proton in Oxygen nucleus
Theta_k:   direction of the momentum of a proton in O nucleus
Theta_NN:  scattering angle in 2-nucleon center of mass system
S:         separation energys

***** suffix notation ****
suffix "L" is Lab frame
suffix "" is Oxygen frame
suffix "c" is CM frame
suffix "X" is experiment

***** notation ****
k is for momentum
P is for 4-momentum
E is Total relativistic energy
T is for Kinetic energy

***************** Procedure
we can transform the mulit-bpdy to 2-body scattering

in nucleus frame
A(a, 1 + 2) Resi = > Neo(a, 1) 2, such that Neo = A - Resi

by Lorentz transform of center of momentum 4-vector of New and a

then set the Theta_NN and Phi_NN in CM frame by rotation operator.

transform back to nucleus frame and lab frame

done

***************** Reverse problem

given Pi, P1, P2, find k, S, Theta_NN, Phi

Pi={Ei,0,0,ki}
P1 = {E1, k1*sin(Theta_P1), 0, k1*cos(Theta_P1)}
P2 = {E2, k2*sin(Theta_P2)*cos(Phi_P2), k2*sin(Theta_P2)*sin(Phi_P2), k2*cos(Theta_P2)}

S = sqrt((Ei+Mo-E1-E2)^2-(ki-k1-k2)^2)-Mo+mn

k = ki-k1-k2

***********************************/

#include <iostream> // enable cin, cout
#include <sstream> // enable string control
#include <cmath> // math , enable simple math function
#include <iomanip>
#include <stdio.h>
#include <stdlib.h> // standard General Utlilities Library
#include <fstream> // File I/O
#include <time.h>
#include "../CppLibrary/constant.h"
#include "../CppLibrary/nuclei_mass.h"
#include "../CppLibrary/fourVector.h"
#include "../CppLibrary/RotMatrix4D.h"
#include "../CppLibrary/lorentzian.h"

using namespace std; // declare a namespace "std", every variable in this code is inside "std"

//variable___________________________________________________________________
int A_num;
int Z_num;
double TKEA; //Kinetic energy per nucleon of A in Labframe
double k; //momentum of orbial neutron
double Theta_k, Phi_k;
double Theta_NN, Phi_NN;
double S;

string proj="O", residual="O";

//v1(v2, 1 + 2) resi
double mass_v1[3];
double mass_v2[3];
double mass_p1[3];
double mass_p2[3];
double mass_resi[3];
double mass_resi_gs;

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

    Lorentzian L1, L2, L3;


//prototype____________________________________________________________________
void Display();
void Display4V();

double DSCfactor(FourVector A, FourVector C ,double beta);  // dsc from oxygen frame A to frame C

void Exp(char arg[]);
void Knockout( char argv[]);

void Output(string filename);


//function___________________________________________________________________

void Display(){

	//cout << endl ;
    cout << "========================================" << endl;

    printf("A(a, b+c)B = %3.0f%s(p, p1+p2)%3.0f%s  => Neo(p,p1)p2 \n", mass_v1[2], proj.c_str(), mass_resi[2], residual.c_str());
    printf("S: %5.1f MeV, T(a): %5.1f MeV/A \n",S,TKEA );
    printf("k: %5.1f MeV/c, Theta(k): %5.1f deg, Phi(k): %5.1f deg \n",k,Theta_k,Phi_k );
    printf("Theta(NN): %8.3f deg, Phi(NN): %8.3f deg \n",Theta_NN,Phi_NN );
    printf("DSC factor for p2 from nucleus frame to Lab frame = %12.4f \n", DSCfactor(p2,p2_L, v2.beta));

    cout << "-----\e[33m Nucleus Frame \e[m------"<< endl;
    v1.printKinamatics(6,  "  A   ");
    v2.printKinamatics(0,  "  a   ");
    resi.printKinamatics(0," resi ");
    Neo.printKinamatics(0, " Neo  ");
    p1.printKinamatics(0,  "  b   ");
    p2.printKinamatics(0,  "  c   ");
/*    cm.printKinamatics(0,  " cm   ");
    cout << "-----\e[33m CM Frame \e[m------"<< endl;
    cm_c.printKinamatics(0,  " cm_c ");
    v1_c.printKinamatics(0,  "  A_c ");
    v2_c.printKinamatics(0,  "  a_c ");
    resi_c.printKinamatics(0,"resi_c");
    Neo_c.printKinamatics(0, "Neo_c ");
    p1_c.printKinamatics(0,  "  b_c ");
    p2_c.printKinamatics(0,  "  c_c ");   */
    cout << "-----\e[33m Lab Frame \e[m----------"<<endl;
    v1_L.printKinamatics(0,  "  A_L ");
    v2_L.printKinamatics(0,  "  a_L ");
    resi_L.printKinamatics(0,"resi_L");
    Neo_L.printKinamatics(0, " Neo_L");


    cout <<                  "  b_L ";
    printf("%3.0f ", p1_L.A);
    printf("%3.0f ", p1_L.Z);
    printf("%8.2f ", p1_L.mass);
    printf("%8.2f ", p1_L.energy);
    cout << "\e[32m";
    printf("%8.2f ", p1_L.keA); cout << "\e[m";
    printf("%8.2f ", p1_L.momentum);
    printf("%8.4f ", p1_L.beta);
    cout << "\e[32m";
    printf("%8.2f ", p1_L.angle[0]*rad2deg);
    printf("%8.2f ", p1_L.angle[1]*rad2deg);
    cout << "\e[m" << endl;


    cout <<"  c_L ";
    printf("%3.0f ", p2_L.A);
    printf("%3.0f ", p2_L.Z);
    printf("%8.2f ", p2_L.mass);
    printf("%8.2f ", p2_L.energy);
    cout << "\e[32m";
    printf("%8.2f ", p2_L.keA); cout << "\e[m";
    printf("%8.2f ", p2_L.momentum);
    printf("%8.4f ", p2_L.beta);
    cout << "\e[32m";
    printf("%8.2f ", p2_L.angle[0]*rad2deg);
    printf("%8.2f ", p2_L.angle[1]*rad2deg);
    cout << "\e[m"<<endl;

	cout<< "======================================================="<<endl;
}

void Display4V(){

	//cout << endl ;
    cout << "========================================" << endl;

    printf("A(a, b+c)B = %3.0f%s(p, p1+p2)%3.0f%s  => Neo(p,p1)p2 \n", mass_v1[2], proj.c_str(), mass_resi[2], residual.c_str());
    printf("S: %5.1f MeV, T(a): %5.1f MeV/A \n",S,TKEA );
    printf("k: %5.1f MeV/c, Theta(k): %5.1f deg, Phi(k): %5.1f deg \n",k,Theta_k,Phi_k );
    printf("Theta(NN): %5.1f deg, Phi(NN): %5.1f deg \n",Theta_NN,Phi_NN );
    printf("DSC factor for p2 from nucleus frame to Lab frame = %12.4f \n", DSCfactor(p2,p2_L, v2.beta));

    v1.print("  A   ","\n");
    v2.print("  a   ","\n");
    resi.print(" resi ","\n");
    Neo.print(" Neo  ","\n");
    p1.print( "  b   ","\n");
    p2.print( "  c   ","\n");
    cm.print( " cm   ","\n");
    cout << "---------------------"<< endl;
    cm_c.print( " cm_c ","\n");
    v1_c.print( "  A_c ","\n");
    v2_c.print( "  a_c ","\n");
    resi_c.print("resi_c","\n");
    Neo_c.print("Neo_c ","\n");
    p1_c.print( "  b_c ","\n");
    p2_c.print( "  c_c ","\n");
//    (Neo_c+v2_c).print("","\n");
//    (p1_c+p2_c).print("","\n");
    cout << "---------------------"<<endl;
    v1_L.print( "  A_L ","\n");
    v2_L.print( "  a_L ","\n");
    resi_L.print("resi_L","\n");
    Neo_L.print(" Neo_L","\n");
    p1_L.print( "  b_L ","\n");
    p2_L.print( "  c_L ","\n");

    cout << endl;

	cout<< "======================================================="<<endl;
}

double DSCfactor(FourVector A, FourVector C, double beta){
    // dsc from frame A to frame C
    //beta is the relative speed;

    double pA = A.momentum;
    double pC = C.momentum;
    double Theta_A = A.angle[0];
    double Theta_C = C.angle[0];

    double gamma = 1/sqrt(1-pow(beta,2));

    return pow(pC,2)/pow(pA,2)/(cos(Theta_A)*cos(Theta_C)+gamma*sin(Theta_A)*sin(Theta_C));

}

void Exp( char *argv[]){

    double KE_1, Theta_1, Phi_1;
    double KE_2, Theta_2, Phi_2;

    Z_num    = atoi(argv[1]);
    A_num    = atoi(argv[2]);
    TKEA     = atof(argv[3]);
    KE_1     = atof(argv[4]);
    Theta_1  = atof(argv[5]);
    Phi_1    = atof(argv[6]);
    KE_2     = atof(argv[7]);
    Theta_2  = atof(argv[8]);
    Phi_2    = atof(argv[9]);

    mass_v1[1] = (double) Z_num;
    mass_v1[2] = (double) A_num;
    mass_v1[0] = Nucleus_Mass(mass_v1[1],mass_v1[2]);
    proj = Nucleus_Name(mass_v1[1],mass_v1[2]);
    mass_v2[1]= 1, mass_v2[2]=1, mass_v2[0]   = Nucleus_Mass(mass_v2[1],mass_v2[2]);

    mass_p1[1]= 1, mass_p1[2]=1, mass_p1[0]   = Nucleus_Mass(mass_p1[1],mass_p1[2]);
    mass_p2[1]= 1, mass_p2[2]=1, mass_p2[0]   = Nucleus_Mass(mass_p2[1],mass_p2[2]);

    mass_resi[1]= mass_v1[1] - mass_p1[1];
    mass_resi[2]= mass_v1[2] - mass_p1[2];
    mass_resi_gs = Nucleus_Mass(mass_resi[1],mass_resi[2]);
    residual = Nucleus_Name(mass_resi[1],mass_resi[2]);

    v2.set(1,mass_v2, TKEA,180,0);

    v1_L.set(4, mass_v1, v2.beta, 0, 0);
    v2_L.set(1, mass_v2, 0, 0, 0);

    p1_L.set(1,mass_p1, KE_1, Theta_1, Phi_1);
    p2_L.set(1,mass_p2, KE_2, Theta_2, Phi_2);

    resi_L = v1_L+v2_L-p1_L -p2_L;
    Neo_L = v1_L-resi_L;

    cm = (p1_L+p2_L)/2;

    L1.set(-cm.beta, cm.angle[0]*rad2deg,cm.angle[1]*rad2deg); // Lab to CM
    L2.set(cm.beta, cm.angle[0]*rad2deg,cm.angle[1]*rad2deg);  // CM to Lab
    L3.set(v2.beta, v2.angle[0]*rad2deg,v2.angle[1]*rad2deg); // Lab to Nucleus

    cm_c = L1^cm;
    v1_c = L1^v1_L;
    v2_c = L1^v2_L;
    p1_c = L1^p1_L;
    p2_c = L1^p2_L;
    resi_c = L1^resi_L;
    Neo_c = v1_c-resi_c;

    v1 = L3^v1_L;
    v2 = L3^v2_L;
    p1 = L3^p1_L;
    p2 = L3^p2_L;
    resi = v1 + v2 - p1 - p2;
    Neo = v1 - resi;

    k = Neo.momentum;
    Theta_k = Neo.angle[0]*rad2deg;
    Phi_k = Neo.angle[1]*rad2deg;

    Theta_NN = p1_c.angle[0]*rad2deg;
    Phi_NN = p1_c.angle[1]*rad2deg;

    S = sqrt(pow(resi.mass,2) + pow(resi.momentum,2)) - v1.mass + p1.mass;

    //printf("p1 : %8.3F , %8.3F, %8.3F \n", KE_1, Theta_1, Phi_1);
    //printf("p2 : %8.3F , %8.3F, %8.3F \n", KE_2, Theta_2, Phi_2);

    //printf("k = %8.3F,  %8.3F, %8.3F \n", k, Theta_k, Phi_k);
    //printf("S = %8.3F,  %8.3F, %8.3F \n", S, Theta_NN, Phi_NN);


}

void Knockout( char *argv[]){

    Z_num    = atoi(argv[1]);
    A_num    = atoi(argv[2]);
    TKEA     = atof(argv[3]);
    k        = atof(argv[4]);
    Theta_k  = atof(argv[5]);
    Phi_k    = atof(argv[6]);
    Theta_NN = atof(argv[7]);
    Phi_NN   = atof(argv[8]);
    S        = atof(argv[9]);

    mass_v1[1] = (double) Z_num;
    mass_v1[2] = (double) A_num;
    mass_v1[0] = Nucleus_Mass(mass_v1[1],mass_v1[2]);
    proj = Nucleus_Name(mass_v1[1],mass_v1[2]);
    mass_v2[1]= 1, mass_v2[2]=1, mass_v2[0]   = Nucleus_Mass(mass_v2[1],mass_v2[2]);

    mass_p1[1]= 1, mass_p1[2]=1, mass_p1[0]   = Nucleus_Mass(mass_p1[1],mass_p1[2]);
    mass_p2[1]= 1, mass_p2[2]=1, mass_p2[0]   = Nucleus_Mass(mass_p2[1],mass_p2[2]);

    mass_resi[1]= mass_v1[1] - mass_p1[1];
    mass_resi[2]= mass_v1[2] - mass_p1[2];
    mass_resi[0]= sqrt(pow(mass_v1[0]-mass_p1[0]+S,2)-pow(k,2));
    mass_resi_gs = Nucleus_Mass(mass_resi[1],mass_resi[2]);
    residual = Nucleus_Name(mass_resi[1],mass_resi[2]);

    v1.set(1, mass_v1, 0, 0, 0);
    v2.set(1, mass_v2, TKEA, 180, 0);
    resi.set(2,mass_resi, k,180-Theta_k,180+Phi_k);
    Neo = v1-resi;

    cm = (Neo + v2)/2;

    L1.set(-cm.beta, cm.angle[0]*rad2deg,cm.angle[1]*rad2deg); //Nucleus to CM
    L2.set(cm.beta, cm.angle[0]*rad2deg,cm.angle[1]*rad2deg);  // CM to Nucleus
    L3.set(-v2.beta, v2.angle[0]*rad2deg,v2.angle[1]*rad2deg); // Nucleus to Lab

    cm_c = L1^cm;
    v1_c = L1^v1;
    v2_c = L1^v2;
    Neo_c = L1^Neo;

	double Etotal = sqrt(1-pow(cm.beta,2))*(v2.energy+Neo.energy);
	double k1c = sqrt((Etotal-mass_p1[0]-mass_p2[0])*(Etotal+mass_p1[0]-mass_p2[0])*(Etotal-mass_p1[0]+mass_p2[0])*(Etotal+mass_p1[0]+mass_p2[0]))/(2*Etotal);

    p1_c.set(2,mass_p1, k1c, 180-Theta_NN, 180+Phi_NN );
    p2_c.set(2,mass_p2, k1c, Theta_NN, Phi_NN);
    resi_c = v1_c + v2_c - p1_c - p2_c;

    p1 = L2^p1_c;
    p2 = L2^p2_c;

    v1_L = L3^v1;
    v2_L = L3^v2;
    Neo_L = L3^Neo;
    p1_L = L3^p1;
    p2_L = L3^p2;
    resi_L = L3^resi;


}

void Output(string filename){

    string tmp;

    ifstream file_out1(filename.c_str());
    file_out1 >> tmp;
    if (tmp.empty()){
        cout << "creating " << filename << endl;

        FILE*file;
        file = fopen(filename.c_str(),"w");
        fprintf(file, "%16s %8s %6s %6s %8s %8s %8s %8s %8s %8s %8s %8s %8s %8s\n",
                      "reaction", "TKEA", "S", "k", "Theta_k", "Phi_k", "Theta_NN", "Phi_NN",
                      "KE1", "Theta_1", "Phi_1",
                      "KE2", "Theta_2", "Phi_2");
//        file_out1 << <<"Reaction\tTiL\tS\tk\tTheta_k\tPhi_k\tTheta_NN\tPhi_NN\tT1L(p)\ttheta_1L\tT2L(n)\ttheta2L\tT1(p)\ttheta_1\tT2(n)\ttheta2\tDSC_factor" << endl;
        fclose(file);
    }
    file_out1.close();

    ofstream file_out;
    file_out.open(filename.c_str(), ios::app);

    file_out << setw(2) << mass_v1[1]<< proj;
    file_out << "(p,2p)";
    file_out << setw(2) << mass_resi[1]<<residual;
    file_out << fixed << setw(9) << setprecision(2) << TKEA ;
    file_out << fixed << setw(7) << setprecision(2) <<  S ;
    file_out << fixed << setw(7) << setprecision(2) <<  k ;
    file_out << fixed << setw(9) << setprecision(2) <<  Theta_k ;
    file_out << fixed << setw(9) << setprecision(2) <<  Phi_k ;
    file_out << fixed << setw(9) << setprecision(2) <<  Theta_NN ;
    file_out << fixed << setw(9) << setprecision(2) <<  Phi_NN ;
    file_out << fixed << setw(9) << setprecision(2) <<  p1_L.keA ;
    file_out << fixed << setw(9) << setprecision(2) <<  p1_L.angle[0]*rad2deg ;
    file_out << fixed << setw(9) << setprecision(2) <<  p1_L.angle[1]*rad2deg ;
    file_out << fixed << setw(9) << setprecision(2) <<  p2_L.keA ;
    file_out << fixed << setw(9) << setprecision(2) <<  p2_L.angle[0]*rad2deg ;
    file_out << fixed << setw(9) << setprecision(2) <<  p2_L.angle[1]*rad2deg ;
    file_out << endl;
    file_out.close();

}