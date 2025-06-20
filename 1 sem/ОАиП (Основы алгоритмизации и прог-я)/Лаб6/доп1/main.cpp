#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <string.h>

using namespace std;

void doubleLetter(char *text, int i);
void replaceCc(char *text, int i);
void replaceQqandQUqu(char *text, int i);
void replaceWw(char *text, int i);
void replaceOO(char *text, int i);
void replaceEE(char *text, int i);
void replaceYou(char *text, int i);
void replacePh(char *text, int i);
void replaceTh(char *text, int i);
void replaceXx(char *text, int i);

int main()
{
    setlocale(LC_ALL, "Russian");
    char text[500];
    cout<<"Введите текст: "<<endl;
    gets(text);
    for (int i=0; i<strlen(text); i++)
    {
        replaceCc(text, i);
        replaceQqandQUqu(text, i);
        replaceWw(text, i);
        replaceOO(text, i);
        replaceEE(text, i);
        replaceYou(text, i);
        replacePh(text, i);
        replaceTh(text, i);
        replaceXx(text, i);
        doubleLetter(text, i);
    }
    cout<<"Переработанный текст:"<<endl<<text<<endl;
    getch ();
    return 0;
}

void doubleLetter(char *text, int i)
{
    if (text[i]==text[i+1])
        for (int j=i; j<strlen(text); j++)
            text[j]=text[j+1];
    if (text[i]==toupper(text[i+1]))
        for (int j=i; j<strlen(text); j++)
            text[j+1]=text[j+2];
}

void replaceCc(char *text, int i)
{
    if (text[i]=='c')
    {
        if(text[i+1]=='e'||text[i+1]=='i'||text[i+1]=='y')
            text[i]='s';
        else text[i]='k';
    }
    if (text[i]=='C')
    {
        if(text[i+1]=='e'||text[i+1]=='i'||text[i+1]=='y')
            text[i]='S';
        else text[i]='K';
    }
}

void replaceQqandQUqu(char *text, int i)
{
    if (text[i]=='q')
    {
        text[i]='k';
        if (text[i+1] =='u')
            text[i+1]='v';
    }
    if (text[i]=='Q')
    {
        text[i]='K';
        if (text[i+1] =='u')
            text[i+1]='v';
    }
}

void replaceXx(char *text, int i)
{
    if (text[i]=='x')
    {
        for (int j=strlen(text); j>=i; j--)
            text[j+1]=text[j];
        text[i]='k';
        text[i+1]='s';
    }
    if (text[i]=='X')
    {
        for (int j=strlen(text); j>=i; j--)
            text[j+1]=text[j];
        text[i]='K';
        text[i+1]='s';
    }
}

void replaceWw(char *text, int i)
{
    if (text[i]=='w')
        text[i]='v';
    if (text[i] =='W')
        text[i]='V';
}

void replaceOO(char *text, int i)
{
    if (text[i]=='o' && text[i+1]=='o')
    {
        text[i]='u';
        for (int j=i+1; j< strlen(text); j++)
            text[j]=text[j+1];
    }
}

void replaceEE(char *text, int i)
{
    if (text[i]=='e' && text[i+1]=='e')
    {
        text[i]='i';
        for (int j=i+1; j< strlen(text); j++)
            text[j]=text[j+1];
    }
}

void replaceYou(char *text, int i)
{
    if (text[i]=='y' && text[i+1]=='o'&& text[i+2]=='u')
    {
        text[i]='u';
        for (int j=i+1; j< strlen(text); j++)
            text[j]=text[j+2];
    }
    if (text[i]=='Y' && text[i+1]=='o'&& text[i+2]=='u')
    {
        text[i]='U';
        for (int j=i+1; j< strlen(text); j++)
            text[j]=text[j+2];
    }
}

void replacePh(char *text, int i)
{
    if (text[i]=='p' && text[i+1]=='h')
    {
        text[i]='f';
        for (int j=i+1; j< strlen(text); j++)
            text[j]=text[j+1];
    }
    if (text[i]=='P' && text[i+1]=='h')
    {
        text[i]='F';
        for (int j=i+1; j< strlen(text); j++)
            text[j]=text[j+1];
    }
}

void replaceTh(char *text, int i)
{
    if (text[i]=='t' && text[i+1]=='h')
    {
        text[i]='z';
        for (int j=i+1; j< strlen(text); j++)
            text[j]=text[j+1];
    }
    if (text[i]=='T' && text[i+1]=='h')
    {
        text[i]='Z';
        for (int j=i+1; j< strlen(text); j++)
            text[j]=text[j+1];
    }
}
