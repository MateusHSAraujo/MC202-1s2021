#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

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
    int distance;
    int previous;
    int marked;
    li* edges;

};
typedef struct vertex vertex;

//Add at the end
void enqueue(li* queue, int key){
    node* newnode= malloc(sizeof(node));
    newnode->data=key;
    newnode->next=NULL;
    if(queue->head==NULL){
        queue->head=newnode;
    }
    else{
        node* p=queue->head; 
        while(p->next!=NULL){
            p=p->next;
        }
        p->next=newnode;
    }

    return;
}

//Retrive the first
int dequeue(li* queue){
    if(queue->head==NULL){
        return -1;
    }
    node* p=queue->head;
    int value=queue->head->data;
    queue->head=queue->head->next;
    free(p);
    return value;
}

void bsf(vertex* graph, int o,int n){
    li* queue=calloc(1,sizeof(li));
    queue->head=NULL;
    graph[o-1].distance=0;
    graph[o-1].marked=1;
    printf("%d %d\n",o,graph[o-1].distance);
    enqueue(queue,o-1);
    while (queue->head!=NULL){
        int u=dequeue(queue);
        vertex* vertexu=&graph[u];
        for(node* v=vertexu->edges->head; v!=NULL; v=v->next){
            vertex* vertexv=&graph[(v->data)-1];
            if(vertexv->marked==0){
                vertexv->distance=vertexu->distance+1;
                vertexv->previous=u;
                enqueue(queue,(v->data-1));
                vertexv->marked=1;
                printf("%d %d\n",v->data,vertexv->distance);
                
            }
        }

    }
    return;
}

int main(void){
    scanf("Vertices: ");
    int n; //number of vertices
    scanf("%d ",&n);
    vertex graph[n];

    // Making all list in the array point to null
    for(int i=0; i<n;i++){
        graph[i].edges=malloc(sizeof(li));
        graph[i].edges->head=NULL;
        graph[i].distance=INT_MAX;
        graph[i].previous=0;
        graph[i].marked=0;
    }
    
    int a,b; //vertices in the edge
    scanf("Arestas: ");
    scanf("%d,%d ",&a,&b);
    //Reading the edges and completing the graph
    while(a!=0 && b!=0){
        
        node* vertexa=graph[a-1].edges->head;
        node* vertexb=graph[b-1].edges->head;
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
        if(vertexb==NULL){
            node* newnode=calloc(1,sizeof(node));
            newnode->data = a;
            newnode->next = NULL;
            graph[b-1].edges->head=newnode;
        }
        else{
            while(vertexb->next!=NULL){
                vertexb=vertexb->next;
            }
            node* newnode=calloc(1,sizeof(node));
            newnode->data = a;
            newnode->next = NULL;
            vertexb->next=newnode;

        }
        scanf("%d,%d ",&a,&b);
    }
    // O grafo está sendo montado com sucesso!
    scanf("Origem: ");
    int o;
    scanf("%d",&o);
    printf("Origem da busca: %d\n",o);
    printf("Vertices alcancados e distancias:\n");
    bsf(graph,o,n);

    return 0;
}