/*********************************************************
Name : Abhishek
Roll No : B15103
IC 250 Lab Assignment 06 - Question 3 - Header file
Date : 22/09/2016
*********************************************************/
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

struct node
{
	int data;
	struct node* link;
	struct node* random;
};

void append(struct node**,int);
void randominit(struct node**,int);
void display(struct node*);
int count(struct node*);
struct node *deepCopy(struct node**);