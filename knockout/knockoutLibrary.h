/*  Knockout of O(p,pn)R

The Lorentz Tranform on aribtary direction is well discrpted in Goldstien P .281


k(vector): momentum of a proton in Oxygen nucleus
Theta_k:   direction of the momentum of a proton in O nucleus
Theta_NN:  scattering angle in 2-nucleon center of mass system
S:         separation energys

***** suffix notation ****
suffix "L" is Lab frame
suffix "" is Oxygen frame
suffix "c" is CM frame
suffix "X" is experiment

***** notation ****
k is for momentum
P is for 4-momentum
E is Total relativistic energy
T is for Kinetic energy

we can transform the mulit-bpdy to 2-body scattering

in Oxygen frame
O(i,12)R
==>>
n(i,12)

Pi={Ei,0,0,pi}
Pn={Mo-ER,-k*sin(Theta_k)*cos(Phi_k),-k*sin(Theta_k)*sin(Phi_k),-k*cos(Theta_k))}

ER=dqrt((Mo-m2+S)^2+Pn^2)

by Lorentz transform of center of momentum 4-vector

Pc=Pi+Pn

then set the Theta_NN and Phi_NN in CM frame by rotation operator.

transform back

done

*****************

given Pi, P1, P2, find k, S, Theta_NN, Phi

Pi={Ei,0,0,ki}
P1 = {E1, k1*sin(Theta_P1), 0, k1*cos(Theta_P1)}
P2 = {E2, k2*sin(Theta_P2)*cos(Phi_P2), k2*sin(Theta_P2)*sin(Phi_P2), k2*cos(Theta_P2)}

S = sqrt((Ei+Mo-E1-E2)^2-(ki-k1-k2)^2)-Mo+mn

k = ki-k1-k2

***********************************/

#include <iostream> // enable cin, cout
#include <sstream> // enable string control
#include <cmath> // math , enable simple math function
#include <iomanip>
#include <stdio.h>
#include <stdlib.h> // standard General Utlilities Library
#include <fstream> // File I/O
#include <time.h>
#include "../CppLibrary/constant.h"
#include "../CppLibrary/nuclei_mass.h"

using namespace std; // declare a namespace "std", every variable in this code is inside "std"

//variable___________________________________________________________________
int ma_num;
int e_num;
double TiL; //Kinetic energy of i in Labframe
double k; //momentum of orbial neutron
double Theta_k, Phi_k;

string dum;
double m1=Nucleus_Mass(1,1,dum), m2=Nucleus_Mass(1,1,dum);
double mi=m1;
string reaction="(p,2p)", proj="O", residual="O";

double T1L;
double theta_1L;
double phi_1L;
double T2L;
double theta_2L;
double phi_2L ;

double Pn[4]; // 4-momentum of neutron in Oxygen frame
double Pi[4]; // 4-momentum of incident proton. set as Z-axis
double Pc[4]; // 4-momentum of the center of momentum
double P1[4]; // 4-momentum vector of scattered Pi
double P2[4]; // 4-momentum vector of scattered Pn

double PnL[4]; // 4-momentum of neutron in  Lab frame
double PiL[4]; // 4-momentum of incident proton. set as Z-axis
double P1L[4]; // 4-momentum vector of scattered Pi
double P2L[4]; // 4-momentum vector of scattered Pn

double Pnc[4]; // 4-momentum of neutron in Oxygen in Lab frame
double Pcc[4]; // 4-momentum of the center of momentum
double Pic[4]; // 4-momentum of incident proton. set as Z-axis
double P1c[4]; // 4-momentum vector of scattered Pi
double P2c[4]; // 4-momentum vector of scattered Pn

double Theta_NN; //scattering angle in 2-nucleon center of mass system
double Phi_NN;
double beta; // this is inverse Kinematics beta
double beta_Pc; //the lorantz factor
double S; // separation energy
double L[4][4]; // Lorantz operator
double R[4][4]; // rotation operator
const double mina=1e-12;


//prototype____________________________________________________________________
double Chop(double a); //Chop number smaller then 1e-12 in absolute value
void Data(string filename);
void Display();
void DisplayShort();
void DisTkangle(double A[], double m, string name);
void DisVector(double A[], string name);
double DSCfactor(double A[],double C[],double b);  // dsc from oxygen frame A to frame C
double Findk(double A[]);
double FindT(double A[], double m);
void knockout(int ma_num, int e_num, double a, double b, double c, double d, double e, double f, double g);
double Lorentz(double beta,double Theta, double Phi); //L[4][4] generator
void EXP(int ma_num, int e_num, double a, double b, double c, double d, double e, double f, double g);//output Sn
void OutputDetail(string filename);
void OutputSimple(string filename);
double Phi(double A[]); // find the angle Phi
double Rot(double Phi_NN, double Theta, double Phi); //R[4][4] generator
double SIN(double a); //a sin(pi) will give 0
void Simulation(int ma_num, int e_num, double a, double b, double c, double d, double e, double f, double g);
double T2k(double T, double m);//find momentum
double Theta(double A[]); // find the angle Theta






//function___________________________________________________________________
double Chop(double a){
	if (abs(a) < mina){
	     a=0;
	}
	return a;
}

void Display(){

	//cout << endl ;
	cout << "=======================================================" << endl;
	cout << "Reaction :    \e[32m      "<<ma_num << proj << reaction << ma_num-1 << residual <<" \e[m " <<endl;
	cout << "input parameter:" << endl;
	cout << "TiL = " << TiL <<", S = "<< S << ", k = " << k  <<endl
			 << " Theta_k(deg)  = "<< Theta_k*180/pi <<  ",\tPhi_k(deg)  = " << Phi_k*180/pi << endl
			 << " Theta_NN(deg) = "<< Theta_NN*180/pi << ",\tPhi_NN(deg) = "<< Phi_NN*180/pi <<endl;
	cout << " the DSC factor is " << DSCfactor(P1,P1L,beta) << endl;

	cout << "--------------------Lab Frame--------------------------"<<endl;
	DisVector(PiL,"PiL");
	DisVector(PnL,"PnL");
	DisVector(P1L,"P1L");
	DisTkangle(P1L,m1,"  ");
	DisVector(P2L,"P2L");
        DisTkangle(P2L,m2,"  ");
        cout << "\e[32m T1L(p) = " << FindT(P1L,m1) << ", theta_1L = " << 180-Theta(P1L)*180/pi << endl;
        cout << " T2L(n) = " << FindT(P2L,m2) << ", theta_2L = " << -180+Theta(P2L)*180/pi << "\e[m "<< endl;

	cout << "--------------------Nucleus Frame-----------------------"<<endl;

	DisVector(Pi,"Pi ");
	DisVector(Pn,"Pn ");
	DisVector(P1,"P1 ");
	DisTkangle(P1,m1, " ");
	DisVector(P2,"P2 ");
	DisTkangle(P2,m2, " ");
	cout << "\e[32m T1(p) = " << FindT(P1,m1) << ", theta_1 = " << Theta(P1)*180/pi << endl;
        cout << " T2(n) = " << FindT(P2,m2) << ", theta_2 = " << -Theta(P2)*180/pi   << "\e[m "<< endl;
	cout << endl << "         center of momentum 4 vector   " << endl;

	DisVector(Pc,"Pc ");
	cout << "beta = " << Findk(Pc)/Pc[0] << endl;
	DisVector(Pcc,"Pcc");

	cout << "--------------------CM Frame---------------------------"<<endl;

	DisVector(Pic,"Pic");
	DisVector(Pnc,"Pnc");
	DisVector(P1c,"P1c");
	DisVector(P2c,"P2c");


	//cout << "   K.E. = "<< P2[0]-m2 << "| angle of P2 = (" << Theta_P2*180/pi << "," << Phi_P2*180/pi << ")" <<endl;

	cout<< "======================================================="<<endl;
}

void DisplayShort(){
	//printf("%7.3f \n",m2);
	cout << FindT(P2,m2)   << endl <<  Theta(P2)*180/pi << endl <<-Theta(P1)*180/pi << endl;

}


void DisTkangle(double A[], double m, string name){
	cout.setf(ios::fixed);
	cout<< name << setprecision(3) << "(T, k, Theta, Phi) = ("
	    << FindT(A,m) << ", \t"
	    << Findk(A) << ", \t"
	    << Theta(A)*180/pi << ", \t"
	    << Phi(A)*180/pi << ")" << endl;

}

void DisVector(double A[], string name){

	cout.setf(ios::fixed);
	cout<< name << setprecision(3) << "  = ("
        << A[0] << ", \t"
        << A[1] << ", \t"
        << A[2] << ", \t"
        << A[3] << ")" << endl;

}

double DSCfactor(double A[],double C[],double b){
    // dsc from oxygen frame A to frame C

    double a=Findk(A)*Findk(A);
    double c=Findk(C)*Findk(C);
    double gamma=1/(1-b*b);
    double cosin=cos(pi-Theta(A))*cos(Theta(C))+gamma*sin(pi-Theta(A))*sin(Theta(C));

    return c/(a*cosin);

}

void EXP(int ma_num, int e_num, double a, double b, double c, double d, double e, double f, double g){

    double mO=Nucleus_Mass(e_num,ma_num);
    proj = Nucleus_Name(e_num,ma_num);
    residual = Nucleus_Name(e_num-1,ma_num-1);
	TiL=a;
	T1L=b;
	theta_1L = c;
	phi_1L = d;
	T2L = e;
	theta_2L = f;
	phi_2L = g;

	for(int i=0; i<4; i++){
		Pn[i]=0;
		Pc[i]=0;
		Pi[i]=0;
		P1[i]=0;
		P2[i]=0;

		PnL[i]=0;
		PiL[i]=0;
		P1L[i]=0;
		P2L[i]=0;

		Pnc[i]=0;
		Pcc[i]=0;
		Pic[i]=0;
		P1c[i]=0;
		P2c[i]=0;
	}

// 4-vector, PiL, P1L, P2L

	PiL[0]=mi;
	PiL[1]=0;
	PiL[2]=0;
	PiL[3]=0;

	P1L[0]=m1+T1L;
	P1L[1]=T2k(T1L,m1)*SIN(theta_1L)*cos(phi_1L);
	P1L[2]=T2k(T1L,m1)*SIN(theta_1L)*SIN(phi_1L);
	P1L[3]=T2k(T1L,m1)*cos(theta_1L);

	P2L[0]=m2+T2L;
	P2L[1]=T2k(T2L,m2)*SIN(theta_2L)*cos(phi_2L);
	P2L[2]=T2k(T2L,m2)*SIN(theta_2L)*SIN(phi_2L);
	P2L[3]=T2k(T2L,m2)*cos(theta_2L);


// 4-vector , PnL
	for(int i=0; i<4; i++){
		PnL[i]=P1L[i]+P2L[i]-PiL[i];
	}


	//find the Lorentz beta = beta_Pc {Theta_Pc, Phi_Pc}
	beta = T2k(TiL,mi)/(mi+TiL);


    //Claim the Lorentz Transform
	Lorentz(beta, 0, 0);

   // Lorentz Transfrom
	for(int i=0; i<4;i++){
		for (int j=0; j<4;j++){
			Pn[i]=Pn[i]+PnL[j]*L[j][i];
			Pi[i]=Pi[i]+PiL[j]*L[j][i];
			P1[i]=P1[i]+P1L[j]*L[j][i];
			P2[i]=P2[i]+P2L[j]*L[j][i];
		}
	}

	//cout << PiL[0] <<"," << PiL[1]<<"," << PiL[2]<<"," << PiL[3] << endl;

	k=Findk(Pn);
	Theta_k=Theta(Pn);
	Phi_k=Phi(Pn);

	double temp1, temp2;
	temp1 =Pi[0] + mO - P1[0] - P2[0];
 	S=sqrt((temp1-k)*(temp1+k))-(mO-m2);

	//S=sqrt(pow(Pi[0] + mO - P1[0] - P2[0] ,2)-pow(Findk(Pn),2))-(mO-m2);

	Pc[0]=0;
	Pc[1]=0;
	Pc[2]=0;
	Pc[3]=0;

	for (int i =0; i<4;i++){
		Pc[i]=(P1[i]+P2[i])/2;
	}

	double beta_pc=Findk(Pc)/Pc[0];
	double theta_pc=Theta(Pc);
	double phi_pc=Phi(Pc);

   // claim Lorentz transfer again
	Lorentz(-beta_pc, theta_pc, phi_pc);

   // Lorentz Transfrom
	for(int i=0; i<4;i++){
		for (int j=0; j<4;j++){
			Pnc[i]=Chop(Pnc[i]+Pn[j]*L[j][i]);
			Pic[i]=Chop(Pic[i]+Pi[j]*L[j][i]);
			P1c[i]=Chop(P1c[i]+P1[j]*L[j][i]);
			P2c[i]=Chop(P2c[i]+P2[j]*L[j][i]);
		}
	}


}

double Findk(double A[]){
	double a;
        a=sqrt(pow(A[1],2)+pow(A[2],2)+pow(A[3],2));
	return a;
}

double FindT(double A[], double m){
	double a;
	a=A[0]-m;
	return a;
}

void knockout(int ma_num, int e_num, double a, double b, double c, double d, double e, double f, double g){

	Simulation(ma_num, e_num, a, b, c, d, e, f, g);
	Display();

}

double Lorentz(double beta,double Theta, double Phi){

	double g = 1/sqrt(1- pow(beta,2));
	double c1 = cos(Theta);
	double s1 = SIN(Theta);
	double c2 = cos(Phi);
	double s2 = SIN(Phi);

	L[0][0]=g;
	L[0][1]=beta*g*c2*s1;
	L[0][2]=beta*g*s1*s2;
	L[0][3]=beta*g*c1;
	L[1][0]=g*beta*c2*s1;
	L[1][1]=pow(c2,2)*(pow(c1,2)+pow(s1,2)*g)+pow(s2,2);
	L[1][2]=c2*s2*(-1+pow(c1,2)+pow(s1,2)*g);
	L[1][3]=(g-1)*c1*c2*s1;
	L[2][0]=beta*g*s1*s2;
	L[2][1]=c2*s2*(-1+pow(c1,2)+pow(s1,2)*g);
	L[2][2]=pow(c2,2)+(pow(c1,2)+pow(s1,2)*g)*pow(s2,2);
	L[2][3]=(g-1)*c1*s2*s1;
	L[3][0]=beta*g*c1;
	L[3][1]=(g-1)*c1*c2*s1;
	L[3][2]=(g-1)*c1*s2*s1;
	L[3][3]=g*pow(c1,2)+pow(s1,2);
    return 0;
}


double Rot(double a, double Theta, double Phi){

	double c1 = cos(Theta);
	double s1 = SIN(Theta);
	double c2 = cos(Phi);
	double s2 = SIN(Phi);
	double ca = cos(a);
	double sa = SIN(a);

	R[0][0]=1;R[0][1]=0;R[0][2]=0;R[0][3]=0;
	R[1][0]=0;
	R[1][1]=pow(c2,2)*(ca*pow(c1,2)+pow(s1,2))+ ca*pow(s2,2);
	R[1][2]=c1*sa+pow(SIN(a/2),2)*pow(s1,2)*SIN(2*Phi);
	R[1][3]=-s1*((ca-1)*c1*c2+sa*s2);
	R[2][0]=0;
	R[2][1]=-c1*sa+pow(SIN(a/2),2)*pow(s1,2)*SIN(2*Phi);
	R[2][2]= ca*pow(c2,2)+pow(s2,2)*(ca*pow(c1,2)+pow(s1,2));
	R[2][3]=s1*(c2*sa+(1-ca)*c1*s2);
	R[3][0]=0;
	R[3][1]=c2*pow(SIN(a/2),2)*SIN(2*Theta)+sa*s1*s2;
	R[3][2]=-s1*(c2*sa+(ca-1)*c1*s2);
	R[3][3]=pow(c1,2)+ca*pow(s1,2);


	return 0;
}

double SIN(double a){

    if (fmod(a,pi) ==0){
        return 0;
    }else{
        return sin(a);
    }

}

void Simulation(int ma_num, int e_num, double a, double b, double c, double d, double e, double f, double g){

    double mO=Nucleus_Mass(e_num,ma_num);
    proj = Nucleus_Name(e_num,ma_num);
    residual = Nucleus_Name(e_num-1,ma_num-1);
    //cout << "mass[MeV]=" << mO << endl;
	TiL=a;
	k=b;
	Theta_k = c;
	Phi_k = d;
	Theta_NN = e;
	Phi_NN = f;
	S=g;

	for(int i=0; i<4; i++){
		Pn[i]=0;
		Pc[i]=0;
		Pi[i]=0;
		P1[i]=0;
		P2[i]=0;

		PnL[i]=0;
		PiL[i]=0;
		P1L[i]=0;
		P2L[i]=0;

		Pnc[i]=0;
		Pcc[i]=0;
		Pic[i]=0;
		P1c[i]=0;
		P2c[i]=0;
	}

// 4-vector, Pi, Pn

	Pi[0]=mi+TiL;
	Pi[1]=0;
	Pi[2]=0;
	Pi[3]=T2k(TiL, mi);

	Pn[0]= mO-sqrt(pow(mO-m2+S,2)+pow(k,2));
	Pn[1]=Chop(k*SIN(Theta_k)*cos(Phi_k));
	Pn[2]=Chop(k*SIN(Theta_k)*SIN(Phi_k));
	Pn[3]=Chop(k*cos(Theta_k));

// center of momentum Pic+Pnc= 0
	for(int i=0;i<=3;i++){
		Pc[i]=(Pi[i]+ Pn[i])/2;
	}

	//find the Lorentz beta = beta_Pc {Theta_Pc, Phi_Pc}
	beta_Pc = Findk(Pc)/Pc[0];
	double Theta_Pc=Theta(Pc);
	double Phi_Pc=Phi(Pc);


    //Claim the Lorentz Transform
	Lorentz(-beta_Pc, Theta_Pc, Phi_Pc);

   // Lorentz Transfrom
	for(int i=0; i<4;i++){
		for (int j=0; j<4;j++){
			Pnc[i]=Chop(Pnc[i]+Pn[j]*L[j][i]);
			Pic[i]=Chop(Pic[i]+Pi[j]*L[j][i]);
			Pcc[i]=Chop(Pcc[i]+Pc[j]*L[j][i]);
		}
	}

//find out the angle of Pic in CM frame
	double Theta_Pic=Theta(Pic);
	double Phi_Pic=Phi(Pic);

// the unrotated P1c, P2c
	double Etotal = sqrt(1-pow(beta_Pc,2))*(Pi[0]+Pn[0]);

	double P1cG[4]={0,0,0,0}; //P1c b4 rotation, a generator of P1c
	double P2cG[4]={0,0,0,0}; //P2c b4 rotation, a generator of P2c
	double k1c = sqrt((Etotal-m1-m2)*(Etotal+m1-m2)*(Etotal-m1+m2)*(Etotal+m1+m2))/(2*Etotal);

	P1cG[0]= sqrt(pow(m1,2)+pow(k1c,2));
	P1cG[1]= Chop(k1c*SIN(Theta_Pic+Theta_NN)*cos(Phi_Pic));
	P1cG[2]= Chop(k1c*SIN(Theta_Pic+Theta_NN)*SIN(Phi_Pic));
	P1cG[3]= Chop(k1c*cos(Theta_Pic+Theta_NN));

	P2cG[0]= sqrt(pow(m2,2)+pow(k1c,2));
	P2cG[1]= Chop(k1c*SIN(pi+Theta_Pic+Theta_NN)*cos(Phi_Pic));
	P2cG[2]= Chop(k1c*SIN(pi+Theta_Pic+Theta_NN)*SIN(Phi_Pic));
	P2cG[3]= Chop(k1c*cos(pi+Theta_Pic+Theta_NN));

//Claim the rotation operator
	Rot(Phi_NN , Theta_Pic, Phi_Pic);

//rotate the P1c , P2c by given Theta_NN, and Phi_NN
	for(int i=0; i<4;i++){
		for (int j=0; j<4;j++){
			P1c[i]=Chop(P1c[i]+P1cG[j]*R[j][i]);
			P2c[i]=Chop(P2c[i]+P2cG[j]*R[j][i]);
		}
	}

//back to oxygen frame

	//Claim the Inverse Lorentz Transform
 	Lorentz(beta_Pc, Theta_Pc, Phi_Pc);
    //Lorentz Transform of P1c and P2c
	for(int i=0; i<4;i++){
		for (int j=0; j<4;j++){
			P1[i]=Chop(P1[i]+P1c[j]*L[j][i]);
			P2[i]=Chop(P2[i]+P2c[j]*L[j][i]);
		}
	}
// Declare Lorentz Transform to lab frame
	double beta_Pi = Findk(Pi)/Pi[0];
	Lorentz(-beta_Pi, 0, 0);
	for(int i=0; i<4;i++){
		for (int j=0; j<4;j++){
			PnL[i]=Chop(PnL[i]+Pn[j]*L[j][i]);
			PiL[i]=Chop(PiL[i]+Pi[j]*L[j][i]);
			P1L[i]=Chop(P1L[i]+P1[j]*L[j][i]);
			P2L[i]=Chop(P2L[i]+P2[j]*L[j][i]);
		}
	}


}

double Theta(double A[]){
	double a;
	if (A[1]==0 && A[2]==0){
	     a=0;
	}else {
	     a=atan2(sqrt(pow(A[1],2)+pow(A[2],2)),A[3]);
	}
	return a;
}

double Phi(double A[]){
	double a;
	if (A[1]==0 && A[2]==0){
	     a=0;
	}else {
	     a=atan2(A[2],A[1]);
	}
	return a;
}



double T2k(double T, double m){
	double a;
    a=sqrt(T*(T+2*m));
	return a;
}



void OutputDetail(string filename){
	//cout << "outputdetail" << endl;
    ofstream file_out;
    file_out.open(filename.c_str(), ios::app);     // open the input file, c_str() convert string to char
	// ios::app -- all output will be at the end of file

	time_t tim;  //create variable of time_t
	time(&tim); //pass variable tim to time function

    file_out << "=======================================================" << endl;
    file_out << "==============  " << ctime(&tim);
    file_out << "Reaction :         "<<ma_num << reaction << ma_num-1 << residual <<endl;
	file_out << "input parameter:" << endl;
	file_out << "TiL = " << TiL <<", S = "<< S << ", k = " << k  <<endl
			 << " Theta_k(deg)  = "<< Theta_k*180/pi <<  ",\tPhi_k(deg)  = " << Phi_k*180/pi << endl
			 << " Theta_NN(deg) = "<< Theta_NN*180/pi << ",\tPhi_NN(deg) = "<< Phi_NN*180/pi <<endl;

	file_out << "--------------------Lab Frame--------------------------"<<endl;
	file_out << "PiL = ( " << PiL[0] << ", \t" << PiL[1] << ", \t" << PiL[2] << ", \t" << PiL[3] << " )" << endl;
	file_out << "PnL = ( " << PnL[0] << ", \t" << PnL[1] << ", \t" << PnL[2] << ", \t" << PnL[3] << " )" << endl;
	file_out << "P1L = ( " << P1L[0] << ", \t" << P1L[1] << ", \t" << P1L[2] << ", \t" << P1L[3] << " )" << endl;
	file_out << "P2L = ( " << P2L[0] << ", \t" << P2L[1] << ", \t" << P2L[2] << ", \t" << P2L[3] << " )" << endl<<endl;
        file_out << " T1L(p) = " << FindT(P1L,m1) << ", theta_1L = " << -180+Theta(P1L)*180/pi << endl;
        file_out << " T2L(n) = " << FindT(P2L,m2) << ", theta_2L = " << 180-Theta(P2L)*180/pi  << endl;

	file_out << "--------------------Nucleus Frame-----------------------"<<endl;
	file_out << "Pi  = ( " << Pi[0] << ", \t" << Pi[1] << ", \t" << Pi[2] << ", \t" << Pi[3] << " )" << endl;
	file_out << "Pn  = ( " << Pn[0] << ", \t" << Pn[1] << ", \t" << Pn[2] << ", \t" << Pn[3] << " )" << endl;
	file_out << "P1  = ( " << P1[0] << ", \t" << P1[1] << ", \t" << P1[2] << ", \t" << P1[3] << " )" << endl;
	file_out << "P2  = ( " << P2[0] << ", \t" << P2[1] << ", \t" << P2[2] << ", \t" << P2[3] << " )" << endl <<endl;
        file_out << " T1(p) = " << FindT(P1,m1) << ", theta_1 = " << -180+Theta(P1)*180/pi << endl;
        file_out << " T2(n) = " << FindT(P2,m2) << ", theta_2 = " << 180-Theta(P2)*180/pi  << endl;

	file_out << "--------------------CM Frame---------------------------"<<endl;
	file_out << "Pic = ( " << Pic[0] << ", \t" << Pic[1] << ", \t" << Pic[2] << ", \t" << Pic[3] << " )" << endl;
	file_out << "Pnc = ( " << Pnc[0] << ", \t" << Pnc[1] << ", \t" << Pnc[2] << ", \t" << Pnc[3] << " )" << endl;
	file_out << "P1c = ( " << P1c[0] << ", \t" << P1c[1] << ", \t" << P1c[2] << ", \t" << P1c[3] << " )" << endl;
	file_out << "P2c = ( " << P2c[0] << ", \t" << P2c[1] << ", \t" << P2c[2] << ", \t" << P2c[3] << " )" << endl;

    file_out << "=======================================================" << endl;
    file_out.close();

}

void OutputSimple(string filename){

  /*  ifstream file_out1(filename.c_str());
    if (is_empty(file_out1)){
        cout << "creating " << filename << endl;
        file_out1 << <<"Reaction\tTiL\tS\tk\tTheta_k\tPhi_k\tTheta_NN\tPhi_NN\tT1L(p)\ttheta_1L\tT2L(n)\ttheta2L\tT1(p)\ttheta_1\tT2(n)\ttheta2\tDSC_factor" << endl;
    }
    file_out1.close(); */

    ofstream file_out2;
    file_out2.open(filename.c_str(), ios::app);

    file_out2 << ma_num << "O(p,pn)" << ma_num-1 << "O " << "\t" << TiL << "\t" << S << "\t" << k <<"\t" << Theta_k*180/pi << "\t" << Phi_k*180/pi << "\t" << Theta_NN*180/pi << "\t" << Phi_NN*180/pi << "\t" << FindT(P1L,m1) << "\t" << -180+Theta(P1L)*180/pi << "\t" << FindT(P2L,m2) << "\t" << 180-Theta(P2L)*180/pi << "\t" <<  FindT(P1L,m1) << "\t" << -180+Theta(P1L)*180/pi <<"\t"<< FindT(P2,m2) << "\t" << 180-Theta(P2)*180/pi <<"\t" << DSCfactor(P1,P1L,beta) << endl;

    file_out2.close();

}

void Data(string filename){
    ofstream file_out2;
    file_out2.open(filename.c_str());     // open the input file, c_str() convert string to char

	//generate a pair (T1L , Theta_P1L)
	// S = 25, 40, 55, 70
	// Theta_NN = 1, 180, step 1
	// TiL=250
	// k = 0
	// Theta_k = 0, Phi_k = 0
	// Phi_NN =0
	// i = Theta_NN, j = S
	for(int i=1; i<180;i++){
		for (int j=25; j<76;j+=15){
			Simulation(14, 8, 250, 0, 0, 0, i*pi/180, 0, j);
			file_out2 << P1L[0]-m1 << "  \t" << 180-Theta(P1L)*180/pi << "  \t";
			//cout << " Theta_NN = " << i << " , S = " << j << endl;
			//cout << P1L[0] << ", " << Theta(P1L)*180/pi << endl;
		}
		file_out2 << endl;
	}

    file_out2.close();

	cout << " data.dat" << endl;

}
