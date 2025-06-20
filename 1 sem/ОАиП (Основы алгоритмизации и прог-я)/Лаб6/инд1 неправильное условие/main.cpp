#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <string.h>


using namespace std;

void poisk(char *str, char *podstr);

int main()
{
    setlocale(LC_ALL, "Russian");
    char str[81];
    cout<<"Введите строку: "<<endl;
    cin>>str;
    char podstr[81];
    poisk (str,podstr);
    cout<<"Подстрока, соответствующая записи целого числа: "<<endl<<podstr;
    getch();
    return 0;
}

void poisk(char *str, char *podstr)
{
    int x=0;
    for (int i=0; i<strlen(str); i++)
         for(int j=0; j<10; j++)          //for(int j=int('0'); j<=int('9'); j++)
            if(str[i]==char(j+48))        //if(str[i]==char(j))        if(str[i]==char(j+int('0')))
                {
                    podstr[x]=str[i];
                    x++;
                }
    podstr[x]='\0';
}
