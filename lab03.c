#include <stdio.h>
int main(void){
    // Recebe a quantidade de dias e os preços das ações
    int n;
    scanf("%d",&n);
    float acoes[n];
    for ( int i=0; i<n; i++){
        float precos;
        scanf("%f",&precos);
        acoes[i]=precos; //criando o vetor com os valores das ações
    }

    // Recebe a diferença de dias e o dinheiro levado
    int k, q;
    scanf("%d",&k);
    scanf("%d",&q);
    // Avalia o vetor com os valores das ações:
    int diadecompra, diadevenda, qtdcomprada,qtdcompradafinal;
    float valordecompra, valordevenda,lucromaximo=0,lucrototal;
    for(int i = 0; i<n; i++){//seleciona para avaliação o dia de compra
        for(int j = 0; j<=k; j++){//seleciona para avaliação os possíveis dias de venda
            if(j+i<n){//condição que evitar acessar elementos fora do vetor
                float lucrodavenda = acoes[j+i]-acoes[i];
                qtdcomprada= q/acoes[i];
                lucrototal= qtdcomprada*lucrodavenda;
                if(lucrototal > lucromaximo){
                    lucromaximo=lucrototal;
                    diadecompra = i+1;
                    diadevenda = j+i+1;
                    valordecompra= acoes[i];
                    valordevenda= acoes[j+i];
                    qtdcompradafinal= q/valordecompra;
                }
            }
        }
    }
    if(lucromaximo == 0){ //Correção do algoritimo para o pior caso
        diadecompra=1;
        diadevenda=1;
        valordecompra=acoes[0];
        valordevenda=acoes[0];
        qtdcompradafinal=q/acoes[0];
    }
    //Realiza a impressão
    printf("Dia da compra: %d\n",diadecompra);
    printf("Valor de compra: R$ %.2f\n",valordecompra);
    printf("Dia da venda: %d\n",diadevenda);
    printf("Valor de venda: R$ %.2f\n",valordevenda);
    printf("Quantidade de acoes compradas: %d\n",qtdcompradafinal);
    printf("Lucro: R$ %.2f\n",lucromaximo);


    return 0;
}