//read file and store in an array;

#include <iostream> 
#include <fstream> 
#include <string>
using namespace std; 


int main()
{ 
    double data[5000][6];
    ifstream file_in; 
    ofstream file_out; 
    int start, end, col;
    char filename[10];
    
    cout<< " File name to read : ";
    cin >> filename;
    
    file_in.open(filename);     // open the input file
    
    if (file_in.is_open())
    {
        cout << " --> "<< filename << " was opened. \n";
    }else
    {
        cout << "cannot open file : " <<filename  << "\n" ;
        return 0;
    }
    
    // read data and output to a file
    for (int i=0; i<5000; i++) {
        for (int j=0; j<6; j++) {
                file_in>> data[i][j];
        }
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
}