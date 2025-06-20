#include <iostream>
#include <conio.h>
#include <cmath>



using namespace std;

int f(long long int n, int r, long long int k);
int sum(long long int n, long long int k, int t);

int main()
{
 setlocale(LC_ALL, "Russian");
 cout<<"¬ведите 3 целых числа k, n и t (0<k<10^19; 0<n<10^19; 0<t<10)"<<endl;
 long long int k, n;
 int t;
 cin>>k>>n>>t;
 do
 {
     cout<<sum(n, k, t)<<endl;
     cout<<"¬ведите 3 целых числа k, n и t (0<k<10^19; 0<n<10^19; 0<t<10) или 0 0 0 дл€ завершени€"<<endl;
     cin>>k>>n>>t;
 }
 while (k!=0&&n!=0&&t!=0);

 getch();
 return 0;
}

int f(long long int n, int r, long long int k)
{
    if (n==0&&r==0)
        return 1;
    else
    {
        if (n>0&&0<=r<(n*(k-1)+1))
        {
          int sum=0;
          for (int i=0; i<=k-1; i++)
          sum+=f(n-1, r-i, k);
          return sum;
        }
        else return 0;
    }
}

int sum(long long int n, long long int k, int t)
{
    int s=0;
    for (int i=0; i<=n*(k-1); i++)
        s+=f(n, i, k);
    long long int m=pow(10, t);
    int x=s%m;
    return x;
}

