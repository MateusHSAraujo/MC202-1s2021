#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    int data;
    struct node* next;
    
};
typedef struct  node node;

struct li
{
    node* head;
    
};
typedef struct li li;

struct vertex
{
    int discovery; // time of discovery
    int finished; // time of ending
    int color; // -1 is white, 0 is gray, 1 is black
    int previous; 
    li* edges;

};
typedef struct vertex vertex;

void graph_selection_sort(vertex* graph,int n,int* index){
    
    for(int i=0;i<n;i++){
        int min=i;
        for(int j=i+1;j<n;j++){
            if (graph[j].discovery<graph[min].discovery){
                min=j;
            }
        }
        vertex aux=graph[min];
        graph[min]=graph[i];
        graph[i]=aux;
        int temp = index[min];
        index[min]=index[i];
        index[i]=temp;
    }
    return;
}

int dfs_visit(vertex* graph, int u,int* time){
    int cycle=1;
    *time=*time+1;
    vertex* vertexu=&graph[u];
    vertexu->discovery=*time;
    vertexu->color=0;
    for(node* v=vertexu->edges->head; v!=NULL;v=v->next){
        vertex* vertexv=&graph[(v->data)-1];              
        if(vertexv->color==-1){
            vertexv->previous=u+1;
            cycle=cycle*dfs_visit(graph,(v->data)-1,time);
        }
        if(vertexv->color==0){
            cycle=0;
        }
    }
    vertexu->color=1;
    *time=*time+1;
    vertexu->finished=*time;
    return cycle;
}

int dfs(vertex* graph,int n){
    int time=0;
    int cycle=1;
    int countofcycles=0; 
    for(int u=0; u<n;u++){
        if (graph[u].color==-1){
            cycle=dfs_visit(graph,u,&time);
        }
        if(cycle==0){
            countofcycles++;
        }
    }
    if(countofcycles!=0){ 
        cycle=0;
    }
    else{
        cycle=1;
    }
    return cycle; // returns 1 if there is no cycles in the graph and 0 if there is
}



int main(void){
    scanf("Vertices: ");
    int n; //number of vertices
    scanf("%d ",&n);
    vertex graph[n];
    int index[n];

    // Setting the graph and the array of index to be used in the sort
    for(int i=0; i<n;i++){
        graph[i].edges=malloc(sizeof(li));
        graph[i].edges->head=NULL;
        graph[i].discovery=0;
        graph[i].finished=0;
        graph[i].color=-1;
        graph[i].previous=0;
        index[i]=i+1;
    }
    
    int a,b; //vertices in the edge
    scanf("Arestas: ");
    scanf("%d,%d ",&a,&b);
    //Reading the edges and completing the graph
    while(a!=0 && b!=0){
        node* vertexa=graph[a-1].edges->head;
        if(vertexa==NULL){
            node* newnode=calloc(1,sizeof(node));
            newnode->data = b;
            newnode->next = NULL;
            graph[a-1].edges->head=newnode;
        }
        else{
            while(vertexa->next!=NULL){
                vertexa=vertexa->next;
            }
            node* newnode=calloc(1,sizeof(node));
            newnode->data = b;
            newnode->next = NULL;
            vertexa->next=newnode;
        }
        scanf(" %d,%d",&a,&b);
    }
    printf("Vertices e tempos:\n");
    int cycle=dfs(graph,n);
    graph_selection_sort(graph,n,index);
    for(int i=0;i<n;i++){
        printf("%d [%d,%d]\n",index[i],graph[i].discovery,graph[i].finished);
    }
    if(cycle){ // 1 if there is no cycle, 0 if there is
        printf("Grafo aciclico: sim\n");
    }
    else{
        printf("Grafo aciclico: nao\n");
    }

    return 0;
}