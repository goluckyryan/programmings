/*  Knockout of O(p,pn)R

the source code in "knockoutLibrary.h"

***********************************/

#include "knockoutLibrary.h" // call the knockout functions
//Prototype_____________________________
void InputCheck(int a, char *b[]);

//main__________________________________
int main(int argc, char *argv[])
{
	InputCheck (argc, argv);

	Simulation(ma_num, e_num, TiL, k, Theta_k, Phi_k, Theta_NN, Phi_NN, S);
	//Simulation(250, 0, 0, 0, 0, 0, 20);
	//OutputDetail("outputDetail.txt");
	//OutputSimple("outputSimple.txt");
	Display();
	//DisplayShort();
	//Data("data.dat");
    return 0;

}
//============================================
void InputCheck (int a, char *b[]){
	if(a == 7) {
		//cout << "   Option 3 " <<endl;
		ma_num=atoi(b[1]);
		e_num = atoi(b[2]);
		TiL = 260;
		k = atof(b[3]);
		Theta_k = atof(b[4])*pi/180;
		Phi_k = 0;
		Theta_NN = atof(b[5])*pi/180;
		Phi_NN = 0;
		S=atof(b[6]);
    }else if( a ==8){
		//cout << "   Option 2 " <<endl;
		ma_num=atoi(b[1]);
		e_num = atoi(b[2]);
		TiL = atof(b[3]);
		k = atof(b[4]);
		Theta_k = atof(b[5])*pi/180;
		Phi_k = 0;
		Theta_NN = atof(b[6])*pi/180;
		Phi_NN = 0;
		S=atof(b[7]);
	}else if( a ==10){
		//cout << "   Option 1 " <<endl;
		ma_num=atoi(b[1]);
		e_num = atoi(b[2]);
		TiL = atof(b[3]);
		k = atof(b[4]);
		Theta_k = atof(b[5])*pi/180;
		Phi_k = atof(b[6])*pi/180;
		Theta_NN = atof(b[7])*pi/180;
		Phi_NN = atof(b[8])*pi/180;
		S=atof(b[9]);
	}else {
 		cout << endl << "Usage: " << endl
			 << "1)./knockout.o A Z TiL  k Theta_kx(deg) Phi_kx(deg) Theta_NN(deg) Phi_NN(deg) S" << endl
			 << "2)./knockout.o A Z TiL  k Theta_kx(deg)     0       Theta_NN(deg)     0       S" << endl
			 << "3)./knockout.o A Z 260  k Theta_kx(deg)     0       Theta_NN(deg)     0       S" << endl <<endl;
        exit(0);
	}
}
