#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <stdlib.h>
#include <cmath>
#include <cstring>

using namespace std;

float Jocobian(float mass, float Tinc, float theta, float beta){
    
    const float deg2rad = 3.14159/180;
    float Energy = mass + Tinc;
    float Momt = sqrt(2*mass*Tinc+Tinc*Tinc);
    float Momtx = Momt*sin(theta*deg2rad);
    float Momtz = Momt*cos(theta*deg2rad);
    float gamma = 1/sqrt(1-beta*beta);
    
    // Lorentz transform 
    float EnergyA = gamma*Energy + gamma*beta*Momtz;
    float MomtzA  = gamma*beta*Energy + gamma*Momtz;
    float MomtA   = sqrt(MomtzA*MomtzA + Momtx*Momtx);
    float thetaA  = acos(MomtzA/MomtA)/deg2rad;
    
    // Jacobian frome C fram to A frame;
    return MomtA*MomtA*MomtA/Momt/Momt/gamma/(Momt + Energy*beta*cos(theta*deg2rad));

}

int main(int argc, char *argv[]){

     if(argc <= 4) {
	printf("=======================================================\n");
	printf(" Transform cross section from C farme to A farme. \n \n");
	printf("Usage: ./XsecTra.o\e[32m sigam T theta beta\e[m \n \n");
	printf("        sigam = diff X-sec in C frame \n");
	printf("  T [MeV/c^2] = KE of proton in C frame \n");
	printf("  theta [deg] = angle of proton make with transform axis in C frame \n");
	printf("         beta = Lorentz beta of transform from C frame to A frame \n");
	exit(0);
    }

    float sigma = atof(argv[1]);
    float Tinc = atof(argv[2]);
    float theta = atof(argv[3]);
    float beta = atof(argv[4]);
    
    if (beta >= 1) {
	printf(" beta >= 1 !   exit\n");
	exit(0);    
    }
    
    const float mp = 938.272;
    const float deg2rad = 3.14159/180;
    float Energy = mp + Tinc;
    float Momt = sqrt(2*mp*Tinc+Tinc*Tinc);
    float Momtx = Momt*sin(theta*deg2rad);
    float Momtz = Momt*cos(theta*deg2rad);
    float gamma = 1/sqrt(1-beta*beta);
    float betaC = Momt/Energy;

    printf("T: %5.1f, theta: %5.2f \n", Tinc, theta);
    
    // Lorentz transform 
    float EnergyA = gamma*Energy + gamma*beta*Momtz;
    float MomtzA  = gamma*beta*Energy + gamma*Momtz;
    float MomtA   = sqrt(MomtzA*MomtzA + Momtx*Momtx);
    float thetaA  = acos(MomtzA/MomtA)/deg2rad;
    
    // Jacobian frome C fram to A frame;
    float Jaco = Jocobian(mp, Tinc, theta, beta);
    printf(" Infity when betaC + beta*cos(theta) == 0, pA and pC make 90 deg, theta:%6.3f deg\n", acos(-betaC/beta)/deg2rad);
    printf("C | %6.3f, %6.3f, %6.3f | %6.3f\n", Energy, Momtx, Momtz, theta);
    printf("A | %6.3f, %6.3f, %6.3f | %6.3f\n", EnergyA, Momtx, MomtzA, thetaA);
    printf("sigma(C): %6.2f, beta: %4.2f => sigma(A): %6.2f\n", sigma, beta, sigma*Jaco);  

    return 0;

}


