#include <iostream>
#include <cmath>

using namespace std;

// pointer is memeory address. 
// but in fact, a pointer has a memeory address. 

// when declare a variable, there are 2 things : the memeory address and the context.

// to initialiate a pointer, use (int *p = new int)
// or 
// int *p = 6;

// to call the context
// *p
// or p[0]
// or *p+1;

int main()
{
    int a[5];
    int *p = new int; // declare a pointer points to an integer
    p = a; //a pointer "p" to a 

    // int *p = a;

    //declare a[5]
    a[0]=0; 
    a[1]=1;
    a[2]=2;
    a[3]=3;
    a[4]=4;

    int *b;// another pointer;


    cout << "the pointer address is &a =" << &a <<endl;
    cout << "the pointer itself is p = " << p << endl;

    cout << "the pointer point to p[0]=a[1], p[1], p[2]" <<endl;
    
    cout<< p[0] << " " << p[1] << " " << p[2] <<endl;;

    cout << "setting another point b same as p" << endl;

    b = p;

    cout << b << " , b[4] = " << b[4] << endl;

    cout << " this shows that a pointer stores the adress of a. " << endl << " when we add [] behind p, this call the context of the address" << endl;

    cout << "address of p" << &p << endl;

    cout << a << endl;
    //system("pause"); // use in windows

    cout << sizeof(p) << endl; //size of p

    cout << *p << " ,  " << *p+1 << endl;
    
    delete p, b;
    
    
    return 0;
}
