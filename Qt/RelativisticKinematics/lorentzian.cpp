#include "lorentzian.h"

Lorentzian::Lorentzian() :
    Matrix(4,4,1)
{
    this->beta = 0;
    this->gamma = 1;
    this->theta = 0;
    this->phi = 0;
}

Lorentzian::Lorentzian(double beta, double theta_Deg, double phi_Deg):
    Matrix(4,4)
{
    SetMatrix(beta, theta_Deg, phi_Deg);
}

void Lorentzian::SetBeta(double beta)
{
    SetMatrix(beta, 0, 0);
}

void Lorentzian::SetDirection(double theta_Deg, double phi_Deg)
{
    SetMatrix(beta, theta_Deg, phi_Deg);
}

void Lorentzian::SetMatrix(double beta, double theta_Deg, double phi_Deg)
{
    this->beta = beta;
    this->gamma = CalGamma(beta);
    this->theta = theta_Deg * deg2rad;
    this->phi = phi_Deg * deg2rad;

    double alpha = beta*gamma;
    double cTh   = cos(theta); double ccTh = cTh*cTh;
    double sTh   = sin(theta); double ssTh = sTh*sTh;
    double cPh   = cos(phi);   double ccPh = cPh*cPh;
    double sPh   = sin(phi);   double ssPh = sPh*sPh;

    p[0][0] = gamma;
    p[1][0] = alpha*sTh*cPh;
    p[2][0] = alpha*sTh*sPh;
    p[3][0] = alpha*cTh;

    p[1][1] = ccPh*(ccTh + gamma*ssTh)+ssPh;
    p[2][1] = cPh*sPh*(ccTh+gamma*ssTh-1);
    p[3][1] = cTh*sTh*cPh*(gamma-1);

    p[2][2] = ccPh + ssPh*(ccTh + gamma*ssTh);
    p[3][2] = cTh*sTh*sPh*(gamma-1);

    p[3][3] = gamma*ccTh + ssTh;

    p[0][1] = p[1][0];
    p[0][2] = p[2][0];
    p[0][3] = p[3][0];

    p[1][2] = p[2][1];
    p[1][3] = p[3][1];

    p[2][3] = p[3][2];
}
