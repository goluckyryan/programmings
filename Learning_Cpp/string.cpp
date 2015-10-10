#include <iostream>
#include <string> //
#include <sstream>

using namespace std;

int main()
{

    string a="ise7.dat";

    cout<< a << endl;

    string FT="FT";

    //cout<< a.end();


    cout<< a.insert(4,FT) <<endl;




    /*
  string mystr;
  float price=0;
  int quantity=0;

  cout << "Enter price: ";
  getline (cin,mystr);
  stringstream(mystr) >> price;
  cout << "Enter quantity: ";
  getline (cin,mystr);
  stringstream(mystr) >> quantity;
  cout << "Total price: " << price*quantity << endl;
  cout << mystr;
     */
  return 0;
}
