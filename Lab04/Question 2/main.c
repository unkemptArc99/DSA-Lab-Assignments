/*********************************************************
Name : Abhishek
Roll No : B15103
IC 250 Lab Assignment 04 - Question 2 - Option 1 - Main file
Date : 08/09/2016
*********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "header.h"

void main()
{
    int no, ch, e;
 
    printf("\n 1 - Push");
    printf("\n 2 - Pop");
    printf("\n 3 - Top");
    printf("\n 4 - Empty");
    printf("\n 5 - Exit");
    printf("\n 6 - Dipslay");
    printf("\n 7 - Reverse");
    printf("\n 8 - Destroy stack");
 
    create();
 
    while (1)
    {
        printf("\n Enter choice : ");
        scanf("%d", &ch);
 
        switch (ch)
        {
        case 1:
            printf("Enter data : ");
            scanf("%d", &no);
            push(no);
            break;
        case 2:
            pop();
            break;
        case 3:
            if (top == NULL)
                printf("No elements in stack");
            else
            {
                e = topelement();
                printf("\n Top element : %d", e);
            }
            break;
        case 4:
            if(empty())
            	printf("Yes\n");
            else
            	printf("No\n");
            break;
        case 5:
            exit(0);
        case 6:
            display();
            break;
        case 7:
            reverse();
            break;
        case 8:
            destroy();
            break;
        default :
            printf(" Wrong choice, Please enter correct choice  ");
            break;
        }
    }
}
