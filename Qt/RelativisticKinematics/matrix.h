#ifndef MATRIX3D_H
#define MATRIX3D_H
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <cstdio>
#include <math.h>
#include <cmath>
#include <time.h>
#include "constant.h"

///  a matrix class of aribtary size

///using namespace std;

class Exception
{
public:
  const char* msg;
  Exception(const char* arg): msg(arg){}
};


class Matrix{
    public:

		Matrix();
        Matrix(int row, int col);
        Matrix(const Matrix &mat); // assigment operator
        Matrix(int row, int col,  double v); //matric with diagonal element of v
        ~Matrix(){
			// clean up allocated memory
			for (int r = 0; r < this->row; r++){
				delete this->ele[r];
			}
			delete this->ele;
			this->ele = NULL;
		}
		
		// assigment operator
		Matrix & operator = (const Matrix &mat);
        
        //Interface;  Get element; 
        double & operator ()(const int i, const int j);
        double Get(const int row, const int col) const;
        Matrix GetColVector(const int col) const;
        Matrix GetRowVector(const int row) const;
        int GetRow() const { return row;}
        int GetCol() const { return col;}
        int* Dimension() const;
        
        //Matrix with a constant 
        Matrix operator + (const double v);
        Matrix operator - (const double v);
        Matrix operator * (const double v);
        Matrix operator / (const double v);
        Matrix operator ^ (const int n); // matrix power
        
        //constant with Matrix
        friend Matrix operator + (const double v, const Matrix & mat){
			Matrix res = mat;
			return res + v;
		}
        friend Matrix operator - (const double v, const Matrix & mat){
			Matrix res = mat;
			return -res + v;
		}
		friend Matrix operator - (const Matrix & mat){ // unary minus
			Matrix res = mat;
			return (-1)*mat;
		}
        friend Matrix operator * (const double v, const Matrix & mat){
			Matrix res = mat;
			return res * v;
		}
        // multiplied an inverse.
        friend Matrix operator / (const double v, const Matrix & mat);
        
        //Matrix with Matrix
        Matrix operator + (const Matrix &mat); //matrix sum
        Matrix operator - (const Matrix &mat); 
        Matrix operator * (const Matrix &mat); //matrix multiplicatio
        Matrix operator *= (const Matrix &mat); //matrix multiplicatio
        //Matrix operator / (const Matrix &mat); 
        
        bool operator == (const Matrix &mat); //compare matrix
        bool operator != (const Matrix &mat); //compare matrix
        
        //Matrix self manipulation
        Matrix Transpose(); //matrix transpose
        Matrix Minor(const int i, const int j) const;
        double Det();
        Matrix Inverse();
        Matrix GaussianElimination();
        Matrix GetDiagVector();
        double Trace();
        double Mangnitude();
        Matrix Normalize();
        
        Matrix* QRDecomposition();
        
        //Eigen system //TODO
        Matrix EigenvalueMatrix(){
			return (*this);
		}
        Matrix EigenVetorMatrix();
        
		// Print
        void Print() const;
        void Print(std::string) const;
        
	private:
		double **ele;
		int row, col;
		
		// swap two values
		void Swap(double& a, double& b)
		{
		  double temp = a;
		  a = b;
		  b = temp;
		}
        
};

Matrix::Matrix(){
	this->ele = NULL;
	this->row = 0;
	this->col = 0;
}

Matrix::Matrix (const int row, const int col){
    
    if( row <= 0 && col <= 0 ) return;
    
    this->row = row;
    this->col = col;
    
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

Matrix::Matrix(const Matrix &mat){
	
	this->row = mat.row;
	this->col = mat.col;
	
	ele= new double *[mat.row];
    for ( int i =0 ; i < mat.row ; i++){
        ele[i] = new double [mat.col];
    }
    
    for ( int i = 0; i < row ; i++ ){
        for (int j = 0; j < col; j++ ) {
            ele[i][j] =  mat.ele[i][j];
        }
    }
}

double & Matrix::operator ()(const int i, const int j){
	if( this->ele != NULL && 
	    i > 0 && i <= this->row && 
	    j > 0 && j <= this->col){
		
		return ele[i-1][j-1];
	}else{
		throw Exception("get ele; index out of range");
	}
}

Matrix::Matrix(int row, int col,  double v){
	
	this->row = row;
	this->col = col;
	
	ele= new double *[row];
    for ( int i =0 ; i < row ; i++){
        ele[i] = new double [col];
    }
    
    for ( int i = 0; i < row ; i++ ){
        for (int j = 0; j < col; j++ ) {
			if( i == j){
				ele[i][j] = v ;
			}else{
				ele[i][j] = 0;
			}
        }
    }
}

Matrix & Matrix::operator = (const Matrix &mat){
	this->row = mat.row;
	this->col = mat.col;
	
	ele= new double *[mat.row];
    for ( int i =0 ; i < mat.row ; i++){
        ele[i] = new double [mat.col];
    }
    
    for ( int i = 0; i < row ; i++ ){
        for (int j = 0; j < col; j++ ) {
            ele[i][j] =  mat.ele[i][j];
        }
    }
    return *this;
}

double Matrix::Get(const int row, const int col) const{
	return this->ele[row-1][col-1];
}

Matrix Matrix::operator + (const double v){
	Matrix res  = *this;
	for ( int i = 0; i < res.row ; i++ ){
        for (int j = 0; j < res.col; j++ ) {
            res.ele[i][j] += v;
        }
    }
    return res;
}

Matrix Matrix::operator - (const double v){
	return *this + (-v);
}

Matrix Matrix::operator * (const double v){
	Matrix res = *this;
	for ( int i = 0; i < res.row ; i++ ){
        for (int j = 0; j < res.col; j++ ) {
            res.ele[i][j] = res.ele[i][j] * v;
        }
    }
    return res;
}

Matrix Matrix::operator / (const double v){
	return *this * (1./v);
}

Matrix Matrix::operator ^ (const int n){
	Matrix res = *this;
	Matrix a = *this;
	
	for ( int i = 1; i < n ; i++){
		res *= a;
	}
	
	return res;
}

Matrix Matrix::operator + (const Matrix &mat){
	
	Matrix res = *this;
	
	if( mat.row == res.row && mat.col == res.col){
		for ( int i = 0; i < res.row ; i++ ){
			for (int j = 0; j < res.col; j++ ) {
				res.ele[i][j] +=  mat.ele[i][j];
			}
        }
        return res;
    }else{
		throw Exception("a + b, Dimension does not match");
	}
		
}

Matrix Matrix::operator - (const Matrix &mat){
	
	Matrix res = *this;
	
	if( mat.row == res.row && mat.col == res.col){
		for ( int i = 0; i < row ; i++ ){
			for (int j = 0; j < col; j++ ) {
				res.ele[i][j] -=  mat.ele[i][j];
			}
        }
        return res;
    }else{
		throw Exception("a - b, Dimension does not match");
	}
}

Matrix Matrix::operator * (const Matrix &mat){
	
	//check dimension
	if( this->col == mat.row){
		Matrix res(this->row, mat.col);
		for ( int i = 0; i < this->row ; i++ ){
			for (int k = 0; k < mat.col; k++){
				for (int j = 0; j < this->col; j++ ) {
					res.ele[i][k] +=  this->ele[i][j] * mat.ele[j][k];
				}
			}
        }
        return res;
    }else{
		throw Exception("a * b, Dimension does not match");
	}
}

Matrix Matrix::operator *= (const Matrix &mat){
	//check dimension
	if( this->col == mat.row &&
	    this->col == this->row &&
	    mat.col == mat.row){
			
		Matrix res(this->row, this->col);
		for ( int i = 0; i < this->row ; i++ ){
			for (int k = 0; k < mat.col; k++){
				for (int j = 0; j < this->col; j++ ) {
					res.ele[i][k] +=  this->ele[i][j] * mat.ele[j][k];
				}
			}
        }
     
		*this = Matrix(res);
        return *this;
        
    }else{
		throw Exception("a *= b, Dimension does not match");
	}
}

bool Matrix::operator == (const Matrix &mat){
	
	if( this->row == mat.row && this->col == mat.col){
		for( int i = 1; i <= mat.row; i++){
			for( int j = 1; j <= mat.col; j++){
				if( this->ele[i-1][j-1] != mat.ele[i-1][j-1] ) {
					return 0;
				} 
			}	
		}
		return 1;
	}else{
		return 0;
	}
}

bool Matrix::operator != (const Matrix &mat){
	return !(*this == mat);
}

Matrix Matrix::GetColVector(const int col) const{
	Matrix res(this->row, 1);
	
	for(int i = 1; i <= this->row; i++){
		res(i,1) = this->Get(i, col);
	}
	return res;
}

Matrix Matrix::GetRowVector(const int row) const{
	Matrix res(1, this->col);
	
	for(int i = 1; i <= this->col; i++){
		res(1,i) = this->Get(row, i);
	}
	return res;
}

Matrix Matrix::Transpose(){
	
    Matrix res(this->col, this->row);
    for (int i = 0 ; i < this->row; i ++){
        for (int j = 0 ; j < this->col; j ++){
            res.ele[j][i]= this->ele[i][j];
        }
    }
    return res;
}

Matrix Matrix::Minor(const int i, const int j) const{
	Matrix res;
	
	if( i > 0 && i <= this->row && j > 0 && j <= this->col){
		res = Matrix(this->row - 1, this->col - 1);
		
		// copy the content of the matrix to the minor, except the selected
		for (int r = 1; r <= (this->row - (i >= this->row)); r++){
			for (int c = 1; c <= (this->col - (j >= this->col)); c++){
				res(r - (r > i), c - (c > j)) = this->ele[r-1][c-1];
			}
		}
		return res;
		
	}else{
      throw Exception("Index for minor out of range");
    }

}

int * Matrix::Dimension() const{

	int *dim = new int[2];
	dim[0] = this->row;
	dim[1] = this->col;
	
	return dim;
}

void Matrix::Print() const{
    if( ele != NULL){
		printf("[");
		for (int i = 0 ; i < this->row ; i++){
			if ( i > 0) printf(" ");
			for (int j = 0 ; j < this->col-1; j++){
				printf("%7.3f, ",ele[i][j]);
			}
			if( i < this->row -1) {
				printf("%7.3f;\n", ele[i][this->col-1]);
			}else{
				printf("%7.3f]\n", ele[i][this->col-1]);
			}
		}
    }else{
		printf("[]\n");
	}
}

void Matrix::Print(std::string str) const{
    printf("%s(%d,%d)= \n", str.c_str(), this->row, this->col);
    this->Print();
}

Matrix Matrix::Inverse(){
	Matrix res;
	
	Matrix a = *this;
	int rows = a.row;
	int cols = a.col;
	double d = a.Det();
	
	if (rows == cols && d != 0){
		if (rows == 1){
			res = Matrix(rows, cols);
			res(1, 1) = 1 / a(1, 1);
		}else if (rows == 2){
			res = Matrix(rows, cols);
			res(1, 1) = a(2, 2);
			res(1, 2) = -a(1, 2);
			res(2, 1) = -a(2, 1);
			res(2, 2) = a(1, 1);
			res = (1/d) * res;
		}else{
			// calculate inverse using gauss-jordan elimination
			//   http://mathworld.wolfram.com/MatrixInverse.html
			//   http://math.uww.edu/~mcfarlat/inverse.htm
			res = Matrix(rows, rows, 1);   // a diagonal matrix with ones at the diagonal
			Matrix ai = a;    // make a copy of Matrix 

			for (int c = 1; c <= cols; c++){
				// element (c, c) should be non zero. if not, swap content
				// of lower rows
				int r;
				for (r = c; r <= rows && ai(r, c) == 0; r++){
				}
				if (r != c){
					// swap rows
					for (int s = 1; s <= cols; s++){
						Swap(ai(c, s), ai(r, s));
						Swap(res(c, s), res(r, s));
					}
				}

				// eliminate non-zero values on the other rows at column c
				for (int r = 1; r <= rows; r++){
					if(r != c){
						// eleminate value at column c and row r
						if (ai(r, c) != 0){
							double f = - ai(r, c) / ai(c, c);

							// add (f * row c) to row r to eleminate the value
							// at column c
							for (int s = 1; s <= cols; s++){
								ai(r, s) += f * ai(c, s);
								res(r, s) += f * res(c, s);
							}
						}
					}else{
						// make value at (c, c) one,
						// divide each value on row r with the value at ai(c,c)
						double f = ai(c, c);
						for (int s = 1; s <= cols; s++){
							ai(r, s) /= f;
							res(r, s) /= f;
						}
					}
				}
			}
		}
	}else{
		throw Exception(" fail to calculate inverse");
	}

	return res;
}

double Matrix::Det(){
	double d = 0;
	
	if( this->row == this->col){
		
		Matrix res = *this;
		
		if( res.row == 1){ 
			
			d = res(1,1);
			
		}else if (res.row == 2){
			
			d = res(1,1) * res(2,2) - res(1,2)* res(2,1);
			
		}else{
			for( int j = 1; j <= res.col; j++){
				Matrix M = this->Minor(1,j);
				double det = M.Det();				
				d += (j%2 + j%2 -1) * res(1,j) * det;
			}
		}
		
	}else{
		throw Exception("Matrix must be square");
	}
	
	return d;
}

Matrix Matrix::GaussianElimination(){
	Matrix res = *this;
	
	//eliminate from up to the 2nd last row
	for (int i = 1; i <= res.row-1; i++){
		for(int r = i+1; r <= res.row; r++){
			
			if (res(i,i) == 0){ // if  = 0, swap with next row.
				
				for(int c = 1; c <= res.col; c++){
					Swap(res(i,c), res(i+1,c));
				}
				//res.Print("Swap row");
			}
			
			double f = res(r,i)/res(i,i);
			//printf("======== %d row: %d, f = %f \n", i, r, f);
			//
			//for(int c = i; c <= res.col; c++){
			//	printf("%5.2f, ", res(r,c));
			//}
			//printf(";\n");
			//
			//
			//for(int c = i; c <= res.col; c++){
			//	printf("%5.2f, ", res(i,c)*f);
			//}
			//printf(";\n");
			
			for(int c = i; c <= res.col; c++){
				res(r,c) = res(r,c) - res(i,c)*f;
				//printf("%5.2f, ", res(r,c));
			}
			//printf(";\n");
		}
		//res.Print("temp");
		
	}
	
	return res;
}

Matrix Matrix::GetDiagVector(){
	int n;
	if( this->row <= this->col){
		n = this->row;
	}else{
		n = this->col;
	}
	
	Matrix res(n, 1);
	
	for(int i = 1; i <= n; i++){
		res(i,1) = (*this)(i,i);
	}
	
	return res;
}

double Matrix::Trace(){
	if( this->row == this->col){
	
		double t = 0;
		for(int i = 1; i <= this->row ; i++){
			t += (*this)(i,i);
		}
	
		return t;
	}else{
		throw Exception("Trace : must be square matrix.");
	}
}

double Matrix::Mangnitude(){
	double sq = 0;
	
	for(int i = 1; i <= row ; i++){
		for(int j = 1; j <= col ; j++){	
			sq += pow(Get(i,j),2);
		}
	}
	
	return sqrt(sq);
	
}

Matrix Matrix::Normalize(){
	
	Matrix res = *this;
	
	double sq = Mangnitude();
	
	return res/sq;
}

Matrix* Matrix::QRDecomposition(){
	
	if( row == col ){
		Matrix* u = new Matrix[col];
		for(int i = 1; i <= col; i++){
			u[i-1] = GetColVector(i);
		}
		for(int i = 1; i <= col; i++){
			printf("================= %d\n", i);
			u[i-1].Print("u");
			
			for(int j = 1; j < i; j++){
				Matrix k = u[j-1];
				k = k.Normalize();
				printf("k %d\n", j);
				
				double a = (u[i-1].Transpose() * k)(1,1);
				printf(" a %f \n", a);
				(a*k).Print();
				u[i-1] = u[i-1] - a * k;
				
			}
			
			//double a = (u[i-1].Transpose() * h)(1,1);
			u[i-1].Print("u");
			
		}
		
		printf("========+++++++++=========\n");
		for(int i = 0; i < col; i++){
			
			u[i] = u[i].Normalize();
			u[i].Print("u");
		}

		//Forming Q matrix from u[i]
		Matrix Q(row, col);
		for(int i = 1; i <= row; i++){
			for(int j = 1; j <= col; j++){
				Q(i,j) = u[j-1].Get(i,1);
			}
		}
		
		//R matrix is Q.Transpose()* a; Q.Transpose() = Q.Inverse();
		Matrix a = *this;
		Matrix R = Q.Transpose() * a;
		
		Matrix *output = new Matrix[2];
		output[0] = Q;
		output[1] = R;
		
		return output;
	
	}else{
		throw Exception("The algorithm is only for square matrix currently.");
		return NULL;
	}
	
}

Matrix Matrix::EigenVetorMatrix(){
	Matrix ev = EigenvalueMatrix();

	return ev; 
}

// functions of matrix;
Matrix IdentityMatrix(const int n){
	Matrix res = Matrix(n,n, 1 );
	return res;
}

Matrix RandomMatrix(const int r, const int c){
	srand(time(NULL));
	Matrix res = Matrix(r,c);
	for(int i = 1; i <= r ; i++){
		for(int j = 1; j <= c ; j++){
			res(i,j) = rand()%10000 / 10000.; //random form 0,1
		}
	}
	return res;
}

Matrix Inverse(const Matrix &mat){
	Matrix res = mat;
	return res.Inverse();
}

Matrix Transpose(const Matrix &mat){
	Matrix res = mat;
	return res.Transpose();
}

double Det(const Matrix &mat){
	Matrix res = mat;
	return res.Det();
}


#endif // MATRIX3D_H
