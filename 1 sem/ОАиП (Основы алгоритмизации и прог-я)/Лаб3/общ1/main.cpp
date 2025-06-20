#include <iostream>
#include <cmath>
#include <conio.h>

using namespace std;

int main()
{
 setlocale (LC_ALL, "Russian");
 float a, b, N=0;
 for (int i=1; i<=30; i++)
 {
    if (i%2==0)
         {
          a=i/2;
          b=i*i*i;
         }
     else {
          a=i;
          b=i*i;
          }
 N+=(a-b)*(a-b);
 }
 cout<<N<<endl;
 getch();
 return 0;
}

