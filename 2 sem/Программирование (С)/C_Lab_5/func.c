#include "func.h"

Queue *head1 = NULL, *tail1 = NULL, *head2 = NULL, *tail2 = NULL;
List *head = NULL, *tail = NULL;

/* Заполнение очереди (значение взять из массива)*/
void Enqueue(int queue_num, int amount, int *arr)
{
    Queue *head, *tail;     /* общие переменные для заполнения двух очередей */
    int i;
    Queue* p;

    /* выбор очереди для заполнения */
    if (queue_num == 1)
    {
        head = head1;
        tail = tail1;
    }
    if (queue_num == 2)
    {
        head = head2;
        tail = tail2;
    }
    for (i = 0; i < amount; i++)
    {
        p = (Queue *)malloc(sizeof(Queue));
        p->data = arr[i];
        p->next = NULL;     /* установить признак конца очереди */
        if (head == NULL)   /* если очередь пуста... */
            head = p;       /*head указывает на созданный элемент*/
        else
            tail->next = p; /* поставить новый эл. в конец очереди*/
        tail = p;           /* tail указывает на конец очереди */
    }
    /*возвращение данных из общ. указателей указателям на 1 или  2 очередь */
    if (queue_num == 1)
    {
        head1 = head;
        tail1 = tail;
    }
    if (queue_num == 2)
    {
        head2 = head;
        tail2 = tail;
    }
}

/* Отобразить содержимое очереди */
void Display_Queue(int queue_num)
{
    Queue* p;

    /* выбор очереди для вывода на экран */
    if (queue_num == 1)
        p = head1;
    if (queue_num == 2)
        p = head2;
    if (p == NULL)
        printf("Queue is empty");
    else
        printf("Queue %d:", queue_num);
    while (p != NULL)
    {
        printf("\n%d", p->data);
        p = p->next;
    }
}

/* Запись содержимого двух очередей в список */
void List_of_2_queues(int amount1, int amount2)
{
    List_of_queue(amount1, 1);
    List_of_queue(amount2, 2);
}

/* Запись содержимого 1 очереди в список */
void List_of_queue(int amount, int queue_num)
{
    List *p, *cur = head;
    Queue *p1;
    int i;

    /* выбор из какой очереди заполнять */
    if (queue_num == 1)
        p1 = head1;
    if (queue_num == 2)
        p1 = head2;
    for (i = 0; i < amount; i++)
    {
        p = (List *)malloc(sizeof(List));
        p->data = p1->data;
        p->next = p->prev = NULL;
        if (head == NULL)       /* если список пуст*/
        {
            head = tail = p;        /* head и tail указывают на созданный элемент */
        }
        else
        {
            /* Поиск места для вставки */
            while (cur != NULL && p1->data > cur->data)
                cur = cur->next;
            if (cur == head)    /* если элемент нужно вставить в начало*/
            {
                p->next = head;
                head->prev = p;
                head = p;
            }
            else if (cur == NULL)   /* если элемент нужно вставить в конец*/
            {
                tail->next = p;
                p->prev = tail;
                tail = p;
            }
            else    /* если элемент нужно вставить в середину*/
            {
                cur->prev->next = p;
                p->prev = cur->prev;
                cur->prev = p;
                p->next = cur;
            }
        }
        p1 = p1->next;
    }
}

/* отображение списка */
void Display_List(void)
{
    List *p = head;

    if (p == NULL)
        puts("List is empty");
    else
    {
        printf("List:\n");
        printf("NULL <-> ");
        while (p != NULL)
        {
            printf("%d <-> ", p->data);
            p = p->next;
        }
        printf("NULL");
    }
}
