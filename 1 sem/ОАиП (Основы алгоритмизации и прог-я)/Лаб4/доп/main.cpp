#include <iostream>
#include <math.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
// перестроить матрицу (меняя местами строки и столбцы), чтобы мах элемент был в левом верхнем углу
 setlocale (LC_ALL, "Russian");

int **a;
int n, m;
cout<<"Число строк = ";
cin>>m;
cout<<"Число столбцов = ";
cin>>n;
a=new int*[m];
for (int i=0; i<m; i++)
    a[i]=new int[n];
// Заполняем случайными числами:
srand(time(NULL));
 for (int i=0;i<m;i++)
    for (int j=0;j<n;j++)
	a[i][j] = (1+rand()%10);
// Печатаем:
for(int i=0; i<m; i++)
    {
     for(int j=0; j<n; j++)
     cout<<a[i][j]<<" ";
     cout<<"\n";
    }
// поиск мах элемента матрицы
 int mx=a[0][0], x, y;
 for(int i=0; i<m; i++)
    for(int j=0; j<n; j++)
         if (a[i][j]>=mx)
              mx=a[i][j];
cout<<"mx= "<<mx;
// поиск индексов мах элемента
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
// перестановка строк
for (int j=0; j<n; j++)
    {
     b[0][j]=a[0][j];
     a[0][j]=a[x][j];
     a[x][j]=b[0][j];
    }
//перестановка столбцов
for (int i=0; i<m; i++)
    {
     b[i][0]=a[i][0];
     a[i][0]=a[i][y];
     a[i][y]=b[i][0];
    }
// вывод искомой матрицы
for(int i=0; i<m; i++)
    {for(int j=0; j<n; j++)
     cout<<a[i][j]<<"   ";
     cout<<endl;}
cout<<endl;
// освобождение памяти
for(int i=0;i<m;i++)  delete a[i];
delete   []  a;
 getch();
 return 0;
}


