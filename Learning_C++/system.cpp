/* this show how to call system function */

#include <iostream>
#include <sstream> // for using string as a class
#include <cstdlib> // for using the system function

using namespace std;

int main(){

	string text;

	char *com = new char [80];

	cout << " command ? ";
	cin >> com;

	system(com); //using system function

	// system alias is not working

	//system("~/Dropbox/C++_programs/FFTW/FFTW.o ise0.dat 90 400 1");

	//system("gnuplot -e 'tdsN='0';out=0' -p ~/Dropbox/Expdata/plot_tds.gp");

	delete [] com;

	return 0;
}
