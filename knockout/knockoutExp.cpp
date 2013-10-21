/*  Knockout of O(p,pn)R

// form Experiment point of view.

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

*****************

given T1L, Theta_P1L, Phi_P1L, T2L, Theta_P2L, Phi_P2L, find k, S, Theta_NN, Phi

PiL = {Ei,0,0,0}
P1L = {E1L, k1L*sin(Theta_P1L)*cos(Phi_P1L), k1L*sin(Theta_P1L)*sin(Phi_P1), k1*cos(Theta_P1)}
P2L = {E2L, k2L*sin(Theta_P2L)*cos(Phi_P2L), k2L*sin(Theta_P2L)*sin(Phi_P2), k2*cos(Theta_P2)}

Transform to Lab Frame

Pi
P1
P2

Pn

S = sqrt((Ei+Mo-E1-E2)^2-(ki-k1-k2)^2)-Mo+mn

k = ki-k1-k2

***********************************/
/*
#include <iostream> // enable cin, cout
#include <sstream> // enable string control
#include <cmath> // math , enable simple math function
#include <iomanip>
#include <stdio.h>
//#include <math.h>
#include <stdlib.h> // standard General Utlilities Library
#include <fstream> // File I/O */

#include "knockoutLibrary.h" // include the knockout Library

using namespace std; // declare a namespace "std", every variable in this code is inside "std"
void InputCheck(int a, char *b[]);


//main_____no display___________________
int main(int argc, char *argv[])
{
	
	InputCheck (argc, argv);
	
	EXP(ma_num, e_num, TiL, T1L, theta_1L, phi_1L, T2L, theta_2L, phi_2L);
	
	OutputDetail("OutputDetail_Exp.txt");
	
	Display();
	
    
}
//_____________________________________________________________________________

void InputCheck(int a, char *b[]){

         if( a ==7){
		//cout << "   Option 2 " <<endl;
		ma_num=atoi(b[1]);
		e_num=atoi(b[2]);
		TiL = 250;
		T1L = atof(b[3]);
		theta_1L = atof(b[4])*pi/180;
		phi_1L = 0;
		T2L = atof(b[5]);
		theta_2L = atof(b[6])*pi/180;
		phi_2L=pi;
	}else if( a ==9){
		//cout << "   Option 2 " <<endl;
		ma_num=atoi(b[1]);
		e_num=atoi(b[2]);
		TiL = 250;
		T1L = atof(b[3]);
		theta_1L = atof(b[4])*pi/180;
		phi_1L = atof(b[5])*pi/180;
		T2L = atof(b[6]);
		theta_2L = atof(b[7])*pi/180;
		phi_2L=atof(b[8])*pi/180;
	}else if( a ==10){
		//cout << "   Option 1 " <<endl;
		ma_num=atoi(b[1]);
		e_num=atoi(b[2]);
		TiL = atof(b[3]);;
		T1L = atof(b[4]);
		theta_1L = atof(b[5])*pi/180;
		phi_1L = atof(b[6])*pi/180;
		T2L = atof(b[7]);
		theta_2L = atof(b[8])*pi/180;
		phi_2L=atof(b[9])*pi/180;
	}else {
 		cout << endl << "Usage: " << endl
		<< "1) ./knockoutExp.o A Z TiL  T1L theta_1L(deg) phi_1L(deg) T2L theta_2L(deg) phi_2L(deg)" << endl
		<< "2) ./knockoutExp.o A Z 250  T1L theta_1L(deg) phi_1L(deg) T2L theta_2L(deg) phi_2L(deg)" << endl
		<< "3) ./knockoutExp.o A Z 250  T1L theta_1L(deg)      0      T2L theta_2L(deg)     0      " << endl << endl;
        exit(0);
	}

}
