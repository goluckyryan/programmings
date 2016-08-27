#include <istream> 
#include <fstream> 
#include <string> 
#include <sstream> 
#include <cstdlib> 
#include <cmath> 
#include <ctime> 
#include <stdio.h> 
#include <math.h> 
#include <cstring> 
#include <iostream>

using namespace std;

void func(int * A){
	
	int n = sizeof(A);

    for( int i = 0; i < n ; i++){
		printf("%d \t", A[i]);
	}
	printf("\n");
}

int main (){
	
	int a = 1;   // a = 1
	int *p = &a; // pointer p = adress of a
	
	cout << p << endl; //pointer p = adress of a
	cout << &a << endl; // address of a
	cout << *p << endl; // content of p = a
	
	int vec[3];
	for (int i = 0; i<=3 ; i++){
		vec[i] = i;
	}
	
	cout << vec    << endl; // address of vec
	cout << &(vec[0]) << endl; // address of vec[0]
	cout << &vec[1] << endl;  // address of vec[1], interger is 4 bit
	cout << vec[1] << endl;  // value of vec[1]
	cout << *vec << endl;    // content of vec = vec[0]
	cout << *vec + 1 << endl;    // content of vec + 1 = vec[1]
	
	
	int array[3][3];
	
	for (int i = 0; i<=3 ; i++){
		for (int j = 0; j<=3 ; j++){
			array[i][j] = 10*i +j;
		}
	}

	cout << array << endl; // addree of array
	cout << &array[0][0] << endl; // adress of array[0][0]
	cout << &array[0][1] << endl; // adress of array[0][1]
	cout << &array[1][0] << endl; // adress of array[1][0]
	cout << &array[0] << endl; // adress of array[0]
	cout << &array[1] << endl; // adress of array[1]
	
	cout << array[1] << endl; // adress of array[1]
	
	func(array[0]);
	
	return 0;

}
