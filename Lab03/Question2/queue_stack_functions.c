/*********************************************************
Name : Abhishek
Roll No : B15103
IC 250 Lab Assignment 03 - IMPLEMENTING QUEUE USING STACKS - Question 2 - Function file
Date : 01/09/2016
*********************************************************/
#include "queue_stack_func.h"

stack allocate(int n)
{
	stack p;
	p.top=-1;								//top=NULL
	p.qu=(int *)malloc(n*sizeof(int));		//allocating space for the dynamic array
	p.curr_size=0;							//current size counter
	p.max_size=n;							//maximum allocated size of the stack
	return p;
}

void push(stack *p,int data)
{
	if(p->curr_size==p->max_size)			//stack is full
	{
		return;
	}
	else
	{
		p->top++;
		p->qu[p->top]=data;		
		p->curr_size++;
	}
}

int pop(stack *p)
{
	int x;
	if(p->curr_size==0)						//stack is empty
	{
		return -1;
	}
	else
	{
		x=p->qu[p->top];
		p->qu[p->top]=-1;
		p->top--;
		p->curr_size--;
	}
	return x;
}

int front_element(stack *p)
{
	return p->qu[p->top];
}