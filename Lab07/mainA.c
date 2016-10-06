#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void initialise(double *d,int s,int v)
{
	int i=0;
	for(i=0;i<v;++i)
		d[i]=1000000007;
	d[s-1]=0;
}

void distance_update(double w,int x,int y,double *d)
{
	if(d[y-1]>d[x-1]+w)
		d[y-1]=d[x-1]+w;
}

void bellmanford(int **g,double *w,int v,int s,double *d,int e)
{
	int i,j;
	for(i=0;i<v-1;++i)
	{
		for(j=0;j<e;++j)
		{
			distance_update(w[j],g[j][0],g[j][1],d);
		}
	}
}

void min_finder(double *d,int v,int e,int s,double w)
{
	int i,index;
	double mod_weight=w;
	for(i=0;i<v;++i)
	{
		double factor=d[i];
		double new_w=pow(10,factor)*w;
		if(new_w<w)
		{
			index=i;
			mod_weight=new_w;
		}
	}
	printf("%d %lf\n",index+1,mod_weight);
}

int main(int argc, char const *argv[])
{
	int v,e;
	scanf("%d %d",&v,&e);
	int **graph;
	double *weight;
	graph=(int **)malloc(e*sizeof(int *));
	int i;
	for(i=0;i<e;++i)
		graph[i]=(int *)malloc(2*sizeof(int));
	weight=(double *)malloc(e*sizeof(double));
	for(i=0;i<e;++i)
		scanf("%d %d %lf",&graph[i][0],&graph[i][1],&weight[i]);
	int source;
	double w;
	scanf("%d %lf",&source,&w);
	double *distance;
	distance=(double *)malloc(v*sizeof(double));
	initialise(distance,source,v);
	bellmanford(graph,weight,v,source,distance,e);
	min_finder(distance,v,e,source,w);
	return 0;
}