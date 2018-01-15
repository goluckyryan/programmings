#include "fourvector.h"

FourVector::FourVector() :
    Matrix(4,1)
{
    this->A = 0;
    this->Z = 0;
    this->energy = 0;
}

FourVector::FourVector(double a, double b, double c, double d):
    Matrix(4,1)
{
    SetFourVector(a,b,c,d);
    this->A = 0;
    this->Z = 0;
    this->energy = a;
}

void FourVector::SetFourVector(double a, double b, double c, double d)
{
    p[0][0] = a;
    p[1][0] = b;
    p[2][0] = c;
    p[3][0] = d;
    energy = a;
}

void FourVector::SetMassKEDirection(int A, int Z, double KE_MeV, double theta_Deg, double phi_Deg)
{
    this->A = A;
    this->Z = Z;
    Nucleus nucleus(Z,A);
    nucleus.SetKEA(KE_MeV/A);
    this->mass = nucleus.mass;
    this->energy = this->mass + nucleus.KEA * A;

    double momt = nucleus.Momt;

    double theta = theta_Deg * deg2rad;
    double phi = phi_Deg * deg2rad;

    p[0][0] = energy;
    p[1][0] = momt * sin(theta) * cos(phi);
    p[2][0] = momt * sin(theta) * sin(phi);
    p[3][0] = momt * cos(theta);
}

QVector<double> FourVector::toQVector(){
    QVector<double> vec;
    for(int i = 0; i < 4; i++){
        vec.push_back(p[i][1]);
    }
    return vec;
}

QVector<double> FourVector::toMomentumQVector(){
    QVector<double> vec;
    for(int i = 1; i < 4; i++){
        vec.push_back(p[i][1]);
    }
    return vec;
}

QVector<double> FourVector::toNormalizedMomentumQVector(){
    QVector<double> vec = toMomentumQVector();
    double momt = Momentum();
    vec[1] = vec[1]/momt;
    vec[2] = vec[2]/momt;
    vec[3] = vec[3]/momt;
    return vec;
}

double FourVector::Momentum(){
    return sqrt(pow(p[1][0],2) + pow(p[2][0],2) + pow(p[3][0],2));
}

Matrix FourVector::MomentumVector(){
    Matrix momt(3,1);
    momt(1,1) = p[1][0];
    momt(2,1) = p[2][0];
    momt(3,1) = p[3][0];
    return momt;
}

Matrix FourVector::NormalizedMomentumVector(){
    Matrix momtV = MomentumVector();
    double momt = Momentum();
    momtV(1,1) = momtV(1,1)/momt;
    momtV(2,1) = momtV(2,1)/momt;
    momtV(3,1) = momtV(3,1)/momt;
    return momtV;
}

double FourVector::Mass(){
    double energy = Energy();
    double momt = Momentum();
    return sqrt(pow(energy,2) - pow(momt,2));
}
