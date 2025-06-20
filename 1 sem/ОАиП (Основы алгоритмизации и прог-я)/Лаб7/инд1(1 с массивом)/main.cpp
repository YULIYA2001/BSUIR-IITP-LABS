#include <iostream>

using namespace std;

void iz5v10(int n5, int &n10);
void iz10v14(int n10, char *n14);
int length(char *str);
void revers(char *str, int start, int finish);

int main()
{
    setlocale(LC_ALL, "Russian");

    cout << "¬ведите число в 5-ричной системе счислени€: ";
    int n5, n10=0;
    char n14[20];
    cin >> n5;
    iz5v10(n5, n10);
    iz10v14(n10, n14);
    cout<<"„исло в 14-ричной системе счислени€: "<<n14;
    if (n10==0)
        cout<<0;
    return 0;
}

void iz5v10(int n5, int &n10)
{
    for (int i=1; n5>0; i*=5)
        {
            n10+=(n5%10)*i;
            n5/=10;
        }
}

void iz10v14(int n10, char *n14)
{
    int x=0;
    for(int i=0; n10>0; i++)
	{
        int n;
	    n=(n10%14);
        if (n<=9)
            n=n+48;
        if (n>=10 && n<=13)
            n=n-10+(int)'A';
		n14[x]=n;
		x++;
		n10/=14;
	}
	n14[x]='\0';
	int len=length(n14);
	revers(n14, 0, len-1);
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
