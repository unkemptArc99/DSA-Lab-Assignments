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