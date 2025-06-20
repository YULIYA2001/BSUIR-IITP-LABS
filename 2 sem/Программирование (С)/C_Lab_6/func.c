#include "func.h"

/* проверка на сбалансированность */
int Balance(Item *node)
{
    int l, r;

    if (node == 0) return 1;

    l = Balance(node->left);            /* l, r - уровень узла (NULL-подузел всегда имеет уровень 1) */
    r = Balance(node->right);
    /* если на каком-то этапе выполнился следующий if, то дерево не сбалансированно */
    if (l == 0 || r == 0) return 0;
    /* если разность уровней >1, то дерево не сбалансированно */
    if (sign(l - r) > 1) return 0;
    /* уровень узла на 1 больше, чем больший уровень его поддерева */
    if (l > r)
        return (l + 1);
    else return (r + 1);
}

int sign(int a)
{
    if (a < 0)
        a = (-1) * a;
    return a;
}
/* добавление узла в дерево */
void AddNode(int data, Item **node)
{
    if (*node == NULL)                              /* если узла нет */
    {
        *node = (Item *)calloc(1, sizeof(Item));    /* создать узел */
        (*node)->data = data;
        (*node)->left = (*node)->right = NULL;
    }
    else
    {
        if (data < (*node)->data)               /* если новое значение меньше, чем в узле */
            AddNode(data, &(*node)->left);      /* записывать в левое поддерево */
        else if (data > (*node)->data)          /* если новое значение больше, чем в узле */
            AddNode(data, &(*node)->right);     /* записывать в правое поддерево */
        /*else
            puts("Такой элемент уже есть в дереве");*/
    }
}

/* обход дерева слева (по возрастанию значений) */
void LeftOrder(Item *node)
{
    if (node->left)
        LeftOrder(node->left);
    printf("%5d", node->data);
    if (node->right)
        LeftOrder(node->right);
}
