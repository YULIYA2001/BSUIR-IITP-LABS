#include <iostream>
#include <conio.h>
#include <math.h>

using namespace std;
int main()
{
    setlocale(LC_ALL, "Russian");
    float a, r, sa, sr;
    cout<<"������� ������� �������� (a>0) a=";
    cin>>a;
    if (a<=0) cout<<"�������� ����\n";
    cout<<"������� ������ ����� (r>0) r=";
    cin>>r;
    if (r<=0) cout<<"�������� ����\n";
    sa=a*a;
    float pi=3.14;
    sr=pi*r*r;
    if (sa==sr) cout<<"������� ����� � �������� �����. S="<<sr;
    else if (sa>sr) cout<<"������ ������� ��������. S="<<sa;
    else cout<<"������ ������� �����. S="<<sr;
    getch();
    return 0;
}

