#include <stdio.h>
#include <stdlib.h>
#include "graph_lib.h"

int main(int argc, char const *argv[])
{
	int v,e;
	int **main_graph,**edge_graph,**matrix_graph,*individual_vertice_size,*distance_array,*previous_array;
	scanf("%d %d",&v,&e);
	int i,j;
	main_graph=(int **)malloc(v*sizeof(int *));
	individual_vertice_size=(int *)malloc(v*sizeof(int));
	for(i=0;i<v;++i)
		individual_vertice_size[i]=0;
	distance_array=(int *)malloc(v*sizeof(int));
	previous_array=(int *)malloc(v*sizeof(int));
	for(i=0;i<v;++i)
		main_graph[i]=(int *)malloc(individual_vertice_size[i]*sizeof(int));
	edge_graph=(int **)malloc(e*sizeof(int *));
	for(i=0;i<e;++i)
		edge_graph[i]=(int *)malloc(3*sizeof(int));
	for(i=0;i<e;++i)
	{
		int x,y,w;
		scanf("%d %d %d",&x,&y,&w);
		individual_vertice_size[x]+=2;
		//individual_vertice_size[y]+=2;
		main_graph[x]=(int *)realloc(main_graph[x],individual_vertice_size[x]*sizeof(int));
		//main_graph[y]=(int *)realloc(main_graph[y],individual_vertice_size[y]*sizeof(int));
		main_graph[x][individual_vertice_size[x]-2]=y;
		//main_graph[y][individual_vertice_size[y]-2]=x;
		main_graph[x][individual_vertice_size[x]-1]=w;
		//main_graph[y][individual_vertice_size[y]-1]=w;
		edge_graph[i][0]=x;	
		edge_graph[i][1]=y;
		edge_graph[i][2]=w;
	}
	for(i=0;i<v;++i)
	{
		printf("%d | ",i);
		for(j=0;j<individual_vertice_size[i];++j)
			printf("%d ",main_graph[i][j]);
		printf("\n");
	}
	printf("%d\n",INT_MAX);
	for(i=0;i<e;++i)
	{
		printf("%d %d %d\n",edge_graph[i][0],edge_graph[i][1],edge_graph[i][2]);
	}
	bellmanford(edge_graph,previous_array,v,0,distance_array,e);
	for(i=0;i<v;++i)
		printf("%d\n",distance_array[i]);
	return 0;
}