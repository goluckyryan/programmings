#include "fourvector.h"

FourVector::FourVector()
{
    vec = new Matrix(4,1);
    vec(1,1) = 0;
    vec(2,1) = 0;
    vec(3,1) = 0;
    vec(4,1) = 0;

    SetMass(0,0);
    energy = 0;
}

FourVector::FourVector(double a, double b, double c, double d, int id)
{
    vec = new Matrix(4,1);
    SetFourVector(a,b,c,d,id);
    SetMass(0,0);
}

void FourVector::SetFourVector(double a, double b, double c, double d, int id)
{
    //id = 0, construct by a, b, c, d
    //id = 1,           by mass, T, theta, phi
    if(id == 0){
        vec(1,1) = a;
        vec(2,1) = b;
        vec(3,1) = c;
        vec(4,1) = d;
        energy = a;
    }

}

void FourVector::SetMass(double A, double Z)
{
    this->A = A;
    this->Z = Z;
}

QVector<double> FourVector::toQVector(){
    QVector<double> p;
    for(int i = 1; i <=4; i++){
        p.push_back(vec(i,1));
    }
    return p;
}

QVector<double> FourVector::toMomentumQVector(){
    QVector<double> p;
    for(int i = 2; i <=4; i++){
        p.push_back(vec(i,1));
    }
    return p;
}

QVector<double> FourVector::toNormalizedMomentumQVector(){
    QVector<double> p = toMomentumQVector();
    double momt = Momentum();
    p[1] = p[1]/momt;
    p[2] = p[2]/momt;
    p[3] = p[3]/momt;
    return p;
}

double FourVector::Momentum(){
    return sqrt(pow(vec(2,1),2) + pow(vec(3,1),2) + pow(vec(4,1),2));
}

Matrix FourVector::MomentumVector(){
    Matrix momt(3,1);
    momt(1,1) = vec(2,1);
    momt(2,1) = vec(3,1);
    momt(3,1) = vec(4,1);
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
