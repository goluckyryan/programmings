/*****************************************
 Fast Fourier Transform Code based on FFTW library

// read file and save into an array

// do Fourier Transform and save in another array

//complie method
	 g++ BGFFTWA_batch.cpp -o BGFFTWA_batch.mac -lfftw3 -lm

// display in a graph

// thing to improve
	1) change to pointer for Fdata
	2) add Root compactable code so to draw graph
	3) change atan to atan2

*********************************************
Last updat 2012, Jan, 1st

*********************************************/

#include <iostream> // enable cin, cout
#include <sstream> // enable string control
#include <cmath> // math , enable simple math function
#include <complex>
#include <stdlib.h> // standard General Utlilities Library
#include <fftw3.h> // FFTW library
#include <fstream> // File I/O

using namespace std; // declare a namespace "std", every variable in this code is inside "std"
double data[5000][6]; // raw data 0,1,2,....4998, 4999
double dcos[5000], dsin[5000]; // the cosin and sine part of the raw data
double Fdata[5000][2]; // Fourier transformed data

//prototype
int extract(int col, double array[5000]); // extract cosine and sine part from data
int shiftdata (double array[][2], int num_row);//shift data 


int main(int argc, char *argv[])
{

	if(argc < 2) {
 		cout << endl << "Usage: ./BGFFTWA num_file start" << endl
			 	     << "     num_file = number of file " << endl
					 << "        start = the starting row " << endl
					 << "   ** only good for file name BGise##.dat " << endl
					 << "   ** out Put as AFTBGise##.dat" << endl << endl;
		exit(0);
    	}

    int num_file = atoi(argv[1]); // file name as argv[1]
    int if_file_opened;
    int start = atoi(argv[2]), end=4999; // Start row for fourier transform, atoi() make char to int.
    int num_row = end-start+1;; // number of row exist
    
    // an input complex array and output complex array
    fftw_complex *input, *out;
    
    // define the size of the array n X 2 *)
    out = (fftw_complex*) fftw_malloc((5000-start)*2*sizeof(fftw_complex));
    input = (fftw_complex*) fftw_malloc((5000-start)*2*sizeof(fftw_complex));
    
    //declare a plan from fftw_plan class
    fftw_plan p;
    
    p= fftw_plan_dft_1d((5000-start),input,out,FFTW_FORWARD,FFTW_ESTIMATE);
    
    char filename[50];
    
    cout << "filename| start(us)|    end(us)| interval(us)| Resol. (kHz)"<<endl;
    
    for (int z=0; z<= num_file; z++) 
    {
        snprintf(filename,sizeof(filename),"BGise%d.dat",z) ;
        
        ifstream file_in;
        file_in.open(filename); // Read all data
        
    
        if (file_in.is_open())
        {
            // read data and output to a file
            for (int i=0; i<5000; i++) {
                for (int j=0; j<6; j++) {
                    file_in >> data[i][j];
                }
            }
            file_in.close(); 
            cout << filename << "\t";
            
            extract(1, dcos); //extract all data point
            extract(2, dsin); //extract all data point
        
            // calculate the unit frequency
            double time_interval;
            double freq_unit;
        
            time_interval=(data[4999][0]-data[start][0])*1e6;
            freq_unit = 1/time_interval;
        
            cout<< data[start][0]*1e6 << "\t" << data[4999][0]*1e6 << "\t   ";
            cout<< time_interval << "\t";
            cout <<freq_unit*1000;
        
        //Fourier Transform
        
        
            // set the input array 
            for(int i=0;i<5000-start;i++) 
            {
                input[i][0]=dcos[i+start] ;
                input[i][1]=dsin[i+start] ;
            }
        
            // execute the tranform
            fftw_execute(p);
        
        // save the data into Fdata from 0 to (4999-start)
            for(int i=0;i<5000-start;i++)
            {
            		Fdata[i][0]=sqrt(out[i][0]*out[i][0]+out[i][1]*out[i][1]);
				if (out[i][0] < 0 && out[i][1] < 0){
            			Fdata[i][1]=atan(out[i][1]/out[i][0])-acos(-1);
				} else if (out[i][0] <0 && out[i][0] > 0) {
					Fdata[i][1]=atan(out[i][1]/out[i][0])+acos(-1);
				}else{
				Fdata[i][1]=atan(out[i][1]/out[i][0]);
			}
            // cout << i <<"\t"<< out[i][0] << "\t" << out[i][1] <<endl;
            }
        
        //Fourier Transform end
        
            shiftdata(Fdata,num_row);
                    
            ofstream file_out;
            snprintf(filename,sizeof(filename),"AFTBGise%d.dat",z);
            file_out.open(filename);     // open the output file
            
            // read data and output to a file
            for (int i=num_row/2-50; i<num_row/2+50; i++) {
                //file_out << i << " ";
                file_out << (i-(num_row/2-50+1+num_row/2+49)/2)*freq_unit << "\t";
                file_out << Fdata[i][0]<< "\t";
                file_out << Fdata[i][1]<<endl;
                // cout<< sqrt(Fdata[i][1]*Fdata[i][1]+Fdata[i][0]*Fdata[i][0]) << endl;
            }
            file_out.close(); 
            cout << " --> "<< filename <<" was saved \n";
        
        
        } else
        {
            cout << " ===XXX cannot open file : " <<filename  << "\n" ;
        }
    }
    
    
    fftw_destroy_plan(p);
    delete [] input;
    delete [] out;
    
    return 0;
    
}


int extract(int col, double array[5000])
{
    for (int i=0; i<5000; i++) {
        array[i]=data[i][col];
    }
    
    //cout<< " --- extracted col " << col << endl;
    
    return 0;
    
}

int shiftdata (double array[][2], int num_row)
{
    double temp[5000][2];
    
    for (int i =0 ; i < num_row; i++){
        temp[i][0]=array[(i+num_row/2)%num_row][0];
        temp[i][1]=array[(i+num_row/2)%num_row][1];
    }
    
    for (int i =0 ; i < num_row; i++){
        array[i][0]=temp[i][0];
        array[i][1]=temp[i][1];
    }
}
