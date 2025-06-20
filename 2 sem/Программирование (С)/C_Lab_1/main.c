#include <stdio.h>
#include <conio.h>

int main(void)
{
    char num, sign;
    int sum, i, check_not_num, check_enter, check_dots, check_first_last_dot;

    do
    {
        printf("Input a real number: ");
        num = '0';                  /* вводимое пользователем число (посимвольно) */
        sum = 0;                    /* сумма 3-х цифр после запятой */
        check_enter = 0;            /* индификатор ввода пустой строки (enter) */
        check_dots = 0;             /* индификатор ввода более 1 точки */
        check_not_num = 0;          /* индикатор неверного ввода */
        check_first_last_dot = 0;   /* индикатор ввода первого или последнего символа "точка" */
        while (num != '\n')
        {
            scanf("%c", &num);
            /* проверка на пустой ввод */
            check_enter++;
            /* проверка на неверный ввод (буквы, знаки) */
            if (((num >= '0') && (num <= '9')) || (num == '.') || (num == '\n'));
            else
                check_not_num = 1;
            /* подсчет суммы 3 цифр после точки */
            if (num == '.')
            {
                /* проверка на первый символ точка (.111) */
                if (check_enter == 1)
                    check_first_last_dot = 1;
                else
                {
                    /* проверка на несколько точек в числе (11.111.111) */
                    check_dots++;
                    for (i = 0; i < 3; i++)
                    {
                        scanf("%c", &num);
                        /* проверка на неверный ввод (буквы, знаки) среди 3 знаков после точки */
                        if (((num >= '0') && (num <= '9')) || (num == '\n'));
                        else
                            check_not_num = 1;
                        /* проверка на последний символ точка (111.) */
                        if((i == 0) && (num == '\n'))
                            check_first_last_dot = 1;
                        if (num != '\n')
                            sum += (int)num - 48;
                        else
                            break;
                    }
                }
            }
        }
        if ((check_not_num == 1) || (check_enter == 1) || (check_dots > 1) || (check_first_last_dot == 1))
            printf("\nWrong input\n");
        else
        {
            printf("The sum of the first 3 digits of the fractional part of the number is ");
            printf("%d", sum);
        }
        printf("\nPress + to try again ");
        sign = getche();       /* нужна ли пользователю след. попытка ввода */
        printf("\n");
    } while (sign == '+');
    _getch();
}
