#include <vector>
#include "../CppLibrary/mathlib.h"

int main() {

    Catesian_Vector p;

    p.set(1,1,1);
    p.displayCat();

    cout << p.call_Norm() << endl;

    p.displaySphDegree();

    p.displaySphRad();

    cout << norm(p.Rvector) << endl;


    cout << "**************************" << endl;

    Four_Momentum K;

    K.set(1.2,1,0,0);
    K.display();
    cout << "speed % c : "<<K.beta() << endl;
    cout << "mass :" << K.mass() << endl;
    cout << "momentum :" << K.momentum() << endl;

    K.cal_mom_vec();
    cout << norm(K.mom_vec) << endl;

    cout << " the dot product of : " << DotProduct(K.mom_vec,p.Rvector) << endl;

    double j[3] ={ 1, 1, 0};
    double *fo = new double;
    fo=CrossProduct(p.Rvector,j);
    Display_Vector(fo,3);

    delete fo;


	Matrix mh;
	mh.setDimension(5,3);

    double a[3]={4,5,6};
	mh.set_row(1,a);
	mh.Display();

    Matrix h;
    h.setDimension(3,3);


	double *g =new double;
	g = MatrixProduct(3,h.Mat,j);
	Display_Vector(j,3);
	Display_Vector(g,3);
    delete g;
	return 0;
}
