#include <iostream>
#include <math.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{

setlocale(LC_ALL, "Russian");
 //инициализаци€ при объ€влении двумерного массива
 cout<<"¬ведите количество строк массива: ";
 int m;
 cin>>m;
 cout<<"¬ведите количество столбцов массива: ";
 int n;
 cin>>n;
 int a[m][n];
 int i,j;
 srand(time(NULL));
 for (i=0;i<m;i++)
    for (j=0;j<n;j++)
	a[i][j] = (1+rand()%10);
 for (i=0;i<m;i++)
   {
    for (j=0;j<n;j++)
	cout<<a[i][j]<<"     ";
    cout<<endl;
   }
    //четные элементы на главной диагонали (кол-во)
 int s=0;
 for (int i=0; i<m; i++)
   {
    for (int j=0;j<n;j++)
    if (i==j)
        if (a[i][j]%2==0)
        s+=1;
   }
 //четные элементы на побочной диагонали (кол-во)
 for (int i=0;i<m;i++)
    if (a[i][n-1-i]%2==0)
	s+=1;
 cout<<"„етных элементов на главной и побочной диагонал€х: "<<s;

 getch();
 return 0;
}
