#ifndef RK4
#define RK4

#include <stdio.h>
#include <stdlib.h> //for atoi, atof
#include <math.h> //exp

double mp = 938.272;
double hbarc = 197.362;
double amu = 931.5;

// Wood-Saxon
double Pot(double r, double V0, double R0, double a0){
   return V0/(1+exp((r-R0)/a0));
}

double G(double r, double u, double T, double L, double Pot){
  return (2*mp/pow(hbarc,2))*(Pot-T)*u + L*(L+1)*u/pow(r,2);
} 

int RKfouth (const double KE, int L, int nStep, double dr, float V0, float R0, float a0){

  // output is a file "RK4.dat"

  const double scale = abs(V0);
  double rStart = 0.00001;
  double rEnd = rStart + dr * nStep;

  printf("-------------- inputs\n");
  printf(" KE: %6.2f MeV, L: %2d \n", KE, L);
  printf(" V0: %6.2f MeV, R0: %6.2f fm, a0: %6.2f fm \n", V0, R0, a0);
  printf(" start: %7.5f fm, dr:%5.3f, end: %10.5f fm, nStep: %3d \n", rStart, dr, rEnd, nStep);
 
  const int nStep1 = nStep + 1 ;
  double SolU[nStep1][2]; // SolU[i][0] is U, SolU[i][1] is du/dr
  
  SolU[0][0] = 0;
  SolU[0][1] = 1;
  
  FILE * paraOut;
  paraOut = fopen ("RK4.dat", "w");
  fprintf(paraOut, "# KE: %6.2f MeV, L: %2d \n", KE, L);
  fprintf(paraOut, "# V0: %6.2f MeV, R0: %6.2f fm, a0: %6.2f fm\n", V0, R0, a0);
  fprintf(paraOut, "# start: %7.5f fm, dr:%5.3f, end: %10.5f fm, nStep: %3d \n", rStart, dr, rEnd, nStep);
  fprintf(paraOut, "#%12s %12s %9s%-3.0f %12s %12s %12s %12s %9s%-3.0f\n", "r", "Pot/100", "(Pot+LS)/", scale, "u", "du/dr", "R", "dR/dr", "KE/", scale);
  fprintf(paraOut, "#----------\n");
  fprintf(paraOut, " %12.3E %12.3E %12.3E %12.3E %12.3E %12.3E %12.3E %12.3E\n", rStart, Pot(rStart, V0, R0, a0)/scale, 0, SolU[0][0], SolU[0][1], SolU[0][0]/rStart, SolU[0][1]/rStart - SolU[0][0]/pow(rStart,2), 0.0);

  double maxu = 0;  
  for(int i = 0; i <= nStep; i++){
    double r = rStart + i * dr;
    double pot = Pot(r, V0, R0, a0);
    double u = SolU[i][0];
    double v = SolU[i][1];
        
    //printf(" r:%5.2f, u:%5.2f, v:%5.2f, Pot:%5.2f \n", r, u, v, pot);

    double ku1 = v;
    double kv1 = G(r, u, KE, L, pot);

    double ku2 = v + kv1*dr/2;    
    double kv2 = G(r + dr/2, u + ku1*dr/2, KE, L, pot); 

    double ku3 = v + kv2*dr/2;    
    double kv3 = G(r + dr/2, u + ku2*dr/2, KE, L, pot);

    double ku4 = v + kv3*dr;    
    double kv4 = G(r + dr, u + ku3*dr, KE, L, pot);
    
    double du = dr/6*(ku1 + 2*ku2 + 2*ku3 + ku4);
    double dv = dr/6*(kv1 + 2*kv2 + 2*kv3 + kv4);
    
    SolU[i + 1][1] = v + dv;
    SolU[i + 1][0] = u + du;

    if ( u > maxu) maxu = u;
  }
  
  printf("------- normalized ul \n");

  for( int i = 0; i <= nStep; i++){
    double r = rStart + i*dr;
    double pot = Pot(r+dr,V0,R0,a0);
    double poteff = pot + pow(hbarc/(r+dr),2)*L*(L+1)/2/mp;
    if ( abs(poteff) > abs(V0) ) poteff = 0.0;
    SolU[i+1][1] = SolU[i+1][1]/maxu;
    SolU[i+1][0] = SolU[i+1][0]/maxu;
    
    fprintf(paraOut, " %12.3E %12.3E %12.3E %12.3E %12.3E %12.3E %12.3E %12.3E\n", r+dr, pot/scale, poteff/scale , SolU[i+1][0], SolU[i+1][1], SolU[i+1][0]/r, SolU[i+1][1]/r - SolU[i+1][0]/pow(r,2), KE/scale);
  }

  fclose(paraOut);
  printf("----------done.\n");

  return 0;
}

#endif
