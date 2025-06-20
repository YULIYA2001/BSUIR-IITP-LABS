#include <iostream>
#include <math.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{

setlocale(LC_ALL, "Russian");
 cout<<"¬ведите количество строк матрицы: ";
 int m;
 cin>>m;
 cout<<"¬ведите количество столбцов матрицы: ";
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
 //заполнение массива b нул€ми и вывод (дл€ проверки)
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
       {   //поиск мах среди элементов выше и левее данного
           for (int x=0; x<=i; x++)
           for (int y=0; y<=j; y++)
              {
                if (a[x][y]>mx)
                  mx=a[x][y];
              } //заполнение массива b мах элементами а среди тех, что выше и левее данной позиции
              //cout<<"===="<<mx;
                  b[i][j]=mx;
       }
    }
 cout<<endl;
 //вывод нового b
 for (i=0;i<m;i++)
   {
    for (j=0;j<n;j++)
	cout<<b[i][j]<<"     ";
    cout<<endl;
   }
   getch();
 return 0;
}
