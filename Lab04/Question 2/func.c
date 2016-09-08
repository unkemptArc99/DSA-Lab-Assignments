/*********************************************************
Name : Abhishek
Roll No : B15103
IC 250 Lab Assignment 04 - Question 2 - Option 1 - Function file
Date : 08/09/2016
*********************************************************/
#include "header.h"

int count=0;

int topelement()
{
    return(top->info);
}

void push(int data)
{
    if (top == NULL)
    {
        top =(struct node *)malloc(1*sizeof(struct node));
        top->ptr = NULL;
        top->info = data;
    }
    else
    {
        temp =(struct node *)malloc(1*sizeof(struct node));
        temp->ptr = top;
        temp->info = data;
        top = temp;
    }
    count++;
}

void display()
{
    top1 = top;
 
    if (top1 == NULL)
    {
        printf("Stack is empty");
        return;
    }
 
    while (top1 != NULL)
    {
        printf("%d ", top1->info);
        top1 = top1->ptr;
    }
}

int pop()
{
    top1 = top;
 	int x;
    if (top1 == NULL)
    {
        printf("\n Error : Trying to pop from empty stack");
        return;
    }
    else
        top1 = top1->ptr;
    printf("\n Popped value : %d", top->info);
    x=top->info;
    free(top);
    top = top1;
    count--;
    return x;
}

bool empty()
{
	if(top==NULL)
		return true;
	else
		return false;
}

void destroy()
{
    top1 = top;
 
    while (top1 != NULL)
    {
        top1 = top->ptr;
        free(top);
        top = top1;
        top1 = top1->ptr;
    }
    free(top1);
    top = NULL;
     
    printf("\n All stack elements destroyed");
    count = 0;
}

void create()
{
    top = NULL;
}

void insert(int data)                   /** Hold all items in Function Call Stack until we
                                        reach end of the stack. When the stack becomes
                                        empty, the above if part is executed and the item is inserted
                                        at the bottom */
{
	if(empty())
		push(data);
	else
	{
		int x=pop();
		insert(data);
                                        /* Once the item is inserted at the bottom, push all
                                            the items held in Function Call Stack */
		push(x);
	}
}

void reverse()
{
	if(!empty())
	{
        /* Hold all items in Function Call Stack until we
           reach end of the stack */
		int x=pop();
		printf("Reversing %d\n",x);
		reverse();
        /* Insert all the items (held in Function Call Stack)
           one by one from the bottom to top. Every item is
           inserted at the bottom */
		insert(x);
	}
}