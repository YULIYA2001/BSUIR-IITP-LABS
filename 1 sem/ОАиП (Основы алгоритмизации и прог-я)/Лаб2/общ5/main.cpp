#include <iostream>
#include <conio.h>
#include <math.h>

using namespace std;

int main()
{
    float a, b, c, d, Z;
    cout<<"a=";
    cin>>a;
    cout<<"b=";
    cin>>b;
    cout<<"c=";
    cin>>c;
    cout<<"d=";
    cin>>d;
    if (c>=d&&a<d) Z=a+b/c;
        else if (c<d&&a>=d)  Z=a-b/c;
        else Z=0;
    cout<<"Z="<<Z;

    getch();
    return 0;
}
