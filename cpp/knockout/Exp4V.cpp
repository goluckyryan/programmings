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

        int Z_num    = atoi(argv[1]);
        int A_num    = atoi(argv[2]);
        double TKEA     = atof(argv[3]);
        double k        = atof(argv[4]);
        double Theta_k  = atof(argv[5]);
        double Phi_k    = atof(argv[6]);
        double Theta_NN = atof(argv[7]);
        double Phi_NN   = atof(argv[8]);
        double S        = atof(argv[9]);

        int ZT_num   = atoi(argv[10]);
        int AT_num   = atoi(argv[11]);    
        int Z1_num   = atoi(argv[12]);
        int A1_num   = atoi(argv[13]);
        int Z2_num   = atoi(argv[14]);
        int A2_num   = atoi(argv[15]);
        //Knockout(argv);
        Exp(Z_num, A_num, TKEA, k, Theta_k, Phi_k, Theta_NN, Phi_NN, S, ZT_num, AT_num, Z1_num, A1_num, Z2_num, A2_num);
        Display(TKEA, k, Theta_k, Phi_k, Theta_NN, Phi_NN, S);
        Output("Exp.txt",TKEA, k, Theta_k, Phi_k, Theta_NN, Phi_NN, S);
        //Display4V();
        return 0;

}
//============================================
void InputCheck (int a, char *b[]){
	if(a != 16 ) {
 		cout << endl << "Usage: " << endl
			 << "./Exp4V.o Z A TKEA k Theta_kx(deg) Phi_kx(deg) Theta_NN(deg) Phi_NN(deg) S" << endl << endl;
        exit(0);
	}
}
