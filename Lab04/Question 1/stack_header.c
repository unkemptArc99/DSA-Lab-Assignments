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

stack allocate(int n);
bool push(stack *p,char data);
bool para_check(stack p);
void destroy(stack *p);