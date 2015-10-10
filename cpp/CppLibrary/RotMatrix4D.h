#ifndef ROTMATRIX4D_H
#define ROTMATRIX4D_H
#include <iostream>
#include <stdio.h>
#include <cmath>
#include "constant.h"
//#include "matrix4D.h"

using namespace std;

class RotMatrix4D{
    public:
        double ele[4][4];
        double alpha ; //rotated angle
        double angle[2]; // rotating axis

        RotMatrix4D();
        RotMatrix4D(double,double,double) ;
        void set(double,double,double);
        double det();    // matrix determinate of the space part
        RotMatrix4D operator * (const RotMatrix4D) const; //matrix multiplication
        FourVector operator ^ (const FourVector) const; // matrix.vector
        RotMatrix4D transpose(); //matrix transpose
        void print(string) const;
};

RotMatrix4D::RotMatrix4D (){
    for (int i = 0; i < 4; i++ ){
        for (int j = 0; j < 4 ; j++){
                ele[i][j]=0;
        }
    }
    angle[0]=0;
    angle[1]=0;
    alpha = 0;
}

RotMatrix4D::RotMatrix4D (double a,double b,double c){
    set(a, b, c);
}

void RotMatrix4D::set ( double a, double Theta, double Phi){

    Theta = Theta * deg2rad;
    Phi = Phi * deg2rad ;

    a = a * deg2rad ;
    double c1 = cos(Theta);
    double s1 = sin(Theta);
    double c2 = cos(Phi);
    double s2 = sin(Phi);
    double ca = cos(a);
    double sa = sin(a);

	ele[0][0]=1;ele[0][1]=0;ele[0][2]=0;ele[0][3]=0;
	ele[1][0]=0;
	ele[2][0]=0;
	ele[3][0]=0;

    ele[1][1]= pow(c2,2)*(ca*pow(c1,2)+pow(s1,2))+ ca*pow(s2,2);
    ele[1][2]= -c1*sa+pow(sin(a/2),2)*pow(s1,2)*sin(2*Phi);
    ele[1][3]= -s1*((ca-1)*c1*c2-sa*s2);
    ele[2][1]= c1*sa+pow(sin(a/2),2)*pow(s1,2)*sin(2*Phi);
    ele[2][2]=  ca*pow(c2,2)+pow(s2,2)*(ca*pow(c1,2)+pow(s1,2));
    ele[2][3]= s1*(-c2*sa+(1-ca)*c1*s2);
    ele[3][1]= c2*pow(sin(a/2),2)*sin(2*Theta)-sa*s1*s2;
    ele[3][2]= -s1*(-c2*sa+(ca-1)*c1*s2);
    ele[3][3]= pow(c1,2)+ca*pow(s1,2);

    alpha = a;
    angle[0]= Theta;
    angle[1]= Phi;
}

double RotMatrix4D::det(){
    double temp;
    temp = ele[1][1]*ele[2][2]*ele[3][3]+
           ele[1][2]*ele[2][3]*ele[3][1]+
           ele[1][3]*ele[2][1]*ele[3][2]-
           ele[1][3]*ele[2][2]*ele[3][1]-
           ele[1][2]*ele[2][1]*ele[3][3]-
           ele[1][1]*ele[2][3]*ele[3][2];
    return temp;
}

RotMatrix4D RotMatrix4D::operator * (const RotMatrix4D mat2) const{
    RotMatrix4D temp;

    for (int i = 0 ; i < 4; i ++){
        for (int k = 0 ; k < 4; k ++){
            for (int j = 0 ; j < 4; j ++){
                temp.ele[i][k]= temp.ele[i][k] + ele[i][j]*mat2.ele[j][k] ;
            }
        }
    }

    return temp;
}

FourVector RotMatrix4D::operator ^ (const FourVector v2) const{
    FourVector temp;

    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            temp.ele[i]=temp.ele[i] + ele[i][j]*v2.ele[j];
        }
    }

    temp.recalulate(v2.A,v2.Z);

    return temp;
}

RotMatrix4D RotMatrix4D::transpose(){
    RotMatrix4D temp;
    for (int i = 0 ; i < 4; i ++){
        for (int j = 0 ; j < 4; j ++){
            temp.ele[i][j]= ele[j][i];
        }
    }
    return temp;
}

void RotMatrix4D::print(string str) const{
    cout << " ==== " << str <<" matrix : ";
    printf("(%5.1f| %5.2f, %5.2f)\n", alpha*rad2deg, angle[0]*rad2deg,angle[1]*rad2deg);
    for (int i = 0 ; i < 4 ; i++){
        for (int j = 0 ; j < 4; j++){
            printf(" %8.3f ", ele[i][j]);
        }
        cout << endl;
    }
    cout << "===============================" << endl;
}

#endif // MATRIX3D_H
