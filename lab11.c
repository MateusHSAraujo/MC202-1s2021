#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Não pode ter variáveis globais

struct node{
    int key;
    struct node* left;
    struct node* right;
    struct node* parent;
};
typedef struct node node;

struct tree{
    node* root;
};
typedef struct tree tree;

node* bst_minimunfrom(node* p){
    if(p==NULL){
        return NULL;
    }
    while (p->left!=NULL){
        p=p->left;
    }
    return p;
}

node* bst_maximumfrom(node* p){
    if(p==NULL){
        return NULL;
    }
    while (p->right!=NULL){
        p=p->right;
    }
    return p;
}

/*Essa funcao deve criar uma bst vazia*/
tree* bst_create(){
    tree* treepoiter=calloc(1,sizeof(tree));
    return treepoiter;
}

/*Essa funcao deve inserir um inteiro x na bst e retorna 1. Se nao
houver memoria para essa operacao, o programa deve imprimir "memoria inficiente" e retornar zero*/
int bst_inset(tree* T,int x ){
    node* newnode = calloc(1,sizeof(node));
    if(!newnode){
        printf("memoria insuficiente\n");
        return 1;
    }
    newnode->key=x;
    if (T->root == NULL){
        T->root =newnode;
        newnode->parent=NULL;
        return 1;
    }
    //Quando temos garantidademte um no, podemos realizar a busca para inserção verificando o valor do próximo
    
    node* p=T->root;
    node* pp = NULL; // apontador pai de p

    while(p!=NULL){
        pp=p;
        if (p->key > x){
            p=p->left;
        }
        else{
            p=p->right;
        }
    }
    //Depois desse laco while, p eh um apontador para nulo eh pp aponta para o no que deveremos adicionar o valor data
    if(pp->key > x){//Precisamos verificar novamente se o no a ser inserido e para ser inserido na esquerda ou na direita
        pp->left=newnode;
    }
    else{
        pp->right=newnode;
    }
    newnode->parent=pp;
    return 1;
}

/*Essa funcao deve buscar na bst um inteiro x.Retonando o apontador para o no encontrado, ou Null no caso de ele nao pertencer a arvore*/
node* bst_search(node* p, int x){
    if(p==NULL){
        return NULL;
    }
    else{
        if (p->key==x){
            return p;
        }
        else{
            if(p->key > x){
                return bst_search(p->left,x);
            }
            else{
                return bst_search(p->right,x);
            }
        }
    }
    return NULL;
}

/*Essa funcao deve remover um inteiro x da bst. O programa deve usar o sucessor de um no para
substituir um no que tinha dois filhos*/
void bst_remove(node* z,tree* T){
    if(z->left==NULL && z->right==NULL){
        if(z->parent==NULL){ // se z for a raiz da arvore
            T->root=NULL;
            free(z);
            return;
        }
        if(z->parent->right==z){
            z->parent->right=NULL;
            free(z);
        }
        else{
            z->parent->left=NULL;
            free(z);
        }
        return;
    }
    if(z->left == NULL){
        if(z->parent==NULL){ // se z for a raiz da arvore
            T->root=z->right;
            z->right->parent=NULL;
            free(z);
            return;
        }
        if(z->parent->right==z){
            z->parent->right=z->right;
            z->right->parent=z->parent;
            free(z);
        }
        else{
            z->parent->left=z->right;
            z->right->parent=z->parent;
            free(z);
        }
        return;
    }
    if(z->right==NULL){
        if(z->parent==NULL){ // se z for a raiz da arvore
            T->root=z->left;
            z->left->parent=NULL;
            free(z);
            return;
        }
       if(z->parent->right==z){
            z->parent->right=z->left;
            z->left->parent=z->parent;
            free(z);
        }
        else{
            z->parent->left=z->left;
            z->left->parent=z->parent;
            free(z);
        }
        return; 
    }
    node* y=bst_minimunfrom(z->right);
    if(y->parent==z){
        y->left=z->left;
        y->left->parent=y;
        y->parent=z->parent;
        if(z->parent!=NULL){
            if(z->parent->right==z){
                z->parent->right=y;
            }
            else{
                z->parent->left=y;
            }
        }
        if(T->root==z){
            T->root=y;
        }
        free(z);
    }
    else{
        y->parent->left = y->right;
        if(y->right!=NULL){
            y->right->parent = y->parent;
        }
        y->left=z->left;
        y->left->parent=y;
        y->parent=z->parent;
        y->right=z->right;
        y->right->parent=y;
        if(z->parent!=NULL){
            if(z->parent->right==z){
                z->parent->right=y;
            }
            else{
                z->parent->left=y;
            }
        }
        if(T->root==z){
            T->root=y;
        }
        free(z);
    }
    return;
}


/*Essa funcao deve imprimir a bst em pre-ordem*/
void bst_preordem(node* p){
    if(p!=NULL){
        printf("%d ",p->key);
        bst_preordem(p->left);
        bst_preordem(p->right);
    }
}

/*Essa funcao deve imprimir a bst em-ordem*/
void bst_emordem(node* p){
    if(p!=NULL){
        bst_emordem(p->left);
        printf("%d ",p->key);
        bst_emordem(p->right);
    }
}

/*Essa funcao deve imprimir a bst em pos-ordem*/
void bst_posordem(node* p){
    if(p!=NULL){
        bst_posordem(p->left);
        bst_posordem(p->right);
        printf("%d ",p->key);
    }
}

/*Essa função deve buscar o sucessor de um inteiro x da arvore*/
node* bst_sucessor(node* p){
    if(p->right!=NULL){
        return bst_minimunfrom(p->right);
    }
    node* pp=p->parent;
    while(pp!=NULL && p==pp->right){
        p=pp;
        pp=pp->parent;
    }
    return pp;
}

/*Essa função deve buscar o predecessor de um inteiro x da arvore"*/
node* bst_predecessor(node* p){
    if(p->left!=NULL){
        return bst_maximumfrom(p->left);
    }
    node* pp=p->parent;
    while(pp!=NULL && p==pp->left){
        p=pp;
        pp=pp->parent;
    }
    return pp;
}

/*Essa funcao deve desalocar todos os nos de uma arvore e a arvore em si*/
void bst_freenodes(node* p){
    if(p==NULL){
        return;
    }
    bst_freenodes(p->left);
    bst_freenodes(p->right);
    free(p);
}

void bst_free(tree* T){
    bst_freenodes(T->root);
    free(T);
}

tree* leentrada(tree* T){
    char comando[15];
    scanf("%s ",comando);

    if(strcmp(comando,"criar")==0){
        static int primeiravez=0;
        if(primeiravez!=0){ //para o caso de a arvore ja existir, ela e resetada
            bst_freenodes(T->root);
            T->root=NULL;
            return T;
        }
        primeiravez=1;
        T=bst_create();
        return T;
    }

    if(strcmp(comando,"inserir")==0){
        int chave;
        scanf("%d ",&chave);
        if(bst_search(T->root,chave)==NULL){// No caso da chave ja existir na arvore, esse laco nao eh executado e uma copia nao eh criada
        bst_inset(T,chave);
        }
        return T;
    }

    if(strcmp(comando,"remover")==0){
        int chave;
        scanf("%d ",&chave);
        node* p=bst_search(T->root,chave);
        if(p!=NULL){ //No caso da arvore nao existir na arvore, esse laco nao eh executado
            bst_remove(p,T);
        }
        return T;
    }


    if(strcmp(comando,"buscar")==0){
        int chave;
        scanf("%d ",&chave);
        if(bst_search(T->root,chave)!=NULL){ //Caso onde a chave nao esta na arvore
            printf("%d esta na arvore\n",chave);
        }
        else{
            printf("%d nao esta na arvore\n",chave);
        }
        return T;
    }


    if(strcmp(comando,"pre-ordem")==0){
        
        if(T->root==NULL){ //Caso onde a chave nao esta na arvore
            printf("arvore vazia\n");
        }
        else{
            printf("pre-ordem: ");
            bst_preordem(T->root);
            printf("\n");
        }
        return T;
    }

    if(strcmp(comando,"em-ordem")==0){
        
        if(T->root==NULL){ //Caso onde a chave nao esta na arvore
            printf("arvore vazia\n");
        }
        else{
            printf("em-ordem: ");
            bst_emordem(T->root);
            printf("\n");
        }
        return T;
    }

    if(strcmp(comando,"pos-ordem")==0){
        
        if(T->root==NULL){ //Caso onde a chave nao esta na arvore
            printf("arvore vazia\n");
        }
        else{
            printf("pos-ordem: ");
            bst_posordem(T->root);
            printf("\n");
        }
        return T;
    }

    if(strcmp(comando,"sucessor")==0){
        int chave;
        scanf("%d ",&chave);
        node* p=bst_search(T->root,chave);
        
        if(p==bst_maximumfrom(T->root) || p==NULL){ //Caso em que o numero chave e o maximo e caso onde a chave nao esta na arvore
            printf("nao ha sucessor de %d\n",chave);
        }
        else{
            node* q =bst_sucessor(p);
            printf("sucessor de %d: %d\n",chave,q->key);
        }
        return T;
    }

    if(strcmp(comando,"predecessor")==0){ //Caso em que o numero chave e o minimo e caso onde a chave nao esta na arvore
        int chave;
        scanf("%d ",&chave);
        node* p=bst_search(T->root,chave);
        if(p==bst_minimunfrom(T->root) || p==NULL){
            printf("nao ha predecessor de %d\n",chave);
        }
        else{
            node* q =bst_predecessor(p);
            printf("predecessor de %d: %d\n",chave,q->key);
        }
        return T;
    }

    if(strcmp(comando,"terminar")==0){
        bst_free(T);
        return NULL;
    }

    return T;
}

/*Essa funcao deve ler a entrada e direcionar a execucao para a funcao adequada*/
int main(void){
    tree* T=leentrada(NULL);
    while (leentrada(T)!=NULL){
    }
    return 0;
}