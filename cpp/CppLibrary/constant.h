#ifndef constant
#define constant
#include <cmath>

const double pi   = acos(-1.0);
const double E    = 2.718281828459 ;
const double hbar = 1.054571628e-34;   //Js
const double kB   = 1.3806504e-23;     //JK^-1
const double e    = 1.602176487e-19;       //C
const double c    = 299792458;         //ms^-1
const double me_kg   = 9.10938215e-31 ;   //kg
const double mp_kg   = 1.672621637e-27 ;  //kg
const double mn_kg   = 1.67492729e-27 ;   //kg
const double NA   = 6.022141e+23 ;     //mol^-1
const double amu  = 931.494; // MeV/c^2

const double deg2rad = pi/180 ;
const double rad2deg = 180/pi ;

//cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
double kg2MeV(double m){
    return m*c*c/e/1e6;
}

double T2Brho(double mass, double Z, double A, double T){
    //mass in MeV
    // Z in e
    // T in MeV/A
    double gamma = (T*A + mass)/mass;
    double beta = sqrt(1-1/gamma/gamma);
    return mass*beta*gamma/Z/c*1e6;
}

double Brho2T(double mass, double Z, double A, double Brho){
    //mass in MeV
    // Z in e
    return (sqrt(pow(Brho*Z*c/1e6,2)+mass*mass)-mass)/A;
}

//cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
double const mp = kg2MeV(mp_kg);
double const mn = kg2MeV(mn_kg);



#endif
