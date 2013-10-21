#include <iostream>
#include <fstream>
#include <string>
#include "constant.h"
#include <stdlib.h>  //atoi
using namespace std;

double Nucleus_Mass(int Z, int A)
{
  string line, name;
  int    lineNum=0;
  int    list_A, list_Z;
  double list_mass1, list_mass2, list_mass;
  double mass;
  //ifstream myfile ("/home/goluckyryan/Dropbox/programmings/CppLibrary/mass03.txt");
  ifstream myfile ("mass03.txt");
  int    flag=0;

  if (myfile.is_open())
  {
    while (/*! myfile.eof() &&*/ flag == 0 && lineNum <3218)
    {
      lineNum ++ ;
      //printf("%3d  ",lineNum);
      getline (myfile,line);

      if (lineNum >= 40 ){
      	list_Z     = atoi((line.substr(15,5)).c_str());
      	list_A     = atoi((line.substr(10,5)).c_str());
      	list_mass1 = atof((line.substr(96,3)).c_str());
      	list_mass2 = atof((line.substr(99,13)).c_str());
      	list_mass  = list_mass1 + list_mass2*1e-6;
      	name       = line.substr(19,3);
      	//cout << line.substr(2,20) << ", " << line.substr(99,13) << endl;
      	//printf("       %3d,%3d  %10.5f  ,%16.5f \n",list_A,list_Z, list_mass1, list_mass);

      	if ( A == list_A && Z == list_Z) {
      		mass = list_mass*amu;
     		flag = 1;
   //   	}else{
   //   		cout << lineNum << ", not found! \n";
      	}

      }
    }
    myfile.close();
  }
  else cout << "Unable to open file \n";

  if (flag == 1){
 //   printf(" nuclei found! mass of %s = %16.5f MeV \n",name.c_str(), mass);
    return mass;
  }else{
 // 	cout << " no such nucleus in database. \n" ;
  	return -404;
  }

  return 0;
}



