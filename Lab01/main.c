/***********************************************
Name: Abhishek
Roll: B15103
Purpose: IC250 Assignment 01 - Question 1 - Optimum Threshold Selection 
Date: 18/08/2016
***********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
//#include <glib.h>

//Declaring the function entities to create the dynamic 2D array
int** make_arr (int r, int c);	

int main(int argc,char *argv[])	//Command line arguments used in the program to merge Part B and Part Cof the assignment in the same file.
{
	int i,j,k,hi=0,r,c;		//hi is the sentinel for choosing of Part B and Part C
	if(argc==1||strcmp(argv[1],"-h")==0)		//The manual/help option for the program.
	{
		printf("This program is for finding out the optimal threshold of the images.\n");
		printf("Use the following command line arguments to access the program:\n");
		printf("-nhisto : For running the optimal threshold program without the use of histogram algorithm.\n");
		printf("-histo : For running the optimal threshold program with the use of histogram algorithm.\n");
		printf("-1 : For running the program on the first set of data.\n");
		printf("-2 : For running the program on the second set of data.\n");
		printf("-3 : For running the program on the third set of data.\n");
		printf("\"Remember that the file names have to be specified only after the histogram selection.\"\n");
		printf("For example you should type \"./main -histo -1\" to use the histogram and read the data from the first set of data.\n");
	}
	else if(strcmp(argv[1],"-nhisto")==0)
		hi=0;
	else if(strcmp(argv[1],"-histo")==0)
		hi=1;
	else
	{
		printf("ERROR : Invalid command line arguments. Type \"./main -h\" for help and manual on how to use the program.\n");
		return -1;
	}
	int file=0;
	if(strcmp(argv[1],"-nhisto")==0 || strcmp(argv[1],"-histo")==0)		//The data file to be worked upon will be mentioned in this 'if' statement
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
	FILE *fp;					//File pointer to be used
    if(file==1)
    {
    	fp=fopen("/home/abhishek/Documents/DSA_Resources/Lab01/1.txt","r");
		if(fp==NULL)
		{
			printf("ERROR : INPUT FILE NOT FOUND!\nCheck the directory for the input file, closing the program\n");
			return -1;
		}
		r=198;				//SPECIFYING THE ROWS AND COLUMNS BECAUSE THEY ARE NOT GIVEN IN THE .TXT FILE
		c=200;
    }
    else if(file==2)
    {
		fp=fopen("/home/abhishek/Documents/DSA_Resources/Lab01/2.txt","r");
		if(fp==NULL)
		{
			printf("ERROR : INPUT FILE NOT FOUND!\nCheck the directory for the input file, closing the program\n");
			return -1;
		}
		r=1200;				//SPECIFYING THE ROWS AND COLUMNS BECAUSE THEY ARE NOT GIVEN IN THE .TXT FILE
		c=1920;
    }
    else if(file==3)
    {
   		fp=fopen("/home/abhishek/Documents/DSA_Resources/Lab01/1.txt","r");
		if(fp==NULL)
		{
			printf("ERROR : INPUT FILE NOT FOUND!\nCheck the directory for the input file, closing the program\n");
			return -1;
		}
		r=10967;			//SPECIFYING THE ROWS AND COLUMNS BECAUSE THEY ARE NOT GIVEN IN THE .TXT FILE
		c=10004;
    }
    //Part A start
    clock_t begin=clock();
    printf("Reading the input data......\n");
    int **x;
    x=make_arr(r,c);
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
	fclose(fp);
	clock_t end=clock();
	double time_spent=(double)(end-begin)/CLOCKS_PER_SEC;		//help from stackoverflow.com for this
	printf("Data read in %lf s\n",time_spent);
	//Part A End
	//Part B start
	if(hi==0)
	{
		//GSList *clus_A=NULL, *clus_B=NULL;
		begin=clock();
		printf("Performing threshold using iterative method......\n");
		int npa=0,npb=0;
		double meana=0.0,meanb=0.0,sda=0.0,sdb=0.0,dprime,nratio;
		FILE *fp1;						//Initialising the file pointer for writing
		fp1=fopen("result.dat","w");
		for(i=0;i<256;++i)				//Threshold Selection
		{
			for(j=0;j<r;++j)
			{
				for(k=0;k<c;++k)
				{
					if(x[j][k]<=i)
					{
						npa++;
						meana=meana+(double)x[j][k];
						//clus_A=g_slist_append(clus_A,GINT_TO_POINTER(x[j][k]));
					}
					else
					{
						npb++;
						meanb=meanb+(double)x[j][k];
						//clus_B=g_slist_append(clus_B,GINT_TO_POINTER(x[j][k]));
					}
				}
			}
			meana=meana/(double)npa;		//Mean Calculation
			meanb=meanb/(double)npb;
			for(j=0;j<r;++j)
			{
				for(k=0;k<c;++k)
				{
					if(x[j][k]<=i)
						sda=sda+(x[j][k]-meana)*(x[j][k]-meana);
					else
						sdb=sdb+(x[j][k]-meanb)*(x[j][k]-meanb);
				}
			}
			sda=(double)sqrt(sda/npa);		//Standard Deviation Calculation
			sdb=(double)sqrt(sdb/npb);
			nratio=((double)npa)/((double)npb);			//nRatio Calculation
			dprime=(fabs(meana-meanb)/sqrt(sda*sda+sdb*sdb));		//d` calculation
			fprintf(fp1,"%d\t%lf\t%lf\n",i,nratio,dprime);		//printing file
			printf("%d\t%lf\t%lf\n",i,nratio,dprime);
			npa=0;
			npb=0;
			meana=0.0;
			meanb=0.0;
			sda=0.0;
			sdb=0.0;
			nratio=0.0;
			dprime=0.0;
		}
		end=clock();
		time_spent=(double)(end-begin)/CLOCKS_PER_SEC;
		printf("Thresholding done in %lf s\n",time_spent);
		fclose(fp1);
	}
	//Part C start
	else if(hi==1)
	{
		//GSList *clus_A=NULL, *clus_B=NULL;
		begin=clock();
		printf("Performing threshold using iterative method......\n");
		long long npa=0,npb=0;
		double meana=0.0,meanb=0.0,sda=0.0,sdb=0.0,dprime,nratio;
		FILE *fp1;
		fp1=fopen("result_histo.dat","w");
		long long arr1d[256];				//Histogram Array
		for(i=0;i<256;++i)
			arr1d[i]=0;
		for(i=0;i<r;++i)
		{
			for(j=0;j<c;++j)
			{
				arr1d[x[i][j]]++;
			}
		}
		long long arr1dc[256];			//Cumulative Histogram Array
		arr1dc[0]=arr1d[0];
		for(i=1;i<256;++i)
			arr1dc[i]=arr1d[i]+arr1dc[i-1];
		for(i=0;i<256;++i)
		{
			for(j=0;j<=i;++j)
				meana=meana+j*arr1d[j];
			for(j=i+1;j<256;++j)
				meanb=meanb+j*arr1d[j];
			for(j=0;j<=i;++j)
				for(k=0;k<arr1d[j];++k)
					//clus_A=g_slist_append(clus_A,GINT_TO_POINTER(x[j][k]));
			for(j=i+1;j<256;++j)
				for(k=0;k<arr1d[j];++k)
					//clus_B=g_slist_append(clus_B,GINT_TO_POINTER(x[j][k]));
			npa=arr1dc[i];
			npb=arr1dc[255]-arr1dc[i];
			meana=meana/npa;				//Mean Calculation
			meanb=meanb/npb;
			for(j=0;j<=i;++j)
				sda=sda+(((j-meana)*(j-meana))*arr1d[j]);
			for(j=i+1;j<256;++j)
				sdb=sdb+(((j-meanb)*(j-meanb))*arr1d[j]);
			sda=(double)sqrt(sda/npa);			//Standard Deviation Calculation
			sdb=(double)sqrt(sdb/npb);
			nratio=((double)npa)/((double)npb);			//nRatio Calculation
			dprime=(fabs(meana-meanb)/sqrt(sda*sda+sdb*sdb));		//d` Calculation
			fprintf(fp1,"%d\t%lf\t%lf\n",i,nratio,dprime);		//printing in file
			printf("%d\t%lf\t%lf\n",i,nratio,dprime);
			npa=0;
			npa=0;
			npb=0;
			meana=0.0;
			meanb=0.0;
			sda=0.0;
			sdb=0.0;
			nratio=0.0;
			dprime=0.0;
		}
		end=clock();
		time_spent=(double)(end-begin)/CLOCKS_PER_SEC;
		printf("Thresholding done in %lf s\n",time_spent);
		fclose(fp1);
	}
	free(x);
	return 0;
}

int ** make_arr(int r,int c) //Initialize the matrix (allocate the memory for matrix)
{
	int **x, i, j;//x is a matrix pointer
        x = (int **) malloc(r * sizeof(int *));// Allocating the space for r row pointers x[0],x[1],----x[r-1]

        for(i=0;i<r;i++)
         x[i] = (int *) malloc(c * sizeof(int));// Now Allocate space for c elements in each row and assign go its pointer 
return(x);
}