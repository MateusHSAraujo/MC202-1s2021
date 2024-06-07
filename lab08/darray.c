#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
// Essa é a melhor versão até agora
typedef struct darray {

  char** data; // The array of pointers to char, that is, the array of string.

  int first; // The index of the first element in the sequence.
  int size;  // The sequence size.

  int capacity; // The array size.
  int min_cap;  // The minimum array size.

} darray;

/**
  Release all the strings in a darray and the darray itself.
**/
void da_free(darray* A){
    int totaldedados= A->size;
    for (int i=A->first;i<totaldedados;i++){
        free((A->data)[i]);
    }
    free(A->data);
    free(A);
    return;

}

char** aumentaarray(darray* A){ // Essa funcao, alem de aumentar o array dinamico, tambem transforma uma sequencia circular em linear
    char** novoarray = calloc(2*(A->capacity),sizeof(char*));
    int capacidadeatual = A->capacity;
    for(int i=0; i<capacidadeatual;i++){
        if(i>=(A->first)){ //No caso de sequencias lineares, somente essa parte do if ocorrera
            int tamanhostri = strlen((A->data)[i])+1;
            novoarray[i-(A->first)]=malloc(tamanhostri*sizeof(char));
            if(!novoarray[i-(A->first)]){
                return NULL;
            }
            strcpy(novoarray[i-(A->first)],(A->data)[i]);
        }
        else{ // No caso de sequencias circulares, essa parte aplica a correcao das posicoes e transforma a sequencia resultante em linear
            int tamanhostri= strlen((A->data)[i])+1;
            novoarray[capacidadeatual-(A->first)+i]=malloc(tamanhostri*sizeof(char));
            if(!novoarray[capacidadeatual-(A->first)+i]){
                return NULL;
            }
            strcpy(novoarray[capacidadeatual-(A->first)+i],(A->data)[i]); 
        
        }
    }
    A->first=0;
    A->capacity=2*capacidadeatual;

    return novoarray;
}

char** diminuiarray(darray* A){//Essa função deve reduzir um array dinamico pela metade e retornar um apontador para ele
    char** novoarray=calloc((A->capacity)/2,sizeof(char*));
    int tamanhoatual=A->capacity;
    for(int i=A->first,j=0; i+(A->size)<(A->capacity) && j<(A->size);i++,j++){
      int tamstrv= strlen((A->data)[i])+1;
      novoarray[i-(A->first)]=malloc(tamstrv*sizeof(char));
      if(!novoarray[i-(A->first)]){
          return NULL;
      }
      strcpy(novoarray[i-(A->first)],(A->data)[i]);
    }
    int numerosrestantes= (A->size)+(A->first)-(A->capacity);
    for(int i=0;i<numerosrestantes;i++){
      int tamanhostri= strlen((A->data)[i])+1;
      novoarray[tamanhoatual-(A->first)+i]=malloc(tamanhostri*sizeof(char));
      if(!novoarray[tamanhoatual-(A->first)+i]){
        return NULL;
      }
      strcpy(novoarray[tamanhoatual-(A->first)+i],(A->data)[i]);
    }
    /*
    for(int i=0; i<(A->capacity);i++){
      if(strcmp(A->data[i],"(null)")!=0 && !A->data==0){ // Deve pular o elemento caso ele seja NULL
        
        if(i>=(A->first)){//Para sequencias lineares e a parte inicial das sequencias circulares, o codigo funciona como o de aumento
            int tamstrv= strlen((A->data)[i])+1;
            novoarray[i-(A->first)]=malloc(tamstrv*sizeof(char));
            if(!novoarray[i-(A->first)]){
                return NULL;
            }
            strcpy(novoarray[i-(A->first)],(A->data)[i]);
            printf("%d-",i-(A->first));
            printf("%s\n",(A->data)[i]);
        }
        else{//Para sequencias circulares, o codigo funciona como o de aumento, so que mudando a posicao de insercao
            int tamanhostri= strlen((A->data)[i])+1;
            novoarray[tamanhoatual-(A->first)+i]=malloc(tamanhostri*sizeof(char));
            if(!novoarray[tamanhoatual-(A->first)+i]){
                return NULL;
            }
            strcpy(novoarray[tamanhoatual-(A->first)+i],(A->data)[i]);
        }
      }
    }*/
    A->first=0;
    A->capacity=(A->capacity)/2;
  
    return novoarray;
}


/**
   Allocate a darray and the array of pointers to strings with
   initial capacity.  Set the initial state of the darray properly.

   capacity is the initial array size.  It is also the minimum array size.

   It returns the address of a new darray.  On failure it returns NULL.
**/
darray* da_alloc(int capacity){
    darray* vetordinamico=malloc(sizeof(darray));
    if(!vetordinamico){
        return NULL;
    }
    char** arraydestrings = calloc(capacity,sizeof(char*));
    if(!arraydestrings){

        return NULL;
    }
    
    vetordinamico->data = arraydestrings;
    vetordinamico->capacity= capacity;
    vetordinamico->min_cap=capacity;
    vetordinamico->size=0;
    vetordinamico->first=0;

    return vetordinamico;
}


/**
   Add a copy of a string to the end of the sequence.

   If the array is full, it tries to double its capacity and then adds the
   string.

   On success it returns 1.  When resizing the array is not possible it will not
   push and will return 0.
**/
int da_push(darray* A, char* string){
    if((A->size)<(A->capacity)){
        int tamanhodastringinserida = strlen(string)+1;
        int posinicio = A->first;
        if(A->size==0){
            (A->data)[0]= malloc(tamanhodastringinserida*sizeof(char));
            if(!(A->data)[0]){
            return 0;
            }
            strcpy((A->data)[0],string);
            A->size+=1;
            return 1;
        }
        else{
            if ((A->size)+posinicio < (A->capacity)){ // A sequencia e linear
                int posfinalnova=(A->size)+posinicio;
                (A->data)[posfinalnova]= malloc(tamanhodastringinserida*sizeof(char));
                if(!(A->data)[posfinalnova]){
                    return 0;
                }
                strcpy((A->data)[posfinalnova],string);
                A->size+=1;
                return 1;
            }
            else{ // Sequencia circular
                int posfinalnova=(A->size)-(A->capacity)+posinicio;
                (A->data)[posfinalnova]= malloc(tamanhodastringinserida*sizeof(char));
                if(!(A->data)[posfinalnova]){
                    return 0;
                }
                strcpy((A->data)[posfinalnova],string);
                A->size+=1;
                return 1;
            }
        }
    }
    else{
        A->data=aumentaarray(A);
        if(!A->data){
            return 0;
        }
        int tamanhodastringinserida = strlen(string)+1;
        // Do jeito que o codigo esta construido, depois de um aumento de tamanho, o array resultante sera uma sequencia linear
        // Como o array e linear, nao e preciso verificar linearidade
        int posfinalnova=(A->size);
        (A->data)[posfinalnova]= malloc(tamanhodastringinserida*sizeof(char));
        if(!(A->data)[posfinalnova]){
            return 0;
        }
        strcpy((A->data)[posfinalnova],string);
        A->size+=1;
        return 1;


    }

}

/**
   Remove a string from the end of the sequence and return a pointer to it.

   If the array is 1/4 full, this function halves its capacity and then removes
   the string.  The capacity will never be smaller than the initial capacity.
**/
char* da_pop(darray* A){
    if(((A->size)-1)<=((A->capacity)/4)){
      if(A->capacity!= A->min_cap){
        A->data=diminuiarray(A); 
      }
    }
    int posinicio=(A->first);
    if ((A->size)+posinicio <= (A->capacity)){// Verifica se a sequencia e linear
        
        int posfinal=(A->size)+posinicio-1;
        A->size-=1;
        char* apstrremovida=(A->data)[posfinal];
        return apstrremovida; // A unica coisa que se e pedido pra retornar e o apontador da string removida

    }
    else{// Ocorre se a sequencia for circular

        int posfinal=(A->size)-(A->capacity)+posinicio-1;
        A->size-=1;
        char* apstrremovida=(A->data)[posfinal];
        return apstrremovida;

    }


}



/**
   Add a copy of a string to the **beginning** of the sequence.

   If the array is full, it tries to double its capacity and then adds the
   string.

   On success it returns 1.  When resizing the array is not possible it will not
   inject and will return 0.
**/
int da_inject(darray* A, char* string){
    

    if((A->size)<(A->capacity)){
        int tamanhodastringinserida = strlen(string)+1;
        int posinicio=A->first;

        if(A->size==0){
            (A->data)[0]= malloc(tamanhodastringinserida*sizeof(char));
            if(!(A->data)[0]){
            return 0;
            }
            strcpy((A->data)[0],string);
            A->size+=1;
            return 1;
        }
        else{
            if (posinicio==0){// e o primeiro elemento da sequencia
                (A->data)[(A->capacity)-1]=malloc(tamanhodastringinserida*sizeof(char));
                if (!(A->data)[(A->capacity)-1]){
                    return 0;
                }
                strcpy((A->data)[(A->capacity)-1],string);
                A->size+=1;
                A->first=(A->capacity)-1;
                return 1;
            }
            else{
                (A->data)[posinicio-1]=malloc(tamanhodastringinserida*sizeof(char));
                if (!(A->data)[posinicio-1]){
                    return 0;
                }
                strcpy((A->data)[posinicio-1],string);      
                A->size+=1;
                A->first = posinicio-1;                         
                return 1;
            }

          
        }
    }
    else{
        A->data=aumentaarray(A);
        if(!A->data){
            return 0;
        }
        int tamanhodastringinserida = strlen(string)+1;
        // A funcao de aumento do array dinamico retorna sempre uma sequencia linear, por isso nao e necessario analizar o caso
        (A->data)[(A->capacity)-1]=malloc(tamanhodastringinserida*sizeof(char));
        if (!(A->data)[(A->capacity)-1]){
            return 0;
        }
        strcpy((A->data)[(A->capacity)-1],string);
        A->size+=1;
        A->first=(A->capacity)-1;
        return 1;
    }

}



/**
   Remove a string from the beginning of the sequence and return a pointer to it.

   If the array is 1/4 full, this function halves its capacity and then removes
   the string.  The capacity will never be smaller than the initial capacity.
**/
char* da_eject(darray* A){
    if(((A->size)-1)<=((A->capacity)/4)){
      if(A->capacity>A->min_cap){
        A->data=diminuiarray(A); 
      }
    }
    char* strposini= (A->data)[A->first];
    A->size-=1;
    if((A->first)+1>=(A->capacity)){
      A->first=0;
      
    }
    else{
      if(A->size!=0){
        A->first= (A->first)+1;
      }
      else{
        A->first=0;
      }
    }


    return strposini;
}



/**
   Return a pointer to the first string in the sequence.
**/
char* da_first(darray* A){
    return (A->data)[A->first];
}



/**
   Return a pointer to the last string in the sequence.
**/
char* da_last(darray* A){
    int posinicio=A->first;
    if ((A->size)+posinicio <= (A->capacity)){ // A sequencia e linear
        int posfinal=(A->size)+posinicio-1;
        return (A->data)[posfinal];
    }
    else{// A sequencia e circular
        int posfinal=(A->size)-(A->capacity)+posinicio-1;
        return (A->data)[posfinal];
    }
}



/**
   Return 1 if the sequence is empty, otherwise return 0.
**/
int da_is_empty(darray* A){
  if(A->size==0){
    return 1;
  }
  else{
    return 0;
  }
}
