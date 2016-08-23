/***********************************************
Name: Abhishek
Roll: B15103
Purpose: IC250 Assignment 02 - Question 1 - TOWER OF HANOI 
Date: 25/08/16
***********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

static int count=0;

void DiskMove(int n,char source,char dest,char spare)
{
	if(n==1)
	{
		count++;
		printf("[%d] Move disk from Peg %c to Peg %c\n",count,source,dest);
	}
	else
	{
		DiskMove(n-1,source,spare,dest);
		count++;
		printf("[%d] Move disk from Peg %c to Peg %c\n",count,source,dest);
		DiskMove(n-1,spare,dest,source);
	}
}

int main(int argc, char const *argv[])
{
	bool selection;			//False, if recursion is chosen, and True, if iteration is chosen.
	if(argc!=2)
	{
		printf("ERROR! Wrong input for the program. Type \"./main -h\" for help.\n");
		return -1;
	}
	else
	{
		if(strcmp(argv[1],"-h")==0)
			printf("This is the \"TOWER OF HANOI\" Program. Just choose the options - iterative or recursive - with \"-i\" and \"-r\" arguments and type the number of discs for which you want to perform the game\n");
		else if(strcmp(argv[1],"-r")==0)
			selection=false;
		else if(strcmp(argv[1],"-i")==0)
			selection=true;
		else
		{
			printf("ERROR! Wrong input for the program. Type \"./main -h\" for help.\n");
			return -1;
		}
	}
	if(!selection)				//RECURSION METHOD
	{
		int n;
		printf("Enter the number of disks : ");
		scanf("%d",&n);
		printf("\nConsidering Peg A as the source, Peg B as the destination, and Peg C as the spare\n");
		printf("Disk movement sequence to solve it is as follows :\n\n");
		DiskMove(n,'A','B','C');
		printf("\n");
		printf("The total moves taken to complete the movement : %d\n",count);
	}
	return 0;
}