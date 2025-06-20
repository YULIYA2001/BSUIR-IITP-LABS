#include <stdio.h>
#include <conio.h>
#include <locale.h>

void decision(int weight, int distance);
void order_details(int weight, int distance);

void my_2_1_6(void)
{
    int weight = 0, distance = 0;
    char choose;

    setlocale (LC_CTYPE, "Russian");
    printf("\t\t\t\t\t\tTask 1: \"EUROTRANS GROUP\"\n\n");
    printf("1 - Ввод веса (от 50 до 300)\n2 - Ввод расстояния (не более 4000)\n3 - Решение относительно заказа\n");
    printf("4 - Параметры заказа\n5 - Версия и автор программы\n6 - Выход\n");
    do
    {
        printf("\nВыберите пункт меню: ");
        choose = _getche();
        printf("\n");
        switch (choose)
        {
            case '1':
            {
                /* ввод числа и проверка ввода (новый ввод при неверных символах) */
                printf("Введите вес груза (тонны): ");
                while (scanf("%d", &weight) != 1)
                {
                    scanf("%*[^\n]");
                    printf("Некорректный ввод. Введите еще раз: ");
                }
                break;
            }
            case '2':
            {
                /* ввод числа и проверка ввода (новый ввод при неверных символах) */
                printf("Введите расстояние перевозки (км): ");
                while (scanf("%d", &distance) != 1)
                {
                    scanf("%*[^\n]");
                    printf("Некорректный ввод. Введите еще раз: ");
                }
                break;
            }
            case '3':
            {
                decision(weight, distance);
                break;
            }
            case '4':
            {
                order_details(weight, distance);
                break;
            }
            case '5':
            {
                printf("Версия 1.0.0\tАвтор: Голубович Ю. И.\n");
                break;
            }
            case '6':
            {
                printf("Вы вышли из программы\n");
                break;
            }
            default: printf("Неверный пункт меню\n");
        }
    } while (choose != '6');
}

/* Решение о принятии заказа */
void decision(int weight, int distance)
{
    if ((weight <= 0) || (distance <= 0))
        printf("Неверные исходные данные. Введите данные\n");
    else
    {
        if ((weight < 50) || (weight > 300) || (distance > 4000))
            printf("Ваш заказ отклонен \n");
        else
            printf("Ваш заказ принят \n");
    }
}

/* Вывод параметров заказа при его принятии */
void order_details(int weight, int distance)
{
    int cars;
    float order_cost, insurance;

    if ((weight <= 0) || (distance <= 0))
        printf("Неверные исходные данные. Введите данные\n");
    else
    {
        if ((weight < 50) || (weight > 300) || (distance > 4000))
            printf ("Ваш заказ отклонен\n");
        else
        {
            if ((weight % 20) == 0)
                cars = weight / 20;
            else
                cars = (weight / 20) + 1;
            insurance = distance * 2 * cars * 0.05;
            order_cost = (distance * 2 * cars) + insurance;
            printf("Количество машин - %d\n", cars);
            printf("Стоимость страховки - %.2f $\n", insurance);
            printf("Общая стоимость заказа - %.2f $\n", order_cost);
        }
    }
}
