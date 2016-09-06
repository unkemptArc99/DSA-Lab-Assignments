/*********************************************************
Name : Abhishek
Roll No : B15103
IC 250 Lab Assignment 04 - Question 1 - Option 2 - Main file
Date : 08/09/2016
*********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack_header.c"
#include <string.h>

int main(int argc, char const *argv[])
{
	printf("WELCOME TO THE PARANTHESIS CHECKER\n");
	printf("\n----------------------------------\n");
	printf("Please enter the expression to check (or 0 to exit) : \n");
	char string[20];
	scanf("%s",string);
	if(strcmp(string,"0")==0)
		return 0;
	else
	{
		int n=strlen(string),i;
		stack st_main=allocate(n);
		for(i=0;i<n;++i)
		{
			bool cech=push(&st_main,string[i]);
			if(!cech)
			{
				printf("ERROR\n");
				return -1;
			}
		}
		bool cech1=para_check(st_main);
		if(cech1)
			printf("Expression \"%s\" is having a BALANCED paranthesis.\n",string);
		else
			printf("Expression \"%s\" is having an UN-BALANCED paranthesis.\n",string);
	}
	return 0;
}