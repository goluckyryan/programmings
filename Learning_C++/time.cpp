#include <iostream> 
#include <time.h>
#include <sstream>
using namespace std;

int main()
{
	time_t tim;  //create variable of time_t
	time(&tim); //pass variable tim to time function 
	cout << ctime(&tim); // this translates what was returned from time() into a readable format
	string timestr;
	timestr = ctime(&tim);
	cout << timestr.c_str();
	timestr.erase(0,4);
	timestr.erase(20,22);
	cout << timestr;

	

	return 0;
}


