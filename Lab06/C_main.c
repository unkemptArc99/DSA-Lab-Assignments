/*********************************************************
Name : Abhishek
Roll No : B15103
IC 250 Lab Assignment 06 - Question 3 - Main file
Date : 22/09/2016
*********************************************************/
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "C_header.h"

int main(int argc, char const *argv[])
{
	int ch,i,num,coun;
	struct node *main,*copy;
	main=NULL;
	copy=NULL;
	printf("1 - Append the linked list\n");
	printf("2 - Define the random pointers for the list created up to the point\n");
	printf("3 - Display the list\n");
	printf("4 - Generate a Deep Copy of the list\n");
	printf("5 - Exit\n");
	while(1)
	{
		printf("\nEnter your choice : ");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				printf("Enter the number to be added : ");
				scanf("%d",&num);
				append(&main,num);
				break;
			case 2:
				coun=count(main);
				randominit(&main,coun);
				break;
			case 3:
				display(main);
				break;
			case 4:
				printf("The present list is \n");
				display(main);
				copy=deepCopy(&main);
				printf("The copied list is \n");
				display(copy);
				break;
			case 5:
				free(main);
				free(copy);
				exit(0);
			default:
				printf("WRONG INPUT!!\n");
				break;
		}
	}
	return 0;
}