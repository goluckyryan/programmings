#include "nuclei_mass.h"
using namespace std;

int main (int argc, char *argv[])
{

   int    A, Z;
   double mass; 
  
   if (argc == 3){
      Z= atoi(argv[1]);
      A= atoi(argv[2]);
   }else{
      cout << "./nuclei_mass.o Z A";
      exit(0);
   }
	
   mass = Nucleus_Mass(A,Z);

   if (mass > 0){
      printf(" mass of (Z,A)=(%3d,%3d) is %12.5f MeV \n",Z,A, mass);
   }else{
  	   cout << "Error " <<  mass << ", no such nucleus in database. \n" ;
   }
  	
   return 0;
}

