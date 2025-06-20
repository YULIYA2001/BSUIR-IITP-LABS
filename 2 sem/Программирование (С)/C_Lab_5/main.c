#include "func.h"

int main(void)
{
    int arr1[] = {1, 3, 10}, arr2[] = {2, 4, 6, 11};
    int amount1, amount2;

    setlocale (LC_CTYPE, "Russian");
    printf("Объединить две упорядоченные очереди в упорядоченный двунаправленный список\n\n");  /* условие */
    amount1 = sizeof(arr1) / sizeof(int);
    amount2 = sizeof(arr2) / sizeof(int);
    Enqueue(1, amount1, arr1);
    Enqueue(2, amount2, arr2);
    Display_Queue(1);
    printf("\n\n");
    Display_Queue(2);
    printf("\n\n");
    List_of_2_queues(amount1, amount2);
    Display_List();
    printf("\n");
    return 0;
}

