#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#define M 10 /* диапазон случайных значений */

/* Случайное заполнение массива */
void input(int rows, int columns, int **array)
{
    int i, j;

    srand(time(NULL));
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < columns; j++)
        {
            array[i][j] = (1 + rand()) % M;
        }
    }
}


/* Вывод элементов массива */
void output(int rows, int columns, int **array)
{
    int i, j;

    putchar('\n');
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < columns; j++)
        {
            printf("%5d ", array[i][j]); /* 5 знакомест под элемент массива */
        }
        putchar('\n');
    }
}

/* Поиск мах элемента */
void max(int rows, int columns, int **array, int *max_i, int *max_j)
{
    int i, j, max = array[0][0];

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < columns; j++)
        {
            if (array[i][j] >= max)
            {
                max = array[i][j];
                *max_i = i;
                *max_j = j;
            }
        }
    }
}


/* Добавление строки из нулей после строки с мах элементом*/
void null_row(int rows, int columns, int **array, int max_i, int max_j)
{
    int i, j;

    for (i = rows - 1; i > max_i; i--)
    {
        for (j = 0; j < columns; j++)
        {
            array[i][j] = array[i-1][j];
        }
    }
    for (j = 0; j < columns; j++)
    {
        array[max_i + 1][j] = 0;
    }
}

/* Зеркальное отображение элементов массива относительно главной диагонали */
void mirror_main_diagonal(int rows, int columns, int **array, int **help_array)
{
    int i, j;

    for (j = 0; j < columns; j++)
    {
        for (i = 0; i < rows; i++)
        {
            help_array[j][i]=array[i][j];
        }
    }
}

/* Зеркальное отображение элементов массива относительно побочной диагонали */
void mirror_side_diagonal(int rows, int columns, int **array, int **help_array)
{
    int i, j;

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < columns; j++)
        {
            array[i][j] = help_array[columns - 1 - j][rows - 1 - i];
        }
    }
}






