#include <iostream>
#include <cmath>

using namespace std;

const double pi=3.14159;

int main()
{
    int arraysize;
    double dummy1;
    
    cout <<" enter the array size \t: ";
    cin>> arraysize;
    double array[arraysize];
    
    
    cout<<" enter a number \t: ";
    cin>>dummy1;
    
    
    for (int i=0; i < arraysize; i++) {
        array[i]=dummy1*i;
    } 
    
    
    cout<< "the elements in the array is : \n";
    
    for (int i=0; i < arraysize; i++) {
        cout<< "array" << i << " = " << array[i] << endl;
    } 

    
    cin.get();

    return 0;
}