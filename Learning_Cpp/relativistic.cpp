#include <iostream>
#include <cmath>
#include "../CppLibrary/constant.h"
#include "../CppLibrary/fourVector.h"
#include "../CppLibrary/RotMatrix4D.h"
#include "../CppLibrary/lorentzian.h"

using namespace std;

int main(){
    double mass[3] = {mp_MeV, 1,  1};
    FourVector v1, v2, v1c, v2c, u1c, u2c, u1, u2;
    FourVector cm, cmc;


    Lorentzian L1, L2;


    v1.set(3, mass, 2.4842, 0, 0);
    v2.set(4, mass, 0, 0, 0);
    
    double scat_ang;
    
    cout << " scattering angle [deg] in CM frame : ";
    cin >> scat_ang; 
    
    RotMatrix4D rot (scat_ang, 90, 90);

    cm = v1+v2;
    cm = cm/2; // center of momentum 4 vector

    L1.set(-cm.beta,cm.angle[0],cm.angle[1]);
    L2.set(cm.beta,cm.angle[0],cm.angle[1]);

    cmc = L1^cm;

    v1c=L1^v1;
    v2c=L1^v2;

    u1c= rot^v1c;
    u2c= rot^v2c;

    u1 = L2^u1c;
    u2 = L2^u2c;

    /// Display
    v1.printKinamatics(5," v1  ");
    v2.printKinamatics(0," v2  ");
    cm.printKinamatics(0," cm  ");
    cout << "------- CM frame ----------" << endl;
    cmc.printKinamatics(0," cmc ");
    v1c.printKinamatics(0," v1c ");
    v2c.printKinamatics(0," v2c ");
    u1c.printKinamatics(0," u1c ");
    u2c.printKinamatics(0," u2c ");
    cout << "------- Lab     ----------" << endl;
    u1.printKinamatics(0," u1  ");
    u2.printKinamatics(0," u2  ");
    cout << "opening angle = " << (u1.angle[0]+u2.angle[0])*rad2deg << endl;
    /*
    L1.print();
    rot.print("rot");
    v1.print();cout << endl;
    v2.print();cout << endl;
    v1c.print();cout << endl;
    v2c.print();cout << endl;
    u1c.print();cout << endl;
    u2c.print();cout << endl;
    u1.print();cout << endl;
    u2.print();cout << endl;
    */
    return 0;
}
