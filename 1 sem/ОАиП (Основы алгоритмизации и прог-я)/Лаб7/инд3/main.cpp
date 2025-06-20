#include <iostream>

using namespace std;

int length(string n);
void invers(string &n);
void vDopCod (string &n);
void sum (string &n1, string &n2, char *n3);
void revers(char *n3, int start, int finish);
void perevod (char *n3);

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Введите 1 число в естественной форме: ";
    string n1;
    cin >> n1;
    cout << "Введите 1 число в естественной форме: ";
    string n2;
    cin >> n2;
    vDopCod (n1);
    vDopCod (n2);
    char n3[10];
    cout << n1 << endl;
    cout << n2 << endl;
    sum (n1, n2, n3);
    revers(n3, 0, 7);
    if (n3[0]=='1')
        perevod (n3);
    cout << n3 << endl;
    return 0;
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

void invers(string &n)
{
    for(int i=1; i<length(n); i++)
    {
        if (n[i]=='1')
            n[i]='0';
        else n[i]='1';
    }
}

void vDopCod (string &n)
{
    if (n[0]=='-')
    {
        n[0]='1';
        invers(n);
        string k1="00000001";
        char k[10];
        int x=0;
        bool ind=0;
        for (int i=length(n)-1; i>=0; i--)
        {
            k[x]=(char)(((int)n[i]-48+(int)k1[i]-48+ind)+48);
            ind=0;
            if (k[x]=='2')
            {
                k[x]='0';
                ind=1;
            }
            else
            {
                if(k[x]=='3')
                {
                    k[x]='1';
                    ind=1;
                }
            }
            x++;
        }
        if (ind)
        {
            k[x]=(char)(ind+48);
            x++;
        }
        k[8]='\0';
        revers(k, 0, 7);
        n=k;
    }
    else n='0'+n;
}

void sum (string &n1, string &n2, char *n3)
{
    int x=0;
    bool ind=0;
    for (int i=length(n1)-1; i>=0; i--)
    {
        n3[x]=(char)(((int)n1[i]-48+(int)n2[i]-48+ind)+48);
        ind=0;
        if (n3[x]=='2')
            {
                n3[x]='0';
                ind=1;
            }
        else
        {
            if(n3[x]=='3')
            {
                n3[x]='1';
                ind=1;
            }
        }
        x++;
    }
    if (ind)
        {
            n3[x]=(char)(ind+48);
            x++;
        }
    n3[8]='\0';
}

void revers(char *n3, int start, int finish)
{
    char x;
    for(int i=start, j=finish; i<j; i++, j--)
    {
        x=n3[i];
        n3[i]=n3[j];
        n3[j]=x;
    }
}

void perevod (char *n3)
{
    string k1="11111111";
        char k[10];
        int x=0;
        bool ind=0;
        for (int i=length(n3)-1; i>=0; i--)
        {
            k[x]=(char)(((int)n3[i]-48+(int)k1[i]-48+ind)+48);
            ind=0;
            if (k[x]=='2')
            {
                k[x]='0';
                ind=1;
            }
            else
            {
                if(k[x]=='3')
                {
                    k[x]='1';
                    ind=1;
                }
            }
            x++;
        }
        k[8]='\0';
        revers(k, 0, 7);
        string inver=k;
        invers(inver);
        for (int i=0; i<length(n3); i++)
            n3[i]=inver[i];
}

