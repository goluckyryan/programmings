#include <stdio.h>
#include <stdlib.h> //for atoi, atof
#include <math.h> //exp
#include "RK4.h"


int main(int argc, char *argv[]){

  if(argc < 7+1) {
    printf("====== Runge-Kutta 4-th order method to solve SE =====\n");
    printf("Usage: ./RK4.o KE L nStep dx V0 R0 a0\n");
    printf("  KE : kinetics  energy (MeV)\n");
    printf("  L  : orbital angular momentum \n");
    printf("nStep: number of Step \n");
    printf("  dr : stepSize (fm) \n");
    printf("  V0 : Wood-Saxons depth \n");
    printf("  R0 : half-maximum radius (fm) \n");
    printf("  a0 : diffusiveness (fm) \n");
    exit(0);
  }

  double KE = atof(argv[1]);
  int L  = atoi(argv[2]);
  int nStep = atoi(argv[3]);
  double dr = atof(argv[4]);
  double V0 = atof(argv[5]);
  double R0 = atof(argv[6]);
  double a0 = atof(argv[7]);

  RKfouth(KE, L, nStep, dr, V0, R0, a0);


  return 0;
}


