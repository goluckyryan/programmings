#include <iostream>
#include <cmath>

using namespace std;

const double pi=3.14159;
int display(double array[20]);

int main()
{
    double dsin[20];
    double shifted[20];
    
    for (int i =0; i<20; i++) {
        dsin[i]=sin(2*pi*i/20);
    }
    
    display(dsin);
    
    for (int i=0; i<20; i++) {
        shifted[i]=dsin[ (i+10)%20 ];
    }
    
    display(shifted);
    
    return 0;
}

int display(double array[20])
{
    int start, end;
    cout<< " ==== Display ==== " << "\n" ;
    cout<< " start row\t: ";
    cin>> start;
    cout<< " end row\t: ";
    cin>> end;
    
    for (int i=start-1; i<end; i++) {
        cout<< i+1 <<"\t"<< array[i] <<"\n";
    }
    
    cout<< " ==== End Display ===="<<endl;
    
    return 0;
}