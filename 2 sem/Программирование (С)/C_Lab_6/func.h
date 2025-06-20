#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct item
{
    int data;
    struct item *left;
    struct item *right;
} Item;

void AddNode(int data, Item **node);
void LeftOrder(Item *node);
int Balance(Item *node);
int sign(int a);

#endif // FUNC_H_INCLUDED
