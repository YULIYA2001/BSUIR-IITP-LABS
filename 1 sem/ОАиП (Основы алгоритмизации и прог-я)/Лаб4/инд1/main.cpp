#include <iostream>
#include <math.h>
#include <conio.h>

using namespace std;

int main()
{
 setlocale (LC_ALL, "Russian");
 //����� ������� �������, ���������� � ����������
 cout<<"���������� ����� ������� �����:";
 int k;
 cin>>k;
 int a[k];
 cout<<endl<<"��������� ������"<<endl;
 for (int i=0; i<k; i++)
 {
    cout<<"a["<<i<<"]=";
    cin>>a[i];
 }
 //����� �������
 cout<<endl<<"������:";
 for (int i=0; i<k; i++)
 cout<<a[i]<<" ";

 //����� ��������� ���������� �� n �����
 int n;
 cout<<endl<<"�� ������� ������� �������� �������� ������� �����?\nn=";
 cin>>n;
 int b[k];
 for (int i=0; i<k-n; i++)
 b[i]=a[n+i];
 for (int i=k-n,j=0; i<k; i++,j++)
 b[i]=a[j];
 //����� ������� �� �������
 cout<<endl<<"������ �� �������:";
 for (int i=0; i<k; i++)
 cout<<b[i]<<" ";

 getch();
 return 0;
}
