#include <stdio.h>
#include <stdlib.h>
#define CHAR 32;

/* Проверка наличия пробела после ,:; */
char check1(char symbol)
{
    if ((symbol == ',') || (symbol == ':') || (symbol == ';'))   /* если символ ,:; */
    {
        symbol = getchar();                                      /* ввод следующего символа */
        if (symbol == ' ');                                      /* если след. символ не пробел */
        else putchar(' ');                                       /* вывести пробел*/
            putchar(symbol);                                     /* вывести символ */
    }
    return symbol;
}

/* Проверка наличия пробела и заглавной буквы после !?. */
char check2(char symbol)
{
    if ((symbol == '!') || (symbol == '?') || (symbol == '.'))   /* если символ !?. */
    {
        symbol = getchar();                                      /* ввод 1 символа */
        if (symbol == ' ')                                       /* если 1 символ - пробел */
        {
            putchar(symbol);                                     /* вывести 1 символ */
            symbol = getchar();                                  /* ввод 2 символа */
            if ((symbol >= 'a') && (symbol <= 'z'))              /* если 2 символ - строчный */
                symbol -= (char)CHAR;                            /* сделать 2 символ прописным */
        }
        else                                                     /* если 1 символ - не пробел */
        {
            putchar(' ');                                        /* вывести пробел */
            if ((symbol >= 'a') && (symbol <= 'z'))              /* если 1 символ - строчный */
                symbol -= (char)CHAR;                            /* сделать 1 символ прописным */
        }
        putchar(symbol);                                         /* вывести ппрописной символ */
    }
    return symbol;
}

