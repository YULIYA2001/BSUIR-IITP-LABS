#include <iostream>
#include <conio.h>
#include <math.h>

using namespace std;

int main()
{
    float A, B, C;
    cout<<"A=";
    cin>>A;
    cout<<"B=";
    cin>>B;
    cout<<"C=";
    cin>>C;
    if (A>B&&A>C) A-=0.3;
        else if (B>C) B-=0.3;
        else C-=0.3;
    cout<<"A="<<A<<"\nB="<<B<<"\nC="<<C;
    getch();
    return 0;
}
