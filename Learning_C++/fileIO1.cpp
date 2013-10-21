#include <fstream>
#include <iostream>

using namespace std;

int main()
{
    string str;
    
    //Creates an instance of ofstream, and opens example.txt ( if example.txt not exist, it creates it )
    ofstream file1 ( "example.txt" );

    // ask for input to file
    cout<< " type something ? ";
    cin >> str;
    // Outputs to example.txt through a_file
    file1<< str;
    cout<< "saved into file example.txt.";


    // Close the file stream explicitly
    file1.close();
    //Opens for reading the file
    ifstream file2 ( "example.txt" );
    //Reads one string from the file
    file2>>str;
    //Should output 'this'
    cout<< "\n" << str <<"\n";
    cin.get();    // wait for a keypress
    // b_file is closed implicitly here
}
