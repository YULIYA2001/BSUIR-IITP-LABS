#include <iostream>
#include <conio.h>
#include <math.h>

using namespace std;
int main()
{
    int num;
    float a, b, c, kv1, kv2, x1, x2, x3, x4;
    cout<<"a=";
    cin>>a;
    cout<<"b=";
    cin>>b;
    cout<<"c=";
    cin>>c;
    { cout<<"Your equation:"<<a<<"*x^4+"<<b<<"*x^2+"<<c<<"=0\n";
      if (a==0)
           {if (b==0)
                {if (c==0) cout<<"x any number";
                else cout<<"\nEquation has no solutions";}
           else {if(c/b<=0) {x1=sqrt(-(c/b)); x2=-sqrt(-(c/b));cout<<"\nx="<<x1<<" x="<<x2;}
                 else cout<<"\nEquation has no solutions";}}
      else {if (b==0)
                  {if(c==0) cout<<"\nx=0";
                   else {if(c/a<0) {float d=sqrt(-(c/a)); x1=sqrt(d);x2=-sqrt(d);cout<<"\nx="<<x1<<" x="<<x2;}
                         else cout<<"\nEquation has no solutions";}}
            else {if (c==0)
                    {if (b/a<0) {x1=sqrt(-(b/a)); x2=-sqrt(-(b/a));cout<<"\nx="<<x1<<" x="<<x2<<" x=0";}
                  else cout<<"\nx=0 ";} }}
      if ((a!=0)&&(b!=0)&&(c!=0))
          {
            float D=b*b-4*a*c;
            if (D<0) cout<<"\nEquation has no solutions\n";
            else
                {
                  kv1=(-b-sqrt(D))/(2*a);
                  kv2=(-b+sqrt(D))/(2*a);
                  if (kv1>=0)
                    {
                     x1=sqrt(kv1);
                     x2=-sqrt(kv1);
                     cout<<"\nx="<<x1<<" x="<<x2;
                    }
                   if (kv2>=0)
                    {
                     x3=sqrt(kv2);
                     x4=-sqrt(kv2);
                     cout<<"\nx="<<x3<<" x="<<x4<<"\n";
                    }
                   else cout<<"\nEquation has no solutions\n";
                 }
           }
        }




    getch();
    return 0;
}
