#ifndef MATRIX3D_H
#define MATRIX3D_H
#include <iostream>
#include <cmath>
#include "constant.h"

using namespace std;

class Matrix3D{

    public:
        double ele[3][3];

        Matrix3D();
        Matrix3D(double,double,double, double,double,double, double,double,double) ;
        void set(double,double,double);
        double det();    // matrix determinate
   //     Matrix3D operator + (Matrix3D); //matrix sum
        Matrix3D operator * (Matrix3D); //matrix multiplicatio
        Vector operator & (Vector) ; // matrix.vector
        Matrix3D transpose(); //matrix transpose
        Matrix3D inverse(); // matrix inverse
  //      Matrix3D eigenvector(); //eigen vector
   //     Matrix3D eigenValue(); // eigen value matrix
        void print(string) const;
};

Matrix3D::Matrix3D (){
    for (int i = 0; i < 3; i++ ){
        for (int j = 0; j < 3 ; j++){
                ele[i][j]=0;
        }
    }
}

Matrix3D::Matrix3D (double a11,double a12,double a13, double a21,double a22,double a23, double a31,double a32,double a33){
    ele[0][0]=a11; ele[0][1] = a12; ele[0][2] = a13;
    ele[1][0]=a21; ele[1][1] = a22; ele[1][2] = a23;
    ele[2][0]=a31; ele[2][1] = a32; ele[2][2] = a33;
}

void Matrix3D::set ( double a, double Theta, double Phi){

    Theta = Theta * deg2rad;
    Phi = Phi * deg2rad ;
    a = a * deg2rad ;
    double c1 = cos(Theta);
    double s1 = sin(Theta);
    double c2 = cos(Phi);
    double s2 = sin(Phi);
    double ca = cos(a);
    double sa = sin(a);


    ele[0][0]=pow(c2,2)*(ca*pow(c1,2)+pow(s1,2))+ ca*pow(s2,2);
    ele[0][1]=-c1*sa+pow(sin(a/2),2)*pow(s1,2)*sin(2*Phi);
    ele[0][2]=-s1*((ca-1)*c1*c2-sa*s2);
    ele[1][0]=c1*sa+pow(sin(a/2),2)*pow(s1,2)*sin(2*Phi);
    ele[1][1]= ca*pow(c2,2)+pow(s2,2)*(ca*pow(c1,2)+pow(s1,2));
    ele[1][2]=s1*(-c2*sa+(1-ca)*c1*s2);
    ele[2][0]=c2*pow(sin(a/2),2)*sin(2*Theta)-sa*s1*s2;
    ele[2][1]=-s1*(-c2*sa+(ca-1)*c1*s2);
    ele[2][2]=pow(c1,2)+ca*pow(s1,2);


}

double Matrix3D::det(){
    double temp;
    temp = ele[0][0]*ele[1][1]*ele[2][2]+
           ele[0][1]*ele[1][2]*ele[2][0]+
           ele[0][2]*ele[1][0]*ele[2][1]-
           ele[0][2]*ele[1][1]*ele[2][0]-
           ele[0][1]*ele[1][0]*ele[2][2]-
           ele[0][0]*ele[1][2]*ele[2][1];
    return temp;
}

Matrix3D Matrix3D::operator * (Matrix3D mat2){
    Matrix3D temp;

    for (int i = 0 ; i < 3; i ++){
        for (int k = 0 ; k < 3; k ++){
            for (int j = 0 ; j < 3; j ++){
                temp.ele[i][k]= temp.ele[i][k] + ele[i][j]*mat2.ele[j][k] ;
            }
        }
    }

    return temp;
}

Vector Matrix3D::operator & (Vector v2) {
    Vector temp;
    temp.x = ele[0][0]*v2.x + ele[0][1]*v2.y + ele[0][2]*v2.z;
    temp.y = ele[1][0]*v2.x + ele[1][1]*v2.y + ele[1][2]*v2.z;
    temp.z = ele[2][0]*v2.x + ele[2][1]*v2.y + ele[2][2]*v2.z;

    temp.set (2, temp.x, temp.y, temp.z);

    return temp;
}

Matrix3D Matrix3D::transpose(){
    Matrix3D temp;
    for (int i = 0 ; i < 3; i ++){
        for (int j = 0 ; j < 3; j ++){
            temp.ele[i][j]= ele[j][i];
        }
    }
    return temp;
}

Matrix3D Matrix3D::inverse(){
    double a;
    a = det();
    Matrix3D temp;

    if ( a == 0 ){
        for (int i = 0 ; i < 3; i ++){
            for (int k = 0 ; k < 3; k ++){
                temp.ele[i][k] = 0 ;
            }
        }
    }else{
        temp.ele[0][0] = (ele[1][1]*ele[2][2]-ele[2][1]*ele[1][2])/a;
        temp.ele[0][1] = (ele[2][1]*ele[0][2]-ele[0][1]*ele[2][2])/a;
        temp.ele[0][2] = (ele[0][1]*ele[1][2]-ele[1][1]*ele[0][2])/a;
        temp.ele[1][0] = (ele[1][2]*ele[2][0]-ele[2][2]*ele[1][0])/a;
        temp.ele[1][1] = (ele[2][2]*ele[0][0]-ele[0][2]*ele[2][0])/a;
        temp.ele[1][2] = (ele[0][2]*ele[1][0]-ele[1][2]*ele[0][0])/a;
        temp.ele[2][0] = (ele[1][0]*ele[2][1]-ele[2][0]*ele[1][1])/a;
        temp.ele[2][1] = (ele[2][0]*ele[0][1]-ele[0][0]*ele[2][1])/a;
        temp.ele[2][2] = (ele[0][0]*ele[1][1]-ele[1][0]*ele[0][1])/a;
    }
    return temp;
}

void Matrix3D::print(string str) const{
    cout << endl << " ==== " << str <<" matrix : " << endl;
    for (int i = 0 ; i < 3 ; i++){
        for (int j = 0 ; j < 3; j++){
            cout << ele[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

#endif // MATRIX3D_H
