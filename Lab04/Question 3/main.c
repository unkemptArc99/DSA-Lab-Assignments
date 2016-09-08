/*********************************************************
Name : Abhishek
Roll No : B15103
IC 250 Lab Assignment 04 - Question 3 - Main file
Date : 08/09/2016
*********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "queue_header.h"

int main()
{
	int no,ch,e;
	printf("Stack implementation using queue\n");
	printf("\n--------------------------------\n");
	printf("\n 1 - Push");                                             //All choices are listed
    printf("\n 2 - Pop");
    printf("\n 3 - Top");
    printf("\n 4 - Exit");
    printf("\n 5 - Display");
    printf("\n 6 - Destroy stack");
 
 	int n;
 	printf("\nEnter the max size of stack : ");
 	scanf("%d",&n);
    queue q1,q2;
    q1=allocate(n);
    q2=allocate(n);
 
    while (1)
    {
        printf("\n Enter choice : ");
        scanf("%d", &ch);
 
        switch (ch)
        {
        case 1:
            printf("Enter data : ");
            scanf("%d", &no);
            if(q1.curr_size==n)
            	printf("Cannot push! Stack full\n");
            else
            {
            	while(q1.curr_size>0)                              //Pushing all the remaining elements into another stack so that the new element can come at the top
            	{
            		int x=pop(&q1);
            		push(&q2,x);
            	}
            	push(&q1,no);
            	while(q2.curr_size>0)
            	{
            		int x=pop(&q2);
            		push(&q1,x);
            	}
            	printf("Pushed %d\n",no);
            }
            break;
        case 2:
        	if(q1.curr_size==0)
        		printf("Cannot pop! Stack Empty!");
        	else
        	{
        		int x=pop(&q1);
        		printf("%d has been popped\n", x);
        	}
            break;
        case 3:
            printf("%d\n", front_element(&q1));
        case 4:
        	free(q1.qu);
            free(q2.qu);
            printf("Destroyed stack!\n");
            exit(0);
        case 5:
            display(&q1);
            break;
        case 6:
            free(q1.qu);
            free(q2.qu);
            printf("Destroyed stack!\n");
            break;
        default :
            printf(" Wrong choice, Please enter correct choice  ");
            break;
        }
    }
}