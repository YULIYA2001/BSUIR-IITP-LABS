#include <iostream>
#include <math.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{

setlocale(LC_ALL, "Russian");
 cout<<"������� ���������� ����� �������: ";
 int m;
 cin>>m;
 cout<<"������� ���������� �������� �������: ";
 int n;
 cin>>n;
 int a[m][n];
 int i,j;
 /*srand(time(NULL));
 for (i=0;i<m;i++)
    for (j=0;j<n;j++)
	a[i][j] = (1+rand()%10);*/
 for (i=0;i<m;i++)
    for (j=0;j<n;j++)
        cin>>a[i][j];
 for (i=0;i<m;i++)
   {
    for (j=0;j<n;j++)
	cout<<a[i][j]<<"     ";
    cout<<endl;
   }
 int b[m][n], mx;
 //���������� ������� b ������ � ����� (��� ��������)
 for (i=0;i<m;i++)
   {
    for (j=0;j<n;j++)
    {
     b[i][j]=0;
	 //cout<<b[i][j]<<"     ";
	}
    cout<<endl;
   }
 for (i=0;i<m;i++)
    for (j=0;j<n;j++)
    {
        mx=a[0][0];
       {   //����� ��� ����� ��������� ���� � ����� �������
           for (int x=0; x<=i; x++)
           for (int y=0; y<=j; y++)
              {
                if (a[x][y]>mx)
                  mx=a[x][y];
              } //���������� ������� b ��� ���������� � ����� ���, ��� ���� � ����� ������ �������
              //cout<<"===="<<mx;
                  b[i][j]=mx;
       }
    }
 cout<<endl;
 //����� ������ b
 for (i=0;i<m;i++)
   {
    for (j=0;j<n;j++)
	cout<<b[i][j]<<"     ";
    cout<<endl;
   }
   getch();
 return 0;
}
