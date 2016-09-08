/*********************************************************
Name : Abhishek
Roll No : B15103
IC 250 Lab Assignment 04 - Question 1 - Option 2 - Header file
Date : 08/09/2016
*********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node{
	int top;
	char *st;
	int max_size;
}stack;

stack allocate(int n);						//allocates memory for the stack
bool push(stack *p,char data);				//pushes elements into the stack
bool para_check(stack p);					//Paranthesis check function
void destroy(stack *p);						//Destroys the stack