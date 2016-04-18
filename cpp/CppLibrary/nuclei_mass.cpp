#include "nuclei_mass.h"
#include "constant.h"
#include "nuclei_mass.h"
#include "fourVector.h"
#include "RotMatrix4D.h"
#include "lorentzian.h"
#include "../knockout/knockoutLibrary4V.h"

using namespace std;

void Usage();
void Mass_cal(int A, int Z);
void Mass_cal_extra(int A1, int Z1, int A2, int Z2);
void Kinematics_cal(int A, int Z);
void React_cal_1(int A, int Z); // 2-body use CM angle 
void React_cal_2(int A, int Z); // 3-body use CM angle
void PrintP(double P[3], string name);

int main (int argc, char *argv[])
{

   int    Z, A, Za, Aa;
   string Opt = "--";

   Opt = argv[1];
   if (argc == 4){
      A= atoi(argv[2]);
      Z= atoi(argv[3]);
   }else if ( argc == 6){
      A= atoi(argv[2]);
      Z= atoi(argv[3]);
      Aa= atoi(argv[4]);
      Za= atoi(argv[5]);      
   }else{
      Usage();
   }
   
   int id1 = atoi(Opt.substr(2,1).c_str());
   
   if( id1 == 1 ) {
     Mass_cal(A, Z);
     if( argc == 6 )     Mass_cal_extra(A, Z, Aa, Za);
   }

   int id2 = atoi(Opt.substr(1,1).c_str());   
   if( id2 == 1) {
      Kinematics_cal(A, Z);
   }

   int id3 = atoi(Opt.substr(0,1).c_str());   
   if( id3 == 1) {
      React_cal_1(A, Z);
   }else if(id3 == 2){
      React_cal_2(A, Z);
   }
   
   if (id1 == 0 && id2 == 0 && id3 == 0) Usage();

   printf("--------- end of program ---------\n");
   return 0;
}

void Usage(){
   cout << "./nuclei_mass.o Opt A Z" << endl;
   cout << "./nuclei_mass.o Opt A Z A' Z'" << endl;
   cout << " Opt = rkm, e.g. 001 only calculate mass" << endl;
   cout << "       |||_ mass " << endl;
   cout << "       ||__ kinematics " << endl;
   cout << "       |___ reaction kinematics " << endl;
   exit(0);
}

void Mass_cal(int A, int Z){

   double mass = Nucleus_Mass(Z,A);
   string name = Nucleus_Name(Z,A);

   double BE = (Z*mp + (A-Z)*mn - mass)/A;

   if (mass > 0){
     printf(" mass of \e[47m\e[31m%3d%s\e[m nucleus (Z,A)=(%3d,%3d) is \e[47m\e[31m%12.5f\e[m MeV, BE/A=%7.5f\n",A,name.c_str(), Z,A, mass, BE);     
     printf(" mass in amu : %12.5f u\n",mass/amu);
     printf(" S1p: %8.4f| S1n: %8.4f| S(2H ): %8.4f| S1p1n : %8.4f\n", SpBreak(Z,A, 0, 1), SpBreak(Z,A, 1, 0), Sp(Z,A, 1, 1), SpBreak(Z,A,1,1));
     printf(" S2p: %8.4f| S2n: %8.4f| S(3He): %8.4f| S(3H) : %8.4f\n", SpBreak(Z,A, 0, 2), SpBreak(Z,A, 2, 0), Sp(Z,A, 1, 2), Sp(Z,A, 2, 1));
     printf(" S3p: %8.4f| S3n: %8.4f| S(4He): %8.4f|\n", SpBreak(Z,A, 0, 3), SpBreak(Z,A, 3, 0), Sp(Z,A, 2, 2));
     printf(" S4p: %8.4f| S4n: %8.4f| \n", SpBreak(Z,A, 0, 4), SpBreak(Z,A, 4, 0));
     
   }else{
      printf("Error %6.0f, no nucleus with (Z,A) = (%3d,%3d). \n", mass, Z, A);
   }

}

void Mass_cal_extra(int A1, int Z1, int A2, int Z2){

  string name = Nucleus_Name(Z1,A1);
  string name2 = Nucleus_Name(Z2, A2);
  string name3 = Nucleus_Name(Z1-Z2, A1-A2);
  printf(" S(%2d%2s) = S(%2d%2s) : %8.4f MeV\n", A2, name2.c_str(), A1-A2, name3.c_str(), Sp(Z1,A1,A2-Z2,Z2));
  printf(" Q-factor = m(%2d%2s) - m(%2d%2s) - m(%2d%2s) = %8.4f MeV\n",A1, name.c_str(), A2, name2.c_str(), A1-A2, name3.c_str(),Nucleus_Mass(Z1,A1)-Nucleus_Mass(Z2,A2)-Nucleus_Mass(Z1-Z2,A1-A2));

}

void Kinematics_cal(int A, int Z){
   
   double mass = Nucleus_Mass(Z,A);

   int id1, id2;
   float val1, val2;
   printf("[id1 id2 v1 v2] (id1, input: 1 Brho, 2 T/A) (id2, input: 1 TOF, 2 Length ) \n <<< ");
   scanf("%d %d %f %f", &id1, &id2, &val1, &val2);
   
   double T, Brho;
   if ( id1 == 1){ T = Brho2T(mass, Z, A, val1); Brho = val1;}
   if ( id1 == 2){ T = val1; Brho = T2Brho(mass, Z, A, val1);}
   double vel = T2beta(mass, A, T)*c;
   
   double TOF, length;
   if ( id2 == 2){ TOF = val2/vel; length = val2;}
   if ( id2 == 1){ TOF = val2    ; length = val2*vel;}
   
   
   double momt, dBw;
   momt = sqrt(T*A*(2*mass+T*A));
   dBw = 2*pi*hbarc/momt;

   printf("       KE/A = %10.3f A MeV, KE = %f MeV\n", T, T*A);
   printf("       Brho = %10.3f T.m\n", Brho);
   printf("       momt = %10.3f MeV/c\n", momt);
   printf("       beta = %10.3f \n", vel/c);
   printf("     length = %10.3f mm\n", length);
   printf("       TOF  = %10.3f ns \n", TOF);
   printf(" de Broglie = %10.8f fm \n", dBw);

}


void React_cal_1(int A, int Z){
   
   printf("-----Reaction Kinematics (2-body) T(p,1)2 ---------\n");
   float KEp;
   int Ap, Zp, A1, Z1;
   float theta_NN, Ex1, Ex2;
   printf("KEp Ap Zp A1 Z1 theta_NN Ex1 Ex2\n <<< ");
   scanf("%f %d %d %d %d %f %f %f",&KEp, &Ap, &Zp, &A1, &Z1, &theta_NN, &Ex1, &Ex2);
   
   int A2 = A + Ap - A1;
   int Z2 = Z + Zp - Z1;
   
   if( A2 <= 0 || Z2 < 0 ) {
      printf("   Mass of residue is %d.\n", A2);
      printf(" Charge of residue is %d.\n", Z2);
      printf(" Abort !!!\n");
      exit(0);
   }
   
   double massT = Nucleus_Mass(Z,A); // target mass 
   double massp = Nucleus_Mass(Zp,Ap); // project 
   double mass1 = Nucleus_Mass(Z1,A1); // Scattered 1 
   double mass2 = Nucleus_Mass(Z2,A2); // Scattered 2 
   
   string nameT = Nucleus_Name(Z,A);
   string namep = Nucleus_Name(Zp,Ap);
   string name1 = Nucleus_Name(Z1,A1);
   string name2 = Nucleus_Name(Z2,A2);
   printf("------------------------------\n");   
   printf("  Energy Conservation : E1 + E2 = ET + Ep, E1 = m1* + T1, m1* = m1 + Ex1\n");
   printf("Momentum Conservation : k1 + k2 = kT + kp \n");
   printf("------------------------------\n");
   printf(" Reaction: %d%s(%d%s,%d%s)%d%s \n", A, nameT.c_str(), Ap, namep.c_str(), A1, name1.c_str(), A2, name2.c_str());   
   printf(" Incident KE = %10.3f MeV \n", KEp);
   printf("       no excited Q - value = mT + mp - m1  - m2  = %10.6f MeV \n", massT + massp - mass1 - mass2 );
   printf("bounding energy = Q - value = mT + mp - m1* - m2* = %10.6f MeV \n", massT + massp - mass1 - mass2 - Ex1 - Ex2 );
   printf(" center of mass scattered angle of p = %10.5f deg\n", theta_NN);
   printf("------------------------------\n");
   
   double PT[3] = {massT, 0, 0}; // (E, px, pz)
   double momtp = sqrt(KEp*Ap*(2*massp+KEp*Ap));
   double Pp[3] = {massp+KEp*Ap, 0, momtp};
      
   double Pc[3];
   Pc[0] = (PT[0] + Pp[0])/2.;
   Pc[1] = (PT[1] + Pp[1])/2.;
   Pc[2] = (PT[2] + Pp[2])/2.;
   
   double beta  = Pc[2]/Pc[0];
   double gamma = 1/sqrt((1-beta)*(1+beta));
   
   //Lorentz transform for CM frame
   double PT_c[3];
   PT_c[0] = gamma*PT[0] - gamma*beta*PT[2];
   PT_c[1] = PT[1];
   PT_c[2] = -gamma*beta*PT[0] + gamma*PT[2];

   double Pp_c[3];
   Pp_c[0] = gamma*Pp[0] - gamma*beta*Pp[2];
   Pp_c[1] = Pp[1];
   Pp_c[2] = -gamma*beta*Pp[0] + gamma*Pp[2];   
   
   double TotE_c = PT_c[0] + Pp_c[0];
   
   double m1 = mass1 + Ex1;
   double m2 = mass2 + Ex2;
   double k_c = sqrt( (TotE_c - m1 - m2)*(TotE_c + m1 - m2)*(TotE_c - m1 + m2)*(TotE_c + m1 + m2))/2/TotE_c;
   
   theta_NN = theta_NN*deg2rad; //in rad
   
   double P1_c[3];
   P1_c[0] = sqrt(m1*m1 + k_c*k_c);
   P1_c[1] = k_c * sin(theta_NN);
   P1_c[2] = k_c * cos(theta_NN);
   
   double P2_c[3];
   P2_c[0] = sqrt(m2*m2 + k_c*k_c);
   P2_c[1] = -k_c * sin(theta_NN);
   P2_c[2] = -k_c * cos(theta_NN);
   
   //Transform back to Lab frame
   
   double P1[3];
   P1[0] = gamma*P1_c[0] + gamma*beta*P1_c[2];
   P1[1] = P1_c[1];
   P1[2] = gamma*beta*P1_c[0] + gamma*P1_c[2];
   
   double P2[3];
   P2[0] = gamma*P2_c[0] + gamma*beta*P2_c[2];
   P2[1] = P2_c[1];
   P2[2] = gamma*beta*P2_c[0] + gamma*P2_c[2];
   
   PrintP(PT, "PT");
   PrintP(Pp, "Pp");
   PrintP(P1, "P1");
   PrintP(P2, "P2");
   
   //PrintP(PT_c, "PT_c");
   //PrintP(Pp_c, "Pp_c");
   //PrintP(P1_c, "P1_c");
   //PrintP(P2_c, "P2_c");
   
}

void React_cal_2(int A, int Z){
   
   printf("-----Reaction Kinematics (3-body) T(p,12)R  ---------\n");
   float KEp;
   int Ap, Zp, A1, Z1, A2, Z2;
   float k, theta_k, phi_k, theta_NN, phi_NN, S;
   printf("KEp Ap Zp A1 Z1 A2 Z2 k theta_k phi_k theta_NN phi_NN S\n <<< ");
   scanf("%f %d %d %d %d %d %d %f %f %f %f %f %f",&KEp, &Ap, &Zp, &A1, &Z1, &A2, &Z2, &k, &theta_k, &phi_k, &theta_NN, &phi_NN, &S);
   
   int AR = A + Ap - A1 - A2;
   int ZR = Z + Zp - Z1 - Z2;
   
   if( A2 <= 0 || Z2 < 0 ) {
      printf("   Mass of residue is %d.\n", A2);
      printf(" Charge of residue is %d.\n", Z2);
      printf(" Abort !!!\n");
      exit(0);
   }
   
   Knockout(Z, A, KEp, k, theta_k, phi_k, theta_NN, phi_NN, S , Zp, Ap, Z1, A1, Z2, A2);
   Display(KEp, k, theta_k, phi_k, theta_NN, phi_NN, S);
   
}

void PrintP(double P[3], string name){
   
   double momt = sqrt(P[1]*P[1] + P[2]*P[2]);
   double mass = sqrt((P[0]-momt)*(P[0]+momt));
   double angle = atan2(P[1],P[2])/deg2rad; // in deg
   
   printf("%4s : %10.2f %10.2f %10.2f | mass: %10.2f, KE: %6.2f, Momt: %10.2f, Ang: %6.2f\n", name.c_str(), P[0], P[1], P[2], mass, P[0]-mass, momt, angle);
   
}
