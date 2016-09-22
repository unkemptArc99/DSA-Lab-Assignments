/*********************************************************
Name : Abhishek
Roll No : B15103
IC 250 Lab Assignment 06 - Question 2 - Main file
Date : 22/09/2016
*********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int **maker(int n,int m)
{
	int **main;
	int i,j;
	time_t t;	
	main=(int **)malloc(n*sizeof(int *));
	for(i=0;i<n;++i)
	{
		main[i]=(int *)malloc(m*sizeof(int));
	}
	srand((unsigned int)time(&t));
	for(i=0;i<n;++i)
		for(j=0;j<m;++j)
			main[i][j]=rand()%100000;
	return main;
}

void writer(int **matrix,int n,int m,char *filename)
{
	FILE *fp=fopen(filename,"w");
	int i,j;
	for(i=0;i<n;++i)
	{
		for(j=0;j<m;++j)
			fprintf(fp,"%d ",matrix[i][j]);
		fprintf(fp,"\n");
	}
	fclose(fp);
}

void printDelete(int **matrix,int n,int m)
{
	int i,j;
	printf("Printing the matrix\n");
	for(i=0;i<n;++i)
	{
		for(j=0;j<m;++j)
			printf("%d ",matrix[i][j]);
		printf("\n");
	}
	free(matrix);
}
int main(int argc, char const *argv[])
{
	system("clear");
	printf("2D MATRIX CREATER\n");
	printf("1 - Initialise 2D matrix with random numbers (with a max limit of 100000)\n");
	printf("2 - Write the 2D matrix in a file\n");
	printf("3 - Print the 2D matrix and destroy the matrix\n");
	printf("4 - Exit\n");
	int **arr=NULL;
	int ch,n,m;
	n=atoi(argv[1]);
	m=atoi(argv[2]);
	char string[10000];
	clock_t begin,end;
	double time_spent;
	while(1)
	{
		printf("Please enter your choice : ");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				printf("Initialising matrix..............\n");
				begin=clock();
				arr=maker(n,m);
				end=clock();
				time_spent=(double)(end-begin)/CLOCKS_PER_SEC;
				printf("Done initialising in %lf\n",time_spent);
				break;
			case 2:
				if(arr==NULL)
					printf("Initialise the array first!!!\n");
				else
				{
					printf("Enter the filename : ");
					scanf("%s",string);
					printf("Starting the writing process.....\n");
					begin=clock();
					writer(arr,n,m,string);
					end=clock();
					time_spent=(double)(end-begin)/CLOCKS_PER_SEC;
					printf("Done writing in %lf\n",time_spent);
				}
				break;
			case 3:
				if(arr==NULL)
					printf("Initialise the array first!!!\n");
				else
					printDelete(arr,n,m);
				break;
			case 4:
				exit(0);
			default:
				printf("WRONG INPUT\n");
				break;
		}
	}
	return 0;
}