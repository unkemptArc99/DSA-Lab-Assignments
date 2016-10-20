/*input
9 14   
0 1 4
0 7 8
1 2 8
1 7 11
2 3 7
2 8 2
2 5 4
3 4 9
3 5 14
4 5 10
5 6 2
6 7 1
6 8 6
7 8 7
*/

#include "my_lib.h"

extern MAX, initial, waiting, visited, front,rear, n;

int main(){
	system("clear");
    int no, ch, e;
    int node;
    int dis=0;
    int front=-1, rear=-1;
    int V, E;
    scanf("%d %d",&V, &E);
    struct Graph* graph = newGraph(V);
    struct Graph_B* graph_B = createGraph(V, E);
    int i,j,k, u, v ,weight;
    for(i=0;i<E;++i){
        scanf("%d %d %d",&u, &v, &weight);
        addEdge(graph, u, v, weight);

        graph_B->edge[i].src = u;
        graph_B->edge[i].dest = v;
        graph_B->edge[i].weight = weight;

    }

     int n= graph->V;          
     int *arr[graph->V];
    for (i=0; i<graph->V; i++)
        arr[i] = (int *)malloc(graph->V * sizeof(int)); 

     bool visited[V];
     int dist[V],parent[V],state[MAX],queue[MAX];
	system("clear");  
    while (1){
        printf("\n 1 : DFS");
        printf("\n 2 : Dijkstra");
        printf("\n 3 : Bellman ford");
        printf("\n 4 : Bfs for graph traversal");
        printf("\n 5 : Prims algo for MST");
        printf("\n 6 : Kruskals Algo for MST");
        printf("\n 7 : Add edge");
        printf("\n 8 : Delete Edge");
        printf("\n 9 : Print Graph");
        printf("\n 10: Exit");

        printf("\n\nEnter choice : ");
        scanf("%d", &ch);
 
        switch (ch)
        {
        case 1:

            for(i=0;i<V;++i)
              visited[i]=false;
            dfs(0,visited,graph);
            
            break;

       case 2:
            
            printf("\nEnter start node :");
            scanf("%d",&node);
            dijkstra(graph,node,dist, parent); 
            printarr(dist,V);
            printf("=======================\n");
      		printarr(parent,V);
            break;

       case 3:
            BellmanFord(graph_B, 0);
            break;

       case 4:
            transform(graph,arr);
            for(k=0; k<n; k++) 
                state[k] = initial;
            int dis=0;
            for(i=0;i<=n;i++)
            {
                if(state[i]==initial)
                { 
                    dis++; 
                    printf("Disjoint Graph Section Number : %d ", dis);  
                    BFS(i,n,arr,state,queue);
                } 
            }   
            break;

       case 5: 
            transform(graph,arr);
            primMST(arr, graph->V);
            
            break;

       case 6:
            KruskalMST(graph_B);
            break;

       case 7:
            add_edge(graph);
            E++;
            break;


       case 8:
            delete_edge(graph);
            E--;
            break;

       case 9:
            printGraph(graph);
            break;

       case 10: 
            exit(0);
            break;                                      
    
        default :
            printf(" Wrong choice, Please enter correct choice  ");
            break;
        }
    }


    return 0;
}
