/*********************************************************
Name : Abhishek
Roll No : B15103
IC 250 Lab Assignment 03 - IMPLEMENTING QUEUE USING STACKS - Question 1 - Header file
Date : 01/09/2016
*********************************************************/
#include <stdio.h>
#include <stdlib.h>

struct node{
	int num;
	struct node *ptr;
};

int count=0;

int topelement(struct node **top);
void push(struct node **top,int data);
int pop(struct node **top);
void destroy(struct node **top);
struct node create();