#include <iostream>
#include <math.h>
#include <iostream>
#include <math.h>
#include <conio.h>

using namespace std;

int main()
{
 setlocale (LC_ALL, "Russian");
 int n;
 double f, x, minf, minx=1;
 cout<<"�� ������� ������ ��������� ������� ������? n=";
 cin>>n;
 double shag;
 shag=(3.0-1)/n;
 f=acos(exp(-1))-2*sin(1);
 minf=fabs(f);
 for (x=1;x<=3;x+=shag)
 {
     cout<<"x="<<x;
     f=acos(exp(-x))-2*sin(x);
     cout<<"\tf="<<f<<endl;
     if (fabs(f)<minf)
        {
            minf=fabs(f);
            minx=x;
        }
 }
 cout<<"������������ ������ x="<<minx<<"\n������ ������� ������� ��� ���� f(x)="<<minf;
 getch();
 return 0;
}
