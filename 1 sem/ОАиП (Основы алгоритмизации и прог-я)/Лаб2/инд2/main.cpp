#include <iostream>
#include <conio.h>
#include <math.h>

using namespace std;

int main()
{

    float  y, x, s, p;
    cout<<"Initial data: x=";
    cin>>x;
    cout<<"y=";
    cin>>y;
    p=x*y;
    if (p>0.5&&p<10) {s=exp(x-fabs(y)); cout<<"s=e^(x-|y|)="<<s;}
    else {if (p>0.1&&p<0.5) {s=pow(fabs(x+y),(1./3)); cout<<"s=|x+y|^1/3="<<s;}
    else s=2*x*x; cout<<"s=2x*x="<<s;}
    getch();
    return 0;
}
