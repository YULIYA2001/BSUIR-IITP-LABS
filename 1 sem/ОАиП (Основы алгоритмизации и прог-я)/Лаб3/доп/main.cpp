#include <iostream>
#include <math.h>
#include <conio.h>

using namespace std;

int main()
{
 setlocale (LC_ALL, "Russian");
 int k, a, b, c;
 for (k=100;k<=999;k+=1)
 {
    a=k/100;
    b=(k/10)%10;
    c=k%10;
 //расчет факториала для числа сотен
    int fa=1;
    if (a>1)
    for(int i=1;i<=a;i++)
    fa*=i;
    else if (a==1) fa=1;
  //расчет факториала для числа десятков
    int fb=1;
    if (b>1)
    for(int i=1;i<=b;i++)
    fb*=i;
    else if (b==1||b==0) fa=1;
  //расчет факториала для числа единиц
    int fc=1;
    if (c>1)
    for(int i=1;i<=c;i++)
    fc*=i;
    else if (c==1||a==0) fc=1;
    if (k==fa+fb+fc)
        cout<<k<<" можно представить в виде суммы факториалов цифр"<<endl;
 }
 getch();
 return 0;
}
