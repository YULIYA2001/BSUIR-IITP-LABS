#include <iostream>
#include <math.h>
#include <conio.h>
#include <iomanip> // ��� std::setprecision()


using namespace std;

int main()
{
 setlocale (LC_ALL, "Russian");
 cout<<setprecision(8); // ����� �������� � 8 ����
 int n, k;
 double x,y,s=0;
 cout<<"������� ���������� ������ ���� (n>0) n=";
 cin>>n;
 cout<<"������� ���������� ����� �� ������� ������� ������� k=";
 cin>>k;
  //������ � ������� ����
   cout<<"������� "<<k<<" ���������� x\n";
   for (int i=1;i<=k;i++)
 {
   cout<<"�������  ���������� (0,1<=x<=1) x=";
   cin>>x;
   int a=1;
   double s=0;
   while (a<=n)
   {
    int factorial=1, b;
    for (b=1;b<=2*a-1;b++)
         factorial*=b;
    s+=pow(x,2*a-1)/factorial;
    a+=1;
   }
   //������ � ������� �������
   y=(exp(x)-exp(-x))/2;
   cout<<"\nS(x)="<<s<<"\tY(x)="<<y<<endl;
 }
 getch();
 return 0;
}
