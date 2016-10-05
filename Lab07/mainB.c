#include <stdio.h>
#include <stdlib.h>

void initialise(int *d,int *p,int v,int s)
{
	int i;
	for(i=0;i<v;++i)
	{
		d[i]=1000000007;
		p[i]=s;
	}
	d[s]=0;
}

void relax(int x,int y,int *s,int **g,int *d,int *p)
{
	int i,r;
	for(i=0;i<s[x];i+=2)
	{
		if(g[x][i]==y)
			r=g[x][i+1];
	}
	if(d[y]>d[x]+r)
	{
		d[y]=d[x]+r;
		p[y]=x;
	}
}

int priority_queue(int *d,int *c,int v)
{
	int min=1000000007,index=v,i;
	for(i=0;i<v;++i)
	{
		if(d[i]<min && c[i]==0)
		{
			min=d[i];
			index=i;
		}
	}
	return index;
}

void djikstra(int **g,int *s,int *d,int *p,int v)
{
	int done=0;
	int donecheck[v];
	int i;
	for(i=0;i<v;++i)
		donecheck[i]=0;
	while(done!=v)
	{
		int u=priority_queue(d,donecheck,v);
		if(u==v)
			break;
		done++;
		donecheck[u]=1;
		int i;
		for(i=0;i<s[u];i=i+2)
		{
			relax(u,g[u][i],s,g,d,p);
		}
	}
}

int main(int argc, char const *argv[])
{
	int v,e;					//vertices and edges
	scanf("%d %d",&v,&e);
	int i,j;
	int **graph=(int **)malloc(v*sizeof(int *));	
	int size[v];
	for(i=0;i<v;++i)
		size[i]=0;
	for(i=0;i<v;++i)
		graph[i]=(int *)malloc(size[i]*sizeof(int));

	for(i=0;i<e;++i)
	{
		int x,y,w;
		scanf("%d %d %d",&x,&y,&w);
		x--;
		y--;
		size[x]+=2;
		graph[x]=(int *)realloc(graph[x],size[x]*sizeof(int));
		graph[x][size[x]-2]=y;
		graph[x][size[x]-1]=w;
	}

	for(i=0;i<v;++i)
	{
		printf("%d| ",i);
		for (j = 0; j < size[i]; j=j+2)
		{
			printf("%d %d| ",graph[i][j],graph[i][j+1]);
		}
		printf("\n");
	}

	int source,no_of_host;
	scanf("%d %d",&source,&no_of_host);
	source--;

	int *distance,*prev;
	distance=(int *)malloc(v*sizeof(int));
	prev=(int *)malloc(v*sizeof(int));
	initialise(distance,prev,v,source);

	for(i=0;i<v;++i)
	{
		printf("%d | %d\n",distance[i],prev[i]);
	}

	djikstra(graph,size,distance,prev,v);

	for(i=0;i<no_of_host;++i)
	{
		int x;
		scanf("%d",&x);
		x--;
		printf("%d %d\n",x+1,distance[x]);
	}
	return 0;
}