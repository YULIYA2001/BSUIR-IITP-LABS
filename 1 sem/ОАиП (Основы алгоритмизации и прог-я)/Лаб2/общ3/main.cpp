#include <iostream>
#include <conio.h>
#include <math.h>

using namespace std;

int main()
{
    float a, b, maxi;
    cout<<"a=";
    cin>>a;
    cout<<"b=";
    cin>>b;
    bool c=a>b;
    maxi=c?a:b;

    cout<<"max="<<maxi;

    getch();
    return 0;
}
