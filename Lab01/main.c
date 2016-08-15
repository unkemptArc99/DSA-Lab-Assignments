#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

//Declaring the function entities to create the dynamic 2D array
int** init_2d (int r, int c);	

int main(int argc,char *argv[])	//Command line arguments used in the program to merge Part B and Part Cof the assignment in the same file.
{
	int i,j,hi=0,r,c;		//hi is the sentinel for choosing of Part B and Part C
	if(strcmp(argv[1],"-h")==0)		//The manual/help option for the program.
	{
		printf("This program is for finding out the optimal threshold of the images.\n");
		printf("Use the following command line arguments to access the program:\n");
		printf("-histo : For running the optimal threshold program with the use of histogram algorithm.\n");
		printf("-chisto : For running the optimal threshold program with the use of histogram algorithm.\n");
		printf("-1 : For running the program on the first set of data.\n");
		printf("-2 : For running the program on the second set of data.\n");
		printf("-3 : For running the program on the third set of data.\n");
		printf("\"Remember that the file names have to be specified only after the histogram selection.\"\n");
		printf("For example you should type \"./main -histo -1\" to use the histogram and read the data from the first set of data.\n");
	}
	else if(strcmp(argv[1],"-histo")==0)
		hi=0;
	else if(strcmp(argv[1],"-chisto")==0)
		hi=1;
	else
	{
		printf("ERROR : Invalid command line arguments. Type \"./main -h\" for help and manual on how to use the program.\n");
		return -1;
	}
	int file=0;
	if(strcmp(argv[1],"-histo")==0 || strcmp(argv[1],"-chisto")==0)		//The data file to be worked upon will be mentioned in this 'if' statement
	{
		if(strcmp(argv[2],"-1")==0)	//first data
			file=1;
		else if(strcmp(argv[2],"-2")==0)	//second data
			file=2;
		else if(strcmp(argv[2],"-3")==0)	//third data
			file=3;
		else
		{
			printf("ERROR : Invalid command line arguments. Type \"./main -h\" for help and manual on how to use the program.\n");
			return -1;
		}
	}
	//Part A Start
	FILE *fp;					//File pointer to be used
    if(file==1)
    {
    	fp=fopen("1.txt","r");
		if(fp==NULL)
		{
			printf("ERROR : INPUT FILE NOT FOUND!\nCheck the directory for the input file, closing the program\n");
			return -1;
		}
		r=198;
		c=200;
    }
    else if(file==2)
    {
    	FILE *fp;
		fp=fopen("2.txt","r");
		if(fp==NULL)
		{
			printf("ERROR : INPUT FILE NOT FOUND!\nCheck the directory for the input file, closing the program\n");
			return -1;
		}
		r=1200;
		c=1920;
    }
    else if(file==3)
    {
    	FILE *fp;
		fp=fopen("1.txt","r");
		if(fp==NULL)
		{
			printf("ERROR : INPUT FILE NOT FOUND!\nCheck the directory for the input file, closing the program\n");
			return -1;
		}
		r=10967;
		c=10004;
    }
    int **x;
    x=init_2d(r,c);
    if(x==NULL)
		return -1;
	for (i=0;i<r;i++)			//scanning the input
	{
		for (j=0;j<c;j++)
		{
			if(j==c-1)
				fscanf(fp,"%d\n",&x[i][j]);
			else
				fscanf(fp,"%d\t",&x[i][j]);
		}
	}
	return 0;
}

int ** init_2d(int r,int c) //Initialize the matrix (allocate the memory for matrix)
{
	int **x, i, j;//x is a matrix pointer
        x = (int **) malloc(r * sizeof(int *));// Allocating the space for r row pointers x[0],x[1],----x[r-1]

        for(i=0;i<r;i++)
         x[i] = (int *) malloc(c * sizeof(int));// Now Allocate space for c elements in each row and assign go its pointer 
return(x);
}