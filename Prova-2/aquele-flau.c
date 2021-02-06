#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

char nomes[10];
char igor[] = "Igor3k";
char monark[] = "Monark";
char con1[] = "Con1";
char con2[] = "Con2";
char camera[] = "Silencio";

void Trata_igor(){
    if(scanf("%s", nomes) != EOF){
        if(strcmp(nomes, igor) == 0)
            printf("Certo\n");
        else{
            printf("Erro\n");
        }
    }
    else
        exit(0);
}

void Trata_monark(){
    if(scanf("%s", nomes) != EOF){
        if(strcmp(nomes, monark) == 0)
            printf("Certo\n");
        else{
            printf("Erro\n");
        }
    }
    else
        exit(0);
}

void Trata_con1(){
    if(scanf("%s", nomes) != EOF){
        if(strcmp(nomes, con1) == 0)
            printf("Certo\n");
        else{
            printf("Erro\n");
        }
    }
    else
        exit(0);
}

void Trata_con2(){
    if(scanf("%s", nomes) != EOF){
        if(strcmp(nomes, con2) == 0)
            printf("Certo\n");
        else{
            printf("Erro\n");
        }
    }
    else
        exit(0);
}

void Trata_camera(){
    if(scanf("%s", nomes) != EOF){
        if(strcmp(nomes, camera) == 0)
            printf("Certo\n");
        else{
            printf("Erro\n");
        }
    }
    else
        exit(0);
}

int main() {

    signal(SIGUSR1, Trata_igor);
    signal(SIGUSR2, Trata_monark);
    signal(SIGINT, Trata_con1);
    signal(SIGTERM, Trata_con2);
    signal(SIGALRM, Trata_camera);
    while(1){
        pause();
    }
    return 0;
}
