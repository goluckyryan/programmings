// Trim the data file to only cosin and size file

#include <iostream> // enable cin, cout
#include <sstream> // enable string control
#include <cmath> // math , enable simple math function
#include <complex>
#include <stdlib.h> // standard General Utlilities Library
#include <fftw3.h> // FFTW library
#include <fstream> // File I/O

using namespace std; // declare a namespace "std", every variable in this code is inside "std"

//prototype
int readfile(string filename, int start, int end); // read a file and store to data
int extract(int col, double array[5000]); // extract cosine and sine part from data
int savefile(string filename); // save file


int main()
{
    string filename; // file name
    
    double data[5000][6]; // raw data 0,1,2,....4998, 4999
    double Tdata[5000][2]; // Fourier transformed data


    cout<< " File name to read : ";
    cin >> filename;
    
// Read File
    
    ifstream file_in;
    file_in.open(filename.c_str());     // open the input file
    
    // Display file was opened or not
    if (file_in.is_open())
    {
        cout << " --> "<< filename << " was opened. \n";
    }else
    {
        cout << " ===XXX cannot open file : " <<filename  << "\n" ;
        return 0;
    }
    
    // read data and output to a file
    for (int i=0; i<5000; i++) {
        for (int j=0; j<6; j++) {
            file_in >> data[i][j];
        }
    }
    
    file_in.close(); 
    cout << " --> "<< filename << " was readed and closed \n";
    
// Trim data to Tdata
    for (int i=0; i<5000; i++) {
        Tdata[i][0]=data[i][1];
        Tdata[i][1]=data[i][2];
    }
    
// Save to 
        
    ofstream file_out;
    file_out.open((filename+"Trim").c_str());     // open the output file
    
    // read data and output to a file
    for (int i=0; i<5000; i++) {
        // file_out << i << " ";
        for (int j=0; j<2; j++) {
            file_out << Tdata[i][j] << " ";
        }
        file_out<<endl;
    }
    file_out.close(); 
    cout << " --> "<< filename <<"Trim was saved \n";

    
}