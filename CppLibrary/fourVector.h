#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>
#include <stdio.h>
#include <cmath>
#include "constant.h"

using namespace std;

class FourVector{
    public:
        double ele[4]; // assume it is (E,px,py,pz)

        double mass;     //MeV c^-2
        double Z;   // charge
        double A;   // mass number
        double energy;   //MeV
        double keA   ;   //MeV/A
        double momentum; // MeV/c
        double beta;
        double angle[2]; //0 = theta , 1 = phi, in rad

        FourVector ();  // overloading constructor
        FourVector (int id, double m[3],double, double, double); //constructor
        void set(int id, double m[3], double, double, double);
        void recalulate(double, double);
        FourVector operator + (FourVector); //vector sum
        FourVector operator - (FourVector); //vector substract
        FourVector operator * (double); //vector muliple by a constant
        FourVector operator / (double); //vector divided by a constant
        double     operator ^ (FourVector); //vector dot product
       // FourVector operator * (FourVector); //vector cross product
        void normalize();
        void print(string pre, string suf) const;
        void printKinamatics(int id, string msg) const;
        void debug(string) const;
};

FourVector::FourVector (){
    for(int i =0; i<4; i++){
        ele[i]=0;
    }
    mass = 0;
    energy = 0;
    keA = 0;
    A =0; Z =0;
    momentum = 0;
    beta = 0;
    angle[0]=0; angle[1] =0;
}

FourVector::FourVector (int id, double m[3], double T, double theta, double phi){
    set(id, m, T, theta, phi);
}

void FourVector::set (int id, double m[3], double T, double theta, double phi){
    // id = 1, contruct by mass, keA and angle
    // id = 2,             mass, momentum and angle
    // id = 3,             mass, Brho and angle
    // id = 4,             mass, beta and angle
    mass = m[0];
    A =m[1]; Z =m[2];
    angle[0]=theta*deg2rad; angle[1] =phi*deg2rad;
    if (id == 1){
        energy = T*m[1]+mass;
        momentum = sqrt(pow(energy,2)-mass*mass);
    }else if(id ==2){
        momentum = T;
        energy = sqrt(mass*mass + momentum*momentum);
    }else if(id ==3){
        energy = sqrt(pow(T*Z*c/1e6,2)+mass*mass);
        momentum = sqrt(pow(energy,2)-mass*mass);
    }else if(id == 4){
        energy = mass / sqrt( 1- pow(T,2));
        momentum = sqrt(pow(energy,2)-mass*mass);
    }

    keA = (energy-mass)/A;
    beta = momentum/energy;

    ele[0]=energy;
    ele[1]=momentum*cos(angle[1])*sin(angle[0]);
    ele[2]=momentum*sin(angle[1])*sin(angle[0]);
    ele[3]=momentum*cos(angle[0]);

}

void FourVector::recalulate(double a, double b){
    mass = sqrt(pow(ele[0],2)-pow(ele[1],2)-pow(ele[2],2)-pow(ele[3],2));
    energy = ele[0];
    keA = (ele[0]-mass)/a;
    A = a; Z =b;
    momentum = sqrt(pow(ele[1],2)+pow(ele[2],2)+pow(ele[3],2));
    beta = momentum/energy;
    angle[0]=atan2(sqrt(pow(ele[1],2)+pow(ele[2],2)),ele[3]);
    angle[1] =atan2(ele[2],ele[1]);
}

void FourVector::normalize(){
    momentum = 1;
    energy = sqrt(mass*mass + 1);
    beta = momentum/energy;

	ele[0]=energy;
    ele[1]=momentum*cos(angle[1])*sin(angle[0]);
    ele[2]=momentum*sin(angle[1])*sin(angle[0]);
    ele[3]=momentum*cos(angle[0]);


    cout << "vector nomralized !" << endl;
}

FourVector FourVector::operator + (FourVector v2) {
    FourVector temp;
    for (int i = 0; i < 4; i++){
        temp.ele[i]= ele[i] + v2.ele[i];
    }
    temp.recalulate(A+v2.A, Z+v2.Z);
    return (temp);
}

FourVector FourVector::operator - (FourVector v2) {
    FourVector temp;
    for (int i = 0; i < 4; i++){
        temp.ele[i]= ele[i] - v2.ele[i];
    }
    temp.recalulate(A-v2.A, Z-v2.Z);
    return (temp);
}

FourVector FourVector::operator * (double a) {
    FourVector temp;
    for (int i = 0; i < 4; i++){
        temp.ele[i]= ele[i]*a;
    }
    temp.recalulate(A, Z);
    return (temp);
}

FourVector FourVector::operator / (double a) {
    FourVector temp;
    for (int i = 0; i < 4; i++){
        temp.ele[i]= ele[i]/a;
    }
    temp.recalulate(A/a, Z/a);
    return (temp);
}

double FourVector::operator ^ (FourVector v2) { //dot product
    double temp;
    temp = ele[0]*v2.ele[0] - ele[1]*v2.ele[1] - ele[2]*v2.ele[2] - ele[3]*v2.ele[3];
    return (temp);
}

/*
FourVector FourVector::operator * (FourVector v2) { //cross product
    FourVector temp;
    temp.x = y*v2.z - z*v2.y;
    temp.y = z*v2.x - x*v2.z;
    temp.z = x*v2.y - y*v2.x;
    temp.set (2, temp.x, temp.y, temp.z);
    return (temp);
}
*/

void FourVector::print(string pre, string suf) const{
    cout << pre;
    printf("{%11.3f, %11.3f, %11.3f, %11.3f}",ele[0],ele[1],ele[2],ele[3]);
    cout << suf;
}

void FourVector::printKinamatics(int id, string msg) const{

    if (id != 0){
        printf("%*d  ",id-2, id);
        printf("%3s ", "A");
        printf("%3s ", "Z");
        printf("%8s ", "mass");
        printf("%8s ", "energy");
        printf("%8s ", "keA");
        printf("%8s ", "momt.");
        printf("%8s ", "beta");
        printf("%8s ", "theta");
        printf("%8s ", "phi");
        cout << endl;
    }

    cout << msg;
    printf("%3.0f ", A);
    printf("%3.0f ", Z);
    printf("%8.2f ", mass);
    printf("%8.2f ", energy);
    printf("%8.2f ", keA);
    printf("%8.2f ", momentum);
    printf("%8.4f ", beta);
    printf("%8.2f ", angle[0]*rad2deg);
    printf("%8.2f ", angle[1]*rad2deg);
    cout << endl;

}

void FourVector::debug(string msg) const{
    cout << msg << endl;
    cout << " 4-vector :" ;
    print("", "\n");
    cout <<  "--------------------------" << endl;
    cout << "     mass : " << mass << endl;
    cout << "   energy : " << energy << endl;
    cout << " T[MeV/A] : " << keA << endl;
    cout << "   {A, Z} : {" << A << "," << Z <<"}" << endl;
    cout << " momenutm : " << momentum << endl;
    cout << "     beta : " << beta << endl;
    cout << "    theta : " << angle[0]*rad2deg << endl;
    cout << "      phi : " << angle[1]*rad2deg << endl;
    cout << "==============================="<< endl;
}

#endif // VECTOR_H
