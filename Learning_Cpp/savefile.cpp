//read file and store in an array;

#include <iostream> 
#include <fstream> 
using namespace std; 


int main()
{ 
    double data[5000][6];
    ifstream file_in; 
    ofstream file_out; 
    int start, end, col;
    
    file_in.open("ise7.dat");     // open the input file
    file_out.open("file1.dat");  // open the output file
    
    // read data and output to a file
    for (int i=0; i<5000; i++) {
        for (int j=0; j<6; j++) {
                file_in>> data[i][j];
                file_out<< data[i][j]<< "\t";
        }
        file_out<< endl;
    }
    
    cout<< " ==== Display ==== " << "\n" << " col \t: ";
    cin>> col;
    cout<< " start row\t: ";
    cin>> start;
    cout<< " end row\t: ";
    cin>> end;
    
    for (int i=start-1; i<end; i++) {
        cout<< data[i][col-1] <<"\n";
    }
    
    file_in.close(); 
    file_out.close(); 
}