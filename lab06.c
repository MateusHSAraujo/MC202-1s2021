#include <stdio.h>
#include <string.h>


char ctrmaisfrequente(char msg[10001], int tam){
    char caracter, caractermaisfrequente='A';
    int ocorrencias=0, ocorrenciasmax=0;
    for (int i=0; i<tam; i++){
        caracter = msg[i];
        if(caracter!= ' '){
            for (int j=0; j<tam; j++){
                if(caracter == msg[j]){
                    ocorrencias+=1;
                }
            }
            if (ocorrencias > ocorrenciasmax){
                caractermaisfrequente = caracter;
                ocorrenciasmax= ocorrencias;
            }
            if (ocorrencias == ocorrenciasmax){
                if (caracter<caractermaisfrequente){
                    caractermaisfrequente= caracter;
                    ocorrenciasmax=ocorrencias;
                }
            }
            ocorrencias=0;
        }
    }
    return caractermaisfrequente;
}


void decodificadora(char msg[10001],int tam,char chave){
    int msgeminteiros[10001];

    for( int i=0; i<tam; i++){
        if(msg[i]!=' '){
            int crteminteiro = msg[i];
            msgeminteiros[i]=crteminteiro;
        }
        if(msg[i] == ' '){
            msgeminteiros[i]= msg[i];
        }

    }

    
    int chaveint=chave;
    int deslocamento = (chaveint-97)+1;
    if(chave != 'a' && chave != 'z'){
        for(int i=0; i<tam; i++){
            if (msgeminteiros[i]!=32){
                if (msgeminteiros[i]<chaveint){
                    if(chaveint<101){
                        msgeminteiros[i]= (msgeminteiros[i]+1)+(122-chaveint);}
                    else{
                        if ((msgeminteiros[i]+(122-chaveint))<chaveint){
                            msgeminteiros[i]=msgeminteiros[i]+(122-chaveint);                            
                        }
                        else{
                            msgeminteiros[i]=msgeminteiros[i]+(122-chaveint)+1;
                        }
                    }   
                }
                else if (msgeminteiros[i]>chaveint && msgeminteiros[i]<(chaveint+deslocamento)){
                    msgeminteiros[i]=(msgeminteiros[i]-deslocamento);
                    
                }
                else if (msgeminteiros[i]>=(chaveint+deslocamento)){
                    msgeminteiros[i]=(msgeminteiros[i]-(deslocamento-1));
                }

            }
        }

    }

    if(chave == 'a'){
        for(int i=0; i<tam;i++){
           if(msgeminteiros[i]!= 32 && msgeminteiros[i] != 'a'){
                if (msgeminteiros[i] == 98){
                   msgeminteiros[i]=122;
                }
                else{
                msgeminteiros[i]-=1;
                }
            }
        }

    }


    if (chave == 'z'){
        for(int i=0; i<tam;i++){
           if(msgeminteiros[i]!= 32 && msgeminteiros[i] != 'z'){
                if (msgeminteiros[i] ==97 ){
                   msgeminteiros[i]=121;
                }
                else{
                msgeminteiros[i]-=1;
                }
            }
        }

    }
    




    char msgdecodificada[10001];
    for(int i=0;i<tam;i++){
        if(msgeminteiros[i]!=32){
            char crtcrt = msgeminteiros[i];
            msgdecodificada[i]= crtcrt;
        }
        if(msgeminteiros[i] == 32){
            msgdecodificada[i]= ' ';
        }
    }

    printf("%s\n",msgdecodificada);
    return ;

}

int main(void){

    char msg[10001];
    char chr, chave;
    int tam;
    int i=0;
    while( scanf("%c",&chr)){
        if(chr == '\n'){
            break;
        }
        msg[i]=chr;
        i++;
    }
    msg[i]='\0';
    tam=strlen(msg);
    chave= ctrmaisfrequente(msg,tam);
    decodificadora(msg,tam,chave);

    return 0;
}