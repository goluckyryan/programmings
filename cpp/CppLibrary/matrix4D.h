#ifndef MATRIX3D_H
#define MATRIX3D_H
#include <iostream>
#include <stdio.h>
#include <cmath>
#include "constant.h"
#include "vector4D.h"

using namespace std;

const int size = 4;

class Matrix4D{
    public:
        double ele[size][size];

        Matrix4D();
        Matrix4D(double,double,double,double,
                 double,double,double,double,
                 double,double,double,double,
                 double,double,double,double) ;
        void set(double,double,double,double,
                 double,double,double,double,
                 double,double,double,double,
                 double,double,double,double);
  //      double det() const;    // matrix determinate
        Matrix4D operator + (const Matrix4D) const; //matrix sum
        Matrix4D operator - (const Matrix4D) const; //matrix sub
        Matrix4D operator * (const Matrix4D) const; //matrix multiplicatio
        Vector4D operator ^ (const Vector4D) const; // matrix.vector
        Matrix4D transpose() const; //matrix transpose
  //      Matrix3D minor();   // matrix minor
  //      Matrix4D inverse(); // matrix inverse
  //      Matrix4D eigenvector(); //eigen vector
   //     Matrix4D eigenValue(); // eigen value matrix
        void print(string) const;
};

Matrix4D::Matrix4D (){
    for (int i = 0; i < size; i++ ){
        for (int j = 0; j < size ; j++){
                ele[i][j]=0;
        }
    }
}

Matrix4D::Matrix4D (double a11,double a12,double a13, double a14,
                    double a21,double a22,double a23, double a24,
                    double a31,double a32,double a33, double a34,
                    double a41,double a42,double a43, double a44){
    set(a11, a12, a13, a14, a21, a22, a23, a24, a31, a32, a33, a34, a41, a42, a43, a44);
}

void Matrix4D::set (double a11,double a12,double a13, double a14,
                    double a21,double a22,double a23, double a24,
                    double a31,double a32,double a33, double a34,
                    double a41,double a42,double a43, double a44){

    ele[0][0]=a11; ele[0][1]=a12; ele[0][2]=a13; ele[0][3]=a14;
    ele[1][0]=a21; ele[1][1]=a22; ele[1][2]=a23; ele[1][3]=a24;
    ele[2][0]=a31; ele[2][1]=a32; ele[2][2]=a33; ele[2][3]=a34;
    ele[3][0]=a41; ele[3][1]=a42; ele[3][2]=a43; ele[3][3]=a44;
}

/* Det
double Matrix4D::det() const{
    double temp;
    temp = ele[1][1]*ele[2][2]*ele[3][3]+
           ele[1][2]*ele[2][3]*ele[3][1]+
           ele[1][3]*ele[2][1]*ele[3][2]-
           ele[1][3]*ele[2][2]*ele[3][1]-
           ele[1][2]*ele[2][1]*ele[3][3]-
           ele[1][1]*ele[2][3]*ele[3][2];
    return temp;
}

*/

Matrix4D Matrix4D::operator + (const Matrix4D mat2) const{
    Matrix4D temp;

    for (int i = 0 ; i < size; i ++){
        for (int k = 0 ; k < size; k ++){
             temp.ele[i][k]= ele[i][k] + mat2.ele[i][k] ;
        }
    }
    return temp;
}

Matrix4D Matrix4D::operator - (const Matrix4D mat2) const{
    Matrix4D temp;

    for (int i = 0 ; i < size; i ++){
        for (int k = 0 ; k < size; k ++){
             temp.ele[i][k]= ele[i][k] - mat2.ele[i][k] ;
        }
    }
    return temp;
}

Matrix4D Matrix4D::operator * (const Matrix4D mat2) const{
    Matrix4D temp;

    for (int i = 0 ; i < size; i ++){
        for (int k = 0 ; k < size; k ++){
            for (int j = 0 ; j < size; j ++){
                temp.ele[i][k]= temp.ele[i][k] + ele[i][j]*mat2.ele[j][k] ;
            }
        }
    }
    return temp;
}

Vector4D Matrix4D::operator ^ ( const Vector4D v2) const{
    Vector4D temp;
    for (int i = 0 ; i < size; i ++){
        for (int j = 0 ; j < size; j ++){
            temp.ele[i]= temp.ele[i]+ ele[i][j]*v2.ele[j] ;
        }
    }

    temp.set(temp.ele[0],temp.ele[1],temp.ele[2],temp.ele[3]);

    return temp;
}

Matrix4D Matrix4D::transpose() const{
    Matrix4D temp;
    for (int i = 0 ; i < size; i ++){
        for (int j = 0 ; j < size; j ++){
            temp.ele[i][j]= ele[j][i];
        }
    }
    return temp;
}

/* inverse
Matrix4D Matrix4D::inverse(){
    double a;
    a = det();
    Matrix4D temp;

    if ( a == 0 ){
        for (int i = 0 ; i < 3; i ++){
            for (int k = 0 ; k < 3; k ++){
                temp.ele[i][k] = 0 ;
            }
        }
    }else{

    }
    return temp;
}
*/

void Matrix4D::print(string str) const{
    cout << endl << " ==== " << str <<" matrix : " << endl;
    for (int i = 0 ; i < size ; i++){
        for (int j = 0 ; j < size; j++){
            printf("%10.3f",ele[i][j]);
        }
        cout << endl;
    }
    cout << endl;
}

#endif // MATRIX3D_H
