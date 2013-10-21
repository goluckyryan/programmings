// Sum data file

// read "iesX.dat" files and save into an array

// load another file and do again. 

// output as Sum.dat

//command

//sumdata [num_file]

#include <iostream> // enable cin, cout
#include <sstream> // enable string control
#include <cmath> // math , enable simple math function
#include <stdlib.h> // standard General Utlilities Library
#include <fstream> // File I/O
#include <string> //string control

using namespace std; // declare a namespace "std", every variable in this code is inside "std"

int main(int argc, char *argv[]) //BGfilename num_file
{
    int num_file=atoi(argv[1]); // number of file as argv[1]
    double data[5000][6]; // raw data 0,1,2,....4998, 4999
    double temp[5000][6];
    int read_file=0;
	
    
    // begin loop-reading files
    char filename[50];
	char filename2[50];

    for (int d=0; d< num_file; d++) 
    {
        snprintf(filename,sizeof(filename),"ise%d.dat",d) ;
    
        ifstream file_in;
        file_in.open(filename); 
    
    
        if (file_in.is_open())
        {
     	read_file++;   
        if (d==0){
        for (int i=0; i<5000; i++) {
            for (int j=0; j<6; j++) {
                    file_in >> data[i][j];
                   }
                   }
        }else {
            for (int i=0; i<5000; i++) {
                 for (int j=0; j<6; j++) {
                 	file_in >> temp[i][j];
                     if(j==1 || j==2 || j==4 || j == 5){
           		data[i][j]=data[i][j]+temp[i][j];
           		}

         	}
          }
        }
          
            
            file_in.close(); 
            cout << " --> "<< filename << "\t \n";
        
        }else
        {
            cout << " ===XXX cannot open file : " <<filename  << "\n" ;
        }
        
    }
    
    //begin output
    
   
	ofstream file_out;
	file_out.open("sumdata.dat");
        
            for (int i=0; i<5000; i++) {
				for (int j = 0 ; j<6 ; j++) {
	                	file_out << data[i][j] << "\t";
				}
				file_out << endl;
            }
     		
	file_out.close(); 
	
	cout << "**** " << read_file <<" file(s) were summed --> saved to sumdata.dat"<<endl;
	

    
    return 0;
    
}
