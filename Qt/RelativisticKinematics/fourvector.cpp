#include "fourvector.h"

FourVector::FourVector() :
    Matrix(4,1)
{
    SetMass(0,0);
    energy = 0;
}

FourVector::FourVector(double a, double b, double c, double d, int id):
    Matrix(4,1)
{
    //vec = new Matrix(4,1);
    SetFourVector(a,b,c,d,id);
    SetMass(0,0);
}

void FourVector::SetFourVector(double a, double b, double c, double d, int id)
{
    //id = 0, construct by a, b, c, d
    //id = 1,           by mass, T, theta, phi
    if(id == 0){
        p[0][0] = a;
        p[1][0] = b;
        p[2][0] = c;
        p[3][0] = d;
        energy = a;
    }

}

void FourVector::SetMass(double A, double Z)
{
    this->A = A;
    this->Z = Z;
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
