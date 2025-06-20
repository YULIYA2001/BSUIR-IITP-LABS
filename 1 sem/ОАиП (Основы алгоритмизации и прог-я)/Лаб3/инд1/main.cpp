#include <iostream>
#include <math.h>
#include <conio.h>
#include <iomanip> // дл€ std::setprecision()


using namespace std;

int main()
{
 setlocale (LC_ALL, "Russian");
 cout<<setprecision(8); // задаЄм точность в 8 цифр
 int n, k;
 double x,y,s=0;
 cout<<"¬ведите количество членов р€да (n>0) n=";
 cin>>n;
 cout<<"¬ведите количество чисел от которых считать функцию k=";
 cin>>k;
  //расчет с помощью р€да
   cout<<"¬ведите "<<k<<" переменных x\n";
   for (int i=1;i<=k;i++)
 {
   cout<<"¬ведите  переменную (0,1<=x<=1) x=";
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
   //расчет с помощью функции
   y=(exp(x)-exp(-x))/2;
   cout<<"\nS(x)="<<s<<"\tY(x)="<<y<<endl;
 }
 getch();
 return 0;
}
