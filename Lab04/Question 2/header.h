/*********************************************************
Name : Abhishek
Roll No : B15103
IC 250 Lab Assignment 04 - Question 2 - Option 1 - Header file
Date : 08/09/2016
*********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node								//Struct implementation of Stack
{
    int info;
    struct node *ptr;
}*top,*top1,*temp,*temp1;

int topelement();						//Displays top element of the stack
void push(int data);					//Pushes elements into the stack
int pop();								//Pops elements from the stack
bool empty();							//Checks if the stack is empty or not
void display();							//Displays all the elements of stack
void destroy();							//Destroys the stack
void create();							//Initial allocation of the stack
void reverse();							//Main reverse function which is exteriorly recursed
void insert(int data);					//intrinsic reverse function which holds the value into a call stack and then inserts it