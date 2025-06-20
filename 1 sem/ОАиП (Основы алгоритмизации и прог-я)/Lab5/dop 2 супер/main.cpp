#include <iostream>
#include <conio.h>

using namespace std;

long long int pow(long long int a, long long int b);
long long int binpow (long long int a, long long int n, long long int m);

int main()
{
 setlocale(LC_ALL, "Russian");
 cout<<"¬ведите 3 целых числа k, n и t (0<k<10^19; 0<n<10^19; 0<t<10)"<<endl;
 long long int k, n, t;
 cin>>k>>n>>t;
 long long int m;
 do
 {
     m=pow(10, t);
     cout<<binpow(k, n, m)<<endl;
     cout<<"¬ведите 3 целых числа k, n и t (0<k<10^19; 0<n<10^19; 0<t<10) или 0 0 0 дл€ завершени€"<<endl;
     cin>>k>>n>>t;
 }
 while (k!=0&&n!=0&&t!=0);

 getch();
 return 0;
}

long long int pow(long long int a, long long int b)
{
    if (b==0)
        return 1;
    else
        {
         long long int rez=1;
         for (int i=1; i<=b; i++)
             rez*=a;
             return rez;
        }
}

long long int binpow (long long int a, long long int n, long long int m)
{
	if (n == 0)
		return (1%m);
	if (n % 2 == 1)
		return ((((binpow (a, n-1, m))%m)*(a%m))%m);
	else {
		long long int b = ((binpow (a, n/2, m))%m);
		return ((b * b)%m);
	}
}
