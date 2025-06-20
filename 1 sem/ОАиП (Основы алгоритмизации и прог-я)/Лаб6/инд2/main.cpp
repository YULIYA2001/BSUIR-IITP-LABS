#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <string.h>


using namespace std;

void ydalen(char *str, char *simv);

int main()
{
    setlocale(LC_ALL, "Russian");
    char str[100];
    cout<<"Введите текст:";
    gets(str);
    cout<<"Введите символ для удаления: ";
    char simv[2];
    cin>>simv;
    int len=strlen(str)/2+1;
    for (int i=0; i<len; i++)
        ydalen(str, simv);
    cout<<"Строка без символа "<<simv<<":"<<endl<<str;
    getch ();
    return 0;
}

void ydalen(char *str, char *simv)
{
    for (int i=0; i<strlen(str); i++)
        if (str[i]==simv[0])
            for (int j=i; j<strlen(str); j++)
                str[j]=str[j+1];
}
