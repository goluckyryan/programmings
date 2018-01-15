#ifndef LORENTZIAN_H
#define LORENTZIAN_H

#include <cmath>
#include "matrix.h"
#include "constant.h"

class Lorentzian : public Matrix
{
public:
    Lorentzian();
    Lorentzian(double beta, double theta_Deg = 0, double phi_Deg = 0);
    void SetBeta(double beta);
    void SetDirection(double theta_Deg, double phi_Deg);
    void SetMatrix(double beta, double theta_Deg, double phi_Deg);

private:
    double beta;
    double gamma;
    double theta, phi;

    double CalGamma(double beta){
        if( qAbs(beta) > 1 ){
            return 0.;
        }else{
            return 1./sqrt(1-pow(beta,2));
        }
    }
};

#endif // LORENTZIAN_H
