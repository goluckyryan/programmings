#include <stdio.h>

//######################################## Passing Argument

// pass by value
// never changed the argument
// Copying large structs or classes can take a lot of time and memories.
// return value can only be done by "return"
void PassByValue(int y){
   printf("Pass by Value: y = %d\n", y);
}


// pass by reference
// the argument can be changed
// Fast, return multiple value.
// output and input are not distinguishable
void PassByReference(int &y){
   y = y + 1;
   printf("Pass by Reference: y = %d\n",y);
}

// pass by const reference
// fixed the argument.
void PassByConstReference(const int &y){
   printf("Pass by Const Reference: y = %d\n",y);
}

// pass by address
// argument can be changed
// Fast
// return multiple value
// the pointer be NULL
void PassByAddress(int *pValue){
   *pValue = 6; // chaneg the context of pValue to 6
   printf("Pass by Address: y = %d\n", *pValue);
}


//######################################## Return Value
// Retunn by Value
int ReturnByValue(int z){
   int kValue = z * 2 ;
   return kValue;  // A copy of kValue will be returned
}

// Return by reference
int& ReturnByReference(int z){
   int kValue = z * 2;
   return kValue;  // return a reference
}

// Return by Address
int* ReturnByAddress(int z){
   int kValue = z * 2;
   return &kValue;
}


int main(){

   PassByValue(5); //first call

   int x = 6;
   printf ("Original : x = %d\n", x);
   PassByValue(x);   //2nd call
   PassByValue(x+1); // 3rd call
   printf ("Original : x = %d\n", x);

   PassByReference(x);
   printf ("Original : x = %d\n", x);

   PassByAddress(&x);
   printf ("Original : x = %d\n", x);

}
