#include "nucleus.h"

Nucleus::Nucleus(int z, int a)
{

    this->Z = z;
    this->A = a;
    this->N = a-z;
    this->name = Nucleus_Name(z, a);
    this->mass = Nucleus_Mass(z, a);
    this->BEA = (this->mass - z*mp - this->N * mn )/a;
    this->Sp = SeparationEnergy(z, a, 0, 1);
    this->Sn = SeparationEnergy(z, a, 1, 0);

    ZeroKinematics();

}

double Nucleus::Nucleus_Mass(int z, int a)
{
    QString line;
      int    lineNum=0;
      int    list_A, list_Z;
      double list_BEA, mass;

      int    flag=0;

      int numLineStart = 40;
      int numLineEnd  = 3392;

      if ( a >= 50 && a < 100) numLineStart = 447; //545;
      if ( a >=100 && a < 150) numLineStart = 1072;//1100;
      if ( a >=150 && a < 200) numLineStart = 1833;//1899;
      if ( a >=200 ) numLineStart = 2534;//2622;

      QFile myfile(":/massTable/mass12.txt");
      if (myfile.open(QIODevice::ReadOnly | QIODevice::Text)){
        while ( flag == 0 && lineNum <numLineEnd)
        {
          lineNum ++ ;
          line = myfile.readLine();

          //qDebug() << lineNum << "," << line;

          if (lineNum >= numLineStart ){
            list_Z = line.mid(10, 5).toInt();
            list_A = line.mid(15,5).toInt();
            list_BEA = line.mid(55,11).toDouble();
            if ( a == list_A && z == list_Z) {
                mass = list_Z*mp + (list_A-list_Z)*mn - list_BEA/1000*list_A;
                flag = 1;
            }else if ( list_A > a) {
              break;
            }

          }
        }
        myfile.close();
      }
      else {
          qDebug() << "Unable to open " << ":/massTable/mass12.txt";
      }

      if (flag == 1){
        return mass;
      }else{
        return -404;
      }

      return 0;
}

QString Nucleus::Nucleus_Name(int z, int a)
{
    QString line, name;
      int    lineNum=0;
      int    list_A, list_Z;
      int    flag=0;

      int numLineStart = 40;
      int numLineEnd  = 3392;

      if ( a >= 50 && a < 100) numLineStart = 545;
      if ( a >=100 && a < 150) numLineStart = 1100;
      if ( a >=150 && a < 200) numLineStart = 1899;
      if ( a >=200 ) numLineStart = 2622;

      QFile myfile(":/massTable/mass12.txt");
      if (myfile.open(QIODevice::ReadOnly | QIODevice::Text))
      {
        while ( flag == 0 && lineNum <numLineEnd)
        {
          lineNum ++ ;
          line = myfile.readLine();

          if (lineNum >= numLineStart ){
              list_Z = line.mid(10, 5).toInt();
              list_A = line.mid(15,5).toInt();
              name   = line.mid(19,3);
            if ( a == list_A && z == list_Z) {
                   flag = 1;
            }else if ( list_A > z) {
              break;
            }

          }
        }
        myfile.close();
      }
      else {
          qDebug() << "Unable to open" << ":/massTable/mass12.txt";
        }
      //if( isspace(name[0])) name.erase(0, 1);

      if (flag == 1){
          return name;
      }else{
           return "---";
      }
}

double Nucleus::SeparationEnergy(int z, int a, int Nn, int Np)
{
    if ( a == 1 ) return 0;

    double massP, massD1, massD2;

    massP = Nucleus_Mass(z,a);
    massD1 = Nucleus_Mass(z-Np,a-Np-Nn);
    massD2 = Nucleus_Mass(Np, Np+Nn);

    if ( massP != -404 && massD1 != -404 && massD2 != -404) {
      return massD1 + massD2 - massP;
    }else{
      return -0.000;
    }
}


void Nucleus::SetKEA(double kea){
    this->KEA = kea;
    KEA2Gamma(kea);
    Gamma2Beta(this->Gamma);
    Gamma2Momt(this->Gamma);
    Gamma2Brho(this->Gamma);
}

void Nucleus::SetMomt(double momt){
    this->Momt = momt;
    Momt2KEA(momt);
    KEA2Gamma(this->KEA);
    Gamma2Beta(this->Gamma);
    Gamma2Brho(this->Gamma);
}

void Nucleus::SetGamma(double g){
    this->Gamma = g;
    Gamma2KEA(g);
    Gamma2Momt(g);
    Gamma2Beta(g);
    Gamma2Brho(g);
}

void Nucleus::SetBeta(double b){
    this->Beta = b;
    Beta2Gamma(b);
    Gamma2KEA(this->Gamma);
    Gamma2Momt(this->Gamma);
    Gamma2Brho(this->Gamma);
}

void Nucleus::SetBrho(double brho){
    this->Brho = brho;
    Brho2Gamma(brho);
    Gamma2KEA(this->Gamma);
    Gamma2Momt(this->Gamma);
    Gamma2Beta(this->Gamma);
}





