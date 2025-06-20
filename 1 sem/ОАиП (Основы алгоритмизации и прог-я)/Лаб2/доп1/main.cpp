#include <iostream>
#include <conio.h>
#include <math.h>

using namespace std;
int main()
{
 setlocale(LC_ALL, "Russian");
 unsigned M;
 int  k;
 double y;
 cout<<"¬ведите четырехзначное число k.\n"<<"k=";
 cin>>k;
 int m1=k/1000, m2=k%10;
 M=m1+m2;
 switch (M)
 {case 3:case 5: y=tan(k)*tan(k)+sin(k)*sin(k)/2.7; cout<<"y="<<y;break;
  case 7:case 8:case 9: y=log(fabs(k-6)); cout<<"y="<<y;break;
  case 10:y=exp(0.2*k); cout<<"y="<<y;break;
  default:y=k*sin(k*k); cout<<"y="<<y;break;
 }
  getch ();
  return 0;
}
