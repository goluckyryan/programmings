/* this demonstrate

1) the use of pointer as dynamic array

2) passing this dynamic array into a function

*/




#include <iostream>

using namespace std;


int main() {


	double *p = new double [2];

    p[0]=1;
    p[1]=2;

    cout << p[0] << "\t" << p[1] << "\t" << p[2] << endl;

	delete [] p;



	return 0;

}
