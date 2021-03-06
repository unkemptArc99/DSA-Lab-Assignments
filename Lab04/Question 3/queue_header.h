/*********************************************************
Name : Abhishek
Roll No : B15103
IC 250 Lab Assignment 04 - Question 3 - Header file
Date : 08/09/2016
*********************************************************/
#include <stdio.h>
#include <stdlib.h>

typedef struct node{				//Struct implementation of array-implemented queue
	int front;
	int rear;
	int *qu;
	int curr_size;
	int max_size;
}queue;

queue allocate(int n);				//Allocating space for the dynamic array
void push(queue *p,int data);		//Push function (from the rear)
int pop(queue *p);					//Pop function (from the front)
int front_element(queue *p);		//To show the front element of the queue
void display(queue *p);				//To display the elements of the queue