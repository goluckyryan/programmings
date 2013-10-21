#include <iostream>
#include <cmath>

using namespace std;

double pi=3.14159;
 
int fib(int n)
{
    int product;
    if (n <= 0)
    {
        return 0;
    }else if (n == 1 )
    {
        return 1;
    }

    product = fib(n-1)+fib(n-2);
    
    return product;
}

int main()
{
    int number;
    cout<<" enter a number \t: ";
    cin>> number;
    cout<<" the " << number <<" Fibonacci number is \t: ";
    cout<< fib(number)<<endl;
    cin.get();

    return 0;
}