#include <iostream>
#include <conio.h>
#include <math.h>

using namespace std;

int main()
{
    float x1, x2, L;
    int m;
    cout<<"x1=";
    cin>>x1;
    cout<<"x2=";
    cin>>x2;
    cout<<"m=";
    cin>>m;
    float k=pow(cos(x1*x1),3)+pow(sin(x2*x2*x2),2);
    if (k<1) L=pow(k,3)+pow(m,0.2);
        else  L=k*k-exp(m);
    cout<<"L="<<L;

    getch();
    return 0;
}
