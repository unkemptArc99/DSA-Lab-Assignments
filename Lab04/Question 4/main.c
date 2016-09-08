/*********************************************************
Name : Abhishek
Roll No : B15103
IC 250 Lab Assignment 04 - Question 4 - Main file
Date : 08/09/2016
*********************************************************/
#include <stdio.h>
#include <stdlib.h>



int main(int argc, char const *argv[])
{
	printf("Welcome to the sparse matrix transposer!\n");
	printf("\n----------------------------------------\n");
	printf("Enter the number of rows of the matrix : ");
	int m,n,i,j;														//m=no.of rows, n=no. of columns
	scanf("%d",&m);
	printf("Enter the number of columns of the matrix : ");
	scanf("%d",&n);
	
	//////////////////////////////////////////////////////////////

	int *x,*y,*dat,count=0;												//Declaration of triplet arrays
	int hist_row[m],hist_col[n],chist_row[m+1],chist_col[n+1];			//Declaration of histograph and cumulative histograph arrays
	int index_row[m+1],index_col[n+1];									//Declaration of indexes for transpose implementation
	
	///////////////////////////////////////////////////////////////

	for(i=0;i<m;++i)													//Assigning default values in histograph and cumulative histograph
	{
		hist_row[i]=0;
		chist_row[i]=0;
		index_row[i]=0;
	}
	for(i=0;i<n+1;++i)
	{
		hist_col[i]=0;
		chist_col[i]=0;
		index_col[i]=0;
	}
	
	////////////////////////////////////////////////////////////////

	x=(int *)malloc((count)*sizeof(int));								//Initial allocation of dynamic arrays
	y=(int *)malloc((count)*sizeof(int));
	dat=(int *)malloc((count)*sizeof(int));
	
	////////////////////////////////////////////////////////////////

	for(i=0;i<m;++i)
	{
		printf("Enter the %d row of the matrix : ",i);
		for(j=0;j<n;++j)
		{
			int d;
			scanf("%d",&d);
			if(d!=0)
			{
				count++;
				x=(int *)realloc(x,(count)*sizeof(int));				//Increasing the size of dynamic arrays as the number of non-zero element increases
				y=(int *)realloc(y,(count)*sizeof(int));
				dat=(int *)realloc(dat,(count)*sizeof(int));
				x[count-1]=i;											//Assigning triplets into the array
				y[count-1]=j;
				dat[count-1]=d;
				hist_col[j]++;
				hist_row[i]++;
			}
		}
	}

	/////////////////////////////////////////////////////////////////SHOWING THE INITIAL TRIPLETS

	printf("No. of rows = %d, No. of cols = %d\n",m,n);
	printf("The triplets are as follows : \n");
	printf("row\tcol\tdat\n");
	for(i=0;i<count;++i)
	{
		printf("%d\t%d\t%d\n",x[i]+1,y[i]+1,dat[i]);
	}
	printf("\n");
	
	//////////////////////////////////////////////////////////////////BUILDING THE HISTOGRAPHS

	for(i=1;i<m+1;++i)
	{
		chist_row[i]=chist_row[i-1]+hist_row[i-1];
		index_row[i]=chist_row[i];
	}
	for(i=1;i<=n+1;++i)
	{
		chist_col[i]=chist_col[i-1]+hist_col[i-1];
		index_col[i]=chist_col[i];
	}

	//////////////////////////////////////////////////////////////////ALLOCATING SPACE FOR TRANSPOSE TRIPLETS

	int *x_t=(int *)malloc((count)*sizeof(int));
	int *y_t=(int *)malloc((count)*sizeof(int));
	int *dat_t=(int *)malloc((count)*sizeof(int));
	
	//////////////////////////////////////////////////////////////////TRANSPOSE FUNCTION

	for(i=0;i<count;++i)
	{
		int key=index_col[y[i]];
		x_t[key]=y[i];
		y_t[key]=x[i];
		dat_t[key]=dat[i];
		index_col[y[i]]++;
	}
	
	//////////////////////////////////////////////////////////////////SHOWING TRANSPOSE TRIPLET ELEMENTS

	printf("The triplets after transpose are as follows : \n");
	printf("row\tcol\tdat\n");
	for(i=0;i<count;++i)
	{
		printf("%d\t%d\t%d\n",x_t[i]+1,y_t[i]+1,dat_t[i]);
	}
	return 0;
}