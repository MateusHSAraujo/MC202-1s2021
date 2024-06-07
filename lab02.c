# include <stdio.h>

int main(void){
    int N;
    scanf("%d\n",&N);
    int n,f;
    int ff;
    char c;
    while(N!=1){
        scanf("(%d,%d,%c) ",&n,&f,&c);
        ff=f;
        printf("%4d |",n);
        while(f!=0){
            printf("%c",c);
            f-=1;
        }
        printf(" %d\n",ff);
        N-=1;
    } 
        scanf(" (%d,%d,%c)",&n,&f,&c);   
        printf("%4d |",n);
        ff=f;
        while(f!=0){
            printf("%c",c);
            f-=1;
        }
        printf(" %d\n",ff);        

    return 0;
}