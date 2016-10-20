#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>


struct Graph{
	int V;
	struct  AdjList* array;
};

//represents the List containing head pointers of every node 
struct AdjList{

	struct  AdjListNode* head;

};

//represents each node corresponding to every head pointer in AdjList 
struct AdjListNode{ 

	int dest;
	int weight;
	struct AdjListNode* next;
};

struct PQ_node{
	
	int v;
	int dis;

};

//structure to create min heap 
struct Min_Heap{
	int N;
	int max_size;
    int *pos;
    struct PQ_node **array;
};

struct Edge{
    int src, dest, weight;
};


struct Graph_B{
    // V-> Number of vertices, E-> Number of edges
    int V, E;
 
    // graph is represented as an array of edges.
    struct Edge* edge;
};

// A structure to represent a subset for union-find
// USED IN KRUSKALS
struct subset{
    int parent;
    int rank;
};


struct AdjListNode* newNode(int dest, int weight);
struct Graph* newGraph( int V );
void addEdge(struct Graph* graph, int src, int dest, int weight);
void printGraph(struct Graph*graph);
void dfs(int i, bool visited[], struct Graph* graph);
struct PQ_node* CreateNode(int v, int dis);
struct Min_Heap* CreateHeap(int capacity);
int isEmpty(struct Min_Heap* mh);
void swapNode(struct PQ_node** a, struct PQ_node** b);
void minHeapify(struct Min_Heap* mh , int index);
bool is_InMinHeap(struct Min_Heap *mh, int v);
struct PQ_node* extract_min(struct Min_Heap* mh);
void decreaseKey(struct Min_Heap* mh, int v, int dis);
void printarr(int *dist , int V);
void dijkstra(struct Graph* graph , int source, int* dist, int *parent);
void add_edge(struct Graph* graph);
void delete_edge(struct Graph* graph);
void transform (struct Graph* graph , int **arr);
int delete_queue(int *queue);
int isEmpty_queue();
void insert_queue(int vertex,int *queue);
void BFS(int v,int n, int **G,int *state, int *queue );
struct Graph_B* createGraph(int V, int E);
void printArr(int dist[], int n);
void BellmanFord(struct Graph_B* graph, int src);
int minKey(int key[], bool mstSet[], int n);
int printMST(int *parent, int n, int **graph);
void primMST(int **graph, int n);
int find(struct subset subsets[], int i);
void Union(struct subset subsets[], int x, int y);
int myComp(const void* a, const void* b);
void KruskalMST(struct Graph_B* graph);