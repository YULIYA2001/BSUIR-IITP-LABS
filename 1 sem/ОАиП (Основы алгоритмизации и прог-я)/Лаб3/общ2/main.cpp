#include <iostream>
#include <cmath>
#include <conio.h>

using namespace std;

int main()
{
 double d=0.0;
 int n=1;
 do
 {
  d+=pow(2,-n)+pow(3,-n);
  n+=1;
 }
 while ((pow(2,-n)+pow(3,-n))>0.001);
 cout<<"d="<<d<<endl;
 getch();
 return 0;
}
