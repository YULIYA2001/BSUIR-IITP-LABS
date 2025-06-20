#include <stdio.h>
#include <malloc.h>
#include <conio.h>
#include "func.h"

int main(void)
{
    int **array, **help_array;    /* указатель на массив */
    int i, rows, columns, max_i, max_j;
    char cheeck;

    printf("Enter number of rows (>1): ");
    /* Проверка на ввод: не циры || цифры < 2 || строки вида: цифра + буквы */
    while (scanf("%d", &rows) != 1 || rows <= 1 || (scanf("%c", &cheeck) == 1 && cheeck != '\n'))
    {
        scanf("%*[^\n]");
        printf("Wrong input. Try again.\n");
        printf("Enter number of rows (>1): ");
    }
    columns = rows - 1;
    printf("\nYour array:\n");

    /* Память под основной массив*/
    array = (int**)malloc(rows * sizeof(int*));     /* Выделение памяти под массив указателей*/
    if (!array)
    {
        printf("error");
        exit(1);
    }
    for (i = 0; i < rows; i++)
    {
        array[i] = (int*)malloc(columns * sizeof(int));     /* Выделение памяти под хранение строк */
    }

    input(rows, columns, array);    /* Случайное заполнение массива */
    output(rows, columns, array);   /* Вывод элементов массива */

    max(rows, columns, array, &max_i, &max_j);    /* Поиск мах элемента */

    /* Увеличение памяти под основной массив*/
    array = (int**)realloc(array, (rows + 1) * sizeof(int*));
    if (!array)
    {
        printf("error");
        exit(1);
    }
    rows += 1;
    array[rows - 1] = (int*)malloc(columns * sizeof(int));

    null_row(rows, columns, array, max_i, max_j);   /* Добавление строки из нулей */

    /* Память под вспомогательный (горизонтальный) массив*/
    help_array = (int**)malloc(columns * sizeof(int*));
    if (!help_array)
    {
        printf("error");
        exit(1);
    }
    for (i = 0; i < columns; i++)
    {
        help_array[i] = (int*)malloc(rows * sizeof(int));
    }

    mirror_main_diagonal(rows, columns, array, help_array);   /* Отображение относительно главной диагонали */
    mirror_side_diagonal(rows, columns, array, help_array);   /* Отображение относительно побочной диагонали */
    printf("\nResulting array:\n");
    output(rows, columns, array);

    /* Очистка памяти основного и вспомогательного массивов*/
    for (i = 0; i < rows; i++)
        free(array[i]);
    free(array);
    for (i = 0; i < columns; i++)
        free(help_array[i]);
    free(help_array);

    getch();
    return 0;
}
