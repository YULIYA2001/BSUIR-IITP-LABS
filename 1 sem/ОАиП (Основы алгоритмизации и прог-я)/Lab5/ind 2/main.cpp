#include <iostream>
#include <math.h>
#include <conio.h>
#include <windows.h>
#include <ctime>


using namespace std;

double sum(int b[], int l, int r);
int main()
{
 setlocale(LC_ALL, "Russian");
 int n;
 cout<<"������� ���������� ��������� ������� (n>0):";
 cin>>n;
 if (n<=0) {cout<<"�� ����� "<<n<<"<=0. ��������� ��������� �����";return 0;}
 int *b;
 b=new int[n];
 cout<<"������ B: ";
 srand(time(NULL));
 for (int i=0; i<n; i++)
    {
       b[i] = (1+rand()%6);
       cout<<b[i]<<"  ";
    }
cout<<endl<<"����� ��������� �����: "<<sum(b, 0, n-1)<<endl;
    delete []b;
 getch();
 return 0;
}
//����������� ����� ��������� ��� ������ �� ������� ������� (��������� � �������������� ����������)
double sum(int *b, int l, int r)
{
    int raz=r-l;
    if (l==r)
        return (sin(b[l])*cos(b[l]));
    else
        return (sum(b, l, l+raz/2)+sum(b, l+raz/2+1, r));
}


