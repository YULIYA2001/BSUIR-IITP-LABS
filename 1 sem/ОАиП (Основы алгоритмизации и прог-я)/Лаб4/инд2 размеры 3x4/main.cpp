#include <iostream>
#include <math.h>
#include <conio.h>

using namespace std;

int main()
{
 setlocale (LC_ALL, "Russian");
 //инициализация при объявлении двумерного массива
 const int n=4;
 int a[][n]={1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
 for (int i=0;i<3;i++)
   {
    for (int j=0;j<n;j++)
    cout<<a[i][j]<<"     ";
    cout<<endl;
   }
 //четные элементы на главной диагонали (кол-во)
 int s=0;
 for (int i=0;i<3;i++)
   {
    for (int j=0;j<n;j++)
    if (i==j)
        if (a[i][j]%2==0)
        s+=1;
   }
 //четные элементы на побочной диагонали (кол-во)
 for (int i=0;i<3;i++)
    if (a[i][n-1-i]%2==0)
    s+=1;
 cout<<"Чтных элементов на главной и побочной диагоналях: "<<s;

 getch();
 return 0;
}
