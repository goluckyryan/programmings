// Dynamic Nuclear Polarization Pulses seqeunce Calculator
// abbrr. : Pulse Calculator

// chooper freqeuncy, duty , pulse width
// micorwave freqeuncy, pulse width

// input chopper freqeuncy and pulse width -> duty
// microwvae freeqeuncy -> pulse width

#include <iostream> 
#include <sstream>
#include <cmath>
#include <stdlib.h>

using namespace std; 

int main()
{
    double fc,t1,fm,duty;
    double a, b;
    int n,m;
    double pi=3.141592458;
    
    cout<< "           Laser Duty (1) \n";
    cout<< "    Laser Pulse width (2) \n";
    cout<< "Microwave Pulse width (3) \n";
    cout<< "           Everything (4) :  "; 
    cin>> n;
    cout<< "\n";
    
    if ( n==4){
         m = 1;
    }else if (n <5 && n > 0){
         m = n;
    }else{
          return 0;
    }
    
    do{
       if ( m==1){ 
          cout<<"\n====Laser Duty====\n";
          cout<< " chopper freqeuncy (kHz) = ";
          cin >> fc;
          cout<< "laser pulse width (usec) = " ;
          cin>>t1;
          a = t1*fc/10;
          cout<< "\n                            period = "<< 1000/fc << " usec";
          cout <<"\n                        Laser duty = "<< a << " %\n";
          if (n == 4){
                m = 2;
          } else {
                 m = 4;
                 }
       }else if (m == 2){
             cout<<"\n====Laser Pulse Width====\n";
             cout<<"         Laser Duty (%) = ";
             cin>>duty;
             cout<<"Chopper frequency (kHz) = ";
             cin>>fc;
             cout<< "\n                           period = "<< 1000/fc << " usec";
             cout <<"\n                      Pulse Width = "<< 10*duty/fc << " usec\n";
             if (n == 4){
                m = 3;
             }else {
                 m = 4;
                 }
       }else if (m == 3){
          cout<<"\n====Microwave Pulse Duty====\n";      
          cout<< "microwave freqeuncy (kHz) = " ;
          cin>>fm;
          cout<< "\n            microwave pulse width = " << 500/fm << " usec \n";
          m = 4;
       }else if( m ==4 ){
             cout<< "\n Again? \n(1=Laser duty, 2=Pulse width, 3=Microwave Pulse width, 4==Everything, 0=No) ";
             cin >> n;
             cout<<"\n";
             if ( n ==0 ){
                  m = 0;
             }else if( n ==4 ){
                   m =1;
                   system("cls");
             }else{
                   m = n;
             } 
       }
       } while ( m != 0 );

    cin.ignore(); // this stop the program terminate automatically, by igonring the "enter key"
    cout<< "\n++++++++++++\nProgram Ended. ( Press ENTER for exit )";
    cin.get(); // this require an "enter" to terminate the program
    return 0;
}
