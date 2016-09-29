#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

double **maker(int n,int beta)
{
	double **a;
	int i,j;
	a=(double **)malloc(n*sizeof(double *));
	for(i=0;i<n;++i)
	{
		a[i]=(double *)malloc(n*sizeof(double));
	}
	for(i=0;i<n;++i)
	{
		for(j=0;j<n;++j)
		{
			if((i==0 && j==0)||(i==n-1 && j==n-1))
				a[i][j]=1;
			else if(i==n-1 && j==n-2)
				a[i][j]=-1;
			else if(i==0 && j==1)
				a[i][j]=0;
			else if(i==j-1||i==j+1)
				a[i][j]=(n-1)*(n-1);
			else if(i==j)
				a[i][j]=-(2*(n-1)*(n-1)+beta);
			else
				a[i][j]=0;
			printf("%10lf ",a[i][j]);
		}
		printf("\n");
	}
	return a;
}

double *theta_exact_calculator(int n,int beta,double deltax)
{
	int i;
	double *theta_exact;
	double count;
	theta_exact=(double *)malloc(n*sizeof(double));
	for (i = 0,count=0.0; i < n; ++i,count+=deltax)
	{
		theta_exact[i]=(cosh(sqrt(beta)*(1-count)))/(cosh(sqrt(beta)));	
	}
	return theta_exact;
}

double *r_matrix(int n)
{
	double *r;
	r=(double *)malloc(n*sizeof(double));
	r[0]=1.0;
	int i;
	for (i = 1; i < n; ++i)
		r[i]=0.0;
	return r;
}

void display(double **a,double *r,int n)
{
	printf("The augmented matrix is : \n");
	int i,j;
	for(i=0;i<n;++i)
	{
		for(j=0;j<n+1;++j)
		{
			if(j<n)
				printf("%10lf ",a[i][j]);
			else
				printf("| %10lf\n",r[i]);
		}
	}
}

void display_exact(double *theta_exact,int n)
{
	int i;
	printf("The exact theta values are :\n");
	printf("%12s %12s\n","N","Theta_Exact");
	for (i = 0; i < n; ++i)
	{
		printf("%12d %11lf\n",i+1,theta_exact[i]);
	}
}

void pivot_maker(double **a,double *r,int n)
{
	int i,j,k;
	for(i=0;i<n;++i)								//the pivot creation row
	{	
		for(j=i+1;j<n;++j)							//the rows whose elements below pivot needs to be made zero
		{
			double c=a[j][i]/a[i][i];				//the constant used to make the element zero
			for(k=0;k<n+1;++k)						//traversing the whole row
			{
				if(k<n)
					a[j][k]=a[j][k]-c*a[i][k];
				else
					r[k]=r[k]-c*r[i];
			}
		}
	}
}

double *back_substitution(double **a,double *r,int n)
{
	double *theta_calculated=(double *)malloc(n*sizeof(double));
	int i,j;
	theta_calculated[n-1]=r[n-1]/a[n-1][n-1];
	for(i=n-2;i>=0;i--)
	{
		double add=0;
		for(j=n-1;j>i;j--)
		{
			add+=a[i][j]*theta_calculated[j];
		}
		theta_calculated[i]=(r[i]-add)/a[i][i];
	}
	return theta_calculated;
}

double error_calculator(double *theta_exact,double *theta_calculated,int n)
{
	int i;
	double error=0;
	for(i=0;i<n;++i)
		error+=(theta_exact[i]-theta_calculated[i])*(theta_exact[i]-theta_calculated[i]);
	error=sqrt(error/n);
}

/*void file_printer(double **a,double *r,int n,double *theta_calculated,double *theta_exact)
{
	FILE *fp;
	char *string;
	if(n==11)
		*string="result_11.dat";
	else if(n==101)
		*string="result_101.dat";
	else if(n==501)
		*string="result_501.dat";
	else if(n==1001)
		*string="result_1001.dat";
	else
		*string="result.dat";
	int i;
	fp=fopen(string,"w");
	for(i=0;i<n;++i)
	{

	}

}*/

int main(int argc, char const *argv[])
{
	system("clear");
	printf("Please enter the value of n : ");
	int n,i,j;
	double beta;
	scanf("%d",&n);
	printf("Please enter the value of beta (Fixed) : ");
	scanf("%lf",&beta);
	double deltax=(1/(double)(n-1));
	double **a;												//(//)
	a=maker(n,beta);
	double *theta_exact;									//
	theta_exact=theta_exact_calculator(n,beta,deltax);	
	double *r;												//
	r=r_matrix(n);	
	display(a,r,n);
	printf("\n");
	display_exact(theta_exact,n);
	printf("\n");
	pivot_maker(a,r,n);
	display(a,r,n);
	printf("\n");
	double *theta_calculated;								//
	theta_calculated=back_substitution(a,r,n);
	double error=error_calculator(theta_exact,theta_calculated,n);
	printf("The error is %lf\n",error);
	//file_printer(a,r,n,theta_calculated,theta_exact);

	for(i=0;i<n;++i)
		free(a[i]);
	free(a);
	free(theta_exact);
	return 0;
}