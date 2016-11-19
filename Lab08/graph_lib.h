#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>
#include <math.h>

#define INF INT_MAX
#define fr(i,s,l) for(i=s;i<l;++i)
#define frr(i,s,l) for(i=s;i>=l;i--)

//Used in BFS
struct queue_struct{
	int *queue;
	int *state;
	int MAX;
	int front;
	int rear;
};
//
//Used in Kruskal
struct subset{
    int parent;
    int rank;
};
struct Edge{
    int src;
    int dest;
    int weight;
};
struct Graph_B{
    // V-> Number of vertices, E-> Number of edges
    int V;
    int E;
 
    // graph is represented as an array of edges.
    struct Edge* edge;
};
//
void create_graph(int **main_graph,int *distance_array,int *previous_array,int *individual_vertice_size,int v,int e,int **edge_graph);
void matrix_create(int **main_graph,int **matrix_graph,int v,int *individual_vertice_size);
void add_node(int **main_graph,int **edge_graph,int v,int *individual_vertice_size,int start,int end,int weight,int edgeIteration);
void initialiseDjikstra(int *distance_array,int *previous_array,int v,int source);
void relax(int x,int y,int *individual_vertice_size,int **main_graph,int *distance_array,int *previous_array);
int priority_queue(int *distance_array,int *done_check,int v);
void djikstra(int **main_graph,int *individual_vertice_size,int *distance_array,int *previous_array,int v,int source);
void initialiseBellman(int *distance_array,int *previous_array,int source,int v);
void distance_update(int x,int y,int w,int *distance_array,int *previous_array);
void bellmanford(int **edge_graph,int *previous_array,int v,int source,int *distance_array,int e);
bool *visited_maker(int v);
void dfs(int **main_graph,int v,bool *visited,int current,int *individual_vertice_size);
void init_dfs(int **main_graph,int v,int source,int *individual_vertice_size);
void insert_queue(int vertex, struct queue_struct *major);
bool isEmpty_queue(struct queue_struct *major);
int delete_queue(struct queue_struct *major);
void bfs(int source, int v,int n, int **main_graph,int *individual_vertice_size);
int find(struct subset subsets[], int i);
void Union(struct subset subsets[], int x, int y);
int myComp(const void* a, const void* b);
struct Graph_B *structure_change(int **edge_graph,int vertices,int graph);
void KruskalMST(int **edge_graph,int vertices,int edges);
