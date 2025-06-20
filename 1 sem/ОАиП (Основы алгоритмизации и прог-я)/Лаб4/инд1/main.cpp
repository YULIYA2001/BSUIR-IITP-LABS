#include <iostream>
#include <math.h>
#include <conio.h>

using namespace std;

int main()
{
 setlocale (LC_ALL, "Russian");
 //выбор размера массива, заполнение с клавиатуры
 cout<<" оличество чисел массива равно:";
 int k;
 cin>>k;
 int a[k];
 cout<<endl<<"«аполните массив"<<endl;
 for (int i=0; i<k; i++)
 {
    cout<<"a["<<i<<"]=";
    cin>>a[i];
 }
 //вывод массива
 cout<<endl<<"ћассив:";
 for (int i=0; i<k; i++)
 cout<<a[i]<<" ";

 //сдвиг элементов циклически на n влево
 int n;
 cout<<endl<<"Ќа сколько позиций сдвинуть элементы массива влево?\nn=";
 cin>>n;
 int b[k];
 for (int i=0; i<k-n; i++)
 b[i]=a[n+i];
 for (int i=k-n,j=0; i<k; i++,j++)
 b[i]=a[j];
 //вывод массива со сдвигом
 cout<<endl<<"ћассив со сдвигом:";
 for (int i=0; i<k; i++)
 cout<<b[i]<<" ";

 getch();
 return 0;
}
