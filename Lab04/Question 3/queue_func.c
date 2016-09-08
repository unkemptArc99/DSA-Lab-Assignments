/*********************************************************
Name : Abhishek
Roll No : B15103
IC 250 Lab Assignment 04 - Question 3 - Function file
Date : 08/09/2016
*********************************************************/
#include "queue_header.h"

queue allocate(int n)
{
	queue p;
	p.front=-1;								//front=NULL
	p.rear=-1;								//rear=NULL
	p.qu=(int *)malloc(n*sizeof(int));		//allocating space for the dynamic array
	p.curr_size=0;							//current size counter
	p.max_size=n;							//maximum allocated size of the queue
	return p;
}

void push(queue *p,int data)
{
	if(p->curr_size==p->max_size)			//queue is full
	{
		return;
	}
	else
	{
		if(p->front==-1)					//queue is empty
		{
			p->front=0;
			p->rear=0;
		}
		else if(p->rear==p->max_size-1)		//cyclicity of the rear variable
			p->rear=0;
		else
			p->rear++;
		p->qu[p->rear]=data;		
		p->curr_size++;
	}
}

int pop(queue *p)
{
	int x;
	if(p->curr_size==0)						//queue is empty
	{
		return -1;
	}
	else
	{
		x=p->qu[p->front];
		p->qu[p->front]=-1;
		p->curr_size--;
		if(p->front==p->rear)				//only one element is present
		{
			p->front=-1;
			p->rear=-1;
		}
		else if(p->front==p->max_size-1)	//cyclicity of the front variable
			p->front=0;
		else
			p->front++;
	}
	return x;
}

int front_element(queue *p)
{
	return p->qu[p->front];					//returning top element
}

void display(queue *p)						//function to display the contents of the queue
{
	int i=p->front;
	while(i!=p->rear)
	{
		printf("%d ",p->qu[i]);
		i++;
		if(i==p->max_size)					//cyclicity of the index
			i=0;
	}
	printf("%d\n",p->qu[i]);
}