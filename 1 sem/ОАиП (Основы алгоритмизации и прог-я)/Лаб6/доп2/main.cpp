#include <iostream>
#include <string.h>
#include <math.h>

using namespace std;

void povtChast(char *w1, char *w2, char *w, bool &indicator);
int answCase1(char *w1, char *w2, int m, int L);

int main()
{
 setlocale(LC_ALL, "Russian");
 char w1[201], w2[201];
 int t, L, m, stepen;
 cout<<"������� ���������� ������� ������� ������ (1<=t<=100): ";
 cin>>t;
 do
 {
    cout<<"������� ����� ������� ������ L � ������ m: ";
    cin>>L>>m;
    cout<<"������� 1 �����: ";
    cin>>w1;
    cout<<"������� 2 �����: ";
    cin>>w2;
    char w[100]{};
    bool indicator;
    povtChast(w1, w2, w, indicator);//����� ������������� ����� � ������
    if (!indicator)
        povtChast(w2, w1, w, indicator);
    if (!indicator)
    {
        if (strlen(w1)+strlen(w2)>L)
            cout<<endl<<"�������� ������������� 0 ���. "<<endl<<endl;
        else
        {
            stepen=answCase1(w1, w2, m, L);
            cout<<endl<<"�������� ������������� "<<(2*stepen)%m<<" ���. "<<endl<<endl;
        }
    }
    else
    {
        if (strlen(w1)+strlen(w2)>L)
        {
            if (strlen(w1)+strlen(w2)-strlen(w)>L)
                cout<<endl<<"�������� ������������� 0 ���. "<<endl<<endl;
            if (strlen(w1)+strlen(w2)-strlen(w)==L)
                cout<<endl<<"�������� ������������� 1 ���. "<<endl<<endl;
            if (strlen(w1)+strlen(w2)-strlen(w)< L)
                cout<<endl<<"�������� ������������� 0 ���. "<<endl<<endl;

        }
        else
        {
            stepen=answCase1(w1, w2, m, L);
            cout<<endl<<"�������� ������������� "<<(2*stepen)%m<<" ���. "<<endl<<endl;
        }
    }
    t--;
 }
 while (t>0);
 return 0;
}

void povtChast(char *w1, char *w2, char *w, bool &indicator)
{
    int i=0, j=0, x=0;
    do
    {
        if (w1[i]==w2[j])
        {
            w[x]=w1[i];
            i++;
            x++;
        }
        j++;
    }
    while(j<strlen(w2)&&i<strlen(w1));
    if (w1[0]==w[0]&&w2[strlen(w2)-1]==w[x-1])
         indicator=1;
    else indicator=0;
}

int answCase1(char *w1, char *w2, int m, int L)      //����� �� ������������� � ���������
{
    int stepen=1;
    for (int i=1; i<=(L-strlen(w1)-strlen(w2)); i++)
        stepen=(stepen*26)%m;
    return stepen;
}
