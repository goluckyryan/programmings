#include "mathlib.h"
#include <stdio.h>
using namespace std;

int main (int argc, char *argv[])
{
    int *a = new int [3];
    int *b;

    a[0]=3;
    a[1]=2;
    a[2]=1;

    cout << *a << "   "<< sizeof(*a) << endl;;

    b = InversionVector(3,a);

    printf("%2d %2d %2d \n", a[0], a[1], a[2]);
    printf("%2d %2d \n", b[0], b[1]);

    cout << "parity = " << Parity(3,a) << endl;


   return 0;
}

