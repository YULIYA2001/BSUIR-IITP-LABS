#include <iostream>
#include <conio.h>
#include <math.h>

using namespace std;
int main()
{
 setlocale(LC_ALL, "Russian");
 unsigned N;
 int  k;
 cout<<"������� 0<N<20, ��������� ����� �����.\n"<<"N=";
 cin>>N;
 cout<<"������� k<80, ����������� �����.\n"<<"k=";
 cin>>k;
 N=N+k;
 int d1=N/10, d2=N%10;
 switch (d2)
 {case 1: if (d1!=1) cout<<"����� ����� N="<<N<<" �����";
        else cout<<"����� ����� N="<<N<<" ������";break;
  case 3:case 4:
  case 2: if (d1!=1) cout<<"����� ����� N="<<N<<" �����";
          else cout<<"����� ����� N="<<N<<" ������";break;
  default:  cout<<"����� ����� N="<<N<<" ������"; break;
 }
  getch ();
  return 0;
}



