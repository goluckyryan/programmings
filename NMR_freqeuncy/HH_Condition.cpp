/* this is preprocessor, tells the compiler to put code
   from the header called iostream into our program before
   actually creating the executable. By including header files, 
   you gain access to many different functions. 
   For example, the cout function requires iostream.
*/
#include <iostream> 
#include <cmath>


/* This line tells the compiler to use a group 
   of functions that are part of the standard 
   library (std). By including this line at the 
   top of a file, you allow the program to use functions such as cout.
*/
using namespace std; 

int main()
{
    double H, fs , dt;
    double gp=42.577481, ge=28024.9527; // gyromagnetic ratio in MHz T^-1
    double u0=12.566370614e-7; // premeability
    const double y=418;
    const double x=503;
    const double z=-921;
    double a, b;
    
    cout<< "=======================================\n";
    cout<< "Enter the external B-field (in Tesla ) = " ;
    cin>>H;
    cout<< "Enter the Microwave frequency (GHz) = ";
    cin>>fs;
    fs=fs*1000;
    a=pow(gp*H,2)-pow(fs-ge*H,2);
    cout<< " \n The difference w_I^2 - (w_mu - w_S )^2= " << a << " MHz^2 ";
    b=sqrt(a)/ge;
    cout<< " \n the micorwave B-field strenght is = " << b << " T ";
    cout<< " \n the micorwave Power is = " << u0*(pow(b,2))/2 << " W \n\n";
    
    cin.ignore(); // this stop the program terminate automatically, by igonring the "enter key"
    cout<<"\nProgram ended (press ENTER for exist)";
    cout<<"\n=====================================";
    cin.get(); // this require an "enter" to terminate the program
    return 0;
}
