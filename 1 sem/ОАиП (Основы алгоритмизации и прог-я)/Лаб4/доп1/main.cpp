#include <iostream>
#include <math.h>
#include <conio.h>

using namespace std;

int main()
{//из матрицы а создать динамическую b, строки которой - повторяющиеся элементы а (строки переменной длины)
setlocale(LC_ALL, "Russian");
 cout<<"Введите количество строк массива (m<=100): ";
 int m;
 cin>>m;
 cout<<"Введите количество столбцов массива (n<=100): ";
 int n;
 cin>>n;
 int a[m][n];
 cout<<"Введите матрицу А:"<<endl;
 for (int i=0; i<m; i++)
    for (int j=0; j<n; j++)
	cin>>a[i][j];
//замена неповторяющихся элементов А на 0
int k, sum;
 for (int i=0; i<m; i++)
   {
    for (int j=0; j<n; j++)
        {
         k=0;
         for (int y=0; y<n; y++)
            if (a[i][j]==a[i][y])
               k+=1;
            if (k==1)
               a[i][j]=0;
        }
   }
//заполнение одномерного массива kolvo для определения длины строк массива В
//каждый элемент kolvo показывает длину соответствующей строки В
int kol, kolvo[m];
for (int i=0; i<m; i++)
   {kol=0;
    for (int j=0; j<n; j++)
        if (a[i][j]!=0)
            kol++;
        kolvo[i]=kol;
   }
//создание динамического массива B с переменной длиной строк
int **B;
B=new int*[m];
int x;
for (int i=0; i<m; i++)
    B[i]=new int[kolvo[i]];
//заполнение его нулями
for (int i=0; i<m; i++)
    for (int j=0; j<kolvo[i]; j++)
           B[i][j]=0;
//заполнение массива В повторяющимися элементами А и печать
cout<<"Матрица В: "<<endl;
for (int i=0; i<m; i++)
   {
       x=0;
       for (int j=0; j<n; j++)
         if (a[i][j]!=0)
            {
                B[i][x]=a[i][j];
                cout<<B[i][x]<<"  ";
                x++;
            }
    cout<<endl;
   }
 for (int i=0; i<m; i++) delete B[i];
 delete []B;
   getch();
 return 0;
}
