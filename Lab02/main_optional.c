/***********************************************
Name: Abhishek
Roll: B15103
Purpose: IC250 Assignment 02 - Question 2 (OPTIONAL) - DOUBLE TOWER OF HANOI 
Date: 25/08/16
***********************************************/
#include <stdio.h>
#include <stdlib.h>

static int count=0;

void DiskMove(int n,char source,char dest,char spare)				//Recursive method function
{
	if(n==2)
	{
		count++;
		printf("[%d] Move disk from Peg %c to Peg %c\n",count,source,dest);
		count++;
		printf("[%d] Move disk from Peg %c to Peg %c\n",count,source,dest);
	}
	else
	{
		DiskMove(n-2,source,spare,dest);
		count++;
		printf("[%d] Move disk from Peg %c to Peg %c\n",count,source,dest);
		count++;
		printf("[%d] Move disk from Peg %c to Peg %c\n",count,source,dest);
		DiskMove(n-2,spare,dest,source);
	}
}

int main(int argc, char const *argv[])
{
	printf("Welcome to the simulator of double tower of hanoi. \n");
	printf("This tower of hanoi takes 2n disks, in which there are two disks of the same size.\n");
	printf("Enter the number of disks (it should be an even number since you are accessing the program for double tower of hanoi) : ");
	int n;
	scanf("%d",&n);
	if(n%2==1)
	{
		printf("Wrong Input! Expected Even Input. Exiting the program....\n");
		return -1;
	}
	else
	{
		DiskMove(n,'A','B','C');
		printf("\n");
		printf("The total moves taken to complete the movement : %d\n",count);
		count=0;
	}
	return 0;
}