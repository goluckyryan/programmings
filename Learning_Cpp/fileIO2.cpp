#include <iostream> 
#include <fstream> 
using namespace std; 


int main()
{ 
    ifstream file_in; 
    ofstream file_out; 
    int count=0; 
    char next;
    
    file_in.open("ise0.dat");     // open the input file
    file_out.open("file2.dat");  // open the output file

    while(true)
    {	// loop for each line 
        while(true)
        { // loop to read each char on line
            
            file_in.get(next); 
            if(file_in.eof() || next== '\n')
            {
                break;
            }
            cout << next;
            file_out << next;
        } 
        count++; 
        cout << endl; 
        if(file_in.eof())
        {
            break;
        }
        file_out << endl;
    }
    file_in.close(); 
    file_out.close(); 
    cout << "Number of lines copied: " << count << endl;
}