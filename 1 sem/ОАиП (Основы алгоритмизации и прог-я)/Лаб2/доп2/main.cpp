#include <iostream>
#include <conio.h>
#include <math.h>

using namespace std;
int main()
{
    setlocale(LC_ALL, "Russian");
    float a, r, sa, sr;
    cout<<"Введите сторону квадрата (a>0) a=";
    cin>>a;
    if (a<=0) cout<<"Неверный ввод\n";
    cout<<"Введите радиус круга (r>0) r=";
    cin>>r;
    if (r<=0) cout<<"Неверный ввод\n";
    sa=a*a;
    float pi=3.14;
    sr=pi*r*r;
    if (sa==sr) cout<<"Площадь круга и квадрата равны. S="<<sr;
    else if (sa>sr) cout<<"Больше площадь квадрата. S="<<sa;
    else cout<<"Больше площадь круга. S="<<sr;
    getch();
    return 0;
}

