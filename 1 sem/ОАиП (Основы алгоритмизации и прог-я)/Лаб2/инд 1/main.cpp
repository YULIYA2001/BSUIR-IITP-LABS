#include <iostream>
#include <conio.h>
#include <math.h>

using namespace std;

int main()
{
    int n;
    float a, b, y, x, f, z;

    cout<<"Select function 1-2x; 2-x^2; 3- x/3\n";
    cin>>n;
    switch(n)
    {
        case 1: f=2*x;cout<<"Your function f=2*x\n";break;
        case 2: f=x*x;cout<<"Your function f=x*x\n";break;
        case 3: f=x/3;cout<<"Your function f=x/3\n";break;
        default: cout<<"Function not selected\n"; return 0;
    }
    cout<<"Initial data: a=";
    cin>>a;
    cout<<"b=";
    cin>>b;
    cout<<"z=";
    cin>>z;
    x=z<0?z:sin(z);
    y=2*a*(sin(x)*sin(x))/3-3*b*(cos(f)*cos(f))/4;
    cout<<"y=(2a(sin(x))^2)/3-(3b(cos(f))^2)/4="<<y;
    getch();
    return 0;
}

