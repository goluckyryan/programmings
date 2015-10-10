/********************************************** 
Fast Fourier Transform Code based on FFTW library

// read file and save into an array

/***********************************
do Fourier Transform and save in another array

//complie method
g++ FFTW.cpp -o FFTW.mac -lfftw3 -lm

/*********thing to improve**********
1) change to pointer for Fdata

*********************************************
Last update Sun Jun 10 16:48:43 2012 

********************************************/

#include "FFTWLibrary.h" // use the functions in FFTWFunctions.cpp


//main_________________________________________________________________________
int main(int argc, char *argv[])
{
	if(argc < 2) {
 		cout << endl << "Usage: ./FFTW filename start end Opt" << endl
			 	     << "     filename = file name (e.g. ise0.dat)" << endl
					 << "        start = the starting row " << endl
					 << "          end = the ending row " << endl
					 << "          Opt = (0 = real+img, 1 = Opt+angle) " << endl
					 << "   ** output as FT+filename.dat (e.g FTise0.dat)" << endl<<endl;
		exit(0);
    	}

    string filename = argv[1]; // file name as argv[1]
    int if_file_opened;
    int start   = atoi(argv[2]);
    int end     = atoi(argv[3]); // Start row for fourier transform, atoi() make char to int.
    int Opt     = atoi(argv[4]);
    int num_row = end-start+1; // number of row exist
    
    if_file_opened=Readfile(filename,1); // Read all data
    Extract(1, dcos); //extract all data point, 1 = 2nd columes
    Extract(2, dsin); //extract all data point, 2 = 3rd columes

    if (if_file_opened==1){
     
	// calculate the unit frequency________________________________________________
		double freq_unit;
		freq_unit=Frequency(data, start, end, 1);
        
	//Fourier Transform____________________________________________________________
    		Fourier(start, end, Opt, 1); 
      
	//shift data that the 0 at center______________________________________________ 
        	Shiftdata(Fdata,num_row);

	// Save Data___________________________________________________________________
        	Savefile("FT"+filename, freq_unit, num_row/2-50, num_row/2+49); //num_row/2-50,num_row/2+49);
        
        
    } else{
        cout << "Program aborb. due to no data was read!"<<endl;
        return 1;
    }
    
    return 0;
    
}

