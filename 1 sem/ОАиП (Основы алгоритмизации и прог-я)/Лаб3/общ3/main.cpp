#include <iostream>
#include <math.h>
#include <conio.h>
#define M_PI 3.1415

using namespace std;

int main()
{
 int M=20, A=0;
 double x, y, H, B=M_PI/2;
 H=(B-A)/M;
 int i=1;
 for (x=0;x<=B;i++)
 {
     x=A+i*H;
     y=sin(x)-cos(x);
     cout<<"x="<<x<<"\ty="<<y<<endl;
 }
 getch();
 return 0;
}
