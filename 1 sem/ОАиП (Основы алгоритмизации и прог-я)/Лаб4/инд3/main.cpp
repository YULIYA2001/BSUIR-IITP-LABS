/*программа находит все седловые точки матрицы
если убрать все // !!! комментарии (или следовать им)
то будет пошаговый вывод  решения */
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
     cout<<a[i][j]<<"   ";
     cout<<"\n";
    }
int mxg, mng, bmxg[m][n]={0}, bmng[m][n]={0};//g - горизонтальнo (строка)
 //поиск максимального и минимального элемента в каждой строке
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
//заполнение нулевой матрицы bmxg max элементами из a (на своих местах в строках)
            if (a[i][j]==mxg)
            bmxg[i][j]=a[i][j];
            else bmxg[i][j]=0;
//заполнение нулевой матрицы bmng min элементами из a (на своих местах в строках)
            if (a[i][j]==mng)
            bmng[i][j]=a[i][j];
            else bmng[i][j]=0;
           }
    }

/* !!!//вывод матрицы bmxg (из нулей и max элементов а на своих местах в строках)
       for (int i=0;i<m;i++)
   {
    for (int j=0;j<n;j++);// !!! ; - убрать
    cout<<bmxg[i][j]<<"     ";
    cout<<endl;
   }
   cout<<endl;
//вывод матрицы bmng (из нулей и min элементов а на своих местахв строках)
       for (int i=0;i<m;i++)
   {
    for (int j=0;j<n;j++); // !!! ; - убрать
    cout<<bmng[i][j]<<"     ";
    cout<<endl;
   }
!!! */
   //поиск минимального и максимального элемента в каждом столбце
 int mnv, mxv, cmnv[m][n]={0}, cmxv[m][n]={0};//v - вертикально (столбец)
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
//заполнение нулевой матрицы cmnv min элементами из a (на своих местах в столбцах)
            if (a[i][j]==mnv)
            cmnv[i][j]=a[i][j];
            else cmnv[i][j]=0;
//заполнение нулевой матрицы cmxv max элементами из a (на своих местах в столбцах)
            if (a[i][j]==mxv)
            cmxv[i][j]=a[i][j];
            else cmxv[i][j]=0;
          }
      }
/* !!!//вывод матрицы cmnv (из нулей и min элементов а на своих местах в столбцах)
       for (int i=0;i<m;i++)
   {
    for (int j=0;j<n;j++); // !!! ; - убрать
    cout<<cmnv[i][j]<<"     ";
    cout<<endl;
   }
cout<<endl;
//вывод матрицы cmxv (из нулей и max элементов а на своих местах в столбцах)
       for (int i=0;i<m;i++)
   {
    for (int j=0;j<n;j++); // !!! ; - убрать
   cout<<cmxv[i][j]<<"     ";
    cout<<endl;
   }
!!! */
// вывод седловых точек
int k=0;// индикатор если седловых точек нет
for (int i=0;i<m;i++)
   {
    for (int j=0;j<n;j++)
       {
        if((cmnv[i][j]==bmxg[i][j])&&cmnv[i][j]!=0)
           {
            cout<<"Седловая точка (наибольшая в строке, наименшая в столбце) "<<bmxg[i][j]<<", с координатами ("<<i<<"; "<<j<<")"<<endl;
            k+=1;
           }
        if((cmxv[i][j]==bmng[i][j])&&cmxv[i][j]!=0)
           {
            cout<<"Седловая точка (наименшая в строке, наибольшая в столбце) "<<bmng[i][j]<<", с координатами ("<<i<<"; "<<j<<")"<<endl;
            k+=1;
           }
       }
   }
 if (k==0)
 cout<<"Седловых точек нет";
 for(int i=0;i<m;i++)  delete a[i];
delete   []  a;
   getch();
 return 0;
}




