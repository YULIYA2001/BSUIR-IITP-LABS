/*��������� ������� ��� �������� ����� �������
���� ������ ��� // !!! ����������� (��� ��������� ��)
�� ����� ��������� �����  ������� */
#include <iostream>
#include <math.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
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
     cout<<a[i][j]<<"   ";
     cout<<"\n";
    }
int mxg, mng, bmxg[m][n]={0}, bmng[m][n]={0};//g - ������������o (������)
 //����� ������������� � ������������ �������� � ������ ������
 for(int i=0; i<m; i++)
    {
     mxg=a[i][0];
     mng=a[i][0];
        for(int j=1; j<n; j++)
       {
         if (a[i][j]>=mxg)
               mxg=a[i][j];
         if (a[i][j]<=mng)
               mng=a[i][j];
       }
// !!!          cout<<"mxg="<<mxg<<'\t';
// !!!          cout<<"mng="<<mng<<endl;
     for (int j=0; j<n; j++)
           {
//���������� ������� ������� bmxg max ���������� �� a (�� ����� ������ � �������)
            if (a[i][j]==mxg)
            bmxg[i][j]=a[i][j];
            else bmxg[i][j]=0;
//���������� ������� ������� bmng min ���������� �� a (�� ����� ������ � �������)
            if (a[i][j]==mng)
            bmng[i][j]=a[i][j];
            else bmng[i][j]=0;
           }
    }

/* !!!//����� ������� bmxg (�� ����� � max ��������� � �� ����� ������ � �������)
       for (int i=0;i<m;i++)
   {
    for (int j=0;j<n;j++);// !!! ; - ������
    cout<<bmxg[i][j]<<"     ";
    cout<<endl;
   }
   cout<<endl;
//����� ������� bmng (�� ����� � min ��������� � �� ����� ������� �������)
       for (int i=0;i<m;i++)
   {
    for (int j=0;j<n;j++); // !!! ; - ������
    cout<<bmng[i][j]<<"     ";
    cout<<endl;
   }
!!! */
   //����� ������������ � ������������� �������� � ������ �������
 int mnv, mxv, cmnv[m][n]={0}, cmxv[m][n]={0};//v - ����������� (�������)
 for(int j=0; j<n; j++)
    {
     mnv=a[0][j];
     mxv=a[0][j];
        for(int i=1; i<m; i++)
       {
         if (a[i][j]<=mnv)
               mnv=a[i][j];
         if (a[i][j]>=mxv)
               mxv=a[i][j];
       }
// !!!         cout<<"mnv="<<mnv<<'\t';
// !!!         cout<<"mxv="<<mxv<<endl;

      for (int i=0; i<m; i++)
          {
//���������� ������� ������� cmnv min ���������� �� a (�� ����� ������ � ��������)
            if (a[i][j]==mnv)
            cmnv[i][j]=a[i][j];
            else cmnv[i][j]=0;
//���������� ������� ������� cmxv max ���������� �� a (�� ����� ������ � ��������)
            if (a[i][j]==mxv)
            cmxv[i][j]=a[i][j];
            else cmxv[i][j]=0;
          }
      }
/* !!!//����� ������� cmnv (�� ����� � min ��������� � �� ����� ������ � ��������)
       for (int i=0;i<m;i++)
   {
    for (int j=0;j<n;j++); // !!! ; - ������
    cout<<cmnv[i][j]<<"     ";
    cout<<endl;
   }
cout<<endl;
//����� ������� cmxv (�� ����� � max ��������� � �� ����� ������ � ��������)
       for (int i=0;i<m;i++)
   {
    for (int j=0;j<n;j++); // !!! ; - ������
   cout<<cmxv[i][j]<<"     ";
    cout<<endl;
   }
!!! */
// ����� �������� �����
int k=0;// ��������� ���� �������� ����� ���
for (int i=0;i<m;i++)
   {
    for (int j=0;j<n;j++)
       {
        if((cmnv[i][j]==bmxg[i][j])&&cmnv[i][j]!=0)
           {
            cout<<"�������� ����� (���������� � ������, ��������� � �������) "<<bmxg[i][j]<<", � ������������ ("<<i<<"; "<<j<<")"<<endl;
            k+=1;
           }
        if((cmxv[i][j]==bmng[i][j])&&cmxv[i][j]!=0)
           {
            cout<<"�������� ����� (��������� � ������, ���������� � �������) "<<bmng[i][j]<<", � ������������ ("<<i<<"; "<<j<<")"<<endl;
            k+=1;
           }
       }
   }
 if (k==0)
 cout<<"�������� ����� ���";
 for(int i=0;i<m;i++)  delete a[i];
delete   []  a;
   getch();
 return 0;
}




