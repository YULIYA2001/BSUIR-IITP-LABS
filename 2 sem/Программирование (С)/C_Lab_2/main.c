#include <stdio.h>
#include <conio.h>
#include <math.h>
#include "header.h"

int main(void)
{
    char task;

    printf("\t\t\t\t\t\tWELCOME TO LAB 2");
    do
    {
        printf("\n1 - 2.1.6\n2 - 2.2.6\n3 - exit\nChoose a task:");
        task = _getche();
        printf("\n");
        if (task == '1')
            my_2_1_6();
        else if (task == '2')
            my_2_2_6();
        else if (task == '3')
        {
            printf("\nExit");
            break;
        }
        else printf("\nWrong input. Try again\n");
   } while ((task  < 1) || (task >= 3));

}
