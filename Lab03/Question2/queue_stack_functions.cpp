/*********************************************************
Name : Abhishek
Roll No : B15103
IC 250 Lab Assignment 03 - IMPLEMENTING QUEUE USING STACKS - Question 1 - Header file
Date : 01/09/2016
*********************************************************/
#include "queue_stack_func.h"

int topelement(struct node **top)
{
    return(*top->num);
}

void push(struct node **top,int data)
{
	struct node *temp1;
	if(*top==NULL)
    {
        *top =(struct node *)malloc(1*sizeof(struct node));
        *top->ptr = NULL;
        *top->num = data;
    }
    else
    {
        temp1 =(struct node *)malloc(1*sizeof(struct node));
        temp1->ptr = top;
        temp1->num = data;
        *top = temp1;
    }
    count++;
}

int pop(struct node **top)
{
	struct node *temp2;
	temp2 = *top;
    if (temp2 == NULL)
    {
        printf("\n Error : Trying to pop from empty stack");
        return;
    }
    else
        temp2 = temp2->ptr;
    int x=*top->num;
    free(*top);
    *top = temp2;
    count--;
    return x;
}

void destroy(struct node **top)
{
	struct node *temp1;
	temp1 = *top;
    while (*top1 != NULL)
    {
        temp1 = *top->ptr;
        free(*top);
        *top = temp1;
        temp1 = temp1->ptr;
    }
    free(temp1);
    *top = NULL;
    count = 0;
}

struct node create()
{
	struct node *top;
	top=NULL;
	return(top);
}