/*********************************************************
Name : Abhishek
Roll No : B15103
IC 250 Lab Assignment 03 - HOT POTATO PROBLEM - Question 1 - main file
Date : 01/09/2016
*********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "queue_header.h"

static int count;				//to maintain the index of the number of steps

int main(int argc, char const *argv[])
{
	count=0;
	int n,k,i;
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
	queue main_q=allocate(n);						//THE MAIN QUEUE
	for(i=0;i<n;++i)	
		push(&main_q,i+1);
	for(i=1;main_q.curr_size>1;++i)
	{
		if(i%k==0)
		{
			count++;
			int x=pop(&main_q);
			if(count==1)
				printf("[%d] Firstly, the person at position at position %d is removed\n",count,x);
			else if(main_q.curr_size==1)
				printf("[%d] Finally, the person at position %d is removed\n",count,x);
			else
				printf("[%d] Then, the person at position %d is removed\n",count,x);
		}
		else
		{
			int x=pop(&main_q);
			push(&main_q,x);
		}
	}
	int x1=front_element(&main_q);
	printf("\nHence, the person at position %d survives (WINNER)\n",x1);
	return 0;
}