#include <iostream>
#include <conio.h>
#include <math.h>
using namespace std;

int main()
{
    float x,y,K,C;
    cout<<"x=";
    cin>>x;
    cout<<"y=";
    cin>>y;
    cout<<"K=";
    cin>>K;
    cout<<"C=";
    cin>>C;
    float A=x+y;
    cout <<"A="  << A;
    float D=fabs(C-A);
    cout <<"\nD="  << D;
    const float S=10.1+A/C+D/(K*K);
    cout <<"\nS="  << S;
    getch();
    return 0;
}

