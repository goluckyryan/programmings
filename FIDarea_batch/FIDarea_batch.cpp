/**** Calculate the FID area in batch

 command:

$ ./FIDarea_batch.mac [num_file] [start_row] [end_row]

// read "iesX.dat" files and save into an array

// calculate the FID area from array ( FIDarea=Sqrt( ch1^2+ch2^2))

// output the file name and FID area.

// load another file and do again. */



#include <iostream> // enable cin, cout
#include <sstream> // enable string control
#include <cmath> // math , enable simple math function
#include <stdlib.h> // standard General Utlilities Library
#include <fstream> // File I/O
#include <string> //string control

using namespace std; // declare a namespace "std", every variable in this code is inside "std"

int main(int argc, char *argv[])
{
    int num_file=atoi(argv[1]); // number of file as argv[2]
    int start = atoi(argv[2]), end=atoi(argv[3]); // Start row for calculation, atoi() make char to int.
    int num_row = end-start+1;; // number of row exist
    double data[5000][6]; // raw data 0,1,2,....4998, 4999
    double FIDarea;
    
    cout<< " number of row read " << num_row << endl;
    
    ofstream file_out;
    file_out.open("FID_summary.txt");     // open the output file
    
    file_out<< "filename \t FID area \t start time(us) \t end time(us) \t start row \t end row"<<endl;
    
    char filename[50];

    for (int i=0; i< num_file; i++) 
    {
        snprintf(filename,sizeof(filename),"ise%d.dat",i) ;
    
        ifstream file_in;
        file_in.open(filename); 
    
    
        if (file_in.is_open())
        {
            // read data and output to a file
            for (int i=0; i<5000; i++) {
                for (int j=0; j<6; j++) {
                    file_in >> data[i][j];
                }
            }
            file_in.close(); 
            cout << " --> "<< filename << "\t";
        
            for (int i=start; i<end+1; i++) {
                FIDarea = FIDarea + sqrt(data[i][1]*data[i][1] + data[i][2]*data[i][2]);
            }
        
            file_out << filename << "\t" << FIDarea << "\t\t"<< data[start][0]*1e6 << "\t"<< data[end][0]*1e6 << "\t\t"<< start << "\t" << end <<endl;

            cout << FIDarea << "\t\t"<< data[start][0]*1e6 << "\t"<< data[end][0]*1e6<<endl;
        
            FIDarea=0;
        
        }else
        {
            cout << " ===XXX cannot open file : " <<filename  << "\n" ;
        }
    }

    
    file_out.close(); 
    
    return 0;
    
}
