#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>
#include <stdio.h>
#include <cmath>
#include "constant.h"

// a vector class of aribitary size

using namespace std;

class Vector{
    public:
        double *ele; //elements // pointer
        int dimension;

        Vector (int d); //constructor
        ~Vector (); // destructor
        void setDimension(int d);
        void setElement();
        void defaultElement(int id);
   //     Vector (Vector v);  // copy constructor
        Vector& operator = (const Vector &v); //assigmnet
        Vector operator + (const Vector &v); //vector sum
        Vector operator - (const Vector &v); //vector substract
        Vector operator * (double); //vector times constant
        Vector operator / (double); //vector divided constant
        double operator ^ (const Vector &v); //vector dot product
        Vector cross (const Vector &v); //vector cross product for 3D
        double norm();
        void normalize();
        double theta();
        double phi();
        double openAng (const Vector &v);
        void print(string prefix, string suffix) const;
        void debug(string prefix);
    private:
};


Vector::Vector (int d){
    setDimension(d);
}

void Vector::setDimension (int d){
    dimension = d;
    if ( d <= 0) {
        cout << "dimension cannot <= 0 ! (setdimension = 1)";
        dimension = 1;
    }
    ele= new double [dimension];
    for (int i = 0; i < dimension; i++){
        ele[i]=0;
    }
}

void Vector::setElement(){
    cout << " dimension : " << dimension << endl;
    for (int i = 0; i < dimension; i++){
        cout << " set ele["<< i << "] : " ;
        cin >> ele[i];
    }
}

void Vector::defaultElement(int id){

    for (int i = 0; i < dimension; i++){
            ele[i]=id*(i+1);
    }
}

Vector::~Vector(){
    delete ele;
}

Vector& Vector::operator = (const Vector &v){
    if ( this != &v && dimension == v.dimension){
        for (int i = 0; i < v.dimension; i++){
            ele[i] = v.ele[i];
        }
        dimension = v.dimension;
    }else{
        cout << "dimension not equal!" << endl;
    }
    return *this;
}

Vector Vector::operator + (const Vector &v) {
    Vector temp (v.dimension);
    if ( dimension == v.dimension ){
        for (int i = 0; i < dimension; i++){
            *(temp.ele+i) = *(ele+i)+ *(v.ele+i);
        }
    }else{
        cout << " dimension not match! "<< dimension << " != " << v.dimension << endl  ;
    }
    return  temp;
}

Vector Vector::operator - (const Vector &v2) {
    Vector temp (dimension);
    if ( dimension == v2.dimension ){
        for (int i = 0; i < dimension; i++){
            temp.ele[i] = ele[i] - v2.ele[i];
        }
    }else{
        cout << " dimension not match! "<< dimension << " != " << v2.dimension << endl ;
    }
    return (temp);
}

Vector Vector::operator * (double a) {
    Vector temp (dimension);
    for (int i = 0; i < dimension; i++){
        temp.ele[i] = ele[i] * a;
    }
    return (temp);
}

Vector Vector::operator / (double a) {
    Vector temp (dimension);
    for (int i = 0; i < dimension; i++){
        temp.ele[i] = ele[i] / a;
    }
    return (temp);
}

double Vector::operator ^ (const Vector &v) {
    double temp = 0;
    if ( dimension == v.dimension ){
        for (int i = 0; i < dimension; i++){
            temp = temp + ele[i] * (v.ele[i]);
        }
    }else{
        cout << " dimension not match! "<< dimension << " != " << v.dimension << endl ;
    }
    return (temp);
}

Vector Vector::cross (const Vector &v) {
    Vector temp(dimension);
    if ( dimension == v.dimension && dimension == 3 ){
        temp.ele[0] = ele[1]*v.ele[2]-ele[2]*v.ele[1];
        temp.ele[1] = ele[2]*v.ele[0]-ele[0]*v.ele[2];
        temp.ele[2] = ele[0]*v.ele[1]-ele[1]*v.ele[0];
    }else{
        cout << " dimension not match or != 3! "<< endl ;
    }
    return (temp);
}

double Vector::norm(){
    double temp = 0;
    for (int i = 0; i < dimension; i++){
        temp = temp + ele[i]*ele[i];
    }
    return sqrt(temp);
}

void Vector::normalize(){
    double a;
    a = norm();
    if ( a == 0){
        cout << " Norm = 0 ! (aborted)" << endl;
    }else{
        for (int i = 0; i < dimension; i++){
            ele[i] = ele[i]/a;
        }
    }
}

double Vector::theta(){
    double a ;
    if ( dimension == 2 ){
        a = atan2(ele[1], ele[0]);
    }else if (dimension == 3) {
        a = atan2(sqrt(pow(ele[0],2)+pow(ele[1],2)), ele[2]);
    }else{
        a = 0;
    }
    return a;
}

double Vector::phi(){
    double a;
    if ( dimension == 3 ){
        a = atan2(ele[1], ele[0]);
    }else{
        a = 0;
    }
    return a;
}

double Vector::openAng( const Vector &v){
    double a = 0;
    if ( dimension == v.dimension){
        Vector temp1(dimension), temp2(dimension);
        temp1 = *this;
        temp2 = v;
        temp1.normalize();
        temp2.normalize();
        a = acos(temp1^temp2);
    }else{
        cout  << " dimension not equal!" << endl ;
    }

    return a;


}

void Vector::print(string prefix, string suffix) const{
    cout << prefix;
    cout << dimension << " {";
    for (int i = 0; i < dimension ; i++){
        //cout << *(ele+i) << "\t";
        printf("%10.3f, ",ele[i]);
    }
    cout << "}";
    cout << suffix;
}

void Vector::debug(string prefix){
    cout << prefix;
    for (int i = 0; i < dimension ; i++){
        cout << &ele[i] << "\t";
    }
    cout << endl;

}

#endif // VECTOR_H
