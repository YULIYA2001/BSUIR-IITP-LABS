#include <iostream>
#include <conio.h>
#include <math.h>

using namespace std;

int main()
{
    char zn;
    float A, B, d;
    m: cout<<"A=";
    cin>>A;
    cout<<"B=";
    cin>>B;
    cout<<"Input +, -, * or /.\nzn=";
    cin>>zn;
    switch(zn)
    {
        case '-': d=A-B;cout<<"d=A-B="<<d;break;
        case '*': d=A*B;cout<<"d=A*B="<<d;break;
        case '+': d=A+B;cout<<"d=A+B="<<d;break;
        case '/': d=A/B;cout<<"d=A/B="<<d;break;
        default: cout<<"Wrong input\n";

    }
    cout<<"\nIf you want to try again input y\n";
    char y;
    cin>>y;
    if (y=='y') goto m;
    else return 0;
    getch();
    return 0;
}
