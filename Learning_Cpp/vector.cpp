#include <iostream>
#include <cmath>
#include "../CppLibrary/vector.h"

using namespace std;

int main(){

    Vector v1(3), v2(3), v3(3);

    v1.setElement();
    v1.print(" v1 : ", "\n");
    v2.setElement();
    v2.print(" v2 : ", "\n");

    cout << endl;

    cout << " v1.v2 = " << (v1^v2) << endl;

    cout << " opening angle = " << v1.openAng(v2)*rad2deg << endl;

    v3 = v1.cross(v2);
    v3.print(" v3 : ", "\n");

    return 0;
}
