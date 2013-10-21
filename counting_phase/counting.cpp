
#include <iostream> // enable cin, cout
#include <sstream> // enable string control
#include <cmath> // math , enable simple math function
#include <complex>
#include <stdlib.h> // standard General Utlilities Library
#include <fftw3.h> // FFTW library
#include <fstream> // File I/O

using namespace std; // declare a namespace "std", every variable in this code is inside "std"
double a[2][2]; // raw data 0,1,2,....4998, 4999


int main()
{
	int count=0;
	
	
	for(int i=1;i<3;i++){
	for(int j=1;j<3;j++){
	for(int l=1;l<3;l++){
	for(int m=1;m<3;m++){
		cout << "(" << i << "," << j << "),(" << l << "," << m << ")";
		if( (i==l && j==m+1) || (i==l+1 && j==m ) ) { 
			count=count+1;
			cout << "counted";
		}
		cout << endl;
	}
	}
	}
	}

	cout<< count/16 << endl << "**************" <<endl;
    
    return 0;
    
}

