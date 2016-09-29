#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

double *r_maker(int n)
{
	double *r=(double *)malloc(n*sizeof(double));
	int i;
	for(i=0;i<n;++i)
	{
		if(i==0)
			r[i]=1.0;
		else
			r[i]=0.0;
	}
	return r;
}

double *b_maker(int n,double deltax)
{
	double *b=(double *)malloc((n-1)*sizeof(double));
	int i;
	for(i=0;i<n-1;++i)
	{
		if(i!=n-2)
			b[i]=1/(deltax*deltax);
		else
			b[i]=-1;
	}
	return b;
}

double *d_maker(int n,double deltax,double beta)
{
	double *d=(double *)malloc(n*sizeof(double));
	int i;
	for(i=0;i<n;++i)
	{
		if(i==0||i==n-1)
			d[i]=1;
		else
			d[i]=-((2/(deltax*deltax))+beta);
	}
	return d;
}

double *a_maker(int n,double deltax)
{
	double *b=(double *)malloc((n-1)*sizeof(double));
	int i;
	for(i=0;i<n-1;++i)
	{
		if(i!=0)
			b[i]=1/(deltax*deltax);
		else
			b[i]=0;
	}
	return b;			
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

double *theta_calculator(int n,double *r,double *d,double *a,double *b)
{
	double *theta_calculated=(double *)malloc(n*sizeof(double));
	int i;
	for(i=1;i<n;++i)
	{
		d[i]=d[i]-((a[i-1]*b[i-1])/d[i-1]);
		r[i]=r[i]-((r[i-1]*b[i-1])/d[i-1]);
		b[i-1]=0;
	}
	theta_calculated[n-1]=r[n-1]/d[n-1];
	for(i=n-2;i>=0;i--)
	{
		theta_calculated[i]=(r[i]-(a[i]*theta_calculated[i+1]))/d[i];
	}
	return theta_calculated;
}

void display_matrix(double *b,double *d,double *a,double *r,int n)
{
	printf("The augmented matrix is : \n");
	int i,j;
	for(i=0;i<n;++i)
	{
		for(j=0;j<n+1;++j)
		{
			if(j<n && i==j)
				printf("%10lf ",d[i]);
			else if(j<n && j==i-1)
				printf("%10lf ",b[j]);
			else if(j<n && j==i+1)
				printf("%10lf ",a[i]);
			else if(j<n)
				printf("%10lf ",0.000000);
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

void display_calculated(double *theta_calculated,int n)
{
	int i;
	printf("The calculated theta values are :\n");
	printf("%12s %12s\n","N","Theta_Calculated");
	for (i = 0; i < n; ++i)
	{
		printf("%12d %11lf\n",i+1,theta_calculated[i]);
	}
}

double error_calculator(double *theta_exact,double *theta_calculated,int n)
{
	int i;
	double error=0;
	for(i=0;i<n;++i)
		error+=(theta_exact[i]-theta_calculated[i])*(theta_exact[i]-theta_calculated[i]);
	error=sqrt(error/n);
	return error;
}

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
	double *r,*b,*d,*a;										// // // //
	r=r_maker(n);
	b=b_maker(n,deltax);
	a=a_maker(n,deltax);
	d=d_maker(n,deltax,beta);
	display_matrix(b,d,a,r,n);
	printf("\n");
	double *theta_exact=theta_exact_calculator(n,beta,deltax);
	display_exact(theta_exact,n);
	printf("\n");
	double *theta_calculated=theta_calculator(n,r,d,a,b);
	display_calculated(theta_calculated,n);
	printf("\n");
	display_matrix(b,d,a,r,n);
	printf("\n");
	double error=error_calculator(theta_exact,theta_calculated,n);
	printf("The error is %lf\n",error);
	return 0;
}