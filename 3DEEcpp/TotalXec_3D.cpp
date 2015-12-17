#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <cstring>

using namespace std;

const double deg2rad = 3.141592654/180;

int main(int argc, char *argv[]){

	
  char* filename;
  //float TLimit = atof(argv[2]);
  float ang1Limit;
  float ang2Limit;

  if ( argc == 2){
	  ang1Limit = 0.;
    ang2Limit = 90.;    
  }else  if ( argc < 4){
    printf("./TotalXsec.o filename ang1 ang2\n");
  }
	
  filename = argv[1];
  
  if( argc == 4){
    ang1Limit = atof(argv[2]);
    ang2Limit = atof(argv[3]);
  }

  string line;
  ifstream file_in;
  file_in.open(filename);

  if (!file_in) {
    printf("Unable to open file:%s\n", filename);
    exit(1);
  }else{
    printf("opened file:%s\n", filename);
  }
  
  int lineLength = 0; 
  int lineLengthFix = 0;
  int lineNum = 0;
  int DataLineNum = 0;
  	
  double DTc;
  double Dthetac;
  double Dthetad;
  double Dphic ;
  double Dphid ;
  double totalXsec_1s1 = 0;
  double totalXsec_1p3 = 0;
  double totalXsec_1p1 = 0;
  double totalXsec_1d5 = 0;
  double totalXsec_2s1 = 0;
  double totalXsec_1d3 = 0;

  int InfileStartLine = 9999999;

  printf("theta count range (%4.1f,%4.1f) deg\n",ang1Limit, ang2Limit);

  do{
    lineNum ++;
    getline(file_in,line);
        
    lineLength = line.length(); //should be around 300;

    string lineHEAD = line.substr(0,2);

    if ( lineHEAD == "##" ) printf("%s\n",line.c_str());
    if ( lineHEAD == "#X" ) {
      DTc = atoi(line.substr(17,2).c_str());
      printf("DTc = %f \n", DTc);
    }
    if ( lineHEAD == "#Y" ) {
      Dthetac = atoi(line.substr(17,2).c_str())*deg2rad;
      printf("Dtheta_c = %f \n", Dthetac/deg2rad);
    }
    if ( lineHEAD == "#Z" ) {
      Dthetad = atoi(line.substr(17,2).c_str())*deg2rad;
      printf("Dtheta_d = %f \n", Dthetad/deg2rad);
    }
    if ( lineHEAD == "#B" ) {
      Dphic = atoi(line.substr(17,2).c_str())*deg2rad;
      printf("Dphi_c = %f \n", Dphic/deg2rad);
    }
    if ( lineHEAD == "#A" ) {
      Dphid = atoi(line.substr(17,2).c_str())*deg2rad;
      printf("Dphi_d = %f \n", Dphid/deg2rad);
    }

    if ( lineHEAD == "# " )  lineLengthFix = lineLength;  
    // printf(" lineNum:%4d, lineLen = %4d \n", lineNum, lineLength);
  		
    if ( lineHEAD == "  "  &&  lineLength == lineLengthFix ){
      DataLineNum ++;
      double Tc     = atof(line.substr(12*(1-1)+1,11+1).c_str());
      double thetac = atof(line.substr(12*(2-1)+1,12+1).c_str())*deg2rad;
      double thetad = abs(atof(line.substr(12*(5-1)+1,12+1).c_str()))*deg2rad;

      double phic = atof(line.substr(12*(3-1)+1,12+1).c_str())*deg2rad;
      double phid = abs(atof(line.substr(12*(6-1)+1,12+1).c_str()))*deg2rad;

      double theta1 = atof(line.substr(12*(14-1)+1,12+1).c_str());
      double theta2 = atof(line.substr(12*(17-1)+1,12+1).c_str());
      double phi1   = atof(line.substr(12*(15-1)+1,12+1).c_str());
      double phi2   = atof(line.substr(12*(18-1)+1,12+1).c_str());
      double beta_d  = atof(line.substr(12*(7-1)+1,12+1).c_str());
		
      double Xsec_1s1 = atof(line.substr(12*(19-1)+1,12+1).c_str());
      double Xsec_1p3 = atof(line.substr(12*(21-1)+1,12+1).c_str());
      double Xsec_1p1 = atof(line.substr(12*(23-1)+1,12+1).c_str());
      double Xsec_1d5 = atof(line.substr(12*(25-1)+1,12+1).c_str());
      double Xsec_2s1 = atof(line.substr(12*(27-1)+1,12+1).c_str());
      double Xsec_1d3 = atof(line.substr(12*(29-1)+1,12+1).c_str());
	  		
      double ang = 0;
      if ( theta1 > ang1Limit && theta1 < ang2Limit && theta2 > ang1Limit  && theta2 < ang2Limit ){
        ang = sin(thetac)*sin(thetad)*Dthetac*Dthetad*DTc*Dphic*Dphid;
      
        //printf("%4d(%3d), T_c = %7.1f, theta_c = %5.1f(%6.2f), theta_d = %5.1f(%6.2f), phi_c = %5.1f, beta_d = %5.1f , Xsec_1s1 = %12.9f, fac = %12.9f, %12.9f\n"
        //     , lineNum, lineLength, Tc, thetac/deg2rad, theta1, thetad/deg2rad, theta2, phi1, beta_d, Xsec_1s1, ang, ang*Xsec_1s1);
        
        //printf("T_c = %7.1f, theta_c = %5.1f, theta_d = %5.1f, phi_c = %5.1f, phi_d = %5.1f, fac = %12.9f, %12.9f, %12.9f\n",
        //       Tc, thetac/deg2rad, thetad/deg2rad, phic/deg2rad, phid/deg2rad, ang, ang*Xsec_1s1, totalXsec_1s1);
     
      }	
			
      totalXsec_1s1 += ang*Xsec_1s1;
      totalXsec_1p3 += ang*Xsec_1p3;
      totalXsec_1p1 += ang*Xsec_1p1;
      totalXsec_1d5 += ang*Xsec_1d5;
      totalXsec_2s1 += ang*Xsec_2s1;
      totalXsec_1d3 += ang*Xsec_1d3;
	  		
   	}
   	
   	//printf(" terminate :%d, lineLength:%3d \n", terminate, lineLength);
   	//if ( lineNum > 10000 ) break;

    if ( lineLength == 34 ) InfileStartLine = lineNum;
    if ( lineNum > InfileStartLine) printf("%s\n", line.c_str());
  }while( !file_in.eof());
  //  }while( lineLength != 34);
  printf("=======================================\n");
  printf(" DTc %2.0f, Dangc %2.0f, Dangd %2.0f, Dphic %2.0f, Dphid %2.0f \n", DTc, Dthetac/deg2rad, Dthetad/deg2rad, Dphic/deg2rad, Dphid/deg2rad);
   printf("theta count range (%4.1f,%4.1f) deg\n",ang1Limit, ang2Limit);
  printf(" total number of line = %d\n Total X-sec: \n", DataLineNum-1);
  printf("1s1 = %14.6f ub\n", totalXsec_1s1);
  printf("1p3 = %14.6f ub\n", totalXsec_1p3);
  printf("1p1 = %14.6f ub\n", totalXsec_1p1);
  printf("1d5 = %14.6f ub\n", totalXsec_1d5);
  printf("2s1 = %14.6f ub\n", totalXsec_2s1);
  printf("1d3 = %14.6f ub\n", totalXsec_1d3);

  file_in.close();
  return 0;
}
