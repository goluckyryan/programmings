#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <stdio.h>
#include <math.h>
#include <cstring>
#include "constant.h"
#include "XsecTransform.h" //load Jacobian
#include "knockout2D.h"
#include "nuclei_mass.h"
#include "3DeeGenLibrary.h" 

using namespace std;

int main(int argc, char *argv[]){
  time_t Tstart=time(0);

  if(argc < 9) {
    printf("===============Generating Flourine (p,pn) knockout data======================\n");
    printf("          Only for F(p,2p)O knockout [A(a,cd)b]\n");
    printf("Usage: ./3DeeGee_k_angk.o MA Z JA JB BE dk dAngk dAngNN\n");
    printf("      MA = Mass number of isotop \n");
    printf("      Z  = charge number of isotop \n");
    printf("      JA = spin of Flourine isotop\n");
    printf("      JB = spin of Residual \n");
    printf("      BE = binding energy of orbital proton \n");
    printf("      dk = step of k \n");
    printf("   dAngk = step of angk \n");
    printf("  dAngNN = step of angNN \n\n");
    exit(0);
  }

  //##################### variables
  int MA   = atoi(argv[1]);
  float Ti;
  switch (MA) {
  case 14: Ti = 245.46; break;
  case 16: Ti = 200.0; break;
  case 23: Ti = 289.44; break;
  case 25: Ti = 276.779; break;  
  default: Ti = 200.0; break;
  }

  int Z = atoi(argv[2]);
  float JA = atof(argv[3]);
  float JB = atof(argv[4]);
  float BE = atof(argv[5]);
  int  kStep = atoi(argv[6]);
  int angkStep = atoi(argv[7]);
  int angNNStep = atoi(argv[8]);
  
  int N = 0;
  int L = 0;
  float J = 0.5;
  
  const int kRange = 300;
  const int angkRange = 360;
  const int angNNRange = 180;

  int kNum     = (kRange-1 - (kRange-1)%kStep)/kStep+1;
  int angkNum  = (angkRange-1 - (angkRange-1)%angkStep)/angkStep+1;
  int angNNNum = (angNNRange-1 - (angNNRange-1)%angNNStep)/angNNStep+1;

  printf("%3d, %3d, %3d\n",kNum, angkNum, angNNNum);

  int totCount = 6*kNum*angkNum*angNNNum - 6*(angkNum-1)*angNNNum;

  float *output = new float[9]; // knockout output 

  char filename[50];
  sprintf(filename, "../result/paraOut_%2d%s_JA%3.1f_JB%3.1f_Sp%04.1f.dat",  MA, symbolZ(Z), JA, JB, BE);
  
//#############################  display input condition
  printf("===========================\n");
  printf(" %d%s(p,2p)%d%s \n",MA, symbolZ(Z), MA-1, symbolZ(Z-1));
  printf("Ti = %10.3f \n", Ti);
  printf("JA = %3.1f,  JB = %3.1f\n", JA, JB);
  printf("Be = %10.4f MeV\n", BE);
  printf("k Step = %2d deg, angk step = %2d, angNN step = %2d, total loops = %10d \n", kStep, angkStep, angNNStep, totCount);
  printf(" output: %s \n", filename);  
  printf("------------------------------------------------------\n");

  //#######################rewrite output file
  FILE * paraOut;
  paraOut = fopen (filename, "w");
  // file header
  fprintf(paraOut, "#A(a,cd)B = %2dF(p,2p)%2dO, JA=%3.1f  JB=%3.1f\n", MA, MA-1, JA, JB);
  fprintf(paraOut, "#BE=%6.2f  Ti=%9.3f\n", BE, Ti);
  fprintf(paraOut, "#%*s", 12*11, ""); 
  for (int ID = 1; ID<=6 ; ID++) fprintf(paraOut, "%12s%12s", "DWIA", "A00n0") ; fprintf(paraOut, "\n");
  fprintf(paraOut, "#%12d", 1); for (int i = 2; i <= 10+2*6 ; i ++) fprintf(paraOut, "%12d", i); fprintf(paraOut, "\n");
  fprintf(paraOut, "%13s%12s%12s%12s%12s%12s%12s%12s%12s%12s%12s", 
          "k", "angk", "angNN", "T1", "theta1", "T2", "theta2", "T_c","theta_c", "T_d", "theta_d");
  for (int ID= 1; ID <=6 ; ID++){
    orbit(ID, N, L, J);
    char NLJ[9];
    sprintf(NLJ, "%1d%1s%1d/2", N, symbolL(L), (int)(2*J));
    for (int i = 1; i <= 2; i++){
      fprintf(paraOut,"%12s", NLJ);  
    }
  }
  fprintf(paraOut, "\n");
    

  //########################### start looping
  int count = 0;
  int effCount = 0;
  for (float k=0; k <kRange; k+=kStep){
    for (float angk = 0; angk<angkRange; angk+=angkStep){
      if ( k == 0 && angk != 0 ) continue;
      for(float angNN = 0; angNN<angNNRange; angNN+=angNNStep){

        // use knockout2D.h to calculate Tc thetac and thetad;
        output = Knockout2D(MA, Z,  Ti, k, angk, angNN, BE);
        // 0 = T_c, 1 = theta_c, 2 = T_d, 3 = theta_d //CM frame
        // 4 , 5, 6, 7, // Lab frame
        // 8 =  beta , from CM to Lab

        // Accpetance Filter 
        if(AccpetanceFilter2D(output[4], output[5], output[6], output[7])!=1) {
          printf("***Gated by Acceptance filler ; k:%4.0f, angk:%4.0f, angNN:%4.0f | T1:%9.3f, theta1:%9.3f,T2:%9.3f, theta2:%9.3f \n",
                 k, angk, angNN, output[4], output[5], output[6], output[7]);
          count += 6;
          continue;
        }

        if ( isnan(output[0])) {
          printf(" skipped due to impossible kinematic ; k:%4.0f, angk:%4.0f, angNN:%4.0f\n", k, angk, angNN);
          count += 6;
          continue;
        }

        // display
        printf("\e[32m==== %6d[\e[31m%4.1f%%\e[32m]| k:%6.2f angk:%6.2f angNN:%6.2f| T_c:%9.3f, theta_c:%9.3f, theta_d:%9.3f \e[m\n",
               count, count*100./totCount, k, angk, angNN, output[0], output[1], output[3]);

        printf("                                 T1:%9.3f, theta1:%9.3f,T2:%9.3f, theta2:%9.3f \n",
               output[4], output[5], output[6], output[7]);
      
        // save parameters + readout
        fprintf(paraOut,"%12.3f%12.3f%12.3f%12.3f%12.3f%12.3f%12.3f%12.3f%12.3f%12.3f%12.3f",
                k, angk, angNN, output[4],output[5],output[6],output[7], output[0], output[1], output[2], output[3]);       

        for (int ID=1; ID <=6; ID ++){
          count ++;
          effCount ++;
          //orbit
          orbit(ID, N, L, J);

          //make infile
          make_infile(MA, Z, JA, JB,  Ti, N, L, J, BE, output[0], output[1], output[3], 0);

          // run 3Dee code
          system("./threedee infile");
     
          // read_outfile : xsec + Ay
          if (read_outfile(57) == 10) continue;
          
          // save parameters + readout
          fprintf(paraOut,"%12.6f%12.6f",DWIA ,A00n0); 
      
          //Delete outfile
          remove("outfile");
       
        }
        
        fprintf(paraOut, "\n");
      }
      fprintf(paraOut,"\n");
    }
    fprintf(paraOut,"\n");
  }
  fprintf(paraOut,"##################################\n");

  fclose(paraOut);
  // append infile to  output file
  char command[100];
  sprintf(command,"cat %s >> %s","infile", filename);
  system(command);

  //########################## display result
  time_t Tend=time(0);
  printf("\e[32m[%5.1f%%]========== Totol run time %10.0f sec = %5.1f min| speed:#%5.2f(%5.2f)/sec ===========\e[m\n",
         count*100./totCount,difftime(Tend,Tstart),difftime(Tend,Tstart)/60,count/difftime(Tend,Tstart),effCount/difftime(Tend,Tstart)); 
  printf("  condition %2d%s(p,2p)%2d%s   Ti:%7.2f MeV \n", MA, symbolZ(Z) ,MA-1,symbolZ(Z-1),  Ti );
  printf("  JA = %3.1f,  JB = %3.1f\n", JA, JB);
  printf("  assume Binding energy of orbital proton is %7.2f \n", BE );
  printf("  output: %s \n", filename);  

  
  return 0;

}
