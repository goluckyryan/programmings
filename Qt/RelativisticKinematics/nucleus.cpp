#include "nucleus.h"

Nucleus::Nucleus(int z, int a)
{
    /*
    this->Z = z;
    this->A = a;
    this->N = a-z;
    this->name = Nucleus_Name(z, a);
    this->mass = Nucleus_Mass(z, a);
    this->BEA = (this->mass - z*mp - this->N * mn )/a;
    this->Sp = SeparationEnergy(z, a, 0, 1);
    this->Sn = SeparationEnergy(z, a, 1, 0);
*/
    //ZeroKinematics();

}

/*
void Nucleus::SetKEA(double kea){
    this->KEA = kea;
    KEA2Gamma(kea);
    Gamma2Beta(this->Gamma);
    Gamma2Momt(this->Gamma);
    Gamma2Brho(this->Gamma);
}

void Nucleus::SetMomt(double momt){
    this->Momt = momt;
    Momt2KEA(momt);
    KEA2Gamma(this->KEA);
    Gamma2Beta(this->Gamma);
    Gamma2Brho(this->Gamma);
}

void Nucleus::SetGamma(double g){
    this->Gamma = g;
    Gamma2KEA(g);
    Gamma2Momt(g);
    Gamma2Beta(g);
    Gamma2Brho(g);
}

void Nucleus::SetBeta(double b){
    this->Beta = b;
    Beta2Gamma(b);
    Gamma2KEA(this->Gamma);
    Gamma2Momt(this->Gamma);
    Gamma2Brho(this->Gamma);
}

void Nucleus::SetBrho(double brho){
    this->Brho = brho;
    Brho2Gamma(brho);
    Gamma2KEA(this->Gamma);
    Gamma2Momt(this->Gamma);
    Gamma2Beta(this->Gamma);
}

*/




