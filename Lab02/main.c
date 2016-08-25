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

void DiskMove(int n,char source,char dest,char spare)				//Recursive method function
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

void swap(int *arr1,int *arr2,int *key1,int *key2)				//For swapping elements in the iterative version of the code. Essentially the push and pop function of the stack.
{
	*key2++;
	arr2[*key2]=arr1[*key1];
	arr1[*key1]=-1;
	*key1--;
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
	int n;
	printf("Enter the number of disks : ");
	scanf("%d",&n);
	if(selection && n%2==0)					//This condition is to change the destination and auxilary pegs in the iterative method
		printf("\nConsidering Peg A as the source, Peg C as the destination, and Peg B as the spare\n");
	else
		printf("\nConsidering Peg A as the source, Peg B as the destination, and Peg C as the spare\n");
	printf("Disk movement sequence to solve it is as follows :\n\n");
	if(!selection)				//RECURSION METHOD
	{
		DiskMove(n,'A','B','C');
		printf("\n");
		printf("The total moves taken to complete the movement : %d\n",count);
		count=0;
	}
	else						//ITERATIVE METHOD
	{
		int a[n],b[n],c[n];
		int i,keya=0,keyb=0,keyc=0;		//keys are like the top pointers of the stack
		for(i=0;i<n;++i)
		{
			a[i]=n-i;				//Peg A stack
			b[i]=-1;				//Peg B stack (-1 values, i.e., empty)
			c[i]=-1;				//Peg C stack (-1 values, i.e., empty)
		}
		keya=n-1;					//Peg A is full
		int moves=(int)(pow(2,n))-1;		//Total number of moves
		char s='A',d,sp;					//character data types for pegs (for printing) || s-source, d-destination, sp-spare
		if(n%2==1)					//Odd n calculations
		{
			d='C';
			sp='B';
			for(i=1;i<=moves;++i)
			{	
				if(i%3==1)
				{
					int x=a[keya];			//accessing the top elements of the stack
					int y=b[keyb];
					if(y==-1)				//Peg B empty
					{
						printf("[%d] Move disc from Peg %c to Peg %c\n",i,s,sp);
						swap(a,b,&keya,&keyb);
					}
					else if(x==-1)			//Peg A empty
					{
						printf("[%d] Move disc from Peg %c to Peg %c\n",i,sp,s);
						swap(b,a,&keyb,&keya);
					}
					else if(x<y)			//Peg B has larger disk on the top than Peg A
					{
						printf("[%d] Move disc from Peg %c to Peg %c\n",i,s,sp);
						swap(a,b,&keya,&keyb);
					}
					else if(y<x)			//Peg A has larger disk on the top than Peg B
					{
						printf("[%d] Move disc from Peg %c to Peg %c\n",i,sp,s);
						swap(b,a,&keyb,&keya);
					}
				}
				else if(i%3==2)
				{
					int x=a[keya];
					int y=c[keyc];
					if(y==-1)
					{
						printf("[%d] Move disc from Peg %c to Peg %c\n",i,s,d);
						swap(a,c,&keya,&keyc);
					}
					else if(x==-1)
					{
						printf("[%d] Move disc from Peg %c to Peg %c\n",i,d,s);
						swap(c,a,&keyc,&keya);
					}
					else if(x<y)
					{
						printf("[%d] Move disc from Peg %c to Peg %c\n",i,s,d);
						swap(a,c,&keya,&keyc);
					}
					else if(y<x)
					{
						printf("[%d] Move disc from Peg %c to Peg %c\n",i,d,s);
						swap(c,a,&keyc,&keya);
					}
				}
				else
				{
					int x=b[keyb];
					int y=c[keyc];
					if(y==-1)
					{
						printf("[%d] Move disc from Peg %c to Peg %c\n",i,sp,d);
						swap(b,c,&keyb,&keyc);
					}
					else if(x==-1)
					{
						printf("[%d] Move disc from Peg %c to Peg %c\n",i,d,sp);
						swap(c,b,&keyc,&keyb);
					}
					else if(x<y)
					{
						printf("[%d] Move disc from Peg %c to Peg %c\n",i,sp,d);
						swap(b,c,&keyb,&keyc);
					}
					else if(y<x)
					{
						printf("[%d] Move disc from Peg %c to Peg %c\n",i,d,sp);
						swap(c,b,&keyc,&keyb);
					}	
				}
			}
		}
		else 				//Even n calculations
		{
			d='B';
			sp='C';
			for(i=1;i<=moves;++i)
			{	
				if(i%3==1)
				{
					int x=a[keya];
					int y=c[keyc];
					if(y==-1)
					{
						printf("[%d] Move disc from Peg %c to Peg %c\n",i,s,sp);
						swap(a,c,&keya,&keyc);
					}
					else if(x==-1)
					{
						printf("[%d] Move disc from Peg %c to Peg %c\n",i,sp,s);
						swap(c,a,&keyc,&keya);
					}
					else if(x<y)
					{
						printf("[%d] Move disc from Peg %c to Peg %c\n",i,s,sp);
						swap(a,c,&keya,&keyc);
					}
					else if(y<x)
					{
						printf("[%d] Move disc from Peg %c to Peg %c\n",i,sp,s);
						swap(c,a,&keyc,&keya);
					}
				}
				else if(i%3==2)
				{
					int x=a[keya];
					int y=b[keyb];
					if(y==-1)
					{
						printf("[%d] Move disc from Peg %c to Peg %c\n",i,s,d);
						swap(a,b,&keya,&keyb);
					}
					else if(x==-1)
					{
						printf("[%d] Move disc from Peg %c to Peg %c\n",i,d,s);
						swap(b,a,&keyb,&keya);
					}
					else if(x<y)
					{
						printf("[%d] Move disc from Peg %c to Peg %c\n",i,s,d);
						swap(a,b,&keya,&keyb);
					}
					else if(y<x)
					{
						printf("[%d] Move disc from Peg %c to Peg %c\n",i,d,s);
						swap(b,a,&keyb,&keya);
					}
				}
				else
				{
					int y=b[keyb];
					int x=c[keyc];
					if(y==-1)
					{
						printf("[%d] Move disc from Peg %c to Peg %c\n",i,sp,d);
						swap(c,b,&keyc,&keyb);
					}
					else if(x==-1)
					{
						printf("[%d] Move disc from Peg %c to Peg %c\n",i,d,sp);
						swap(b,c,&keyb,&keyc);
					}
					else if(x<y)
					{
						printf("[%d] Move disc from Peg %c to Peg %c\n",i,sp,d);
						swap(c,b,&keyc,&keyb);
					}
					else if(y<x)
					{
						printf("[%d] Move disc from Peg %c to Peg %c\n",i,d,sp);
						swap(b,c,&keyb,&keyc);
					}	
				}
			}
		}
		printf("\n");
		printf("The total moves taken to complete the movement : %d\n",moves);
	}
	return 0;
}
