#include <iostream>

using namespace std;

int length (string n);
void priravRaz (string &n1, string &n2);
void podschetS (string n1, string n2, int &len, string &otvet);
void podschetR (string n1, string n2, int &len, string &otvet);
int toNum (char n);
int toChar (int n);
void sdvigOtricat (string &n);
void preobrazovVPolozhit (int &var, string &n1, string &n2);
int sravn (string n1, string n2);

int main()
{
    setlocale(LC_ALL, "Russian");
    cout<<"¬ведите + дл€ сложени€ или - дл€ вычитани€"<<endl;
    char znak;
    cin>>znak;
    cout<<"¬ведите 2 числа в 14-ричной системе:"<<endl;
    string n1, n2, otvet;
    cin>>n1>>n2;
    int var, len=0;
    preobrazovVPolozhit(var, n1, n2);
    priravRaz(n1, n2);
    if (znak=='+')
    {
        switch (var)
        {
            case 1: podschetS(n1, n2, len, otvet); break;
            case 2: podschetS(n1, n2, len, otvet); otvet='-'+otvet; break;
            case 3: {
                        if(sravn (n1, n2)==2)
                            podschetR(n2, n1, len, otvet);
                        else
                        {
                            podschetR(n1, n2, len, otvet);
                            otvet='-'+otvet;
                        }
                    } break;
            case 4: {
                        if(sravn (n1, n2)==1)
                            podschetR(n1, n2, len, otvet);
                        else
                        {
                            podschetR(n2, n1, len, otvet);
                            otvet='-'+otvet;
                        }
                    } break;
        }
    }
    if (znak=='-')
        switch (var)
        {
            case 1: {
                        if(sravn (n1, n2)==1)
                            podschetR(n1, n2, len, otvet);
                        else
                        {
                            podschetR(n2, n1, len, otvet);
                            otvet='-'+otvet;
                        }
                    } break;
            case 2: {
                        if(sravn (n1, n2)==2)
                            podschetR(n2, n1, len, otvet);
                        else
                        {
                            podschetR(n1, n2, len, otvet);
                            otvet='-'+otvet;
                        }
                    } break;
            case 3: podschetS(n1, n2, len, otvet); otvet='-'+otvet; break;
            case 4: podschetS(n1, n2, len, otvet); break;
        }

    cout<<"–езультат: "<<otvet<<endl;
    return 0;
}

int sravn (string n1, string n2)
{
    int more=0;
    if (length(n1)>length(n2))
        more=1;
    if (length(n1)<length(n2))
        more=2;
    if (length(n1)==length(n2))
        for (int i=0; i<length(n1); i++)
        {
            if(n1[i]>n2[i])
                {more=1; break;}
            if (n1[i]<n2[i])
                {more=2; break;}
            if (n1[i]==n2[i])
                i++;
        }
    return more;
}

void preobrazovVPolozhit (int &var, string &n1, string &n2)
{
 if(n1[0]=='-'&& n2[0]=='-')
    {
        sdvigOtricat(n1);
        sdvigOtricat(n2);
        var=2;
    }
    else {if(n1[0]=='-'&& n2[0]!='-')
            {
             sdvigOtricat(n1);
             var=3;
            }
          else {if(n1[0]!='-'&& n2[0]=='-')
                  {
                   sdvigOtricat(n2);
                   var=4;
                  }
                else var=1;
               }
         }
}

void sdvigOtricat (string &n)
{
    int i=0;
    while (i<length(n))
    {
        n[i]=n[i+1];
        i++;
    }
    n[i]='\0';
}


void podschetS (string n1, string n2, int &len, string &otvet)
{
    int num1, num2, summa, ind=0, x=0, otvNum[100]{};
    char otvCh[100]{};
    for (int i=length(n1)-1; i>=0; i--)
    {
        num1=toNum(n1[i]);
        num2=toNum(n2[i]);
        summa=num1+num2+ind;
        ind=0;
        otvNum[x]=summa%14;
        ind=summa/14;
        x++;
    }
    if(ind>0)
    {
        otvNum[x]=ind;
        x++;
    }
    len=x;
    x=0;
    for (int i=len-1; i>=0; i--)
    {
        otvCh[x]=toChar(otvNum[i]);
        x++;
    }
    otvCh[x]='\0';
    otvet=otvCh;
}

void podschetR (string n1, string n2, int &len, string &otvet)
{
    int num1, num2, razn, ind=0, x=0, otvNum[100]{};
    char otvCh[100]{};
    for (int i=length(n1)-1; i>=0; i--)
    {
        num1=toNum(n1[i]);
        num2=toNum(n2[i]);
        razn=num1-num2-ind;
        ind=0;
        if (razn<0)
        {
            razn=razn+14;
            ind=1;
        }
        otvNum[x]=razn;
        x++;
    }
    len=x;
    x=0;
    for (int i=len-1; i>=0; i--)
    {
        otvCh[x]=toChar(otvNum[i]);
        x++;
    }
    otvCh[x]='\0';
    otvet=otvCh;
    int help=0;
    for (int x=0; x<length(otvet); x++)
        if (otvet[x]!='0')
            help=1;
    if (help!=0)
    {
        while (otvet[0]=='0')
        {
            int i=0;
            while (i<length(otvet))
            {
                otvet[i]=otvet[i+1];
                i++;
            }
            otvet[i]='\0';
        }
    }
}

void priravRaz(string &n1, string &n2)
{
    if(length(n1)>length(n2))
        while (length(n1)>length(n2))
        n2='0'+n2;
    else if (length(n1)<length(n2))
        while (length(n2)>length(n1))
        n1='0'+n1;
}

int toNum(char n)
{
    int num;
    if (n>='0'&& n<='9')
        num=int(n-'0');
    if (n>='A'&& n<='D')
        num=int(n-'A')+10;
    return num;
}

int toChar(int n)
{
    char simv;
    if (n>=0 && n<=9)
        simv=char(n+48);
    if (n>=10&& n<=13)
        simv=char(n-10)+'A';
    return simv;
}

int length(string n)
{
    int length=0, i=0;
    while (n[i]!='\0')
    {
        length+=1;
        i++;
    }
    return length;
}
