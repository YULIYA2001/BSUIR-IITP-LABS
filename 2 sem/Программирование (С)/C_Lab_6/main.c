#include "func.h"

int main(void)
{
    Item *root = NULL;  /* Корень дерева */
    int num[100], is_balance, i = 0;

    setlocale (LC_CTYPE, "Russian");
    printf("Ввод целых чисел (пока не введен '0'). Бинарное дерево поиска ");  /* условие */
    printf("(без повторов). Проверка сбалансированности\n\n");                 /* условие */
    printf("Введите целые числа через пробел (0+\"Enter\" - прекращение ввода).");
    printf("\nНапример: 1 2 3 4 0+\"Enter\"\n\n");
    do
    {
        if (scanf("%d", &num[i]) != 1)
        {
            printf("Неверный ввод");
            return 1;
        }
        if (num[i] == 0)
            break;
        AddNode(num[i], &root);
        i++;
    }while(1);
    if (root != 0)
    {
        printf("\nБинарное дерево поиска (по возрастанию):\n");
        LeftOrder(root);
        printf("\n\n");
        is_balance = Balance(root);
        if (is_balance)
            printf("Дерево сбалансированно\n");
        if (!is_balance)
            printf("Дерево не сбалансированно\n");
    }
    return 0;
}
