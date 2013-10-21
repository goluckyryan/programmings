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
    double gp=42.577481, ge=-28.0249527;
    double a, b;
    
    cout<< "=======================================\n";
    cout<< "Enter the external B-field (in Tesla ) = " ;
    cin>>H;
    cout<< "Enter the NMR pulse frequency (MHz) = ";
    cin>>fs;
    a=fs-gp*H ;
    cout<< " \n The NMR frequency of Proton = " << gp*H << " MHz" ;
    cout<< "\n the different is = " << a << " MHz ; a cycle = " <<1/a << " usec";
    cout<< " \n The ESR freqeuncy of electron = " << ge*H << " GHz \n\n";
    
    cout<< " The B-field for exact matching  = " << fs/gp << " T\n";
    cout<< " the corrsponding ESR freqeuncy in this field  = " << fs/gp*ge << " GHz \n\n";
    
    cout<< "The cycle in NMR signal (usec) = ";
    cin>>dt;
    b = (fs-1/dt)/gp;
    cout<< " the effective field @ " << fs << " MHz = " << b <<" T \n";
    cout<< " the ESR frequency in this field  = " << ge*b <<" GHz ";
    
    // Make a list on the cycle time and field
    
    cin.ignore(); // this stop the program terminate automatically, by igonring the "enter key"
    cout<<"\nProgram ended (press ENTER for exist)";
    cout<<"\n=====================================";
    cin.get(); // this require an "enter" to terminate the program
    return 0;
}
