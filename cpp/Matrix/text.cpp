#include "Matrix.h"

int main(int argc, char *argv[])
{
	Matrix G = Matrix(4, 4); //row, col
	
	for(int i = 1 ; i <= 4 ; i++){
		for(int j = 1 ; j<= 4 ; j++){
			G(i, j) = pow(i,j); 
		}
	}
	//G(1, 1) = 1;
	//G(1, 2) = 2;
	//G(2, 1) = 3;
	//G(2, 2) = 4;
	printf("G = \n");
	G.Print();
	
	printf("det = %f \n", Det(G));

	Matrix G_inv = Inv(G);
	printf("Inv(G) = \n");
	G_inv.Print();

	return 0;
}
