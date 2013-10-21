/********************************************** 
Fast Fourier Transform Code based on FFTW library

This program is form FFT in batch, i.e. many file as once

/***********************************
do Fourier Transform and save in another array

//complie method
	g++ FFTW.cpp -o FFTW.mac -I$FFTW3_dir/include -lfftw3 -lm
	//or
	g++ FFTW_batch.cpp -o FFTW_batch.mac -lfftw3 -lm

/*********thing to improve**********
1) change to pointer for Fdata
2) using FFTWLibrary.cpp as library

*********************************************
Last updat 2012, Jan, 1st

********************************************/

#include "FFTWLibrary.h"
#include <string>


int main(int argc, char *argv[])
{

	if(argc < 2) {
 		cout << endl << "Usage: ./FFTW_batch.o num_file start end Opt" << endl
			 	     << "     num_file = number of file" << endl
					 << "        start = the starting row " << endl
					 << "          end = the ending row " << endl
					 << "          Opt = (0 = real+img, 1 = Opt+angle) " << endl
					 << "   ** output as FT+filename.dat (e.g FTise0.dat)" << endl<<endl;
		exit(0);
    	}


    int num_file = atoi(argv[1]); // file name as argv[1]
    int if_file_opened;
    int start = atoi(argv[2]);
    int end=atoi(argv[3]); // Start row for fourier transform, atoi() make char to int.
    int Opt = atoi(argv[4]);
    int num_row = end-start+1;; // number of row exist
    
    char filename[50];
    
    for (int z=0; z<= num_file; z++) 
    {
        snprintf(filename,sizeof(filename),"ise%d.dat",z) ;
        
        if_file_opened=Readfile(filename,0); // Read all data
    	Extract(1, dcos); //extract all data point, 1 = 2nd columes
    	Extract(2, dsin); //extract all data point, 2 = 3rd columes

    	if (if_file_opened==1){
     
		// calculate the unit frequency________________________________________________
		double freq_unit;
		freq_unit=Frequency(data, start, end, 0);
        
		//Fourier Transform____________________________________________________________
    		Fourier(start, end, Opt, 0); 
      
		//shift data that the 0 at center______________________________________________ 
        	Shiftdata(Fdata,num_row);

		// Save Data___________________________________________________________________
		snprintf(filename,sizeof(filename),"FTise%d.dat",z) ;
        	Savefile(filename, freq_unit, num_row/2-50, num_row/2+49); //num_row/2-50,num_row/2+49);
        
        } 
    }
    
    return 0;
    
}
