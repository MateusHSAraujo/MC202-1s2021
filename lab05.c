#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int verificafim(char str[21]){ //Verifica se a string dada é fim
    if(str[0]=='f' && str[1]=='i' && str[2]=='m' && str[3]=='\0'){
        return 1;
    }
    else{
        return 0;
    }
}

int tamanhomaiorqueoito(char str[21]){//Verifica se a string tem mais que oito caracteres, retorna 1 se sim
    if(strlen(str)>=8){
        return 1;
    }
    else{
        return 0;
    }

}

int temvogal(char str[21]){//Verifica se a string tem vogal, retorna 1 se sim
    int tam=strlen(str);
    char chr;
    for(int i=0;i<tam;i++){
        chr=str[i];
        if(chr =='a' || chr=='e' || chr=='i' || chr=='o'|| chr=='u' || chr =='A' || chr=='E' || chr=='I' || chr=='O'|| chr=='U'){
            return 1;
        }
    }
    return 0;
}

int temdigito(char str[21]){ // Verifica se a função tem ao menos 1 dígito, retorna 1 se sim
    int tam=strlen(str);
    char chr;
    for(int i=0;i<tam;i++){
        chr=str[i];
        if(chr>='0' && chr<='9'){
            return 1;
        }
    }
    return 0;
}

int temmascminsc(char str[21]){ // Verifica se a função tem ao menos uma letra maíuscula e uma minúscula, retorna 1 se sim
    int tam=strlen(str);
    int condicao1=0, condicao2=0;
    char chr;
    for(int i=0; i<tam;i++){
        chr = str[i];
        if(chr>='a' && chr<='z'){
            condicao1=1;
        }
        if(chr>='A' && chr<='Z'){
            condicao2=1;
        }
        if(condicao1==1 && condicao2==1){
            return 1;
        }
    }
    return 0;

}

int naotemtresvogconsec(char str[21]){ // Verifica se existem três vogais consecutivas, se sim retorna 0, se não retorna 1
    int tam=strlen(str);
    char c1,c2,c3;
    for(int i =0;i<tam-2;i++){
        c1=str[i];
        c2=str[i+1];
        c3=str[i+2];
        if(c1 =='a' || c1=='e' || c1=='i' || c1=='o'|| c1=='u' || c1 =='A' || c1=='E' || c1=='I' || c1=='O'|| c1=='U'){
            if(c2 =='a' || c2=='e' || c2=='i' || c2=='o'|| c2=='u'|| c2 =='A' || c2=='E' || c2=='I' || c2=='O'|| c2=='U'){
                if(c3 =='a' || c3=='e' || c3=='i' || c3=='o'|| c3=='u' || c3 =='A' || c3=='E' || c3=='I' || c3=='O'|| c3=='U'){
                    return 0;
                }
            }
        }
    }
    return 1;

}

int temtresconsoantesseguidas(char str[21]){ // Verifica se tem ao menos três consoantes seguidas, se sim retorna 1
    int tam=strlen(str);
    char c1,c2,c3;
    for(int i =0;i<tam-2;i++){
        c1=str[i];
        c2=str[i+1];
        c3=str[i+2];
        if(c1 !='a' && c1!='e' && c1!='i' && c1!='o'&& c1!='u' && c1 !='A' && c1!='E' && c1!='I' && c1!='O'&& c1!='U' && (c1<'0' || c1>'9')){
            if(c2 !='a' && c2!='e' && c2!='i' && c2!='o'&& c2!='u' && c2 !='A' && c2!='E' && c2!='I' && c2!='O'&& c2!='U' && (c2<'0' || c2>'9')){
                if(c3 !='a' && c3!='e' && c3!='i' && c3!='o'&& c3!='u' && c3 !='A' && c3!='E' && c3!='I' && c3!='O'&& c3!='U' && (c3<'0' || c3>'9')){
                    return 1;
                }
            }
        }
    }
    return 0;

}

int main(void){
    char senha[21];
    int nfim= 1;
    while(nfim==1){
        scanf("%s",senha);
        if(verificafim(senha)==1){ // para a repetição ao chegar na palavra fim
            break;
        }
        if(tamanhomaiorqueoito(senha)==1 && temvogal(senha)==1 && temdigito(senha)==1 && temmascminsc(senha)==1 && naotemtresvogconsec(senha)==1 && temtresconsoantesseguidas(senha)==1){
            printf("[%s] e' aceitavel.\n",senha);
        }
        else{
            printf("[%s] e' inaceitavel.\n",senha);
        }
    }

    return 0;
}