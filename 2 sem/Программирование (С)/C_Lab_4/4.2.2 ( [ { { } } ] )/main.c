#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "func.h"
#define N 200

int main(void)
{
    char string[N];
    int i;
    FILE *fp;                               /* ”казатель на файл */

    fp = fopen("File.txt", "r+");
    if (!fp)
        exit(1);                            /* проверка на открытие файла */
    while (fgets(string, N, fp) != NULL);   /* запись содержимого файла в массив string*/
    printf("Text from file:\n%s\n", string);
    /* проверка на соответсвие скобок */
    CheckParentheses(string);
    /* замена нужных скобок */
    Replace(string);
    printf("Corrected text:\n%s", string);
    /* добавление в файл измененного текста */
    fputs("\nCorrected text:\n", fp);
    fputs(string, fp);
    fclose(fp);
    getch();
    return 0;
}

