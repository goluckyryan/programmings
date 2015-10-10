/*  Knockout of T(p,2p)R

The Lorentz Tranform on aribtary direction is well discrpted in Goldstien P .281

k(vector): momentum of a proton in Target nucleus
Theta_k:   direction of the momentum of a proton in O nucleus
Theta_NN:  scattering angle in 2-nucleon center of mass system
S:         separation energys

***** suffix notation ****
suffix "L" is Lab frame
suffix "" is Target frame
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

#include <sstream> // enable string control
#include <cmath> // math , enable simple math function
#include <iomanip>
#include <stdio.h>  // standard I/O
#include <stdlib.h> // standard General Utlilities Library
#include <time.h>
//#include "../../CppLibrary/constant.h"
//#include "../../CppLibrary/nuclei_mass.h"

using namespace std; // declare a namespace "std", every variable in this code is inside "std"

//prototype____________________________________________________________________
float* Lorentz(float *V, float beta, float theta);
void PrintV(float *V, string Vname);
float Momentum(float *V);
float Angle(float *V);

const float mp = 938.272;
const float rad2deg = 57.29577951;


int main(int argc, char *argv[]){
    if( argc != 6) {
        printf("\nUsage: \n./knockout2D.o A k Theta_kx(deg) Theta_NN(deg) Sp \n");
        exit(0);
	}
    
    float masst;
    float TKEA;
    if ( atoi(argv[1]) == 23 ) {
	masst = 21423.094276;
	TKEA  = 289.44;
    }else if ( atoi(argv[1]) == 25 ){
	masst = 23294.025362;
	TKEA = 276.779;
    }
    float k = atof(argv[2]);
    float theta_k = atof(argv[3])/rad2deg;
    float theta_NN = atof(argv[4])/rad2deg;
    float Sp = atof(argv[5]);

//  ########################### Nuclei's frame
    float *Pi = new float[3];
    float *Pt = new float[3];
    float *P1 = new float[3];
    float *P2 = new float[3];
    float *Pr = new float[3];
    float *Pk = new float[3];
    
    Pi[0] = mp+TKEA;
    Pi[1] = 0;
    Pi[2] = sqrt(2*mp*TKEA + TKEA*TKEA);
    
    Pt[0] = masst;
    Pt[1] = 0;
    Pt[2] = 0;
    
    Pr[0] = sqrt(pow(Sp+masst-mp,2)+k*k);
    Pr[1] = k*sin(theta_k);
    Pr[2] = k*cos(theta_k);
    
    Pk[0] = Pt[0] - Pr[0];
    Pk[1] = Pt[1] - Pr[1];
    Pk[2] = Pt[2] - Pr[2];

/*    PrintV(Pi, "Pi");
    PrintV(Pt, "Pt");
    PrintV(Pr, "Pr");
    PrintV(Pk, "Pk");
*/    
    float *Pc = new float[3];
    Pc[0] = (Pi[0] + Pk[0])/2;
    Pc[1] = (Pi[1] + Pk[1])/2;
    Pc[2] = (Pi[2] + Pk[2])/2;

// ########################### 2-body CM frame
    float *Pic = new float[3];
    float *P1c = new float[3];
    float *P2c = new float[3];
    float *Pkc = new float[3];

    float betaPc = Momentum(Pc)/Pc[0];
    float thetaPc = Angle(Pc);
    
    Pic = Lorentz(Pi, -betaPc, thetaPc);
    Pkc = Lorentz(Pk, -betaPc, thetaPc);
    
    float thetaPic = Angle(Pic);
    
    float Etotal = sqrt(1-pow(betaPc,2))*(Pi[0]+Pk[0]); // CM frame total energy
    float p1c = sqrt((Etotal-mp-mp)*(Etotal+mp+mp))/2;
    
   // printf("  Etotal:%10.6f, p1c:%10.6f\n", Etotal, p1c);
    
    P1c[0] = sqrt(mp*mp + p1c*p1c);
    P1c[1] = p1c*sin(thetaPic+theta_NN);
    P1c[2] = p1c*cos(thetaPic+theta_NN);
    
    P2c[0] = P1c[0];
    P2c[1] = -P1c[1];
    P2c[2] = -P1c[2];
    
    P1 = Lorentz(P1c, betaPc, thetaPc);
    P2 = Lorentz(P2c, betaPc, thetaPc);

/*    PrintV(P1, "P1");
    PrintV(P2, "P2");
    
    PrintV(Pc, "Pc");
    
    PrintV(Pic, "Pic");
    PrintV(Pkc, "Pkc");
    PrintV(P1c, "P1c");
    PrintV(P2c, "P2c");
*/    
// ########################### Lab Frame Inversed Kinematics
    float *PiL = new float[3];
    float *P1L = new float[3];
    float *P2L = new float[3];
    float *PtL = new float[3];
    float *PrL = new float[3];
    
    float beta = Momentum(Pi)/Pi[0];
    
    PiL = Lorentz(Pi, -beta, 0);
    PtL = Lorentz(Pt, -beta, 0);
    P1L = Lorentz(P1, -beta, 0);
    P2L = Lorentz(P2, -beta, 0);
    PrL = Lorentz(Pr, -beta, 0);
    
/*    PrintV(PiL, "PiL");
    PrintV(PtL, "PtL");
    PrintV(P1L, "P1L");
    PrintV(P2L, "P2L");
    PrintV(PrL, "PrL");
*/    
    //delete pointer
    delete Pi;
    delete Pt;
    delete P1;
    delete P2;
    delete Pr;
    delete Pk;
    delete Pc;
    
    delete Pic;
    delete Pkc;
    delete P1c;
    delete P2c;

    delete PiL;
    delete PtL;
    delete P1L;
    delete P2L;
    delete PrL;
    
    return 0;
}

//function___________________________________________________________________
float* Lorentz(float *V, float beta, float theta){
    float *U = new float[3];
    
    float gamma = 1/sqrt(1-beta*beta);
    
    U[0] = V[0]*gamma + V[1]*beta*gamma*sin(theta) + V[2]*beta*gamma*cos(theta);
    U[1] = V[0]*beta*gamma*sin(theta) + V[1]*(cos(theta)*cos(theta) + gamma*sin(theta)*sin(theta)) 
               + V[2]*(cos(theta)*sin(theta)*gamma-cos(theta)*sin(theta));
    U[2] = V[0]*beta*gamma*cos(theta) + V[1]*(cos(theta)*sin(theta)*gamma-cos(theta)*sin(theta))
               + V[2]*(sin(theta)*sin(theta) + gamma*cos(theta)*cos(theta));
    
    return U;
}


void PrintV(float *V, string Vname){
    printf("%10s : %10.3f, %10.3f, %10.3f\n", Vname.c_str(), V[0], V[1], V[2]); 
}

float Momentum(float *V){
    return sqrt(V[1]*V[1] + V[2]*V[2]);
}

float Angle(float *V){
    return atan2(V[1], V[2]);
}
