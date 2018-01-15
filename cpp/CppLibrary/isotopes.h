#ifndef ISOTOPES_H
#define ISOTOPES_H

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include "constant.h" // amu
#include <stdlib.h>  //atoi
using namespace std;

//string dataPath="/home/goluckyryan/Dropbox/programmings/cpp/CppLibrary/mass16.txt";
//string dataPath="/Users/mobileryan/Dropbox/programmings/Cpp/CppLibrary/mass16.txt";
string dataPath="mass16.txt";

// about the mass**.txt
// Mass Excess = (ATOMIC MASS - A)*amu | e.g. n : (1.088664.91585E-6-1)*amu
// mass excess uncertaintly
// BEA = (Z*M(1H) + N*M(1n) - Me(A,Z))/A , Me is the mass with electrons
// BEA = (Z*mp + N*mn - M(A,Z))/A , M is the mass without electrons

class Isotopes {
public:
   int A, Z;
   double Mass, MassError, BEA;
   string Name, Symbol;
   double Sp, Sn;
   string dataSource;
   
   Isotopes(int a, int z);
   Isotopes(string name);
   void CalSp(int na, int nz);
   
private:
   void FindMassByAZ(int a, int z); // give mass, massError, BEA, Name, Symbol;
   void FindMassByName(string name); // give Z, mass, massError, BEA;
   
};

Isotopes::Isotopes(int a, int z){
    this->A = a;
    this->Z = z;
    
    FindMassByAZ(a,z); 
    
    this->Sp = 0;
    this->Sn = 0;
    
    this->dataSource = dataPath;
}

Isotopes::Isotopes(string name){
    
    string temp = name;
    
    printf("%s \n", temp.c_str());
    
    temp.replace(temp.begin(), temp.end(), '0', ' '); 
    temp.replace(temp.begin(), temp.end(), '1', ' ');
    temp.replace(temp.begin(), temp.end(), '2', ' ');
    temp.replace(temp.begin(), temp.end(), '3', ' ');
    temp.replace(temp.begin(), temp.end(), '4', ' ');
    temp.replace(temp.begin(), temp.end(), '5', ' ');
    temp.replace(temp.begin(), temp.end(), '6', ' ');
    temp.replace(temp.begin(), temp.end(), '7', ' ');
    temp.replace(temp.begin(), temp.end(), '8', ' ');
    temp.replace(temp.begin(), temp.end(), '9', ' ');

    printf("%s \n", temp.c_str());

    for(int i=0; temp[i]; i++)
     if(temp[i] == ' ') temp[i] = '\b';

    this->Symbol = temp;

    temp = name;
    temp.replace(temp.begin(), temp.end(), this->Symbol.c_str(), ' ');
    
    this->A = atoi(temp.c_str());
    
    printf(" Symbol = %s , Mass = %d\n", this->Symbol.c_str(), this->A);
    
    FindMassByName(name); 
    
    this->Sp = 0;
    this->Sn = 0;
    
    this->dataSource = dataPath;
}

void Isotopes::FindMassByAZ(int a, int z){
    
}

void Isotopes::FindMassByName(string name){
    
}

void Isotopes::CalSp(int na, int nz){
    
}




double Nucleus_Mass(int Z, int A)
{
  string line;
  int    lineNum=0;
  int    list_A, list_Z;
  double list_BEA, mass, massError;

  ifstream myfile;
  int    flag=0;

  int numLineStart = 40;
  int numLineEnd  = 3392;

  if ( A >= 50 && A < 100) numLineStart = 447; //545;
  if ( A >=100 && A < 150) numLineStart = 1072;//1100;
  if ( A >=150 && A < 200) numLineStart = 1833;//1899;
  if ( A >=200 ) numLineStart = 2534;//2622;

  myfile.open(dataPath.c_str());

  if (myfile.is_open())
  {
    while (/*! myfile.eof() &&*/ flag == 0 && lineNum <numLineEnd)
    {
      lineNum ++ ;
      //printf("%3d  ",lineNum);
      getline (myfile,line);

      if (lineNum >= numLineStart ){
        list_Z     = atoi((line.substr(10,5)).c_str());
      	list_A     = atoi((line.substr(15,5)).c_str());
      	list_BEA   = atof((line.substr(54,11)).c_str());
        
      	if ( A == list_A && Z == list_Z) {
      		mass = list_Z*mp + (list_A-list_Z)*mn - list_BEA/1000*list_A;
            massError = atof((line.substr(65,7)).c_str());
     		flag = 1;
      	}else if ( list_A > A) {
          break;
        }

      }
    }
    myfile.close();
  }
  else printf("Unable to open %s\n", dataPath.c_str());

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

  int numLineStart = 40;
  int numLineEnd  = 3392;

  if ( A >= 50 && A < 100) numLineStart = 545;
  if ( A >=100 && A < 150) numLineStart = 1100;
  if ( A >=150 && A < 200) numLineStart = 1899;
  if ( A >=200 ) numLineStart = 2622;

  myfile.open(dataPath.c_str());

  if (myfile.is_open())
  {
    while ( flag == 0 && lineNum <numLineEnd)
    {
      lineNum ++ ;
      getline (myfile,line);

      if (lineNum >= numLineStart ){
      	list_Z     = atoi((line.substr(10,5)).c_str());
      	list_A     = atoi((line.substr(15,5)).c_str());
      	name       = line.substr(19,3);
      	if ( A == list_A && Z == list_Z) {
     		   flag = 1;
      	}else if ( list_A > A) {
          break;
        }

      }
    }
    myfile.close();
  }
  else printf("Unable to open %s\n", dataPath.c_str());

  if( isspace(name[0])) name.erase(0, 1);

  if (flag == 1){
      return name;
  }else{
  	   return "---";
  }

}

double Sp (int Z, int A, int Nn, int Np){

  if ( A == 1 ) return 0;

  double massP, massD1, massD2;

  massP = Nucleus_Mass(Z,A);
  massD1 = Nucleus_Mass(Z-Np,A-Np-Nn);
  massD2 = Nucleus_Mass(Np, Np+Nn);

  if ( massP != -404 && massD1 != -404 && massD2 != -404) {
    return massD1 + massD2 - massP;
  }else{
    return -0.000;
  }

}

double SpBreak (int Z, int A, int Nn, int Np){
  double mass, massD;

  mass  = Nucleus_Mass(Z,A);
  massD = Nucleus_Mass(Z-Np, A-Np-Nn);

  if( mass != -404 && massD != -404){
    return massD + Nn*mn + Np*mp - mass;
  }else{
    return -0.000;
  }
}

#endif
