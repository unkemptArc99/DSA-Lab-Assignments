#include <stdio.h>
void f(int*,int);
int main()
{
	int a[5],i,b=16;
	for(i=0;i<5;++i)
		a[i]=2*i;
	f(a,b);
	for(i=0;i<5;++i)
		printf("\n %d",a[i]);
	printf("\n %d",b);
	return 0;
}
void f(int *x,int y)
{
	int i;
	for(i=0;i<5;++i)
		*(x+i)+=2;
	y+=2;
}