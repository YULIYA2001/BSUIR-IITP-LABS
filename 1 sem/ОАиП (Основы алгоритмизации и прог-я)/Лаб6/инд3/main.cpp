#include <iostream>
#include <conio.h>
#include <stdio.h>

using namespace std;

int length(char *str);
int kolvoSlov(char *str);
void revers(char *str, int start, int finish);
void poziciiProbelov(char *str, int *probel, int nProbelov);


int main()
{
    setlocale(LC_ALL, "Russian");
    char str[300];
    cout<<"������� ������ ��������,����������� ��������� (2 � ����� ����):"<<endl;
    gets(str);

    // ������ ������� ��������
    int nProbelov;
    if (kolvoSlov(str)%2==1)
        nProbelov=kolvoSlov(str);
    else nProbelov=kolvoSlov(str)+1;
    int probel[nProbelov]{};
    poziciiProbelov(str, probel, nProbelov);
    /*cout<<"������, ����������� �� �������: ";
    for (int i=0; i<nProbelov; i++)
        cout<<probel[i]<<" ";
    cout<<endl;*/

    // ������ �������� ��� ������ � �������� �����
    for (int a=0; a<nProbelov-2; a+=2)
        revers(str, probel[a]+1, probel[a+2]-1);
    //cout<<"stroka: "<<str<<endl;

    // ������ ����� ������� ��������
    poziciiProbelov(str, probel, nProbelov);
    /*cout<<"������, ����������� �� �������: ";
    for (int i=0; i<nProbelov; i++)
        cout<<probel[i]<<" ";
    cout<<endl;*/

    // ������ ����������� �� 2 �����
    for (int a=0; a<nProbelov-1; a++)
        revers(str, probel[a]+1, probel[a+1]-1);
    cout<<"��� ������ � �������� ����� � ������ ���������� �������: "<<endl<<str<<endl;
    getch();
    return 0;
}

int length(char *str)
{
    int length=0, i=0;
    while (str[i]!='\0')
    {
        length+=1;
        i++;
    }
    return length;
}

int kolvoSlov(char *str)
{
    int kolvo=0;
    for (int i=0; i<length(str); i++)
        if (str[i]==' ')
            kolvo++;
    return kolvo+1;
}

void revers(char *str, int start, int finish)
{
    char x;
    for(int i=start, j=finish; i<j; i++, j--)
    {
        x=str[i];
        str[i]=str[j];
        str[j]=x;
    }
}

void poziciiProbelov(char *str, int *probel, int nProbelov)
{
    int x=1;
    for (int i=0; i<length(str); i++)
        if (str[i]==' ')
        {
            probel[x]=i;
            x++;
        }
    probel[0]=-1;
    if (kolvoSlov(str)%2==0)
        probel[nProbelov-1]=length(str);
}

