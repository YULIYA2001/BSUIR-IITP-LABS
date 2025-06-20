#include <iostream>

using namespace std;

int pow(int a, int b);
int Kol(int desCh);

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "¬ведите число в 5-ричной системе счислени€: ";
    char simv;
    int desCh=0, num=0, siz=0;
    while (simv=getchar(), simv!='\n')
        {
            siz++;
            num+=(int)(simv-'0')*pow(5, siz-1);
        }
    //cout<<num<<endl;
    for (int i=siz-1; i>=0; i--)
        {
            desCh+=(num%5)*pow(5, i);
            num/=5;
        }
    //cout<<desCh<<endl;
    cout << "„исло в 14-ричной системе счислени€: ";
    int kol=Kol(desCh);
    while (kol>=0)
        {
            int rez;
            rez=desCh/pow(14,kol);
            if (rez<=9)
                cout<<rez;
            else
            {
                char x='A'+(char)(rez-10);
                cout<<x;
            }
            desCh%=pow(14,kol);
            kol--;
        }
    return 0;
}

int Kol(int desCh)
{
    int kol=0;
    while (desCh>13)
        {
            desCh/=14;
            kol++;
        }
    return kol;
}

int pow(int a, int b)
{
    int rez=1;
    for(int i=0; i<b; i++)
        rez*=a;
    return rez;
}
