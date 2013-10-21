#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include "constant.h"
#include <stdlib.h>  //atoi
using namespace std;

string dataPath="/home/goluckyryan/Dropbox/programmings/CppLibrary/mass03.txt";

double Nucleus_Mass(int Z, int A)
{
  string line;
  int    lineNum=0;
  int    list_A, list_Z;
  double list_mass1, list_mass2, list_mass;
  double mass;
  ifstream myfile;
  int    flag=0;
  
  myfile.open(dataPath.c_str());

  if (myfile.is_open())
  {
    while (/*! myfile.eof() &&*/ flag == 0 && lineNum <3218)
    {
      lineNum ++ ;
      //printf("%3d  ",lineNum);
      getline (myfile,line);

      if (lineNum >= 40 ){
         list_Z     = atoi((line.substr(10,5)).c_str());
      	list_A     = atoi((line.substr(15,5)).c_str());
      	list_mass1 = atof((line.substr(96,3)).c_str());
      	list_mass2 = atof((line.substr(99,13)).c_str());
      	list_mass  = list_mass1 + list_mass2*1e-6;
      	//printf("(%3d,%3d) %3d,%3d  %10.5f  ,%16.5f \n",Z,A,list_Z,list_A, list_mass1, list_mass);

      	if ( A == list_A && Z == list_Z) {
      		mass = list_mass*amu;
     		   flag = 1;
      	}

      }
    }
    myfile.close();
  }
  else cout << "Unable to open mass03.txt \n";

  if (flag == 1){
    return mass;
  }else{
  	return -404;
  }

  return 0;
}

string Nucleus_Name(int Z, int A){

  string line, name;
  int    lineNum=0;
  int    list_A, list_Z;
  ifstream myfile;
  int    flag=0;
  
  myfile.open(dataPath.c_str());

  if (myfile.is_open())
  {
    while ( flag == 0 && lineNum <3218)
    {
      lineNum ++ ;
      getline (myfile,line);

      if (lineNum >= 40 ){
      	list_Z     = atoi((line.substr(10,5)).c_str());
      	list_A     = atoi((line.substr(15,5)).c_str());
      	name       = line.substr(19,3);
      	if ( A == list_A && Z == list_Z) {
     		   flag = 1;
      	}

      }
    }
    myfile.close();
  }
  else cout << "Unable to open mass03.txt \n";

  if (flag == 1){
      return name;
  }else{
  	   return "---";
  }

}


