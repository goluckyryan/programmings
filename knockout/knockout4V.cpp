/*  Knockout of O(p,pn)R

the source code in "knockoutLibrary.h"

***********************************/

#include "knockoutLibrary4V.h" // call the knockout functions
//Prototype_____________________________
void InputCheck(int a, char *b[]);

//main__________________________________
int main(int argc, char *argv[])
{
	InputCheck (argc, argv);
	Knockout(argv);
	Display();
    //Display4V();
    return 0;

}
//============================================
void InputCheck (int a, char *b[]){
	if(a < 11) {
	}else {
 		cout << endl << "Usage: " << endl
			 << "1)./knockout.o A Z TiL  k Theta_kx(deg) Phi_kx(deg) Theta_NN(deg) Phi_NN(deg) S" << endl
			 << "2)./knockout.o A Z TiL  k Theta_kx(deg)     0       Theta_NN(deg)     0       S" << endl
			 << "3)./knockout.o A Z 260  k Theta_kx(deg)     0       Theta_NN(deg)     0       S" << endl <<endl;
        exit(0);
	}
}
