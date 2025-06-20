#include <iostream>
#include <conio.h>
#include <iomanip>

using namespace std;

void vvod(int **a, int n, int m);
void aaZap(int n, int m, int **a, int **aa);
void coun(int n, int m, int **aa, int *kol);
void bZapShow(int n, int m, int **aa, int **b, int *kol);
void delet(int **a, int **aa, int **b, int *kol, int n);
 float srArif(int **b, int *kol, int n);

int main()
{
 setlocale(LC_ALL, "Russian");
 int n, m, **a;
 cout<<"Введите количество строк: ";
 cin>>n;
 cout<<"Введите количество столбцов (m>1): ";
 cin>>m;
 a=new int *[n];
 for (int i=0; i<n; i++)
    a[i]=new int [m];
 vvod(a, n, m);

 int **aa=new int *[n];
 for (int i=0; i<n; i++)
    aa[i]=new int [m/2];
 aaZap(n, m, a, aa);

int *kol=new int [n];
coun(n, m, aa, kol);

int **b=new int *[n];
for (int i=0; i<n; i++)
    b[i]=new int [kol[i]];
bZapShow(n, m, aa, b, kol);

float sr=srArif(b, kol,n);
cout<<"Среднее арифметическое данного массива: "<<sr;

delet(a, aa, b, kol, n);
 getch();
 return 0;
}

void vvod(int **a, int n, int m)
{   cout<<"Заполните массив"<<endl;
    for (int i=0; i<n; i++)
        for (int j=0; j<m; j++)
            cin>>a[i][j];
}

void aaZap(int n, int m, int **a, int **aa)
 {
     for (int i=0; i<n; i++)
        for (int j=1, x=0; j<m; j+=2, x++)
            aa[i][x]=a[i][j];
 }

 void coun(int n, int m, int **aa, int *kol)

 {
     for (int i=0; i<n; i++)
    {
        for (int j=0; j<m/2; j++)
        {
            if (aa[i][j]%2==0)
                aa[i][j]=0;
        }
    }
     int k;
         for (int i=0; i<n; i++)
    {
        k=0;
        for (int j=0; j<m/2; j++)
           {
               if (aa[i][j]!=0)
                   k++;
           }
        kol[i]=k;
    }
 }

 void bZapShow(int n, int m, int **aa, int **b, int *kol)
{
    int x;
    cout<<"Искомый массив: "<<endl;

    bool t=0;
    for(int i=0; i<n; i++)
        if (kol[i]==0)
           t=1;
    if(t) cout<<"не существует"<<endl;
    else
   {
     for (int i=0; i<n; i++)
    {
      x=0;
      for (int j=0; j<m/2; j++)
         if (aa[i][j]!=0)
            {
                b[i][x]=aa[i][j];
                cout<<b[i][x]<<"  ";
                x++;
            }
      cout<<endl;
    }
   }
}

void delet(int **a, int **aa, int **b, int *kol, int n)
 {
 for (int i=0; i<n; i++)
    delete a[i];
 delete []a;
 for (int i=0; i<n; i++)
    delete aa[i];
 delete []aa;
 for (int i=0; i<n; i++)
    delete b[i];
 delete []b;
 delete []kol;
 }

 float srArif(int **b, int *kol, int n)
{
 int sum1=0, sum2=0;
  for (int i=0; i<n; i++)
      for (int j=0; j<kol[i]; j++)
        sum1+=b[i][j];
 for (int i=0; i<n; i++)
    sum2+=kol[i];
 return (1.0*sum1/sum2);
}
