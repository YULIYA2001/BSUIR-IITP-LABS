#include <iostream>
#include <conio.h>
#include <math.h>

using namespace std;

int main()
{
    float a, b, c, Y;
    int N;
    cout<<"a=";
    cin>>a;
    cout<<"b=";
    cin>>b;
    cout<<"c=";
    cin>>c;
    cout<<"N=";
    cin>>N;
    switch(N)
    {
     case 2: Y=b*c-a*a; break;
     case 56: Y=b*c; break;
     case 7: Y=a*a+c; break;
     case 3: Y=a-b*c; break;
     default: Y=pow((a+b),3);
    }
    cout<<"Y="<<Y;

    getch();
    return 0;
}
