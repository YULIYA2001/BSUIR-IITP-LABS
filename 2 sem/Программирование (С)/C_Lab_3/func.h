#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED

void input(int rows, int columns, int **array);
void output(int rows, int columns, int **array);
void max(int rows, int columns, int **array, int *max_i, int *max_j);
void null_row(int rows, int columns, int **array, int max_i, int max_j);
void mirror_main_diagonal(int rows, int columns, int **array, int **help_array);
void mirror_side_diagonal(int rows, int columns, int **array, int **help_array);

#endif // FUNC_H_INCLUDED
