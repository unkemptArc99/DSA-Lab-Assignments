/*********************************************************
Name : Abhishek
Roll No : B15103
IC 250 Lab Assignment 03 - IMPLEMENTING QUEUE USING STACKS - Question 2 - Main file
Date : 01/09/2016
*********************************************************/
#include "queue_stack_func.h"
#include <stdio.h>
#include <stdlib.h>

static int index;				//to maintain the index of the number of steps
static int count;				//to maintain the index of the number of elements in the total queue formed by the two stacks

int main(int argc, char const *argv[])
{
	count=0;
	index=0;
	int flag1=0,flag2=0;
	int n=-1,k=-1,i,j;
	printf("\nWELCOME TO THE HOT POTATO PROBLEM OR THE JOSEPHUS PROBLEM SIMULATOR\n");
	printf("\n-------------------------------------------------------------------\n");
	printf("\nEnter the number of children going to participate the game : ");
	while(scanf("%d",&n)!=1 || n<0)
	{
		printf("WRONG INPUT!\n");
	}
	printf("Enter the elimination rule : ");
	while(scanf("%d",&k)!=1 || k<0)
	{
		printf("WRONG INPUT!\n");
	}
	printf("The removal sequence is as follows : \n\n");
	stack stack1=allocate(n);						//STACK 1
	stack stack2=allocate(n);						//STACK 2
	for(i=n;i>0;i--)
	{
		push(&stack1,i);
		count++;
	}
	for(i=1;count>1;++i)
	{
		if(i%k==0)
		{
			index++;
			int x=pop(&stack1);
			count--;
			if(index==1)
				printf("[%d] Firstly, the person at position at position %d is removed\n",index,x);
			else if(count==1)
				printf("[%d] Finally, the person at position %d is removed\n",index,x);
			else
				printf("[%d] Then, the person at position %d is removed\n",index,x);
		}
		else
		{
			int x=pop(&stack1);
			while(stack1.curr_size>0)
			{
				int y=pop(&stack1);				//Pushing everything from stack1 to stack2
				push(&stack2,y);				
			}
			push(&stack1,x);					//pushing the enqueued element at the bottom of stack1
			while(stack2.curr_size>0)
			{
				int y=pop(&stack2);				//Pushing back everything from stack2 to stack1
				push(&stack1,y);
			}
		}
	}
	int x1=front_element(&stack1);
	printf("\nHence, the person at position %d survives (WINNER)\n",x1);
	return 0;
}