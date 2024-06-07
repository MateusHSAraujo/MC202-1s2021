#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "li.h"


li* li_alloc() {
  return calloc(1,sizeof(li));
}



void li_free(li* L) {

  node* p = L->head;
  node* n = NULL;

  while (p != NULL) {
    n = p->next;
    free(p);
    p = n;
  }

  free(L);
}



int li_insert(li* L, int data) {

  node* n = malloc(sizeof(node));
  if (n == NULL)
    return 0;

  n->data = data;
  n->next = L->head;
  L->head = n;

  return 1;
}



void li_print(li* L) {

  node* p = L->head;
  printf("{");

  while (p != NULL && p->next != NULL) {
    printf("%d, ",p->data);
    p = p->next;
  }

  if (p != NULL)
    printf("%d",p->data);

  printf("}");
}


void cutdup(li* L){
    for(node* p=L->head; p!=NULL; p=p->next){
        int count=0;
        for(node* q=p->next; q!=NULL; ){
            count++;
            if(p->data==q->data){
                node* aux=p;
                node* aux2=q;
                if(count>1){
                    for (int i = 0; i < count-1; i++){
                        aux=aux->next;
                    }
                }
                aux->next=q->next;
                q=q->next;
                free(aux2);
            }
            else{
                q=q->next;
            }
        }
    }
}

/*
  Evaluate the union of lists of ints A and B.  Return a new list on success.
  If memory allocation fails any partially constructed list is freed and it
  returns NULL.
*/
li* li_union(li* A, li* B){
    li* U=li_alloc();
    if (!U){
        return NULL;
    }
    
    node* p=A->head;
    node* q=B->head;

    while( p !=NULL){
        if (li_insert(U,p->data)==0){
            li_free(U);
            return NULL;
        }
        p=p->next;
    }
    while( q != NULL){
        if(li_insert(U,q->data)==0){
            li_free(U);
            return NULL;
        }
        q=q->next;
    }
    cutdup(U);
    return U;

}

/*
  Evaluate the intersection of lists of ints A and B.  Return a new list on
  success.  If memory allocation fails any partially constructed list is freed
  and it returns NULL.
*/
li* li_intersection(li* A, li* B){
    li* I=li_alloc();
    for( node* i= A->head; i!=NULL; i=i->next){
        for (node* j = B->head; j!=NULL; j=j->next){
            if (i->data==j->data){
                if(li_insert(I,i->data)==0){
                    li_free(I);
                    return NULL;
                }
            }
        }
    }
    cutdup(I);
    return I;
}

/*
  Evaluate the difference A-B of lists of ints.  Return a new list on success.
  If memory allocation fails any partially constructed list is freed and it
  returns NULL.
*/
li* li_difference(li* A, li* B){
    li* D=li_alloc();
    for( node* i= A->head; i!=NULL; i=i->next){
        int counter=0;
        for (node* j = B->head; j!=NULL; j=j->next){
            if (i->data==j->data){
                counter++;
            }
        }
        if(counter==0){
            if(li_insert(D,i->data)==0){
                li_free(D);
                return NULL;
            }
        }
    }
    cutdup(D);
    return D;
}