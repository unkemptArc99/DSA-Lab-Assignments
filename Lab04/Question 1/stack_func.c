/*********************************************************
Name : Abhishek
Roll No : B15103
IC 250 Lab Assignment 04 - Question 1 - Option 2 - Function file
Date : 08/09/2016
*********************************************************/
#include "stack_header.c"

stack allocate(int n)
{
	stack p;
	p.top=0;
	p.st=(char *)malloc(n*sizeof(char));
	p.max_size=n;
	return p;
}

bool push(stack *p,char data)
{
	if (p->top>=p->max_size)
	{
		printf("ERROR!!\n");
		return false;
	}
	else
	{
		p->st[p->top]=data;
		p->top++;
		return true;
	}
}

bool para_check(stack p)					//This function maintains an index which is incresed when it reads '(' and decreased when it reads ')'
{											//Thus, at the end we only need to check if index is 0 or not
	int index=0,i=0;
	for(i=0;i<=p.top;++i)
	{
		if(p.st[i]=='(')
			index++;
		else if(p.st[i]==')')
			index--;
		if(index<0)
			break;
	}
	if(index==0)
		return true;
	else
		return false;
}

void destroy(stack *p)
{
	free(p->st);
}