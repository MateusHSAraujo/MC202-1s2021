# include <stdio.h>
int main(void){
int n, n2, n3;
int segundos, minutos, horas, dias;
scanf("%d", &n);
segundos = n%60;
n2 = n/60;
minutos = n2%60;
n3 = n2/60;
horas = n3%24;
dias = n3/24;
printf("%d dia(s), %d hora(s), %d minuto(s) e %d segundo(s).\n", dias, horas, minutos, segundos );
return 0;

}