#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct nodel{
    char data;
    struct nodel* prev;
    struct nodel* next;
};
typedef struct nodel nodel;

struct li{
    nodel* head;
};
typedef struct li li;

struct nodet{
    char data;
    struct nodet* right;
    struct nodet* left;
};
typedef struct nodet nodet;

struct tree{
    nodet* root;
};
typedef struct tree tree;

li* li_alloc() {// this function allocates memorie for a list and return its pointer 
    li* lipointer=calloc(1,sizeof(li));
    if(!lipointer){
        printf("problem in lipointer");
        exit(1);
    }
    return lipointer;
}


void li_partialfree(li* L) { //this function free the nodes of a list and turn back its head pointer to null

    nodel* p = L->head->next;
    nodel* n = NULL;

    while (p != NULL) {
      n = p->next;
      free(p);
      p = n;
    }
    L->head=NULL;
}

int li_insert(li* L, char key) { // this function inserts a key in a list
    nodel* n = malloc(sizeof(nodel));
    if(!n){
        printf("error in n alocation");
        exit(1);
    }
    if (n == NULL)
        return 0;
    nodel* p=L->head;
    if(p==NULL){
        L->head=n;
        n->data = key;
        n->next=NULL;
        n->prev=NULL;
    }
    else{
        while (p->next!=NULL){
            p=p->next;
        }
        p->next=n;
        n->data=key;
        n->next=NULL;
        n->prev=p;
    }
  return 1;
}

nodel* li_search(nodel* L, char key){ // this function search a key in a list
    for(nodel* p=L;p!=NULL;p=p->next){
        if(p->data==key){
            return p;
        }
    }
    return NULL;
}

int isleft(char son, char parent, li* pref){ // this function evaluate if a character son is in the left of a character parent in a list
    for(nodel* p=li_search(pref->head,parent)->prev;p!=NULL;p=p->prev){
        if(p==NULL){
            return 0;
        }
        if(p->data==son){
            return 1;
        }
    }
    return 0;
}

int isright(char son, char parent, li* pref){ // this function evaluate if a character son is in the right of a character parent in a list
    for(nodel* p=li_search(pref->head,parent)->next;p!=NULL;p=p->next){
        if(p==NULL){
            return 0;
        }
        if(p->data==son){
            return 1;
        }
    }
    return 0;    
}

void t_insert(nodet* newnodet,tree* T,li* pref){ // this function insert a node into a tree based on a list of preference
    for(nodet*p=T->root;p!=NULL;){
        if(isright(newnodet->data,p->data,pref)){
            if(p->right==NULL){
                p->right=newnodet;
                break;
            }
            p=p->right;
        }
        else if(isleft(newnodet->data,p->data,pref)){
            if(p->left==NULL){
                p->left=newnodet;
                break;
            }
            p=p->left;
        }
        else{
            break;
        }
    }
    return;
}

int createtree(li* po,li* em, tree* T){ // this function creates a tree using a list o roots (post-order) and a list of preference (in-order)
    nodet* firstnodet=calloc(1,sizeof(nodet));
    if(!firstnodet){
        printf("problem in firstnodet");
        exit(1);
    }
    T->root=firstnodet;
    firstnodet->data=po->head->data;
    for(nodel* ins=po->head->next;ins!=NULL;ins=ins->next){
        nodet* newnodet=calloc(1,sizeof(nodet));
        if(!newnodet){
            printf("problem in newnodet");
            exit(1);
        }
        newnodet->data=ins->data;
        t_insert(newnodet,T,em);
    }
    return 1;
}

void t_postorder(nodet* p){ //this function print a tree in post-order
    if(p!=NULL){
        t_postorder(p->left);
        t_postorder(p->right);
        printf("%c",p->data);
    }
}
void t_freenodes(nodet* p){// These functions free a tree
    if(p==NULL){
        return;
    }
    t_freenodes(p->left);
    t_freenodes(p->right);
    free(p);
}

void t_free(tree* T){
    t_freenodes(T->root);
    free(T);
}

int main(void){
    char chr;
    int list2=0;
    li* po=li_alloc();
    li* em=li_alloc();
    while ((chr=getchar())!=EOF){
        if(chr==' '){
            list2=1;
            continue;
        }
        if(chr=='\n'){ // create and print the tree
            list2=0;
            tree* newtree=calloc(1,sizeof(tree));
            if(!newtree){
                printf("problem in newnodet");
                exit(1);
            }
            createtree(po,em,newtree);
            t_postorder(newtree->root);
            printf("\n");
            li_partialfree(po);
            li_partialfree(em);
            t_free(newtree);
            continue;
        }
        if(list2==0){ //create the post-order list
            li_insert(po,chr);

        }
        if(list2==1){ // create the in-order list
            li_insert(em,chr);
        }
    }
    return 0;
}