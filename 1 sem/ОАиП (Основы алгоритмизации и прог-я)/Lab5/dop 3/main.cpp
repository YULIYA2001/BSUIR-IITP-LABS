#include <iostream>
#include <math.h>
#include <conio.h>
#include <windows.h>
#include <ctime>

using namespace std;

int f(int n);
int sum(int n);

int main()
{
 setlocale(LC_ALL, "Russian");
 int n;
 cout<<"Введите натуральное число n:";
 cin>>n;
 do
 {
 cout<<"Искомая сумма: "<<sum(n)<<endl;
 cout<<"Введите натуральное число n (для завершения программы введите 0):";
 cin>>n;
 }
 while (n!=0);
 getch();
 return 0;
}

int f(int n)
{
        if (n%2==1)
           return n;
        else
        {
            do
            n=n/2;
            while (n%2==0);
            return n;
        }
}

int sum(int n)
{
    int sum=0;
    for (int i=1; i<=n; i++)
         sum+=f(i);
    return sum;
}
