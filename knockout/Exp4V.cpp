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
	//Knockout(argv);
	Exp(argv);
	Display();
	Output("Exp.txt");
    //Display4V();
    return 0;

}
//============================================
void InputCheck (int a, char *b[]){
	if(a < 11) {
	}else {
 		cout << endl << "Usage: " << endl
			 << "./Exp4V.o Z A TKEA k Theta_kx(deg) Phi_kx(deg) Theta_NN(deg) Phi_NN(deg) S" << endl << endl;
        exit(0);
	}
}
