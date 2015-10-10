#include "nuclei_mass.h"
using namespace std;

int main (int argc, char *argv[])
{

  int    Zstart, Zend, Nstart,Nend;
  double mass; 
  string name = "--";

  if (argc == 5){
    Zstart = atoi(argv[1]);
    Zend   = atoi(argv[2]);    
    Nstart = atoi(argv[3]);
    Nend   = atoi(argv[4]);
  }else{
    cout << "./nuclei_mass.o Zstart Zend Nstart Nend" << endl;
    exit(0);
  }
	

  FILE * paraOut;
  paraOut = fopen ("nuclei_data.txt", "w");
  // file header
  fprintf(paraOut, "%19s", "Vpn = Spn-Sn-Sp");
  for ( int i = Zstart; i<= Zend; i++) fprintf(paraOut,"%9s",Nucleus_Name(i,2*i).c_str());
  fprintf(paraOut, "\n");

  for( int i = Nstart; i <= Nend; i++){
    bool flag = 0;
    for (int j = Zstart; j<=Zend; j++){
      bool flag_Skip = 0;
      if (flag == 0 ){
        //name = Nucleus_Name(i,2*i);
        //fprintf(paraOut,"%3d%6s", i, name.c_str());
        fprintf(paraOut,"%19d", i);        
        flag = 1;
      }
      if (Sp(j,i+j, 1, 1) == -404) flag_Skip = 1;
      if (Sp(j,i+j-1, 0, 1) == -404) flag_Skip = 1;
      if (Sp(j-1,i+j-1, 1, 0) == -404) flag_Skip = 1;    
      double data = Sp(j,i+j, 1, 1)- Sp(j-1,i+j-1, 1, 0)- Sp(j,i+j-1, 0, 1);

      printf("Spn(%2d,%2d):%8.3f, Sp(%2d,%2d):%8.3f, Sn(%2d,%2d):%8.3f, Vpn:%8.3f \n", j, i, Sp(j,i+j,1 ,1), j,i-1, Sp(j,i+j-1, 0, 1), j-1, i, Sp(j-1,i+j-1,1, 0), data);

      if ( flag_Skip == 1) {
        fprintf(paraOut, "%9.1f", 0.);
      }else{
        fprintf(paraOut, "%9.3f", data);
      }
    }
    fprintf(paraOut, "\n");
  }

  fclose(paraOut);

  return 0;
}

