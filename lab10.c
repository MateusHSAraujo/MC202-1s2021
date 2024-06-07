#include <stdio.h>
#include <stdlib.h>
struct node { // no para a lista encadeada usadas em mtf e transpose
    int data;
    struct node* next;
};
typedef struct node node;


struct nodec { // no para a lista duplamente encadeada usada em count
    int data;
    struct nodec* next;
    struct nodec* prev;
    int count;
};
typedef struct nodec nodec;


struct li{ // lista encadeada
    node* head;
};
typedef struct li li;

struct li2{ // lista duplamente encadeada
    nodec* head;
};
typedef struct li2 li2;

li* licreate(int N){ // constroi uma lista encadeada com numeros crescentes de 1 a N
    li* lista=calloc(1,sizeof(li));
    
    for(int i=0; i<N;i++){
        node* n=malloc(sizeof(node));
        if(!n){return NULL;}
        n->data = N-i;
        n->next = lista->head;
        lista->head = n;
    }
    return lista;
}

li2* licreatec(int N){ // constroi uma lista duplamente encadeada com numeros crescentes de 1 a N
    li2* lista=calloc(1,sizeof(li2));
    
    for(int i=0; i<N;i++){
        nodec* n=malloc(sizeof(nodec));
        if(!n){return NULL;}
        n->data = N-i;
        n->next = lista->head;
        n->count=0;
        lista->head = n;
        if(n->next!=NULL){
            n->next->prev=n;
        }
        n->prev=NULL;
    }
    return lista;
}

void li_free(li* L) { // libera lista encadeada

  node* p = L->head;
  node* n = NULL;

  while (p != NULL) {
    n = p->next;
    free(p);
    p = n;
  }

  free(L);
}

void li_free2(li2* L) { // libera lista duplamente encadeada

  nodec* p = L->head;
  nodec* n = NULL;

  while (p != NULL) {
    n = p->next;
    free(p);
    p = n;
  }

  free(L);
}

int mtf(li* lista,int valor){ //executa permutacao mtf e conta a quantidade de acessos precisos pra chegar ao valor desejado
    int acessos=0;
    for(node* p= lista->head; p->next!=NULL ;p=p->next){ // a execucao e feita de dois em dois. Dessa forma, ela deve parar quando o primeiro elemento for a cauda
        acessos++;
        if(p->data==valor){// esse caso so ocorrera se a cabeca for o no de valor desejado   
            return acessos;
        }
        if(p->next->data==valor){// eh preciso fazer a execucao dois a dois para poder mudar o apontador do no anterior ao que sera movido
            acessos++; // lembrar que, nesse caso, p->next eh o no de valor desejado
            node* q;// variavel auxiliar
            q=p->next->next;
            p->next->next=lista->head;// p->next passa a apontar para o no que esta na cabeca da lista
            lista->head = p->next;// p->next passa a ser o no da cabeca da lista, ou seja, o primeiro elemento
            p->next=q;// p (no anterior ao no de valor desejado) passa a apontar para o antigo no posterior a p
            return acessos;
        }

    }
    return 1;
}

int transpose(li* lista, int valor){ //executa permutacao transpose e conta a quantidade de acessos precisos pra chegar ao valor desejado
    int acessos=0;
    if(lista->head->next==NULL){// no caso da lista ter um valor, essa condicional evita violação de memória
        return 1;
    }
    for (node* p=lista->head;p->next->next!=NULL; p=p->next){// a execucao e feita de tres em tres, parando quando o segundo elemento for a cauda
        acessos++;
        if(p->data==valor){// so ocorre se o no desejado for a cabeca
            return acessos;
        }
        if(p->next->data==valor){// so ocorre quando o no desejado for o segundo elemento
            acessos++; // nesse caso, o no desejado e p->next
            node* q=p->next->next; // variavel auxiliar
            p->next->next=lista->head; // o no dejesado passa a apontar para o no da cabeca
            lista->head=p->next; // o no desejado passa a ser a cabeca da lista
            p->next=q; // o antigo no anterior ao desejado passa a apontar para o antigo no posterior ao desejado
            return acessos;
        }
        if(p->next->next->data==valor){// ocorre quando o no desejado ocupam outras posicoes
            acessos+=2; // nesse caso, o no desejado e p->next->next
            node* aux=p->next->next->next; // guarda o apontador do no apontado pelo no desejado
            node* aux2=p->next->next; // guarda o apontador do no desejado
            node* aux3=p->next; // guarda o apontador do no anterior ao desejado
            p->next->next->next=aux3; // o no desejado passa a apontar para o antigo no anterior a ele
            p->next->next=aux; // o antigo no anterior ao desejado passa a apontar para o antigo no posterior ao desejado
            p->next=aux2; // o no anterior ao antigo no anterior ao desejado passa a apontar para o no desejado
            return acessos;
        }
    }
    return 0;
}

int count(li2* lista, int valor){//executa permutacao count e conta a quantidade de acessos precisos pra chegar ao valor desejado
    int acessos=0;// nessa permutacao, eh usado uma lista duplamente encadeada
    if(lista->head->next==NULL){ // essa condicional deve evitar vioalacao de memoria no caso de a lista ter um unico elemento
        return 1;
    }
    for (nodec* p=lista->head;p!=NULL; p=p->next){// a execucao sera feita de um em um
        acessos++;
        if (p->data==valor){
            p->count++;
            if(p==lista->head){ // Se o no desejado estiver na cabeca, nada, alem de aumentar o seu contador, precisa ser feito
                return acessos;
            }
            else{
                for(nodec* q=p->prev; q!=NULL; q=q->prev){// essa iteracao serve para analisar o contador dos elementos anteriores ao no desejado
                    if((q->count) > (p->count)){ // se encontrar um no com contador maior do que o do no desejado, sabemos que o no desejado deve ser colocado logo depois desse no de contador maior
                        if(q==p->prev){ // se esse no de contador maior vier logo depois do no desejado, nao precisaremos mexer na estrutura da lista
                            return acessos;
                        }
                        p->prev->next=p->next;// o no anterior ao desejado passa a apontar para o no posterior ao desejado
                        if(p->next!= NULL){// se o no desejado nao estiver na cauda...
                            p->next->prev=p->prev;// ...o no posterior ao desejado deve apontar como anterior o no anterior ao desejado
                        }
                        q->next->prev=p; // o no posterior ao no de maior contador encontrado deve apontar como anterior o no desejado
                        p->next=q->next; // o no desejado deve apontar para o no apontado pelo no de contador maior
                        q->next=p; // o no de contador maior tem que apontar como proximo o no desejado
                        p->prev=q; // o no desejado tem que apontar como anterior o no de contador maior
                        return acessos;
                    }
                }// Essa serie de linhas so ocorrerao da iteracao nao encontrar no com contador maior que do no desejado, ou seja, quando o no desejado deve passar a ser a cabeça da lista
                p->prev->next=p->next;// o no anterior ao desejado passa a apontar para o no posterior ao desejado
                if(p->next!= NULL){// se o no desejado nao estiver na cauda...
                    p->next->prev=p->prev;//...o no posterior ao desejado deve apontar como anterior o no anterior ao desejado
                }
                p->next=lista->head;// o no desejado deve apontar para o no da cabeça da lista
                lista->head->prev=p;// o no da cabeca da lista deve apontar como anterior o no desejado
                lista->head=p;// o no da cabeca da lista passa a ser o no desejado
                p->prev=NULL;// o no da cabeca sempre deve apontar null como anterior
                return acessos;
            }


        }

    }
    return 0;
}

int customovetofront(int* acessos,int N,int R){ // essa funcao acumula a quantidade de acessos para a permutacao mtf
    li* lista=licreate(N);
    int contador=0;
    for(int i=0;i<R;i++){
        contador+=mtf(lista,acessos[i]);
    }
    li_free(lista);
    return contador;
}

int custotranspose(int* acessos, int N,int R){ // essa funcao acumula a quantidade de acessos para a permutacao transpose
    li* lista=licreate(N);
    int contador=0;
    for(int i=0;i<R;i++){
        contador+=transpose(lista,acessos[i]);
    }
    li_free(lista);
    return contador;
}

int custocount(int* acessos, int N,int R){ // essa funcao acumula a quantidade de acessos para a permutacao count
    li2* lista=licreatec(N);
    int contador=0;
    for(int i=0;i<R;i++){
        contador+=count(lista,acessos[i]);
    }
    li_free2(lista);
    return contador;
}

int main(void){
    int N , R;
    scanf(" %d ",&N);
    scanf(" %d ",&R); 
    int acessos[R];

    for(int i=0; i<R; i++){
        scanf("%d", &acessos[i]);
    }

    int MTF= customovetofront(acessos,N,R);
    int Transpose= custotranspose(acessos,N,R);
    int Count= custocount(acessos,N,R);
   
    printf("MTF: %d\nTranspose: %d\nCount: %d\n",MTF,Transpose,Count);
    return 0;
}