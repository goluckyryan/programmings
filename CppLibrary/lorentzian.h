#ifndef LORENTZIAN_H
#define LORENTZIAN_H
#include <iostream>
#include <stdio.h>
#include <cmath>
#include "constant.h"

using namespace std;

class Lorentzian{
    public:
        double ele[4][4];
        double beta, gamma, angle[2];

        Lorentzian();
        void set(double beta_a, double Theta, double Phi);
        Lorentzian (double, double, double);
        Lorentzian operator * (Lorentzian); //matrix multiplicatio
        Lorentzian operator + (RotMatrix4D); //matrix multiplicatio
        FourVector operator ^ (FourVector) ; // matrix.vector
        void print() const;
};

Lorentzian::Lorentzian() {
    for (int i = 0; i < 4; i++ ){
        for (int j = 0; j < 4 ; j++){
                if (i == j){
                    ele[i][j]=1;
                }else{
                    ele[i][j]=0;
                }
        }
    }

    beta = 0;
    gamma = 1;
    angle[0] = 0; //theta
    angle[1] = 0; //phi
}

void Lorentzian::set (double beta_a, double Theta, double Phi){
    beta = beta_a ;
	double g = 1/sqrt(1- pow(beta,2));

	Theta = Theta * deg2rad;
	Phi   = Phi * deg2rad;
	double c1 = cos(Theta);
	double s1 = sin(Theta);
	double c2 = cos(Phi);
	double s2 = sin(Phi);

	gamma = g ;
	angle[0] = Theta ;
	angle[1] = Phi ;

	ele[0][0]=g;
	ele[0][1]=beta*g*c2*s1;
	ele[0][2]=beta*g*s2*s1;
	ele[0][3]=beta*g*c1;
	ele[1][0]=g*beta*c2*s1;
	ele[1][1]=pow(c2,2)*(pow(c1,2)+pow(s1,2)*g)+pow(s2,2);
	ele[1][2]=c2*s2*(-1+pow(c1,2)+pow(s1,2)*g);
	ele[1][3]=(g-1)*c1*c2*s1;
	ele[2][0]=beta*g*s1*s2;
	ele[2][1]=c2*s2*(-1+pow(c1,2)+pow(s1,2)*g);
	ele[2][2]=pow(c2,2)+(pow(c1,2)+pow(s1,2)*g)*pow(s2,2);
	ele[2][3]=(g-1)*c1*s2*s1;
	ele[3][0]=beta*g*c1;
	ele[3][1]=(g-1)*c1*c2*s1;
	ele[3][2]=(g-1)*c1*s2*s1;
	ele[3][3]=g*pow(c1,2)+pow(s1,2);
}

Lorentzian::Lorentzian(double a,double Theta, double Phi){
    set(a, Theta, Phi);
}

Lorentzian Lorentzian::operator * (Lorentzian mat2){
    Lorentzian temp;

    for (int i = 0 ; i < 4; i ++){
        for (int k = 0 ; k < 4; k ++){
                temp.ele[i][k]=0;
            for (int j = 0 ; j < 4; j ++){
                temp.ele[i][k]= temp.ele[i][k] + ele[i][j]*mat2.ele[j][k] ;
            }
        }
    }

    temp.gamma = temp.ele[0][0];
    temp.beta  = sqrt(1-1/pow(temp.gamma,2));

/// Problem
    temp.angle[1] = atan2(temp.ele[0][2], temp.ele[0][1]);
    temp.angle[0] = atan2(temp.ele[1][0]/cos(temp.angle[1]),temp.ele[0][3]);

    return temp;
}

Lorentzian Lorentzian::operator + (RotMatrix4D mat2){
    Lorentzian temp1, temp2, temp3;

    for (int i = 0 ; i < 4; i ++){
        for (int k = 0 ; k < 4; k ++){
            temp1.ele[i][k] = mat2.ele[i][k] ;
            temp2.ele[i][k] = ele[i][k];
        }
    }

    temp3=temp1*temp2;

    return temp3;
}

FourVector Lorentzian::operator ^ (FourVector v2) {
    FourVector temp;

    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            temp.ele[i]=temp.ele[i] + ele[i][j]*v2.ele[j];
        }
    }

    temp.recalulate(v2.A,v2.Z);

    return temp;
}

void Lorentzian::print() const{
    cout << " ====  Loreantzian ";
    printf("(%5.3f, %5.3f| %5.2f, %5.2f)\n", beta, gamma, angle[0]*rad2deg,angle[1]*rad2deg);
    for (int i = 0 ; i < 4 ; i++){
        for (int j = 0 ; j < 4; j++){
            printf(" %8.3f ", ele[i][j]);
        }
        cout << endl;
    }
    cout << endl;
}

#endif // LORENTZIAN_H
