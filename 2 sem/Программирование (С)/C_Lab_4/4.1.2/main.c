#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "func.h"
#define CHAR 32;

int main()
{
    char symbol;

    printf("Enter text (in English):\n");
    symbol = getchar();
    /* Проверка первой заглавной буквы */
    if ((symbol >= 'a') && (symbol <= 'z'))
        symbol -= (char)CHAR;
    putchar(symbol);
    /* Проверки на ,:;!?. */
    while (symbol != '\n')
    {
        symbol = getchar();
        putchar(symbol);
        check1(symbol);     /* Для ,:; */
        check2(symbol);     /* Для !?. */
    }
    getch();
    return 0;
}
