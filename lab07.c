#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct data{
    int dia;
    int mes;
    int ano;
};


struct cadastro
{
    char nome[51];
    char endereco[101];
    char telefone[13];
    struct data aniversario;
    int ativo;
};

void insercao(struct cadastro contatos[1000]){
    // quero encontrar o primeiro contato não preenchido, se não tiver, quer dizer que a lista está cheia
    static int primeiraexec=0;  
    int temespaco = 0, pos=0;
    char nome[51], endereco[101],telefone[13],chr;
    int dia,mes,ano;
    for(int i = 0; i<1000 && temespaco == 0; i++){
        if (contatos[i].ativo==0){
            pos=i;
            temespaco = 1;
            break;
        }
    }
    if (temespaco == 0){ // no caso da iteração não encontrar espaços para inserção de contatos
        printf("\nO contato nao foi inserido.\n");
        for(int lext=0;lext<4;lext++){ //Comendo as linhas extras que foram inseridas mesmo o contato não sendo aceito
            while(scanf("%c",&chr)){
                if(chr == '\n'){
                    break;
                }
            }   
        }
        scanf("\n");
    }
    else{
        int i=0,j=0,k=0;
        while( scanf("%c",&chr)){
            if(chr == '\n'){
                break;
            }
            nome[i]=chr;
            i++;
        }
        nome[i]='\0';
        while( scanf("%c",&chr)){
            if(chr == '\n'){
                break;
            }
            endereco[j]=chr;
            j++;
        }
        endereco[j]='\0';
        while( scanf("%c",&chr)){ // telefone está em forma de string por que sou uma anta e não consigo mexer com long
            if(chr == '\n'){
                break;
            }
            telefone[k]=chr;
            k++;
        }
        telefone[k]='\0';
        
        scanf("%d/%d/%d\n",&dia,&mes,&ano);
        strcpy(contatos[pos].nome,nome);
        strcpy(contatos[pos].endereco,endereco);
        strcpy(contatos[pos].telefone,telefone);
        contatos[pos].aniversario.dia=dia;
        contatos[pos].aniversario.mes=mes;
        contatos[pos].aniversario.ano=ano;
        if(primeiraexec==0){
            printf("Contato para %s inserido.\n",nome);
            contatos[pos].ativo = 1;
            primeiraexec=1;
        }
        else{
            contatos[pos].ativo = 1;
            printf("\nContato para %s inserido.\n",nome);
        }
        
    }
    return;
}

void remocao(struct cadastro contatos[1000]){
    char nomealvo[51],chr;
    int i = 0,contador=0;
    while( scanf("%c",&chr)){ // Recebe o nome que se deseja retirar
        if(chr == '\n'){
            break;
        }
        nomealvo[i]=chr;
        i++;
    }
    nomealvo[i]='\0';

    for(int k=0; k-contador<1000 && k-contador>=0 &&contatos[k-contador].ativo == 1;k++){
        if(strcmp(nomealvo,contatos[k-contador].nome) == 0){
            for(int l=k-contador+1; l<=1000 ;l++){ // l é a primeira posição dempois do termo removido
                if(l==1000){
                    contatos[l-1].ativo=0;
                } 
                else{
                    if( contatos[l].ativo == 1){
                        contatos[l-1]=contatos[l]; // duplica o cadastro posterior a k e faz isso para todos os cadastros ativos  a direita de k

                    }
                    else{
                        contatos[l-1].ativo = 0;
                        break;
                }
                }
            }
            contador+=1;// no caso dos nomes serem iguias, uma variável acumuladora guarda a contagem . Ela precisa estar aqui pra não atrapalhar a iteração logo acima
        }
    }


    printf("\nContatos de %s removidos: %d.\n",nomealvo,contador);
    return;
}

void impressao(struct cadastro contatos[1000]){ //imprime o contato cadastrado em ordem e seguindo uma formatação
    int contador =0,temcontato=0;
    printf("\nListagem:\n");
    for(int i=0; i<1000 && contatos[i].ativo==1;i++){
        contador+=1;
        temcontato=1;
        printf("(%d) %s\t%s\t%s\t%.2d/%.2d/%.2d\n",contador,contatos[i].nome,contatos[i].endereco,contatos[i].telefone,contatos[i].aniversario.dia,contatos[i].aniversario.mes,contatos[i].aniversario.ano);
        
    }
    if(temcontato==0){
        printf("Nenhum contato.\n");
    }
    return;
}

int strcontemstr(char str[51],char chave[51]){ // Essa função analisa se a string str contém uma string chave em sua composição...
    int lenstr=strlen(str),lenchave=strlen(chave); //retorna 1 se a string contem a chave e 0 se não
    int igualdade=0;
    
    for(int i=0;i<=lenstr-lenchave;i++){
        if(str[i]==chave[0]){
            int desloc=1;
            for(int j=1;j<lenchave;j++){
                
                if(str[i+desloc]!=chave[j]){
                    break;
                }
                else{
                    desloc+=1;
                    if(j==lenchave-1){
                        igualdade=1;
                    }
                }
            }
            if(igualdade==1){
                return 1; 
            }
        }
    }
    return 0;
}

void busca(struct cadastro contatos[1000]){
    
    char nomebusca[51],chr;
    int w=0, temcontato=0;
    while( scanf("%c",&chr)){ // Recebe o nome que se deseja buscar
        if(chr == '\n'){
            break;
        }
        nomebusca[w]=chr;
        w++;
    }
    nomebusca[w]='\0';
    printf("\nResultado da busca:\n");
    for(int i=0; i<1000 && contatos[i].ativo==1;i++){
        if (strcontemstr(contatos[i].nome,nomebusca)==1){
            temcontato=1;
            printf("(%d) %s\t%s\t%s\t%.2d/%.2d/%.2d\n",(i+1),contatos[i].nome,contatos[i].endereco,contatos[i].telefone,contatos[i].aniversario.dia,contatos[i].aniversario.mes,contatos[i].aniversario.ano);   
        }
    }
    if(temcontato==0){
        printf("Nenhum contato.\n");

    }
    
    return;
}


int identificaoperacao(char c,struct cadastro contatos[1000]){
    scanf("\n");
    if (c == 'i'){
        insercao(contatos);
        return 1;
    }
    if (c == 'r'){
        remocao(contatos);
        return 1;
    }
    if (c == 'b'){
        busca(contatos);
        return 1;
    }
    if (c == 'p'){
        impressao(contatos);
        return 1;
    }
    if (c == 'f'){

        return 0;
    }
    return 0;
}



int main(void){
    struct cadastro contatos[1000];
    for(int i=0; i<1000;i++){
        contatos[i].ativo = 0;
    }
    while(identificaoperacao(getchar(),contatos) == 1){
    }
    printf("\n");
    return 0;
}
  