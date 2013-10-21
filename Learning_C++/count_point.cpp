/******************************
 to find out how many integer point in a circle of given radius

 the method is bull force counting.

 by looping from
 (0,0),
 (1,0), ....(1,y),
 (1,1), (2,1), ...,
 (1,2), (2,2), ...,
 (1,3),.....
 ....

 ******************************/

#include <iostream>
#include <cmath>

using namespace std;

const double pi=3.14159;

double radius ( double x, double y, double z)
{
    return sqrt(x*x+y*y+z*z);
}

double vol (double r)
{
    return 4*pi*r*r*r/3;
}

double area (double r)
{
    return 2*pi*r*r;
}

double max (double x, double y, double z)
{
    if (x>=y && x >= z)
        return x;
    else if (y>=x && y>=z)
        return y;
    else
        return z;

}


double loopcount (double r)
{
    double points = 0;
    double length;

    int i=0;
    int j=0;

    double m=floor(r);

    for (i=-m ; i <= m; i++) {
        for (j=-m ; j<=m ; j++) {
            length=radius(i,j,0);
            if (length <= r )
            {
                points = points+1;
                //cout<<"\t(" << i << "\t, "<<j <<" \t) length : "<<length <<" \n";
            }

        }
    }

    return points;
}

double loopcount3D (double r)
{
    double points = 0;
    double length;

    int i=0;
    int j=0;
    int k=0;

    double m=floor(r);

    for (i=-m ; i <= m; i++) {
        for (j=-m ; j<=m ; j++) {
            for (k=-m;k<=m;k++) {
                length=radius(i,j,k);
                if (length <= r )
                {
                    points = points+1;
                    //cout<<"\t(" << i << "\t, "<<j <<" \t) length : "<<length <<" \n";
                }
            }

        }
    }

    return points;
}

int main()
{
    double a;
    int n,m;
    cout<<"=================================\n";
    cout<<" set 2D(1) or 3D(2) ? ";
    cin>> n;

    do {
        if (n ==2)
        {
            cout<<" \n Radius of the Sphere = ";
            cin>>a;
            cout<<"------------------------ \n";
            cout<<"\t point insides \t: " << loopcount3D(a) << " ,point/vol: "<< loopcount3D(a)/vol(a) <<endl<<endl;
        }else if (n ==1)
        {
            cout<<" Radius of the circle = ";
            cin>>a;
            cout<<"------------------------ \n";
            cout<<"\t point insides \t: " << loopcount(a) << " ,point/area: "<< loopcount3D(a)/area(a) <<endl<<endl;
        }
        cout<<"  again ? (1=2D, 2=3D, 0=exist ) ";
        cin>>m;
        n=m;
        cout<<endl;
    }while (m!=0) ;

    return 0;
}
