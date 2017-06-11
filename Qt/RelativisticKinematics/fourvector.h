#ifndef FOURVECTOR_H
#define FOURVECTOR_H

#include <cmath>
#include <QVector>
#include "matrix.h"
//#include "nucleus.h"

class FourVector: public Matrix
{
public:
    FourVector();
    FourVector(double a, double b, double c, double d, int id);
    void SetFourVector(double a, double b, double c, double d, int id);
    void SetMass(double A, double Z);

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
    double Gamma(){ return Mass()/Energy();}

private:
    int A, Z; // mass number, charge number;
    double energy;

};

#endif // FOURVECTOR_H
