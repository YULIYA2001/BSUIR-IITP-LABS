#include <iostream>
#include <math.h>
#include <conio.h>

using namespace std;

int main()
{
 setlocale (LC_ALL, "Russian");
 double x=3, f;
 while (x<=4.1)
 {
    cout<<"x="<<x;
    f=1.0/(1+(exp(-x)));
    cout<<"\tf="<<f<<endl;
    x+=0.2;
 }
 getch();
 return 0;
}
