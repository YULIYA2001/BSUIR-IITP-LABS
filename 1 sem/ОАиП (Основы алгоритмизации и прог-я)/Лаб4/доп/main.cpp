#include <iostream>
#include <math.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
// ����������� ������� (����� ������� ������ � �������), ����� ��� ������� ��� � ����� ������� ����
 setlocale (LC_ALL, "Russian");

int **a;
int n, m;
cout<<"����� ����� = ";
cin>>m;
cout<<"����� �������� = ";
cin>>n;
a=new int*[m];
for (int i=0; i<m; i++)
    a[i]=new int[n];
// ��������� ���������� �������:
srand(time(NULL));
 for (int i=0;i<m;i++)
    for (int j=0;j<n;j++)
	a[i][j] = (1+rand()%10);
// ��������:
for(int i=0; i<m; i++)
    {
     for(int j=0; j<n; j++)
     cout<<a[i][j]<<" ";
     cout<<"\n";
    }
// ����� ��� �������� �������
 int mx=a[0][0], x, y;
 for(int i=0; i<m; i++)
    for(int j=0; j<n; j++)
         if (a[i][j]>=mx)
              mx=a[i][j];
cout<<"mx= "<<mx;
// ����� �������� ��� ��������
for(int i=0; i<m; i++)
    for(int j=0; j<n; j++)
        if (a[i][j]==mx)
           {
            x=i;
            y=j;
            cout<<"   i="<<i<<"   j="<<j<<endl<<endl;
           }
int b [m][n];
for(int i=0; i<m; i++)
    for(int j=0; j<n; j++)
     b[i][j]=0;
// ������������ �����
for (int j=0; j<n; j++)
    {
     b[0][j]=a[0][j];
     a[0][j]=a[x][j];
     a[x][j]=b[0][j];
    }
//������������ ��������
for (int i=0; i<m; i++)
    {
     b[i][0]=a[i][0];
     a[i][0]=a[i][y];
     a[i][y]=b[i][0];
    }
// ����� ������� �������
for(int i=0; i<m; i++)
    {for(int j=0; j<n; j++)
     cout<<a[i][j]<<"   ";
     cout<<endl;}
cout<<endl;
// ������������ ������
for(int i=0;i<m;i++)  delete a[i];
delete   []  a;
 getch();
 return 0;
}


