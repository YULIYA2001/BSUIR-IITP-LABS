#include <iostream>
#include <math.h>
#include <conio.h>

using namespace std;

void I1(double a, double b, long int n, int numb);
double func1(double x, int numb);
void I2(double a, double b, long int n, int numb);
void I3(double a, double b, long int n, int numb);
void I4(double a, double b, long int n, int numb);

int main()
{
 setlocale(LC_ALL, "Russian");
 double a, b, a1=1.3, b1=2.5, a2=0.4, b2=0.8, a3=0.4, b3=1.2, a4=0.8, b4=1.2;
 long int n;
 cout<<"На сколько частей разбить отрезок? n:";
 cin>>n;
 cout<<"Выберите функцию (1, 2, 3 или 4): ";
 int numb;
 cin>>numb;


 switch(numb)
 {
 case 1: {a=a1; b=b1; break;}
 case 2: {a=a2; b=b2; break;}
 case 3: {a=a3; b=b3; break;}
 case 4: {a=a4; b=b4; break;}
 }
 void (*In[4])(double, double, long int, int)={I1, I2, I3, I4};
 int length = sizeof(In)/sizeof(In[0]);
      for(int i=0; i<length; i++)
    {
        In[i](a, b, n, numb);
    }

 getch();
 return 0;
}

 double func(double x, int numb)
 {
  double f;
  switch(numb)
  {
  case 1: f=(sqrt(x*x+0.6))/(1.4+sqrt(0.8*x*x+1.3)); break;
  case 2: f=(cos(x*x+0.6))/(0.7+sin(0.8*x+1)); break;
  case 3: f=1/(sqrt(2+0.5*x*x)); break;
  case 4: f=(sin(2*x))/(x*x); break;
  }
  return f;
 }

 void I1(double a, double b, long int n, int numb)
 {
  double h,I, s=0;
  h=(b-a)/n;
  for (int i=0; i<n; i++)
    s+=func(a+i*h,numb);
  I=h*s;
  cout<<"1.Метод левых прямоугольников:       "<<I<<endl;
 }

 void I2(double a, double b, long int n, int numb)
 {
  double h,I, s=0;
  h=(b-a)/n;
  for (int i=1; i<=n; i++)
    s+=func(a+i*h, numb);
  I=h*s;
  cout<<"2.Метод правых прямоугольников:      "<<I<<endl;
 }

 void I3(double a, double b, long int n, int numb)
 {
  double h,I, s=0;
  h=(b-a)/n;
  for (int i=0; i<n; i++)
    s+=func(a+i*h+h/2, numb);
  I=h*s;
  cout<<"3.Метод центральных прямоугольников: "<<I<<endl;
 }

 void I4(double a, double b, long int n, int numb)
 {
  double h,I,s=0;
  h=(b-a)/n;
  for (int i=1; i<n; i++)
    s+=func(a+i*h, numb);
  I=h*((func(a+0*h, numb)+func(a+n*h, numb))/2+s);
  cout<<"4.Метод трапеций:                    "<<I<<endl;
 }
