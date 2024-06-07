#include <stdio.h>
#include <stdlib.h>
struct node{
    int key;
    int cost;
};
typedef struct node node;

/*This function should insert a minimum into a heap*/
void hp_insert(node* heap,int* pos,int size, int key, int cost){
    //Adding the new node to the end of the heap
    heap[size].key=key;
    heap[size].cost=cost;
    //Adding new node's position to the positions array
    pos[key]=size;
    int s= size;
    int p= (s-1)/2;

    while( p>=0 && heap[s].cost < heap[p].cost){
        int auxcost = heap[p].cost;
        int auxkey = heap[p].key;
        //Changing the positions in the positions array
        pos[heap[p].key]=s;
        pos[heap[s].key]=p;
        //Changing the key and cost of the parent to become the key and cost of the son
        heap[p].cost = heap[s].cost;
        heap[p].key = heap[s].key;
        //Changing the key and cost of the son to become the key and cost of the parent
        heap[s].cost = auxcost;
        heap[s].key = auxkey;
        //Updating the son and parent to the next execution
        s=p;
        p=(s-1)/2;
    }
    return;

}

/*This function should remove the minimum cost node*/
void hp_remove(node* heap, int* pos, int sizeheap, int heapmax){
    int size=sizeheap-1;
    //Erasing the first node from the positions array
    pos[heap[0].key]=-1;
    if(size==0){
        heap[0].key=-1;
        return;
    }
    //Changing the last node with the first
    heap[0].cost=heap[size].cost;
    heap[0].key=heap[size].key;
    //Erasing the last node
    heap[size].key=-1;
    //Chaging the new first node position in the positions array
    pos[heap[0].key]=0;

    int i=0, ls=1, rs=2;
    int smallestson=0;

    if(rs<heapmax){
        if(heap[rs].key!=-1 && heap[ls].key!=-1 ){
            if(heap[ls].cost < heap[rs].cost){
                smallestson=ls;
            }
            else{
                smallestson=rs;
            }  
        }
        else if(heap[rs].key==-1 && heap[ls].key!=-1){
            smallestson=ls;
        }
        else if(heap[rs].key!=-1 && heap[ls].key==-1){
            smallestson=rs;
        }
        else{
            return;
        }
    }
    else if(ls<heapmax){
        if(heap[ls].key!=-1){
            smallestson=ls;
        }
        else{
            return;
        }
    }
    else{
        return;
    }

    //Evaluating if the cost of the smallest son is smaller than the cost of the parent. If it is, the the son and the parent swipe positions
    while(heap[i].cost > heap[smallestson].cost){
        int auxcostss= heap[smallestson].cost;
        int auxkeyss= heap[smallestson].key;
        //Swiping the positions of the son and the parent in the positions array
        pos[heap[smallestson].key]=i;
        pos[heap[i].key]=smallestson;
        //Changing the key and cost of the son to become the key and cost of the parent
        heap[smallestson].cost=heap[i].cost;
        heap[smallestson].key=heap[i].key;
        //Changing the key and cost of the parent to become the key and cost of the son
        heap[i].cost=auxcostss;
        heap[i].key=auxkeyss;
        //Defining the new sons and parent
        i=smallestson;
        ls=(2*i)+1;
        rs=ls+1;
        if(rs<heapmax){
            if(heap[rs].key!=-1 && heap[ls].key!=-1 ){
                if(heap[ls].cost < heap[rs].cost){
                    smallestson=ls;
                }
                else{
                    smallestson=rs;
                }  
            }
            else if(heap[rs].key==-1 && heap[ls].key!=-1){
                smallestson=ls;
            }
            else if(heap[rs].key!=-1 && heap[ls].key==-1){
                smallestson=rs;
            }
            else{
                break;
            }
        }
        else if(ls<heapmax){
            if(heap[ls].key!=-1){
                smallestson=ls;
            }
            else{
                break;
            }
        }
        else{
            break;
        } 
    }
    
    
    return;
}

/*This function should change the cost of a certain key*/
void hp_changecost(node* heap, int* pos, int key, int newcost){
    //Finding the position of the key
    int s = pos[key];
    //Changing the cost of the key
    heap[s].cost=newcost;
    //Finding the key parent
    int p = (s-1)/2;
    //Changing the key with its parent while key's cost is smaller the parent's cost
    while( p>=0 && heap[s].cost < heap[p].cost){
        int auxcost = heap[p].cost;
        int auxkey = heap[p].key;
        //Changing the positions in the positions array
        pos[heap[p].key]=s;
        pos[heap[s].key]=p;
        //Changing the key and cost of the parent to become the key and cost of the son
        heap[p].cost = heap[s].cost;
        heap[p].key = heap[s].key;
        //Changing the key and cost of the son to become the key and cost of the parent
        heap[s].cost = auxcost;
        heap[s].key = auxkey;
        //Updating the son and parent to the next execution
        s=p;
        p=(s-1)/2;
    }
    return;
}

int main(void){
    int n;
    scanf("%d ",&n);
    node heap[n];
    int size=0;
    int pos[n];
    for(int i=0;i<n;i++){
        heap[i].key=-1;
        pos[i]=-1;
    }

    char op;
    while ((op=getchar())!='t'){
        if(op=='i'){
            int k, c;
            scanf(" %d %d ",&k,&c);

            if(pos[k]==-1){
                hp_insert(heap,pos,size, k ,c);
                size++;
            }
        }
        if(op=='m'){ //tem violação de memória nessa parte
            getchar();
            if(size==0){
                printf("heap vazio\n");
            }
            else{
                printf("minimo {%d,%d}\n",heap[0].key,heap[0].cost);
                hp_remove(heap,pos,size,n);
                size--;
            }
        }
        if(op=='d'){ 
            int k, nc;
            scanf(" %d %d ",&k,&nc);
            hp_changecost(heap,pos,k,nc);
        }
        
    }
    return 0;
}