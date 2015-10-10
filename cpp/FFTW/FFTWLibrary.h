/********************************************** 
Fast Fourier Transform Code based on FFTW library

this file store nessary function for running 
	- FFTW.cpp
	- FFTW_batch.cpp

it contains the core functions for fourier Transform

$$$ data file is 6 columes, 5000 rows. 


/*********thing to improve**********
1) change to pointer for Fdata
2) fftw3.h can not load

*********************************************
Last update Mon Jun 11 14:20:01 2012 , ryan

********************************************/

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


//prototype____________________________________________________________________
int Readfile(string filename); // read a file and store to data
void Extract(int col, double array[5000]); // extract cosine and sine part from data
double Frequency(double A[][6], int start, int end);
void Fourier(int start, int end, int Opt);
void Savefile(string filename, double freq_unit, int start, int end); // save file
int Shiftdata (double array[][2], int num_row);//shift data 
void BGsub (string bgfile, string filename);

int Display(double array[5000]); 
int Display2(double array[][6]);

//_____________________________________________________________________________
/*void Import2Root (string filename){
 	TTree *T = new TTree("data", "data");
	int entries = T->ReadFile(filename,"f:r:i");
	T->Draw("r:f");
}*/

int Readfile(string filename, int Opt)
{
    ifstream file_in;
    file_in.open(filename.c_str());     // open the input file, c_str() convert string to char 
    
    // Display file was opened or not
    if (file_in.is_open()){
        cout << " --> \033[0;34m"<< filename << "\033[0m was opened.";
    }else{
        cout << " ===XXX cannot open file : \033[0;31m" <<filename  << "\033[0m\n" ;
        return 0;
    }
    
    // read data and output to a file
    for (int i=0; i<5000; i++) {
        for (int j=0; j<3; j++) {
            file_in >> data[i][j];
        }
    }
    file_in.close(); 
    if (Opt == 1){
    	cout << " --> "<< filename << " was read and closed \n";
    }
    return 1;
}
//_____________________________________________________________________________
void Extract(int col, double array[5000])
{
    for (int i=0; i<5000; i++) {
        array[i]=data[i][col];
    }
    
    //cout<< " --- extracted col " << col << endl;

}
//_____________________________________________________________________________
double Frequency(double A[][6], int start, int end, int Opt){
	double time_interval;
	double freq_unit;

    time_interval=(A[end][0]-A[start][0])*1e6; //in us unit
    freq_unit = 1/time_interval; // in MHz
    
    if (Opt == 1){    
    	cout<<  "                start time  = " << A[start][0]*1e6 << " us" << endl;
    	cout<<  "                 stop time  = " << A[end][0]*1e6 << " us" << endl;
    	cout<<  "              time interval = "<< time_interval << " us"<< endl;
    	cout << "       freqeuncy resolution = \033[0;34m" << freq_unit*1000 << " \033[0m kHz"<< endl;
    }
	return freq_unit;
}
//_____________________________________________________________________________
void Fourier(int start, int end, int Opt, int Opt2){
  		// an input complex array and output complex array
        fftw_complex *input, *out;
    
        // define the size of the array n X 2 *)
        out = (fftw_complex*) fftw_malloc((end-start+1)*2*sizeof(fftw_complex));
        input = (fftw_complex*) fftw_malloc((end-start+1)*2*sizeof(fftw_complex));
    
        // set the input array 
        for(int i=0;i<=end-start;i++) 
        {
            input[i][0]=dcos[i+start] ;
            input[i][1]=dsin[i+start] ;
        }
        
    
        //declare a plan
        fftw_plan p;
    
        p= fftw_plan_dft_1d((end-start+1),input,out,FFTW_FORWARD,FFTW_ESTIMATE);
        
        // execute the tranform
        fftw_execute(p);
    
		if (Opt==0){
        // save the data into Fdata from 0 to (4999-start)
        		for(int i=0;i<=end-start;i++)
        		{
            		Fdata[i][0]=out[i][0];
            		Fdata[i][1]=out[i][1];
            		// cout << i <<"\t"<< out[i][0] << "\t" << out[i][1] <<endl;
        		}
		}else if(Opt==1){
			for(int i=0;i<=end-start;i++)
        		{
            		Fdata[i][0]=sqrt(out[i][0]*out[i][0]+out[i][1]*out[i][1]);
				// set the angle in range -pi to pi
            		Fdata[i][1]=atan2(out[i][1],out[i][0]);
            		// cout << i <<"\t"<< out[i][0] << "\t" << out[i][1] <<endl;
        		}
		}	
    
        fftw_destroy_plan(p);
        delete [] input;
        delete [] out;
    	
    	if (Opt2 == 1) cout<< " *****Fourier Transform is done! ";
        //Fourier Transform end
}

//_____________________________________________________________________________
int Shiftdata (double array[][2], int num_row)
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
//_____________________________________________________________________________
void Savefile(string filename, double freq_unit, int start, int end)
{
    ofstream file_out;
    file_out.open(filename.c_str());     // open the output file
    
    // read data and output to a file
    for (int i=start; i<end+1; i++) {
        //file_out << i << " ";
        file_out << (i-(end+1+start)/2)*freq_unit << " ";
        for (int j=0; j<2; j++) {
            file_out << Fdata[i][j] << " ";
        }
        file_out<<endl;
    }
    file_out.close(); 
    
    cout << " --> \033[0;34m"<< filename <<"\033[0m \n";
}
//_____________________________________________________________________________
void BGsub (string bgfile, string filename, int Opt){

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
		cout << " XXXX====connot open " << BGfile <<endl;
		return 0;
	}	
	
    
        ifstream file_in;
        file_in.open(filename); 
    
    
        if (file_in.is_open()){
            // read data and output to a file
            for (int i=0; i<5000; i++) {
                for (int j=0; j<6; j++) {
                    file_in >> data[i][j];
                }
            }
            file_in.close(); 
            cout << " --> "<< filename << "\t";
            
            if (Opt ==1 ){
	    	ofstream file_out;
	    	file_out.open("BG"+filename);
        
            	for (int i=0; i<5000; i++) {
		    for (int j = 0 ; j<6 ; j++) {
			if ( j != 1 && j !=2 && j!=4 && j!=5){ //if the columes are time, not substract
	                	file_out << data[i][j] << " ";
			}else{
				file_out << data[i][j]-BGdata[i][j] << " ";
			}
		    }
		    file_out << endl;
                }
			
	        cout << "was substracted by " << BGfile << "| --> saved to BG" <<filename <<endl;
     		
	        file_out.close(); 
            }else{
            
            	for (int i=0; i<5000; i++) {
		    for (int j = 0 ; j<6 ; j++) {
			if ( j == 1 || j ==2 || j==4 || j==5){ //if the columes are time, not substract
				data[i][j] = data[i][j]-BGdata[i][j] << " ";
			}
		    }
                }
            
            }
        }else{
            cout << " ===XXX cannot open file : " <<filename  << "\n" ;
        }

}

//_____________________________________________________________________________
int Display(double array[5000])
{
    int start, end;
    cout<< " ==== Display ==== " << "\n" ;
    cout<< " start row\t: ";
    cin>> start;
    cout<< " end row\t: ";
    cin>> end;
    
    for (int i=start-1; i<end; i++) {
        cout<< array[i] <<"\n";
    }
    
    cout<< " ==== End Display ===="<<endl;
    
    return 0;
}
int Display2(double array[][6])
{
    int col, start, end;
    cout<< " ==== Display ==== " << "\n" << " col \t: ";
    cin>> col;
    cout<< " start row\t: ";
    cin>> start;
    cout<< " end row\t: ";
    cin>> end;
    
    for (int i=start-1; i<end; i++) {
        cout<< array[i][col-1] <<"\n";
    }
    
    cout<< " ==== End Display ===="<<endl;
    
    return 0;
}


