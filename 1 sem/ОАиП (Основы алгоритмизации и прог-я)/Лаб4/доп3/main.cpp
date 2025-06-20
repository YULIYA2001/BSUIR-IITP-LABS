#include <iostream>
#include <math.h>
#include <conio.h>

using namespace std;

int main()
{
 setlocale(LC_ALL, "Russian");
 cout<<"Введите количество строк квадратной матрицы (n<=100): ";
 int n;
 cin>>n;
 int a[n][n], sum=0;
//Вывод матрицы по спирали
for (int i=0; i<=n/2; i++)
   {
    for (int j=i; j<n-i; j++) a[i][j]=++sum;
    for (int j=i+1; j<n-i; j++) a[j][n-1-i]=++sum;
	for (int j=n-2-i; j>=i; j--) a[n-1-i][j]=++sum;
	for (int j=n-2-i; j>=i+1; j--) a[j][i]=++sum;
   }
for (int i=0; i<n; i++)
     {
      for (int j=0; j<n; j++)
	  cout<<a[i][j]<<"   ";
      cout<<endl;
     }
getch();
 return 0;
}

