#include "matrix.h"

int main(){
	
	Matrix a,b;
	
	int row = 3;
	int col = 3;
	//a = Matrix(row,col);
	//for ( int i = 1; i <=row; i++){
	//	for( int j = 1; j <=col; j++){
	//		a(i,j) = (i-1)*col +j;
	//	}
	//}
	a = Matrix(row, col);
	a(1,1) = 1; a(1,2) = 2; a(1,3) = 3; 
	a(2,1) = 1; a(2,2) = 1; a(2,3) = 0; 
	a(3,1) = 7; a(3,2) = 9; a(3,3) = 1; 
	
	//a = RandomMatrix(row, col);
	
	a.Print("a");
		
	//a.GaussianElimination().Print("G(a)");
	//
	//(a.GaussianElimination()).GetDiagVector().Print("eigne");
	//
	//printf("trace : %f , %f\n", a.Trace(), a.GaussianElimination().Trace());
	//printf("Det : %f , %f\n", a.Det(), a.GaussianElimination().Det());
	//
	//Matrix ev = a.EigenvalueMatrix();
	//ev.Print("eigne");
	//
	//Matrix I = IdentityMatrix(row);
	//
	//b = a - ev(1,1)*I;
	//
	//b.Print("a-eI");
	//
	//printf("det(b) %f \n", b.Det());
	//
	////(Transpose(a)).Print("a.a");
	//
	//try{
	//	//(b.Inverse()).Print("Inv(b)");
	//	//(Transpose(a)*a).Print("a.a");
	//}catch(Exception err){
	//	printf("%s\n", err.msg);
	//}
	//
	//Matrix p(2,1);
	//
	//p(1,1) = 3;
	//p(2,1) = 4;
	//
	//p.Print("p");
	//
	//(p.Normalize()).Print("p");
	//
	//a.Print("a");
	
	Matrix* QR = a.QRDecomposition();
	
	QR[0].Print("Q");
	
	(QR[0].Transpose() * QR[0]).Print("Q^T.Q");
	
	QR[1].Print("R");
	
	return 0;

}
