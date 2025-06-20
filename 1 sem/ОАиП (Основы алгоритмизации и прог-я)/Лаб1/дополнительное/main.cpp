#include <iostream>
#include <conio.h>
#include <math.h>
using namespace std;

int main()
{
    int x,y,x1,y1,x2,y2;
    float a,b,c;
    cout<<"x=";
    cin>>x;
    cout<<"y=";
    cin>>y;

     cout<<"x1=";
    cin>>x1;
    cout<<"y1=";
    cin>>y1;

     cout<<"x2=";
    cin>>x2;
    cout<<"y2=";
    cin>>y2;

    a=sqrt((x-x1)*(x-x1)+(y-y1)*(y-y1));
    cout <<"\na="  << a;

    b=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
    cout <<"\nb="  << b;

    c=sqrt((x2-x)*(x2-x)+(y2-y)*(y2-y));
cout <<"\nc="  << c;

    float P=a+b+c;
    cout <<"\nP="  << P;
    float S=sqrt (P/2*(P/2-a)*(P/2-b)*(P/2-c));
    cout <<"\nS="  << S;

    if (S==0) cout<<"";

    getch();
    return 0;
}
