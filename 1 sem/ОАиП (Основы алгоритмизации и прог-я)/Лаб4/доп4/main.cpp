#include <iostream>
#include <math.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
//����������� �������� �������� ������ ������������ ������� (������� ���������) �� �����������
setlocale(LC_ALL, "Russian");
 //������������� ��� ���������� ���������� �������
 cout<<"������� ���������� ����� ������� (m<=100): ";
 int m;
 cin>>m;
 cout<<"������� ���������� �������� ������� (n<=100): ";
 int n;
 cin>>n;
 int a[m][n];
 srand(time(NULL));
 for (int i=0;i<m;i++)
    for (int j=0;j<n;j++)
	a[i][j] = (1+rand()%10);
 for (int i=0;i<m;i++)
   {
    for (int j=0;j<n;j++)
	cout<<a[i][j]<<"     ";
    cout<<endl;
   }
   cout<<endl;
   int k;
   if (m>=n)
    k=0;
   else k=n-m;
 cout<<endl;
//�������������� ��������� �������� ������ ������������ ������� �� �����������
int help=0;
for (int x=0; x<m; x++)
    for (int y=0; y<n-x-k; y++)
         {for (int i=0; i<m; i++)
	         for (int j=0; j<n-i-k; j++)
                  if (a[i][j]>a[x][y])
                    {
                     help=a[i][j];
                     a[i][j]=a[x][y];
                     a[x][y]=help;
                    }
          }
//����� �������� ������������
for (int i=0; i<m; i++)
    {for (int j=0; j<n-i-k; j++)
        cout<<a[i][j]<<"   ";
     cout<<endl;
	}
getch();
 return 0;
}

