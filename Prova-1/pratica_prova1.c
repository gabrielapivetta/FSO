#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>

int cont=0;

void trata_SIGUSR1(int signum){
    printf("Recebi %d\n", signum);
    if(cont==3){
        cont = 4;
        printf("Tchau\n");
        exit(0);
    }
    else{
        cont =0;
    }
}
void trata_SIGUSR2(int signum){
    if(cont==1)
        cont = 2;
    else
        cont = 0;
    printf("Recebi %d\n", signum);
}
void trata_SIGTERM(int signum){
    printf("Recebi %d\n", signum);
    if(cont==2){
        cont =3;
        printf("Senha acionada\n");
    }
    else
        cont =0;
}
void trata_SIGINT(int signum){
    printf("Recebi %d\n", signum);
    cont= 1;
}

int main(void){
    
    signal(SIGUSR1, trata_SIGUSR1);
    signal(SIGUSR2, trata_SIGUSR2);
    signal(SIGTERM, trata_SIGTERM);
    signal(SIGINT, trata_SIGINT);
    while(1)
        pause;

return 0;
}
