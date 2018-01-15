#ifndef FOURVECTOR_H
#define FOURVECTOR_H

#include <cmath>
#include <QVector>
#include "matrix.h"
#include "nucleus.h"

class FourVector: public Matrix
{
public:
    FourVector();
    FourVector(double a, double b, double c, double d);
    void SetFourVector(double a, double b, double c, double d);
    void SetMassKEDirection(int A, int Z, double KE_MeV, double theta_Deg, double phi_Deg);

    QVector<double> toQVector();
    QVector<double> toMomentumQVector();
    QVector<double> toNormalizedMomentumQVector();

    double Energy(){return energy;}
    double Momentum();
    Matrix MomentumVector();
    Matrix NormalizedMomentumVector();
    double Theta(){
        Matrix momtN = NormalizedMomentumVector();
        return acos(momtN(3,1));
    }
    double Phi(){
        Matrix momtN = NormalizedMomentumVector();
        return atan2(momtN(2,1), momtN(1,1));
    }
    double Mass();

    double KE(){ return Energy() - Mass();}
    double Beta(){ return Momentum()/Energy();}
    double Gamma(){ return Energy()/Mass();}

private:
    int A, Z; // mass number, charge number;
    double energy;
    double mass;

};

#endif // FOURVECTOR_H
