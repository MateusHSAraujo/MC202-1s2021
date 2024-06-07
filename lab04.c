#include <stdio.h>

int main(void){
    
    int n, m, r, s;
    scanf("%d ",&n);
    scanf("%d ",&m);
    scanf("%d ",&r);
    scanf("%d",&s);
    
    int A[n][m];
    for (int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            scanf("%d",&A[i][j]);
        }
    }
    int somasubinicial=0,somasubmax=0,spc=0,ssc=0,sca=0,somanovasub=0;
    for(int i=0; i<=n-r; i++){
        somasubinicial=0;
        spc=0;
        ssc=0; //reset das variaveis acumuladoras
        sca=0;

        for(int j=0; j<m && j<m-s+1; j++){
            sca=0;
            if (j==0){
                for(int k=0;k<r && i+k<n ;k++){ //Constroi a primeira submatriz da linha
                    for(int l=0;l<s && j+l<m;l++){
                        somasubinicial+=A[i+k][j+l];
                    }
                    spc+=A[i+k][0]; //Anota o valor da soma da primeira coluna da submatriz
                    if(s!=1){
                        ssc+=A[i+k][1]; //Anota o valor da soma da segunda coluna da submatriz, caso ela exista
                    }
                }
                if(somasubinicial>somasubmax){
                    somasubmax=somasubinicial;
                }
            }
            else{
                if (j+s-1<m){
                        for(int k=0;k<r && k+i<n ;k++){ //Faz a soma dos valores da linha a ser adicionada
                            sca+=A[i+k][j+s-1];
                        }
                    somanovasub= somasubinicial - spc + sca; // A submatriz nova será a submatriz anterior - a primeira linha + a linha adicionada
                    if(somanovasub>somasubmax){
                        somasubmax=somanovasub;
                    }
                    somasubinicial=somanovasub;
                    if(s==1){
                        spc=sca;
                    }
                    else{
                        spc=ssc;
                        ssc=0;
                        if(j+1<m){
                            for(int k=0;k<r && k+i<n ;k++){//Constroi a soma da nova segunda coluna
                                ssc+=A[i+k][j+1];
                            }  
                        }
                    }
                }
            }
        }
           
    }


    
    
    printf("%d\n",somasubmax);
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    return 0;
}