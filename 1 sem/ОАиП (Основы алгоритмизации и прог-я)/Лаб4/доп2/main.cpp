#include <iostream>
#include <math.h>
#include <conio.h>
#include <cstdlib>

using namespace std;

int main()
{//�������� ���������� �������
 setlocale(LC_ALL, "Russian");
 cout<<"������� �������� n>2 - ������� ����������� ��������: ";
 int n;
 cin>>n;
 int a[n][n]={0}, mconst;
 for (int i=0; i<n; i++)
      for (int j=0; j<n; j++)
      a[i][j]=0;
 mconst=(n*(n*n+1))/2;
 cout<<"���������� ��������� = "<<mconst<<endl;
 int j=n/2;
 int i=0;
for (int sum=1; sum<=n*n; sum++)
{
    a[i][j]=sum;
    i=i-1; j=j+1;
    if (sum%n==0)
        {i=i+2; j=j-1;}
    else {
            if(i<0)
              i=n-1;
            else {
                    if (j==n)
                    j=0;
                 }
         }
}
//����� ����������� ��������
 for (int i=0; i<n; i++)
     {
      for (int j=0; j<n; j++)
      cout<<a[i][j]<<"   ";
      cout<<endl;
     }
//��������
int sumpd=0, sumg=0, sumv=0, sumgd=0;
//�������� �����
for (i=0, j=0; i<n; i++, j++)
    sumg+=a[i][j];
//�������� ��������
for (j=0, i=0; j<n; j++, i++)
    sumv+=a[i][j];
//�������� ����������
for (i=0, j=i; i<n; i++, j++)
    sumgd+=a[i][j];
for (i=0, j=n-1-i; i<n; i++, j--)
    sumpd+=a[i][j];
    if (sumg==mconst && sumv==mconst && sumgd==mconst && sumpd==mconst)
    cout<<"�������� �������� �������";
    else cout<<"������! �������� �� ��������";
 getch();
 return 0;
}

