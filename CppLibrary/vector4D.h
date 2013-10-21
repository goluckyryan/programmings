#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>
#include <stdio.h>
#include <cmath>
#include "constant.h"

using namespace std;

class Vector4D{
    public:
        ele[4];

        double magnitude;
        double length;
        double theta; //deg
        double phi;   //deg

        Vector4D ();  // overloading constructor
        Vector4D (double,double, double, double); //constructor
        void set(double, double, double, double);
        Vector4D operator + (Vector4D); //vector sum
        Vector4D operator - (Vector4D); //vector substract
        double operator & (Vector4D); //vector dot product
  //      Vector4D operator * (Vector4D); //vector cross product
        void print(string) const;
};

Vector4D::Vector4D (){
    length = 0;
    theta = 0;
    phi =0 ;
    for (int i = 0; i < 4; i++){
        ele[i]=0
    }
}

Vector4D::Vector4D (double a1, double a2, double a3, double a4){
    set(a1,a2,a3,a4);
}

void Vector4D::set (double a1, double a2, double a3, double a4){
    ele[0]=a1;
    ele[1]=a2;
    ele[2]=a3;
    ele[3]=a4;

    length = a2*a2+a3*a3+a4*a4;
    magnitude = a1*a1-length;
    theta = atan2(sqrt(a2*a2+a3*a3),a4);
    phi   = atan2(a3,a2);
}


Vector4D Vector4D::operator + (Vector4D v2) {
    Vector4D temp;
    for(int i = 0; i < 4; i ++){
        temp.ele[i]=ele[i]+v2.ele[i];
    }
    temp.set(temp.ele[1],temp.ele[2],temp.ele[3],temp.ele[4]);
    return (temp);
}

Vector4D Vector4D::operator - (Vector4D v2) {
    Vector4D temp;
    for(int i = 0; i < 4; i ++){
        temp.ele[i]=ele[i]-v2.ele[i];
    }
    temp.set(temp.ele[1],temp.ele[2],temp.ele[3],temp.ele[4]);
    return (temp);
}

double Vector4D::operator & (Vector4D v2) {
    double temp = 0;
    temp = temp + ele[0]*ele[0];
    for(int i = 1; i < 4; i ++){
        temp=temp - ele[i]*v2.ele[i];
    }
    return (temp);
}

void Vector4D::print(string msg) const{
    cout << msg;
    cout << " {";
    for(int i = 0; i < 4; i ++){
        printf("%10.3f, ",ele[i]);
    }

    cout << "}";

}

#endif // VECTOR_H
