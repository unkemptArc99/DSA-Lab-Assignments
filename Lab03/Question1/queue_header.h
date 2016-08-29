/*********************************************************
Name : Abhishek
Roll No : B15103
IC 250 Lab Assignment 03 - HOT POTATO PROBLEM - Question 1 - Header file
Date : 01/09/2016
*********************************************************/
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int front;
	int rear;
	int *qu;
	int curr_size;
	int max_size;
}queue;

queue allocate(int n);
void push(queue *p,int data);
int pop(queue *p);
int front_element(queue *p);