#include <iostream>
#include <math.h>
#include <conio.h>

using namespace std;

void vvodX(double a[]);
void vivodY(double b[]);
void p(double a[], double b[]);

int main()
{
 setlocale(LC_ALL, "Russian");

 double *x, *y;
 x=new double[10];
 y=new double[10];
 cout<<"Вектор X:";
 vvodX (x);
 cout<<"Вектор Y:";
 vivodY (y);
 p(x, y);
 delete []x;
 delete []y;
 getch();
 return 0;
}

void vvodX(double a[])
{
    for (int i=0; i<10; i++)
    cin>>a[i];
}

void vivodY(double b[])
{
    for (int i=0; i<10; i++)
    {
     b[i]=0.1*tan(0.1*(i+1));
     cout<<b[i]<<"  ";
    }
}

void p(double a[], double b[])
{
    double pr=0;
    for (int i=0; i<10; i++)
    pr+=a[i]*b[i];
    cout<<"\nСкалярное произведение векторов X и Y = "<<pr;
}
