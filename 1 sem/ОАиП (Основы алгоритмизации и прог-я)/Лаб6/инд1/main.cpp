#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <string.h>


using namespace std;

void poisk(char *str);

int main()
{
    setlocale(LC_ALL, "Russian");
    char str[81];
    cout<<"¬ведите строку: "<<endl;
    cin>>str;
    poisk(str);
    getch();
    return 0;
}

void poisk(char *str)
{
    char *podstr=0;
    int i=0;
    do
    {
        if (str[i]>='0'&&str[i]<='9')
        {
            if (podstr==0)
                podstr=&str[i];
        }
        else
            if (podstr!=0)
            {
                str[i]='\0';
                cout<<podstr<<endl;
                podstr=0;
            }

        i++;
    }
    while (str[i]!='\0');
    if(podstr!=0)
        cout<<podstr<<endl;
}

