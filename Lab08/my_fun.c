#include "my_lib.h"

int MAX = 20;
 
int initial = 1;
int waiting = 2;
int visited = 3;

int  front = -1,rear = -1;
int n; 

//Function to create AdjList node == normal insert in a linked list
struct AdjListNode* newNode(int dest, int weight){

    struct AdjListNode* ptr  = (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    ptr->dest = dest;
    ptr->weight = weight;
    ptr->next = NULL;
    return ptr;
}

//Function to create Graph
struct Graph* newGraph( int V ){
    struct Graph* ptr = (struct Graph*) malloc(sizeof(struct Graph));
    ptr->V = V ;
    ptr->array = (struct AdjList*) malloc(V* sizeof(struct AdjList));
    
    int i;
    for(i=0;i<V;++i)
        ptr->array[i].head = NULL; 
        
    return ptr;
}

//Function to add edge -> Directed Graph
void addEdge(struct Graph* graph, int src, int dest, int weight){

    struct AdjListNode* newAdjNode = newNode(dest, weight);
    newAdjNode->next = graph->array[src].head;
    graph->array[src].head = newAdjNode; 
    /*struct AdjListNode* newAdjNode1 = newNode(src, weight);
    newAdjNode1->next = graph->array[dest].head;
    graph->array[dest].head = newAdjNode;*/
    
}


//Function to print Graph
void printGraph(struct Graph*graph){

    int i=0;
    for(i=0;i<(graph->V);++i){
    
        struct AdjListNode* temp = graph->array[i].head;
        printf("\nAdj List of vertex %d : ",i);
        while(temp){
        
            printf("%d ->%d (%d), ",i ,temp->dest ,temp->weight);
            temp = temp->next;
            
        } 
        printf("\n\n");
    }
}

void dfs(int i, bool visited[], struct Graph* graph){

    visited[i]=true;
    printf("\n\nThe graph node %d just got visited",i);
    struct AdjListNode* temp = graph->array[i].head;
    while(temp){
        if(!visited[temp->dest])
                dfs(temp->dest, visited, graph);

        temp=temp->next;
    }

}

//Function to create a Priority queue node
struct PQ_node* CreateNode(int v, int dis){

    
    struct PQ_node* ptr = (struct PQ_node*)malloc(sizeof(struct PQ_node));
    ptr->v= v;
    ptr->dis = dis;
    return ptr;
}

//create a min heap (priority queue)
struct Min_Heap* CreateHeap(int capacity){

    struct Min_Heap* ptr = (struct Min_Heap*)malloc(sizeof(struct Min_Heap));
    ptr->N=0;
    ptr->max_size = capacity;
    ptr->pos = (int*)malloc(capacity * sizeof(int));
    ptr->array =  (struct PQ_node**)malloc(capacity * sizeof(struct PQ_node*));
    return ptr;
}

//Checks if min heap is empty or not
int isEmpty(struct Min_Heap* mh){

    return mh->N == 0;
}

//swap
void swapNode(struct PQ_node** a, struct PQ_node** b){
    struct PQ_node* temp;
    temp = (*a);
    (*a) = (*b);
    (*b) = temp;
}

//Function to min heapify the given heapify
void minHeapify(struct Min_Heap* mh , int index){
    int smallest , left , right;
    left = 2*index + 1;
    right = 2*index + 2;
    smallest = index;
    
    if(left<mh->N && mh->array[left]->dis < mh->array[smallest]->dis)
        smallest = left;

    if(right<mh->N && mh->array[right]->dis < mh->array[smallest]->dis)
        smallest = right;
    
    if(smallest!= index){
        struct PQ_node* smallest_node = mh->array[smallest];
        struct PQ_node* index_node = mh->array[index];
        
        //swap pos
        
        mh->pos[smallest_node->v] = index;
        mh->pos[index_node->v] = smallest;
        
        //node swapping
        swapNode(&mh->array[smallest] , &mh->array[index]);     
        
        minHeapify(mh , smallest);
    
    }
        
    
}

bool is_InMinHeap(struct Min_Heap *mh, int v)
{
   if (mh->pos[v] < mh->N);
     return true;
   return false;
}
 
//Function to extract Min
struct PQ_node* extract_min(struct Min_Heap* mh){
    if(isEmpty(mh))
        return NULL;
        
    struct PQ_node* first = mh->array[0];
    struct PQ_node* last = mh->array[mh->N-1];
    
    //replace root with last node, update pos of last node,decrease size of min heap,apply minHeapify again
    mh->array[0]= last;
    mh->pos[first->v] = mh->N-1;
    mh->pos[last->v] = 0;
    --mh->N;
    minHeapify(mh, 0);
    
    return first;
}

//Function to decrease key of minHeap
void decreaseKey(struct Min_Heap* mh, int v, int dis){

    int i = mh->pos[v];
    mh->array[i]->dis = dis; //update dis. value
    
    while(i && mh->array[i]->dis < mh->array[(i-1)/2]->dis){
    
        //swap positions
        mh->pos[mh->array[i]->v] = (i-1)/2;
        mh->pos[mh->array[(i-1)/2]->v] = i;
        //swap nodes
        swapNode(&mh->array[i], &mh->array[(i-1)/2]);
        
        i = (i-1)/2;    
    }
        
}
/*Djikstra disjoint(7)
#include<bits/stdc++.h>
using namespace std;
 
//flag stores which nodes i have already visited
//parent and val array as described in hints
vector<int> flag, parent, val;
 
string solve(int n) {
     
    int p;
    int q;
    int i;
    int tot = 0;
     
    //final string
    string ret = "";
 
    //queue for bfs
    queue <int> Q;
 
    //initial node
    int temp = 1%n;
    flag[temp] = 1;
    val[temp] = 1;
    Q.push(temp);
 
    while(true) {
         
        //pop from queue
        temp = Q.front();
        Q.pop();
        p = temp;
 
        //reached final state
        //build solution here
        if(p == 0) {
     
            p  =0;
            ret += (char)(val[p]+'0');
            p = parent[p];
            while(p != 0) {
 
                ret += (char)(val[p]+'0');
                p = parent[p];
            }
             
            reverse(ret.begin(), ret.end());
            return ret;
        }
         
        //visit two neighbors p*10 and p*10+1
        //if already not visited
        q = (p*10) % n;
         
        if(flag[q] == 0)
            Q.push(q), flag[q] = 1, parent[q] = p, val[q]=0; 
 
        q++;
         
        if(q >= n) q -= n;
         
        if(flag[q] == 0)
            Q.push(q), flag[q] = 1, parent[q] = p, val[q] = 1;
    }
}
 
string getnum(int A) {
     
    flag.clear(), parent.clear(), val.clear();
    flag.resize(A), parent.resize(A), val.resize(A);
     
    return solve(A);
}
     
int main() {
     
    cout << getnum(55) << endl;
*/

void printarr(int *dist , int V){

    int i;
    
    for(i=0; i<V; ++i){
    
        printf("%d\t\t%d\n", i , dist[i]);
    }
}

void dijkstra(struct Graph* graph , int source, int* dist, int *parent){

    int vert = graph->V;
    int i;
    
    struct Min_Heap* mh = CreateHeap(vert) ;
    
    //loop to initialize heap
    for(i=0; i< vert; ++i){
    
        dist[i] = INT_MAX;
        mh->array[i] = CreateNode(i, dist[i]);
        mh->pos[i] = i; 
        
    }
    
    mh->array[source] = CreateNode(source, dist[source]);
    mh->pos[source] = source;
    dist[source]=0;
    decreaseKey(mh, source, dist[source]);   
    
    mh->N = vert;
    
    while(!isEmpty(mh)){
        
        struct PQ_node* heapnode = extract_min(mh);
        int u = heapnode->v;
        
        struct AdjListNode* temp = graph->array[u].head;
        while(temp!=NULL){
        
            int v = temp->dest;
            //relax edge
            if(is_InMinHeap(mh,v)&& dist[u]!= INT_MAX && dist[v]> temp->weight + dist[u]){
                dist[v] = dist[u] + temp->weight;
                decreaseKey(mh, v, dist[v]);     
                parent[v]=u;            
            }
            
            temp = temp->next;
        
         }
        
    }
    parent[source]=source;
}


//Function to Add EDGE to a Given Graph
void add_edge(struct Graph* graph){
    int src, dest, wt; 
    printf("Enter new edge (src-dest-weight) :");
    scanf("%d%d%d", &src, &dest, &wt);
    addEdge(graph, src, dest, wt);

}

//Function to delete An EDGE from a given Graph
void delete_edge(struct Graph* graph){
 
    int src, dest;
    printf("Enter the value of source and dest(src - dest) :");
    scanf("%d%d",&src,&dest);
    struct AdjListNode* temp1 = graph->array[src].head;
    struct AdjListNode* temp2= temp1->next;

    if(temp1->dest== dest){

        graph->array[src].head=temp2;
        temp1->next=NULL;
        free(temp1);

    }

    else{
    while(temp2){
        if(temp2->dest== dest){
            temp1->next=temp2->next;
            temp2->next=NULL;
            free(temp2);            
        }
      
        temp2=temp2->next;
        temp1=temp1->next;
    
      }

 
    }

}

void transform (struct Graph* graph , int **arr){

        int i, j;
        int V= graph->V;

        for(i=0;i<V;++i)
            for(j=0;j<V;++j)
                arr[i][j]=0;


        for(i=0;i<V;++i){
          struct AdjListNode* temp = graph->array[i].head;
          j=0;
           while(temp){

            arr[i][temp->dest]=temp->weight;
            arr[temp->dest][i]=temp->weight;
            temp= temp->next;
           }

        }

        for(i=0;i<V;++i){
            for(j=0;j<V;++j)
                printf("%d ",arr[i][j]);
        
            printf("\n");
        }
       

}
void BFS(int v, int n, int **G,int *state, int *queue)
{
    int i,k;
    
    insert_queue(v,queue);
    state[v] = waiting;
    
    while(!isEmpty_queue())
    {
        v = delete_queue(queue);
        printf("\n The Graph Node : %d Just Got Visited \n",v);
        state[v] = visited;
        
        for(i=0; i<n; i++)
        {
            if(G[v][i] == 1 && state[i] == initial) 
            {
                insert_queue(i,queue);
                state[i] = waiting;
            }
          }
    }
    
}
 

void insert_queue(int vertex, int*queue)
{
    if(rear == MAX-1)
        printf("Queue Overflow\n");
    else
    {
        if(front == -1) 
            front = 0;
        rear = rear+1;
        queue[rear] = vertex ;
    }
}
 
int isEmpty_queue()
{
    if(front == -1 || front > rear)
        return 1;
    else
        return 0;
}
 
int delete_queue(int *queue)
{
    int delete_item;
    if(front == -1 || front > rear)
    {
        printf("Queue Underflow\n");
        exit(1);
    }
    
    delete_item = queue[front];
    front = front+1;
    return delete_item;
}

struct Graph_B* createGraph(int V, int E)
{
    struct Graph_B* graph = 
         (struct Graph_B*) malloc( sizeof(struct Graph_B) );
    graph->V = V;
    graph->E = E;
 
    graph->edge = 
       (struct Edge*) malloc( graph->E * sizeof( struct Edge ) );
 
    return graph;
}
 
// A utility function used to print the solution
void printArr(int dist[], int n)
{
    int i;
    printf("Vertex   Distance from Source\n");
    for (i = 0; i < n; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}

void BellmanFord(struct Graph_B* graph, int src)
{
    int i,j;
    int V = graph->V;
    int E = graph->E;
    int dist[V];
 
    // Step 1: Initialize distances from src to all other vertices
    // as INFINITE
    for (i = 0; i < V; i++)
        dist[i]   = INT_MAX;
    dist[src] = 0;
 
    // Step 2: Relax all edges |V| - 1 times. A simple shortest 
    // path from src to any other vertex can have at-most |V| - 1 
    // edges
    for (i = 1; i <= V-1; i++)
    {
        for (j = 0; j < E; j++)
        {
            int u = graph->edge[j].src;
            int v = graph->edge[j].dest;
            int weight = graph->edge[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
                dist[v] = dist[u] + weight;
        }
    }

    printArr(dist, V);
 
    return;
}


//Function to implement Prims Algorithm
int minKey(int key[], bool mstSet[], int n)
{
   int v;
   // Initialize min value
   int min = INT_MAX, min_index;
 
   for (v = 0; v < n; v++)
     if (mstSet[v] == false && key[v] < min)
         min = key[v], min_index = v;
 
   return min_index;
}


// A utility function to print the constructed MST stored in parent[]
int printMST(int *parent, int n, int **graph)
{
   int i;
   printf("Edge   Weight\n");
   for (i = 1; i < n; i++)
      printf("%d - %d    %d \n", parent[i], i, graph[i][parent[i]]);
}

 
// Function to construct and print MST for a graph represented using adjacency
// matrix representation
void primMST(int **graph, int n)
{
     int i ,j, v, count;
     int parent[n]; // Array to store constructed MST
     int key[n];   // Key values used to pick minimum weight edge in cut
     bool mstSet[n];  // To represent set of vertices not yet included in MST
 

     // Initialize all keys as INFINITE
     for (i = 0; i < n; i++){
        key[i] = INT_MAX;
        mstSet[i] = false;
     }
 
     // Always include first 1st vertex in MST.
     key[0] = 0;     // Make key 0 so that this vertex is picked as first vertex
     parent[0] = -1; // First node is always root of MST 
 
     // The MST will have V vertices
     for (count = 0; count < n-1; count++)
     {
        // Pick the minimum key vertex from the set of vertices
        // not yet included in MST
        int u = minKey(key, mstSet, n);
 
        // Add the picked vertex to the MST Set
        mstSet[u] = true;
 

        // Update key value and parent index of the adjacent vertices of
        // the picked vertex. Consider only those vertices which are not yet
        // included in MST
        for (v = 0; v < n; v++)
 
           // graph[u][v] is non zero only for adjacent vertices of m
           // mstSet[v] is false for vertices not yet included in MST
           // Update the key only if graph[u][v] is smaller than key[v]
          if (graph[u][v] && mstSet[v] == false && graph[u][v] <  key[v]){

                parent[v]  = u;
                key[v] = graph[u][v];

          }
             
     }
 
   #if 0
   
    for(i=1;i<n;++i)
        printf("%d ",parent[i]);
  
   #endif
   
   //print the constructed MST
   printMST(parent, n, graph);
}

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

void KruskalMST(struct Graph_B* graph)
{
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

/*
#include "graph_lib.h"

//EVERYTHING HERE IS 0-INDEXED

/*HERE, THE MAIN GRAPH IS OF THE FORM OF A DOUBLE POINTER, HAVING DATA OF EACH VERTEX IN THE FORM OF AN ARRAY, CONSISTING OF DESTINATIONS ON EVEN INDEX AND THE WEIGHTS ON ODD INDEX *//*

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
*/
/*BFS Disjoint (4)
include<bits/stdc++.h>
#define R 3
#define C 3
using namespace std;
 
// tool matrices to recur for adjacent cells.
int x[] = {0, 1, 1, -1, 1, 0, -1, -1};
int y[] = {1, 0, 1, 1, -1, -1, 0, -1};
 
// dp[i][j] Stores length of longest consecutive path
// starting at arr[i][j].
int dp[R][C];
 
// check whether mat[i][j] is a valid cell or not.
bool isvalid(int i, int j)
{
    if (i < 0 || j < 0 || i >= R || j >= C)
      return false;
    return true;
}
 
// Check whether current character is adjacent to previous
// character (character processed in parent call) or not.
bool isadjacent(char prev, char curr)
{
    return ((curr - prev) == 1);
}
 
// i, j are the indices of the current cell and prev is the
// character processed in the parent call.. also mat[i][j]
// is our current character.
int getLenUtil(char mat[R][C], int i, int j, char prev)
{
     // If this cell is not valid or current character is not
     // adjacent to previous one (e.g. d is not adjacent to b )
     // or if this cell is already included in the path than return 0.
    if (!isvalid(i, j) || !isadjacent(prev, mat[i][j]))
         return 0;
 
    // If this subproblem is already solved , return the answer
    if (dp[i][j] != -1)
        return dp[i][j];
 
    int ans = 0;  // Initialize answer
 
    // recur for paths with differnt adjacent cells and store
    // the length of longest path.
    for (int k=0; k<8; k++)
      ans = max(ans, 1 + getLenUtil(mat, i + x[k],
                                   j + y[k], mat[i][j]));
 
    // save the answer and return
    return dp[i][j] = ans;
}
 
// Returns length of the longest path with all characters consecutive
// to each other.  This function first initializes dp array that
// is used to store results of subproblems, then it calls
// recursive DFS based function getLenUtil() to find max length path
int getLen(char mat[R][C], char s)
{
    memset(dp, -1, sizeof dp);
    int ans = 0;
 
    for (int i=0; i<R; i++)
    {
        for (int j=0; j<C; j++)
        {
            // check for each possible starting point
            if (mat[i][j] == s) {
 
                // recur for all eight adjacent cells
                for (int k=0; k<8; k++)
                  ans = max(ans, 1 + getLenUtil(mat,
                                    i + x[k], j + y[k], s));
            }
        }
    }
    return ans;
}
 
// Driver program
int main() {
 
    char mat[R][C] = { {'a','c','d'},
                     { 'h','b','a'},
                     { 'i','g','f'}};
 
    cout << getLen(mat, 'a') << endl;
    cout << getLen(mat, 'e') << endl;
    cout << getLen(mat, 'b') << endl;
    cout << getLen(mat, 'f') << endl;
    return 0;
}
*/
/*QUEUE FUNCTIONALITY
/*
 * C Program to Implement Queue Data Structure using Linked List
 *//*
#include <stdio.h>
#include <stdlib.h>
 
struct node
{
    int info;
    struct node *ptr;
}*front,*rear,*temp,*front1;
 
int frontelement();
void enq(int data);
void deq();
void empty();
void display();
void create();
void queuesize();
 
int count = 0;
 
void main()
{
    int no, ch, e;
 
    printf("\n 1 - Enque");
    printf("\n 2 - Deque");
    printf("\n 3 - Front element");
    printf("\n 4 - Empty");
    printf("\n 5 - Exit");
    printf("\n 6 - Display");
    printf("\n 7 - Queue size");
    create();
    while (1)
    {
        printf("\n Enter choice : ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            printf("Enter data : ");
            scanf("%d", &no);
            enq(no);
            break;
        case 2:
            deq();
            break;
        case 3:
            e = frontelement();
            if (e != 0)
                printf("Front element : %d", e);
            else
                printf("\n No front element in Queue as queue is empty");
            break;
        case 4:
            empty();
            break;
        case 5:
            exit(0);
        case 6:
            display();
            break;
        case 7:
            queuesize();
            break;
        default:
            printf("Wrong choice, Please enter correct choice  ");
            break;
        }
    }
}
 
/* Create an empty queue *//*
void create()
{
    front = rear = NULL;
}
 
/* Returns queue size *//*
void queuesize()
{
    printf("\n Queue size : %d", count);
}
 
/* Enqueing the queue *//*
void enq(int data)
{
    if (rear == NULL)
    {
        rear = (struct node *)malloc(1*sizeof(struct node));
        rear->ptr = NULL;
        rear->info = data;
        front = rear;
    }
    else
    {
        temp=(struct node *)malloc(1*sizeof(struct node));
        rear->ptr = temp;
        temp->info = data;
        temp->ptr = NULL;
 
        rear = temp;
    }
    count++;
}
 
/* Displaying the queue elements *//*
void display()
{
    front1 = front;
 
    if ((front1 == NULL) && (rear == NULL))
    {
        printf("Queue is empty");
        return;
    }
    while (front1 != rear)
    {
        printf("%d ", front1->info);
        front1 = front1->ptr;
    }
    if (front1 == rear)
        printf("%d", front1->info);
}
 
/* Dequeing the queue *//*
void deq()
{
    front1 = front;
 
    if (front1 == NULL)
    {
        printf("\n Error: Trying to display elements from empty queue");
        return;
    }
    else
        if (front1->ptr != NULL)
        {
            front1 = front1->ptr;
            printf("\n Dequed value : %d", front->info);
            free(front);
            front = front1;
        }
        else
        {
            printf("\n Dequed value : %d", front->info);
            free(front);
            front = NULL;
            rear = NULL;
        }
        count--;
}
 
/* Returns the front element of queue *//*
int frontelement()
{
    if ((front != NULL) && (rear != NULL))
        return(front->info);
    else
        return 0;
}
 
/* Display if queue is empty or not *//*
void empty()
{
     if ((front == NULL) && (rear == NULL))
        printf("\n Queue empty");
    else
       printf("Queue not empty");
}
*/
