#include "graph_lib.h"

//EVERYTHING HERE IS 0-INDEXED

/*HERE, THE MAIN GRAPH IS OF THE FORM OF A DOUBLE POINTER, HAVING DATA OF EACH VERTEX IN THE FORM OF AN ARRAY, CONSISTING OF DESTINATIONS ON EVEN INDEX AND THE WEIGHTS ON ODD INDEX */

//GRAPH CREATION START
void create_graph(int **main_graph,int *distance_array,int *previous_array,int *individual_vertice_size,int v,int e,int **edge_graph)
{
	int i;
	main_graph=(int **)malloc(v*sizeof(int *));
	individual_vertice_size=(int *)malloc(v*sizeof(int));
	for(i=0;i<v;++i)
		individual_vertice_size[i]=0;
	distance_array=(int *)malloc(v*sizeof(int));
	previous_array=(int *)malloc(v*sizeof(int));
	for(i=0;i<v;++i)
		main_graph[i]=(int *)malloc(individual_vertice_size[i]*sizeof(int));
	edge_graph=(int **)malloc(e*sizeof(int));
	for(i=0;i<v;++i)
		edge_graph[i]=(int *)malloc(3*sizeof(int));
}

void matrix_create(int **main_graph,int **matrix_graph,int v,int *individual_vertice_size)
{
	int i,j;
	matrix_graph=(int **)malloc(v*sizeof(int));
	for(i=0;i<v;++i)
	{
		matrix_graph[i]=(int *)malloc(v*sizeof(int));
		for(j=0;j<v;++j)
			matrix_graph[i][j]=0;
	}
	for(i=0;i<v;++i)
	{
		for(j=0;j<individual_vertice_size[i];j=j+2)
			matrix_graph[i][main_graph[i][j]]=main_graph[i][j+1];
	}
}

void add_node(int **main_graph,int **edge_graph,int v,int *individual_vertice_size,int start,int end,int weight,int edgeIteration)
{
	individual_vertice_size[start]+=2;
	//individual_vertice_size[end]+=2;
	main_graph[start]=(int *)realloc(main_graph[start],individual_vertice_size[start]*sizeof(int));
	//main_graph[end]=(int *)realloc(main_graph[end],individual_vertice_size[end]*sizeof(int));
	main_graph[start][individual_vertice_size[start]-2]=end;
	//main_graph[end][individual_vertice_size[end]-2]=start;
	main_graph[start][individual_vertice_size[start]-1]=weight;
	//main_graph[end][individual_vertice_size[end]-1]=weight;
	edge_graph[edgeIteration][0]=start;
	edge_graph[edgeIteration][1]=end;
	edge_graph[edgeIteration][2]=weight;
}
//GRAPH CREATION END

//DJIKSTRA START
void initialiseDjikstra(int *distance_array,int *previous_array,int v,int source)
{
	int i;
	for(i=0;i<v;++i)
	{
		distance_array[i]=INF;
		previous_array[i]=source;
	}
	distance_array[source]=0;
}

void relax(int x,int y,int *individual_vertice_size,int **main_graph,int *distance_array,int *previous_array)
{
	int i,weight;
	for(i=0;i<individual_vertice_size[x];i+=2)
	{
		if(main_graph[x][i]==y)
			weight=main_graph[x][i+1];
	}
	if(distance_array[y]>distance_array[x]+weight)
	{
		distance_array[y]=distance_array[x]+weight;
		previous_array[y]=x;
	}
}

int priority_queue(int *distance_array,int *done_check,int v)
{
	int min=INF,index=v,i;
	for(i=0;i<v;++i)
	{
		if(distance_array[i]<min && done_check[i]==0)
		{
			min=distance_array[i];
			index=i;
		}
	}
	return index;
}

void djikstra(int **main_graph,int *individual_vertice_size,int *distance_array,int *previous_array,int v,int source)
{
	initialiseDjikstra(distance_array,previous_array,v,source);
	int done=0;
	int donecheck[v];
	int i;
	for(i=0;i<v;++i)
		donecheck[i]=0;
	while(done!=v)
	{
		int u=priority_queue(distance_array,donecheck,v);
		if(u==v)
			break;
		done++;
		donecheck[u]=1;
		int i;
		for(i=0;i<individual_vertice_size[u];i=i+2)
		{
			relax(u,main_graph[u][i],individual_vertice_size,main_graph,distance_array,previous_array);
		}
	}
}
//DJIKSTRA END

//BELLMAN FORD START
void initialiseBellman(int *distance_array,int *previous_array,int source,int v)
{
	int i=0;
	for(i=0;i<v;++i)
	{
		distance_array[i]=INT_MAX;
		previous_array[i]=source;
	}
	distance_array[source]=0;
}

void distance_update(int x,int y,int w,int *distance_array,int *previous_array)
{
	if(distance_array[y]>distance_array[x]+w)
	{
		distance_array[y]=distance_array[x]+w;
		previous_array[y]=x;
	}
}

void bellmanford(int **edge_graph,int *previous_array,int v,int source,int *distance_array,int e)
{
	initialiseBellman(distance_array,previous_array,source,v);
	int i,j,k;
	for(i=0;i<v-1;++i)
	{
		for(j=0;j<e;++j)
		{
			for(k=0;k<v;++k)
				printf("%d\n",distance_array[i]);
			distance_update(edge_graph[j][0],edge_graph[j][1],edge_graph[j][2],distance_array,previous_array);
		}
	}
}
//BELLMAN FORD END

//DFS START
//The DFS function requires a boolean array of visited nodes. Please make it before using the DFS function.
bool *visited_maker(int v)
{
	bool *visited;
	visited=(bool *)malloc(v*sizeof(bool));
	int i;
	for(i=0;i<v;++i)
		visited[i]=false;
	return visited;
}

void dfs(int **main_graph,int v,bool *visited,int current,int *individual_vertice_size)
{
	visited[current]=true;
	printf("Node %d is visited\n",current);
	int i;
	for(i=0;i<individual_vertice_size[current];i=i+2)
	{
		if(!visited[main_graph[current][i]])
			dfs(main_graph,v,visited,main_graph[current][i],individual_vertice_size);
	}
}

void init_dfs(int **main_graph,int v,int source,int *individual_vertice_size)
{
	bool *visited=visited_maker(v);
	dfs(main_graph,v,visited,source,individual_vertice_size);
}
//DFS END

//BFS START

void insert_queue(int vertex, struct queue_struct *major)
{
    if(major->rear == (major->MAX)-1)
        printf("Queue Overflow\n");
    else
    {
        if(major->front==-1) 
            major->front = 0;
        (major->rear)++;
        major->queue[(major->rear)-1]=vertex;
    }
}
 
bool isEmpty_queue(struct queue_struct *major)
{
    if(major->front == -1 || major->front==major->rear)
        return true;
    else
        return false;
}
 
int delete_queue(struct queue_struct *major)
{
    int delete_item;
    if(major->front == -1 || major->front > major->rear)
    {
        printf("Queue Underflow\n");
        exit(1);
    }
    
    delete_item = major->queue[major->front];
    (major->front)++;
    return delete_item;
}

void bfs(int source, int v,int n, int **main_graph,int *individual_vertice_size)
{
	struct queue_struct *major;
	major=(struct queue_struct *)malloc(sizeof(struct queue_struct));
	major->MAX=100;
	major->queue=(int *)malloc((major->MAX)*sizeof(int));
	major->state=(int *)malloc(v*sizeof(int));
	major->front=-1;
	major->rear=0;
    int i,k;
    for(i=0;i<v;++i)
    	major->state[i]=0;
    insert_queue(source,major);
    major->state[source]=1;
    
    while(!isEmpty_queue(major))
    {
        k = delete_queue(major);
        printf("\n The Graph Node : %d Just Got Visited \n",k);
        major->state[k]=2;
        
        for(i=0;i<individual_vertice_size[k];i=i+2)
        {
        	if(major->state[main_graph[k][i]]==0)
        	{
            	insert_queue(main_graph[k][i],major);
            	major->state[main_graph[k][i]]=1;
            }
        }
    }
}
//BFS END

//KRUSKAL START
int find(struct subset subsets[], int i)
{
    // find root and make root as parent of i (path compression)
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
 
    return subsets[i].parent;
}

void Union(struct subset subsets[], int x, int y)
{
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);
 
    // Attach smaller rank tree under root of high rank tree
    // (Union by Rank)
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
 
    // If ranks are same, then make one as root and increment
    // its rank by one
    else
    {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

 
// Compare two edges according to their weights.
// Used in qsort() for sorting an array of edges
int myComp(const void* a, const void* b)
{
    struct Edge* a1 = (struct Edge*)a;
    struct Edge* b1 = (struct Edge*)b;
    return a1->weight > b1->weight;
}

struct Graph_B *structure_change(int **edge_graph,int vertices,int edges)
{
	struct Graph_B *graph;
	graph=(struct Graph_B *)malloc(sizeof(struct Graph_B));
	graph->V=vertices;
	graph->E=edges;
	graph->edge=(struct Edge *)malloc(graph->E*sizeof(struct Edge));
	int i;
	for(i=0;i<graph->E;++i)
	{
		struct Edge temp;
		temp.src=edge_graph[i][0];
		temp.dest=edge_graph[i][1];
		temp.weight=edge_graph[i][2];
		graph->edge[i]=temp;
	}
	return graph;
}

void KruskalMST(int **edge_graph,int vertices,int edges)
{
	struct Graph_B* graph=structure_change(edge_graph,vertices,edges);
    int V = graph->V;
    int v;
    struct Edge result[V];  // Tnis will store the resultant MST
    int e = 0;  // An index variable, used for result[]
    int i = 0;  // An index variable, used for sorted edges
 
    // Step 1:  Sort all the edges in non-decreasing order of their weight
    // If we are not allowed to change the given graph, we can create a copy of
    // array of edges
    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), myComp);
 
    // Allocate memory for creating V ssubsets
    struct subset *subsets =
        (struct subset*) malloc( V * sizeof(struct subset) );
 
    // Create V subsets with single elements
    for (v = 0; v < V; ++v)
    {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }
 
    // Number of edges to be taken is equal to V-1
    while (e < V - 1)
    {
        // Step 2: Pick the smallest edge. And increment the index
        // for next iteration
        struct Edge next_edge = graph->edge[i++];
 
        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);
 
        // If including this edge does't cause cycle, include it
        // in result and increment the index of result for next edge
        if (x != y)
        {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
        // Else discard the next_edge
    }
 
    // print the contents of result[] to display the built MST
    printf("Following are the edges in the constructed MST\n");
    for (i = 0; i < e; ++i)
        printf("%d -- %d == %d\n", result[i].src, result[i].dest,
                                                   result[i].weight);
    return;
}
//KRUSKAL ENDS
