#ifndef NUCLEUS_H
#define NUCLEUS_H

#include <QString>
#include "constant.h"
#include <QFile>
#include <QDebug>

class Nucleus
{
public:
    Nucleus(int z, int a);
    //~Nucleus();

    double mass, Z, A, N, BEA, Sp, Sn;
    QString name;


    double KEA, Momt, Gamma, Beta, Brho;
    double TOF, FLightLength;

    void SetKEA(double kea);
    void SetMomt(double momt);
    void SetGamma(double g);
    void SetBeta(double b);
    void SetBrho(double brho);

    void CalTOF(double fl){
        this->FLightLength = fl;
        this->TOF = fl / this->Beta / c;
    }
    void CalFlightLength(double tof){
        this->TOF = tof;
        this->FLightLength = this->TOF / this->Beta / c;
    }

private:

    double Nucleus_Mass(int z, int a);
    QString Nucleus_Name(int z, int a);
    double SeparationEnergy (int z, int a, int Nn, int Np);


    void ZeroKinematics()
    {
        this->KEA = 0;
        this->Momt = 0;
        this->Gamma = 0;
        this->Beta = 0;
        this->Brho = 0;
        this->TOF = 0;
        this->FLightLength = 0;

    }
    void KEA2Gamma(double kea){
        this->Gamma = (kea * this->A + this->mass )/this->mass;
    }
    void Beta2Gamma(double b){
        this->Gamma = 1/sqrt(1- b * b);
    }
    void Momt2KEA(double momt){
        this->KEA = (sqrt( this->mass*this->mass + momt*momt) - this->mass)/this->A;
    }
    void Brho2Gamma(double brho){
        this->Gamma = sqrt( pow( brho * this->Z * c / this->mass , 2) + 1);
    }


    void Gamma2Beta(double g){
        this->Beta = sqrt(1- 1/g/g);
    }
    void Gamma2KEA(double g){
        this->KEA = (g - 1) * this->mass / this->A;
    }
    void Gamma2Momt(double g){
        Gamma2Beta(g);
        this->Momt = this->mass * g * this->Beta;
    }
    void Gamma2Brho(double g){
        Gamma2Beta(g);
        this->Brho = this->mass * g * this->Beta / c / this->Z;
    }

};

#endif // NUCLEUS_H
