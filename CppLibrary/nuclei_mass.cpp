#include "nuclei_mass.h"
using namespace std;

int main (int argc, char *argv[])
{

   int    Z, A;
   double mass; 
   string name = "--";
  
   if (argc == 3){
      Z= atoi(argv[1]);
      A= atoi(argv[2]);
   }else{
      cout << "./nuclei_mass.o Z A" << endl;
      exit(0);
   }
	
   mass = Nucleus_Mass(Z,A);
   name = Nucleus_Name(Z,A);

   if (mass > 0){
      printf(" mass of %3d%s (Z,A)=(%3d,%3d) is \e[32m%12.5f\e[m MeV \n",A,name.c_str(), Z,A, mass);
   }else{
      printf("Error %6.0f, no nucleus with (Z,A) = (%3d,%3d). \n", mass, Z, A);
   }
  	
   return 0;
}

