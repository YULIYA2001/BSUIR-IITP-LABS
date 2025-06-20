#include <iostream>
#include <conio.h>
#include <math.h>

using namespace std;
int main()
{
    setlocale(LC_ALL, "Russian");
    float x1, x2, y1, y2, dlin;
    cout<<"Введите координаты (x1,x2) первой точки ";
    cin>>x1>>x2;
    cout<<"Введите координаты (y1,y2) второй точки ";
    cin>>y1>>y2;
    int sist;
    cout<<"Выберите систему для ввода координат. Нажмите 1-декартовы или 2-полярные.";
    cin>>sist;
    switch(sist)
    {case 1:dlin=sqrt((x1-y1)*(x1-y1)+(x2-y2)*(x2-y2));break;
     case 2:{float a1,a2,b1,b2;
             a1=x1*cos(x2);
            a2=x1*sin(x2);
            b1=y1*cos(y2);
            b2=y1*sin(y2);
            dlin=sqrt((a1-b1)*(a1-b1)+(a2-b2)*(a2-b2));break;}
    }
    cout<<"Длина отрезка равна "<<dlin;
    getch();
    return 0;
}
