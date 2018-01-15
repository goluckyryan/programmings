//#include "matrix4D.h"
//#include "vector4D.h"
//#include "fourVector.h"

#include <stdio.h> //printf
#include "isotopes.h"

//pass by value, return value
//the object is the symbol, the symbol be copied.
int hunc(int a){
	a = 5;
	return a;
}

//pass by reference , return reference; 
//the object is the symbol, but using the address faster
int & func(int &a){
	a = 5;
	return a;
}

//pass by pointer, return pointer ; 
//the object is the pointer
int* gunc(int *p){
	*p = 5;
	return p;
}

int main(){

//   Matrix4D mat1(1,2,3,4,10,3,4,5,3,4,5,6,4,5,6,7);
//   
//
//   double mass[3]; 
//   mass[0] = 1000, mass[1] = 1, mass[2] = 2;
//   
//   FourVector v1(1, mass, 250, 0, 0);
//   Vector4D vk(1,0,1,0);
//   
//   mat1.print("mat1");
//   v1.print("v1","\n");
//   vk.print("vk");
//   
//   (mat1^vk).print("mat.v1");


//	int a = 0;
//	int *p = new int;
//	*p = 0;
//	
//	printf("%d, %d\n", a, *p);
//	
//	
//	printf("%d, %d\n", func(a), *gunc(p));
	

   Isotopes nucleus("12C");
   
   return 0;

}
