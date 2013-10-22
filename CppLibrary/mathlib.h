#include <cmath>
#include <algorithm>
#include <complex>
#include <iostream>

using namespace std;

double pi = atan2(0,-1);

//Class definition


// Function Definition


double norm(double a[3]){
    return sqrt(pow(a[0],2)+ pow(a[1],2)+ pow(a[2],2));
}

double DotProduct(double *a, double *b){
    return (a[0]*b[0]+a[1]*b[1]+a[2]*b[2]);
    delete a,b;
}

double *CrossProduct(double a[3], double b[3]){
    double *c;
    c[0]=a[1]*b[2]-a[2]*b[1];
    c[1]=-a[0]*b[2]+a[2]*b[0];
    c[2]=a[0]*b[1]-a[1]*b[0];
    return c;
}

double *MatrixProduct(int dimension, double **a, double *b){
    double *c = new double [dimension];
    for (int i = 0 ; i < dimension ; i++){
        c[i]=0;
        for(int j =0; j < dimension ; j++) {
            c[i]=c[i]+ a[i][j]*b[j];
        }
    }
    return c;
    delete [] c;
}

int *InversionVector(int dimension, int *a){
    int *b = new int [dimension-1];
    int count;

    for (int i = 1; i < dimension ; i++ ){
        count = 0;
        for(int j = 0; j < i ; j ++){
            //cout << a[j] << ", " << a[i] << endl;
            if ( a[j] > a[i]){
                count ++ ;
            }
        }
        b[i-1]= count;
    }

    return b;

}


int Parity(int dimension, int *a){
    int *b;
    int sum =0;

    b = InversionVector(dimension, a);

    for ( int i = 0; i < dimension; i ++){
        sum = sum + b[i];
    }

    return pow(-1, sum);

}
