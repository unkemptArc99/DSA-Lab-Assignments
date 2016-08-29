/*********************************************************
Name : Abhishek
Roll No : B15103
IC 250 Lab Assignment 03 - HOT POTATO PROBLEM - Question 1 - Function File
Date : 01/09/2016
*********************************************************/
#include "queue_header.h"

queue allocate(int n)
{
	queue p;
	p.front=-1;
	p.rear=-1;
	p.qu=(int *)malloc(n*sizeof(int));
	p.curr_size=0;
	p.max_size=n;
	return p;
}

void push(queue *p,int data)
{
	if(p->curr_size==p->max_size)
	{
		return;
	}
	else
	{
		if(p->front==-1)
		{
			p->front=0;
			p->rear=0;
		}
		else if(p->rear==p->max_size-1)
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
	if(p->curr_size==0)
	{
		return -1;
	}
	else
	{
		x=p->qu[p->front];
		p->qu[p->front]=-1;
		p->curr_size--;
		if(p->front==p->rear)
		{
			p->front=-1;
			p->rear=-1;
		}
		else if(p->front==p->max_size-1)
			p->front=0;
		else
			p->front++;
	}
	return x;
}

int front_element(queue *p)
{
	return p->qu[p->front];
}