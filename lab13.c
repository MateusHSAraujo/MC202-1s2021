#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define M 6257

struct node{
    unsigned long key;
    int timestamp;
};
typedef struct node node;



//This monstrosity converts strings to intergers
unsigned long djb2(unsigned char *str) {
    unsigned long hash = 5381;
    int c;
  
    while ((c = *str++)){
        hash = ((hash << 5) + hash) ^ c; // hash * 33 XOR c
    }
    
    return hash;
}

int h1(unsigned long k){
    return k%M;
}

int h2(unsigned long k){
    return 1+(k%(M-2));
}

int h(unsigned long k,int i){
    int r=((h1(k)+(i*h2(k)))%M);
    return r;
}
//Search a key into the hashing array
int search(unsigned long key,node* array){
    int pos=h(key,0);
    for(int i=1; array[pos].key!=-1 && array[pos].key!=key ;i++){
        pos=h(key,i);
    }
    if(array[pos].key==key){//key found,return position to enable removal
        return pos;
    }
    else{// key was not found
        return -1;
    }
}

//Insert a key into the hashing array, returning 1 in sucess and 0 if the array already have that key
int insert(unsigned long key,node* array,int timestamp){
    int pos=h(key,0);
    if (search(key,array)!=-1){
        return 0;
    }
    for(int i=1; array[pos].key!=-1 && array[pos].key!=-2 && array[pos].key!=key ;i++){
        pos=h(key,i);
    }
    if(array[pos].key==key){ //key is already in the array
        return 0;
    }
    else{ // key isnt in the array yet
        array[pos].key=key;
        array[pos].timestamp=timestamp;
        return 1;
    }
}



//Remove a key of an hashing array
int push(unsigned long key, node* array){
    int pos=search(key,array);
    if (pos==-1){
        return 0;
    }
    else{
        array[pos].key=-2;
        return 1;
    }
}

int main(void){             
    char operation;
    unsigned char str[251]; 
    unsigned char chr='\0'; 
    int i=0;
    unsigned long key;
    int timestamp=0;
    node array[M];
    for(int j=0;j<M;j++){
        array[j].key=-1;
    }

    while (scanf("%c",&operation)!='f'){
        chr=getchar();
        if(chr!='\n'){
            chr=getchar();
            while(chr!='\n'){
                str[i]=chr;
                i++;
                chr=getchar();
            }
            str[i]='\0';
            i=0;
            key=djb2(str);
            if (operation=='i'){
                if(insert(key,array,timestamp)){
                    printf("[%s] foi inserida\n",str);
                    timestamp++;
                }
                else{
                    printf("[%s] ja esta na tabela\n",str);
                }
            }
            if(operation=='b'){
                int res=search(key,array);
                if(res!=-1){ // key found
                    printf("[%s] esta na tabela, timestamp %d\n",str,array[res].timestamp);
                }
                else{
                    printf("[%s] nao esta na tabela\n",str);
                }
            }
            if (operation=='r'){
                if(push(key,array)){
                    printf("[%s] foi removida\n",str);
                }
                else{
                    printf("[%s] nao esta na tabela\n",str);
                }
            }
            chr='\0';
        }
        else{
            break;
        }
    }
    return 0;
}