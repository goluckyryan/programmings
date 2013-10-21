/* this demonstrate 

1) the use of pointer as dynamic array

2) passing this dynamic array into a function

*/




#include <iostream>

using namespace std;

void multiple ( int *pointer ){

	sizeof(pointer);

}

int main() {


	int array_size;

	cout << " how large is the array ? " ;
	cin >> array_size;
	
	cout << " now generating an array of 3x to " << array_size*3 << endl;
	
	int *p = new int [array_size]; //make a pointer with size and type is int
	
	//alternative int *p = new int; if make it this way, when delete the pointer, it may crash due to unknow size of the pointer.
	
	for ( int i = 0 ; i < array_size ; i++ ) {
		p[i]=(i+1)*3;
		cout << p[i] << endl;
	}

	delete [] p;	
	
	// 2D dynamic array;	
	int row, col;
	
	cout << " row ? " ;
	cin >> row;
	cout << " col ? " ;
	cin >> col;

	int **p2 = new int *[row]; // pointer of pointer, it has number row pointers
	for ( int i =0 ; i < row ; i++){
		p2[i] = new int [col]; // the i-th pointer of pointer is a pointer, it has numbe of col element.
	}
	
	cout << " initialating 2D array with entry of i+j" << endl;
	
	for ( int i = 0; i < row ; i++ ){
		for (int j = 0; j < col; j++ ) {
			p2[i][j] = i+j ;
			cout << p2[i][j] << "\t" ;
		}
		cout << endl;
	}
	
	for (int i =0; i < row ; i++){
		delete [] p2[i];
	}	
	delete [] p2;
	

	
	return 0;

}
