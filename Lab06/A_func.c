/*********************************************************
Name : Abhishek
Roll No : B15103
IC 250 Lab Assignment 06 - Question 1 - Function file
Date : 22/09/2016
*********************************************************/
#include "A_header.h"

void swapPointers(int *a,int *b)
{
	printf("Address of pointer \"a\" is %p (before)\nAddress of pointer \"b\" is %p(before)\n",a,b);
	int *temp;
	temp=a;
	a=b;
	b=temp;
	printf("Address of pointer \"a\" is %p (after)\nAddress of pointer \"b\" is %p(after)\n",a,b);
}

void printPointerValue(int *a)
{
	printf("The value of the variable pointed by the pointer is %d\n",*a);
}

int compareInts(int *a,int *b)
{
	if(*a>*b)
		return 1;
	else
		return 0;
}

int compareStrings(char *a,char *b)
{
	int siza,sizb,comp,i;
	for(siza=0;;++siza)
		if(a[siza]=='\0')
			break;
	for(sizb=0;;++sizb)
		if(b[sizb]=='\0')
			break;
	if(siza>sizb)
		comp=sizb;
	else
		comp=siza;
	int flag=0;
	for(i=0;i<comp;++i)
	{
		if(a[i]<b[i])
			break;
		else if(a[i]>b[i])
		{
			flag=1;
			break;
		}
	}
	if(flag==1)
		return 1;
	if(i!=comp)
		return -1;
	else
	{
		if(siza>sizb)
			return 1;
		else
			return 0;
	}
}

void countTillThisNum(int num)
{
	if(num==1)
		printf("%d\n",num);
	else
	{
		countTillThisNum(num-1);
		printf("%d\n",num);
	}
}