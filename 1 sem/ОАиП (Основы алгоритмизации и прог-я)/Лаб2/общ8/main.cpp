#include <iostream>
#include <conio.h>
#include <math.h>

using namespace std;
int main()
{
 setlocale(LC_ALL, "Russian");
 unsigned N;
 int  k;
 cout<<"Введите 0<N<20, начальную сумму денег.\n"<<"N=";
 cin>>N;
 cout<<"Введите k<80, добавляемую сумму.\n"<<"k=";
 cin>>k;
 N=N+k;
 int d1=N/10, d2=N%10;
 switch (d2)
 {case 1: if (d1!=1) cout<<"Новая сумма N="<<N<<" рубль";
        else cout<<"Новая сумма N="<<N<<" рублей";break;
  case 3:case 4:
  case 2: if (d1!=1) cout<<"Новая сумма N="<<N<<" рубля";
          else cout<<"Новая сумма N="<<N<<" рублей";break;
  default:  cout<<"Новая сумма N="<<N<<" рублей"; break;
 }
  getch ();
  return 0;
}



