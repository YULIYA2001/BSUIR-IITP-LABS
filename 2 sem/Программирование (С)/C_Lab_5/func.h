#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include <locale.h>

typedef struct queue
{
    int data;
    struct queue *next;
} Queue;

typedef struct list
{
    int data;
    struct list *next;
    struct list *prev;
} List;

//для очереди
void Enqueue(int queue_num, int amount, int *arr);
void Display_Queue(int queue_num);
//для списка
void List_of_queue(int amount, int queue_num);
void List_of_2_queues(int amount1, int amount2);
void Display_List(void);

#endif // FUNC_H_INCLUDED
