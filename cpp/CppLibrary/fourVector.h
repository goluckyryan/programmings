#ifndef FOURVECTOR_H
#define FOURVECTOR_H
#include <iostream>
#include <stdio.h>
#include <cmath>
#include "constant.h"
#include "vector4D.h"

//using namespace std;

class FourVector: public Vector4D{
    public:
        double ele[4]; // assume it is (E,px,py,pz)

        double mass;     //MeV c^-2 = sqrt(vector4D.magnitudeSq)
        double Z;   // charge
        double A;   // mass number
        double energy;   //MeV
        double keA   ;   //MeV/A
        double momentum; // MeV/c = vector4D.length
        double beta;
        double angle[2]; //0 = theta , 1 = phi, in rad = (vector4D.theta, vector4D.phi)

        FourVector ();  // overloading constructor
        FourVector (int id, double m[3],double, double, double); //constructor
        void set(int id, double m[3], double, double, double);
        void recalulate(double, double);
        FourVector operator + (const FourVector) const; //vector sum
        FourVector operator - (const FourVector) const; //vector substract
        FourVector operator * (double); //vector muliple by a constant
        FourVector operator / (double); //vector divided by a constant
        double    operator ^ (const FourVector) const; //vector dot product
       // FourVector operator * (FourVector); //vector cross product
        void normalize();
	void AngleCal();
        void print(string pre, string suf) const; //const = the function does not change the data.
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
        momentum = sqrt((energy-mass)*(energy+mass));
    }else if(id ==2){
        momentum = T;
        energy = sqrt(mass*mass + momentum*momentum);
    }else if(id ==3){
        energy = sqrt(pow(T*Z*c/1e6,2)+mass*mass);
        momentum = sqrt((energy-mass)*(energy+mass));
    }else if(id == 4){
        energy = mass / sqrt( 1- pow(T,2));
        momentum = sqrt((energy-mass)*(energy+mass));
    }

    keA = (energy-mass)/A;
    beta = momentum/energy;

    ele[0]=energy;
    ele[1]=momentum*cos(angle[1])*sin(angle[0]);
    ele[2]=momentum*sin(angle[1])*sin(angle[0]);
    ele[3]=momentum*cos(angle[0]);
    AngleCal();

}

void FourVector::recalulate(double a, double b){
    mass = sqrt(pow(ele[0],2)-pow(ele[1],2)-pow(ele[2],2)-pow(ele[3],2));
    energy = ele[0];
    keA = (ele[0]-mass)/a;
    A = a; Z =b;
    momentum = sqrt(pow(ele[1],2)+pow(ele[2],2)+pow(ele[3],2));
    beta = momentum/energy;
    AngleCal();
    //angle[0]=atan2(sqrt(pow(ele[1],2)+pow(ele[2],2)),ele[3]);
    //angle[1] =atan2(ele[2],ele[1]);
}

void FourVector::normalize(){
    momentum = 1;
    energy = sqrt(mass*mass + 1);
    beta = momentum/energy;

    ele[0]=energy;
    ele[1]=momentum*cos(angle[1])*sin(angle[0]);
    ele[2]=momentum*sin(angle[1])*sin(angle[0]);
    ele[3]=momentum*cos(angle[0]);


    printf("vector nomralized !\n");
}

void FourVector::AngleCal(){
    if ( abs(ele[1]) < 0.001 && abs(ele[2]) < 0.001 ){
    	angle[1] = 0;
    	if (ele[3] >= 0 ){
	    angle[0] = 0;
	}else{
	    angle[0] = 3.141592;
	}
    }else{
	angle[0] = atan2(sqrt(pow(ele[1],2)+pow(ele[2],2)),ele[3]);
	angle[1] = atan2(ele[2],ele[1]);
    }
}

FourVector FourVector::operator + (const FourVector v2) const{
    FourVector temp;
    for (int i = 0; i < 4; i++){
        temp.ele[i]= ele[i] + v2.ele[i];
    }
    temp.recalulate(A+v2.A, Z+v2.Z);
    return (temp);
}

FourVector FourVector::operator - (const FourVector v2) const{
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


double FourVector::operator ^ (const FourVector v2) const{ //dot product
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
    printf("%s", pre.c_str());
    printf("{%11.3f, %11.3f, %11.3f, %11.3f}",ele[0],ele[1],ele[2],ele[3]);
        
    printf(", Mass: %10.3f MeV, ", mass);
    printf("Momt: %10.3f MeV/c, ", momentum);
    printf("Angle: %10.5f deg, %10.5f deg", angle[0]/deg2rad, angle[1]/deg2rad);
    
    printf("%s", suf.c_str());;
}

void FourVector::printKinamatics(int id, string msg) const{

    if (id != 0){
        printf("%*d   ",id-2, id);
        printf("%3s ", "A");
        printf("%3s ", "Z");
        printf("%8s ", "mass");
        printf("%8s ", "energy");
        printf("%8s ", "keA");
        printf("%8s ", "momt.");
        printf("%8s ", "beta");
        printf("%8s ", "theta");
        printf("%8s ", "phi");
        printf("%8s \n", "pi-theta");
    }

    printf("%s", msg.c_str());
    printf("%3.0f ", A);
    printf("%3.0f ", Z);
    printf("%8.2f ", mass);
    printf("%8.2f ", energy);
    printf("%8.2f ", keA);
    printf("%8.2f ", momentum);
    printf("%8.4f ", beta);
    printf("%8.2f ", angle[0]*rad2deg);
    printf("%8.2f ", angle[1]*rad2deg);
    printf("%8.2f \n", 180-angle[0]*rad2deg);

}

void FourVector::debug(string msg) const{
    printf("%s \n", msg.c_str());
    printf(" 4-vector :");
    printf("\n");
    printf("--------------------------\n");
    printf("     mass : %10.4f\n"  , mass   );
    printf("   energy : %10.4f\n"  , energy );
    printf(" T[MeV/A] : %10.4f\n"  , keA    );
    printf("   {A, Z} : {%2.0f, %2.0f}\n"  , A , Z );
    printf(" momenutm : %10.4f\n"  , momentum        );
    printf("     beta : %10.4f\n"  , beta            );
    printf("    theta : %10.4f\n"  , angle[0]*rad2deg);
    printf("      phi : %10.4f\n"  , angle[1]*rad2deg);
    printf("===============================\n");
}

#endif // VECTOR_H
