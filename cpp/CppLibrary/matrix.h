#ifndef MATRIX3D_H
#define MATRIX3D_H
#include <iostream>
#include <stdio.h>
#include <cmath>
#include "constant.h"

///  a matrix class of aribtary size

using namespace std;


class Matrix{
    public:
        int row, col;
        double **ele;

        Matrix(int row, int col);
        void setElement();
        Matrix & operator = (const Matrix mat); // assigment operator
        Matrix operator + (Matrix); //matrix sum
        Matrix operator * (Matrix); //matrix multiplicatio
        Vector operator ^ (const Vector &v ) ; // matrix.vector
        Matrix transpose(); //matrix transpose
  //      double det();    // matrix determinate
  //      Matrix3D minor();   // matrix minor
  //      Matrix inverse(); // matrix inverse
  //      Matrix eigenvector(); //eigen vector
  //      Matrix eigenValue(); // eigen value matrix
        void print(string) const;
};

Matrix::Matrix (int row, int col){
    ele= new double *[row];
    for ( int i =0 ; i < row ; i++){
        ele[i] = new double [col];
    }
    for ( int i = 0; i < row ; i++ ){
        for (int j = 0; j < col; j++ ) {
            ele[i][j] = 0 ;
        }
    }
}

void Matrix::setElement(){

}

/* Det
double Matrix::det(){
    double temp;
    temp = 0
    return temp;
}
*/

Matrix Matrix::operator * (const Matrix &mat){
    Matrix temp(row, mat.col);

    for (int i = 0 ; i < row; i ++){
        for (int k = 0 ; k < mat.col; k ++){
            for (int j = 0 ; j < col; j ++){
                temp.ele[i][k]= temp.ele[i][k] + ele[i][j]*mat.ele[j][k] ;
            }
        }
    }
    return temp;
}

Vector Matrix::operator ^ (const Vector &v) {
    Vector temp(row);

    for (int i = 0 ; i < col; i ++){
        for (int j = 0 ; j < row; j ++){
            temp.ele[i]= temp.ele[i]+ ele[i][j]*v.ele[j] ;

        }
    }

    return temp;
}

Matrix Matrix::transpose(){
    Matrix temp(col, row);
    for (int i = 0 ; i < row; i ++){
        for (int j = 0 ; j < col; j ++){
            temp.ele[i][j]= ele[j][i];
        }
    }
    return temp;
}

/* inverse
Matrix Matrix::inverse(){
    double a;
    a = det();
    Matrix temp;

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

void Matrix::print(string str) const{
    cout << endl << " ==== " << str <<" matrix : " << endl;
    for (int i = 0 ; i < row ; i++){
        for (int j = 0 ; j < col; j++){
            printf("%10.3f",ele[i][j]);
        }
        cout << endl;
    }
    cout << endl;
}

#endif // MATRIX3D_H
