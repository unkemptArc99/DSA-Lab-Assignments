/*********************************************************
Name : Abhishek
Roll No : B15103
IC 250 Lab Assignment 06 - Question 1 - Main file
Date : 22/09/2016
*********************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "A_header.h"

int main(int argc, char const *argv[])
{
	int ch;
	int x,y,*a,*b;
	int num;
	int x1;
	char str1[100000],str2[100000];
	system("clear");
	printf("1 - Swap Pointers\n");
	printf("2 - Print Pointer Value\n");
	printf("3 - Compare Ints\n");
	printf("4 - Compare Strings\n");
	printf("5 - Count till this Num\n");
	printf("6 - Exit\n");
	while(1)
	{
		printf("Enter your choice : ");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				printf("Enter the two numbers : ");
				scanf("%d %d",&x,&y);
				a=&x;
				b=&y;
				swapPointers(a,b);
				break;
			case 2:
				printf("Enter the number : ");
				scanf("%d",&x);
				a=&x;
				printPointerValue(a);
				break;
			case 3:
				printf("Enter the two numbers : ");
				scanf("%d %d",&x,&y);
				a=&x;
				b=&y;
				int res=compareInts(a,b);
				if(res==1)
					printf("a>b\n");
				else
					printf("a<b or a=b\n");
				break;
			case 4:
				printf("Enter the first string : ");
				scanf("%s",str1);
				printf("Enter the second string : ");
				scanf("%s",str2);
				x1=compareStrings(str1,str2);
				printf("%d\n",x1);
				break;
			case 5:
				printf("Enter the number (greater than or equal to 1) : ");
				scanf("%d",&num);
				countTillThisNum(&num);
				break;
			case 6:
				exit(0);
			default:
				printf("WRONG INPUT\n");
				break;
		}
	}
	return 0;
}