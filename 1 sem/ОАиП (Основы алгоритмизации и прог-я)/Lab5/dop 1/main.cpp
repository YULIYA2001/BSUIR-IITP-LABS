#include <iostream>
#include <conio.h>


using namespace std;

int func(int n);
void s(int p, int q);

int main()
{
 setlocale(LC_ALL, "Russian");
 int p, q, **a=new int*[2], per;
 for (int i=0; i<2; i++)
    a[i]=new int[per];
 cout<<"¬ведите p и q (p<=q)"<<endl;
 cin>>p>>q;
   while (p>=0&&q>=0)
   {
    cout<<"–езультат действий: "<<endl;
    s(p, q);
    cout<<"¬ведите p и q (p<=q)"<<endl;
    cin>>p>>q;
   }

 getch();
 return 0;
}

int func(int n)
{
    if (n==0)
        return 0;
    else
    {
        if (n%10>0)
            return n%10;
        else return func(n/10);
    }
}

void s(int p, int q)
{
    int sum=0;
    for (int i=p; i<=q; i++)
        sum+=func(i);
    cout<<sum<<endl;
}
