// Subtract data from a selected BG data

// read "iesX.dat" files and save into an array

// output the file name and FID area.

// load another file and do again. 



#include <iostream> // enable cin, cout
#include <sstream> // enable string control
#include <cmath> // math , enable simple math function
#include <stdlib.h> // standard General Utlilities Library
#include <fstream> // File I/O
#include <string> //string control

using namespace std; // declare a namespace "std", every variable in this code is inside "std"

int main(int argc, char *argv[]) //BGfilename num_file
{
	string BGfile=argv[1];
    int num_file=atoi(argv[2]); // number of file as argv[2]
    int start = 0, end=5000;
    double data[5000][6]; // raw data 0,1,2,....4998, 4999
	double BGdata[5000][6];
	
	ifstream file_BG;
	file_BG.open(BGfile.c_str());   
	if (file_BG.is_open()) {
		for (int i=0; i<5000; i++) {
			for (int j=0; j<6; j++) {
                file_BG >> BGdata[i][j];
            }
        }
		file_BG.close();
	} else {
		cout << "XXXX====connot open " << BGfile <<endl;
		return 0;
	}	
    
    char filename[50];
	char filename2[50];

    for (int i=0; i< num_file; i++) 
    {
        snprintf(filename,sizeof(filename),"ise%d.dat",i) ;
		snprintf(filename2,sizeof(filename2),"BGise%d.dat",i);
    
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
	ofstream file_out;
	file_out.open(filename2);
        
            for (int i=0; i<5000; i++) {
				for (int j = 0 ; j<6 ; j++) {
					if ( j != 1 && j !=2 && j!=4 && j!=5){
	                		file_out << data[i][j] << " ";
					}else{
						file_out << data[i][j]-BGdata[i][j] << " ";
					}
				}
				file_out << endl;
            }
			
			cout << "was substracted by " << BGfile << "| --> saved to BG" <<filename <<endl;
     		
			file_out.close(); 
        
        }else
        {
            cout << " ===XXX cannot open file : " <<filename  << "\n" ;
        }
    }

    
    return 0;
    
}
