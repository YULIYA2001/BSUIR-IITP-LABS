#include <iostream>
#include <conio.h>
#include <math.h>

using namespace std;

int main()
{
    int X, Y;
    cout<<"X=";
    cin>>X;
    cout<<"Y=";
    cin>>Y;
    if (X<Y) X=0;
        else if (X>Y) Y=0;
        else X=Y=0;
    cout<<"X="<<X<<"\nY="<<Y;

    getch();
    return 0;
}
