#include <iostream>
#include <cmath>
#include "../CppLibrary/constant.h"
#include "../CppLibrary/nuclei_mass.h"

using namespace std;

int main(){

	int choice;
	double Brho, mass, A, Z;
	
	cout << " choose floowing calculation: \n";
	cout << "--------------------------------------------------\n";
	cout << " 1)  KE per A  -> Brho \n";
	cout << " 2)  Brho      -> KE per A \n";
	c
	
	cout << " (Brho, A, Z) = ";
	cin >> Brho >> A >> Z;
	
	mass = Nucleus_Mass(A,Z);
	if ( mass > 0 ) {
		cout << Brho2T(mass, Z, A, Brho) << "MeV/A" << endl;
	}else{
		cout << "no such nuleus.\n"; 
	}
    return 0;
}
