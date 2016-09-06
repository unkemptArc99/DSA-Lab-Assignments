/*********************************************************
Name : Abhishek
Roll No : B15103
IC 250 Lab Assignment 04 - Question 2 - Option 1 - Header file
Date : 08/09/2016
*********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node
{
    int info;
    struct node *ptr;
}*top,*top1,*temp,*temp1;

int topelement();
void push(int data);
int pop();
bool empty();
void display();
void destroy();
void create();
void reverse();
void insert(int data);