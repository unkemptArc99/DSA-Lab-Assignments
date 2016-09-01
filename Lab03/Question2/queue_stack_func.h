/*********************************************************
Name : Abhishek
Roll No : B15103
IC 250 Lab Assignment 03 - IMPLEMENTING QUEUE USING STACKS - Question 2 - Header file
Date : 01/09/2016
*********************************************************/
#include <stdio.h>
#include <stdlib.h>

typedef struct node{				//Struct implementation of array-implemented stack
	int top;
	int *qu;
	int curr_size;
	int max_size;
}stack;

stack allocate(int n);				//Allocating space for the dynamic array
void push(stack *p,int data);		//Push function
int pop(stack *p);					//Pop function
int front_element(stack *p);		//To show the front element of the stack