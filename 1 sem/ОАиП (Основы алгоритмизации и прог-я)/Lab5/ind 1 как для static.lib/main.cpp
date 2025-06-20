#include <iostream>
#include <math.h>
#include <conio.h>

using namespace std;

double p(double a[], double b[]);

int main()
{
 setlocale(LC_ALL, "Russian");

 double *x, *y;
 x=new double[10];
 y=new double[10];
 cout<<"Вектор X:";
 for (int i=0; i<10; i++)
    cin>>x[i];
 cout<<"Вектор Y:";
 for (int i=0; i<10; i++)
    {
     y[i]=0.1*tan(0.1*(i+1));
     cout<<y[i]<<"  ";
    }
 cout<<"\nСкалярное произведение векторов X и Y = "<<p(x, y);
 delete []x;
 delete []y;
 getch();
 return 0;
}

double p(double a[], double b[])
{
    double pr=0;
    for (int i=0; i<10; i++)
    pr+=a[i]*b[i];
    return pr;
}
