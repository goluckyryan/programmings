/*  Knockout of O(p,pn)R
____________________________
the input are 4 (k, Theta_k, x-axis, y-axis)

and the program will generate the data by run throght all posible (S and Theta_NN)

***********************************/

//#include <iostream> // enable cin, cout
//#include <sstream> // enable string control
//#include <cmath> // math , enable simple math function
//#include <iomanip>
//#include <stdio.h>
//#include <math.h>
//#include <stdlib.h> // standard General Utlilities Library
//#include <fstream> // File I/O
#include "knockoutLibrary.cpp"

using namespace std; // declare a namespace "std", every variable in this code is inside "std"
int para1; // for parameter of {k, Theta_k, Theta_NN, S}
int para2; // for parameter of {T1L, Theta_P1L, T2L, Theta_P2L}
//______________________________________
void Input(int a);
void Loop(int a);
void Output(int a);
void Dataout(int a);


//main_____no display___________________
int main(int argc, char *argv[])
{


	if(argc < 2) {
 	cout << endl << "Usage: ./knockoutGen.o Ti {k, Theta_k, Theta_NN, S} {T1L, Theta_P1L, T2L, Theta_P2L}" << endl
		         << "      e.g. k and Theta_k = 2211                      2211"<<endl;
        exit(0);
	}

	// the input parameters are Ti, {k, Theta_k, Theta_NN, S}
    	Ti = atoi(argv[1]); 
	para1 = atoi(argv[2]);
	para2 = atoi(argv[3]);

	//cout << para1 << endl << para2 <<endl; 

	Input(para1);
	Loop(para1);
	Output(para2);

	//cout << " writted  data.dat" << endl;

    return 0;
    
}
//_____________________________________________________________________________

void Input(int a){
	switch(a){
		case 2211:
			cout << "     k         = ";
			cin >> k ;
			cout << " Theta_k(deg)  = ";
			cin >> Theta_k;
			break;
		case 2121:
			cout << "     k         = ";
			cin >> k ;
			cout << " Theta_NN(deg) = ";
			cin >> Theta_NN;
			break;
		case 2112:
			cout << "     k         = ";
			cin >> k ;
			cout << "     S         = ";
			cin >> S;
			break;
		case 1221:
			cout << " Theta_k(deg)  = ";
			cin >> Theta_k;
			cout << " Theta_NN(deg) = ";
			cin >> Theta_NN;
			break;
		case 1212:
			cout << " Theta_k(deg)  = ";
			cin >> Theta_k;
			cout << "     S         = ";
			cin >> S;
			break;
		case 1122:
			cout << " Theta_NN(deg) = ";
			cin >> Theta_NN;
			cout << "     S         = ";
			cin >> S;
			break;
	}
}

void Loop(int a){

	ofstream file_out;
	file_out.open("data.dat");
	file_out << "";
	file_out.close();

	ofstream data_out;
    data_out.open("data.dat", ios::app);     // open the input file, c_str() convert string to char 
	
	switch(a){
		case 2211: // loop Theta_NN and S
			cout << " Theta_NN = {1,179,1}, S = {25,75,15}" << endl;
			for(int i=1; i<180;i++){
				for (int j=25; j<76;j+=15){
					Simulation(Ti, k, Theta_k*pi/180, 0, i*pi/180, 0, j);
					Dataout(para2);
				}
				data_out << endl;
			}
			break;
		case 2121: // loop Theta_k and S
			cout << " Theta_k = {1,179,1}, S = {25,75,15}" << endl;
			for(int i=1; i<180;i++){
				for (int j=25; j<76;j+=15){
					Simulation(Ti, k, i*pi/180, 0, Theta_NN*pi/180, 0, j);
					Dataout(para2);
				}
				data_out << endl;
			}
			break;
		case 2112: // loop Theta_k and Thet_NN
			cout << " Theta_k = {1,179,1}, Theta_NN = {1,179,1}" << endl;
			for(int i=1; i<180;i++){
				for (int j=1; j<180;j++){
					Simulation(Ti, k, i*pi/180, 0, j*pi/180, 0, S);
					Dataout(para2);
				}
				data_out << endl;
			}
			break;
		case 1221: // loop k and S
			cout << " k = {10,200,10}, S = {25,75,15}" << endl;
			for(int i=10; i<210;i+=10){
				for (int j=25; j<76;j+=15){
					Simulation(Ti, i, Theta_k*pi/180, 0, Theta_NN*pi/180, 0, j);
					Dataout(para2);
				}
				data_out << endl;
			}
			break;
		case 1212: // loop k and Theta_NN
			cout << " k = {10,200,10}, Theta_NN = {1,179,1}" << endl;
			for(int i=10; i<210;i+=10){
				for (int j=1; j<180;j++){
					Simulation(Ti, i, Theta_k*pi/180, 0, j*pi/180, 0, S);
					Dataout(para2);
				}
				data_out << endl;
			}
			break;
		case 1122: // loop k and Theta_k
			cout << " k = {10,200,10}, Theta_k = {1,179,1}" << endl;
			for(int i=10; i<200;i+=10){
				for (int j=1; j<180;j++){
					Simulation(Ti, i, j*pi/180, 0, Theta_NN*pi/180, 0, S);
					Dataout(para2);
				}
				data_out << endl;
			}
			break;
	}

    data_out.close();

}

void Output(int a){
	switch(a){
		case 2211:
			cout <<" 2211: T1L vs Theta_P1L " << endl;
			break;
		case 2121:
			cout <<" 2121: T1L vs Theta_P2L " << endl;		
			break;
		case 2112:
			cout <<" 2112: T1L vs T2L " << endl;
			break;
		case 1221:
			cout << " 1221: Theta_P1L vs Theta_P2L "  << endl;
			break;
		case 1212:
			cout << " 1212: Theta_P1L vs T2L"  << endl;
			break;
		case 1122:
			cout << " 1122: T2L vs Theta_P2L "  << endl;
			break;
	}

}

void Dataout(int a){

	ofstream data_out;
    data_out.open("data.dat", ios::app);     // open the input file, c_str() convert string to char 

	switch(a){
		case 2211:
			data_out << P1L[0]-m1 << "\t" << 180-Theta(P1L)*180/pi << "\t";
			break;
		case 2121:
			data_out << P1L[0]-m1 << "\t" << 180-Theta(P2L)*180/pi << "\t";	
			break;
		case 2112:
			data_out << P1L[0]-m1 << "\t" << P2L[0]-m2 << "\t";
			break;
		case 1221:
			data_out << 180-Theta(P1L)*180/pi << "\t" << 180-Theta(P2L)*180/pi << "\t";
			break;
		case 1212:
			data_out << 180-Theta(P1L)*180/pi << "\t" << P2L[0]-m2 << "\t";
			break;
		case 1122:
			data_out << P2L[0]-m2 << "\t" << 180-Theta(P2L)*180/pi << "\t";
			break;
	}
			//cout << 180-Theta(P1L)*180/pi << "\t" << 180-Theta(P2L)*180/pi << "\t" << endl;		


	data_out.close();
}


