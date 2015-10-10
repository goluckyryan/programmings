#include <iostream>
#include <cmath>

using namespace std;

double pi=3.14159;
 
double mag (double x,double y)
{
    double c;
    c=sqrt(x*x+y*y);
    return c;
}

double Arg (double x, double y)
{
    return atan(y/x)*180/pi;
}

double pointsincircle(double r)
{
    double points;
    points = floor(pi*r*r);
    return points;
}

int main()
{
    double a,b;
    cout<<" x coordinate \t: ";
    cin>>a;
    cout<<" y coordinate \t: ";
    cin>>b;
    cin.ignore();
    cout<<"------------- \n Amp \t\t: " << mag(a,b) << endl;
    cout<<" angle \t\t: " << Arg(a,b)<<endl;
    cout<<" point insides \t: "<<pointsincircle (mag(a,b))<<endl;
    cin.get();

    return 0;
}