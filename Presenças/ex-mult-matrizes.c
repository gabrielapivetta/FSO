// Aluna: Gabriela da Gama Pivetta - 180052845
// Matéria: Fundamentos de Sistemas Operacionais
// Professor: Bruno Ribas
// UnB - FGA

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>

pid_t filho1, filho2, idPai;

#define matriz int
matriz matriz1[2000][2000];
matriz matriz2[2000][2000];
matriz matrizResultado[2000][2000];
int tam_matriz;

void fork_filho2();

void imprimeResultado(int signal){
    
    if(signal == SIGALRM){ //sinal recebido do filho 1
        printf("SIGALRM - sou %d e quem me chamou foi %d\n", getpid(), filho1);
        fork_filho2(); //chama função que cria filho 2
    }
    
    else if(signal == SIGTERM){ //sinal recebido do filho 2
        printf("SIGTERM - sou %d e quem me chamou foi %d\n", getpid(), filho2);
        //sinais recebidos dos dois filhos
        //enviar sinal para o filho 1 imprimir sua parte da matriz
        kill(filho1, SIGPIPE); // manda filho 1 imprimir
        printf("mandei o SIGPIPE pro filho 1\n");
    }
    
    else if(signal == SIGPIPE){ // filho 1 imprime
        printf("SIGPIPE sou %d\n", getpid());
        for (int i = 0; i < tam_matriz; i++){
            if (i > (tam_matriz / 2) - 1)
                break;
            for (int j = 0; j < tam_matriz; j++){
                printf("%d ", matrizResultado[i][j]);
            }
            puts("");
        }
        //avisar o pai que acabou e vai morrer
        kill(idPai, SIGSEGV);
        printf("FILHO 1 - MORRI\n");
        exit(0); // = kill(filho1, SIGKILL)
    }
    
    else if(signal == SIGSEGV){ //filho 1 imprimiu e morreu
        kill(filho2, SIGSYS); // manda filho 2 imprimir
        pause();
    }
    
    else if (signal == SIGSYS){ // filho 2 imprime
        printf("SIGSYS sou %d\n", getpid());
        for (int i = (tam_matriz/2); i < tam_matriz; i++){
            for (int j = 0; j < tam_matriz; j++){
                printf("%d ", matrizResultado[i][j]);
            }
            puts("");
        }
        //avisar o pai que acabou e vai morrer
        kill(idPai, SIGBUS);
        printf("FILHO 2 - MORRI\n");
        exit(0); // = kill(filho2, SIGKILL)
    }
    
    else if(signal == SIGBUS){ //filho 2 imprimiu e morreu
        //pai morre
        printf("SIGBUS - filhos morreram... pai morre\n");
        exit(0);
    }
}


void fork_filho2() {
		filho2 = fork();
        if(filho2==0){ //filho 2 calcula de tam_matriz/2 ate tam_matriz -1
            printf("sou o filho 2 : %d\ne meu pai e : %d\n", getpid(), getppid());
            for (int linha = (tam_matriz/2); linha < tam_matriz; linha++){
                for (int coluna = 0; coluna < tam_matriz; coluna++){
                    for (int var = 0; var < tam_matriz; var++){
                        matrizResultado[linha][coluna] += matriz1[linha][var] * matriz2[var][coluna];
                    }
                }
            }
            //envia o sinal para o pai
            kill(idPai, SIGTERM);
            // recebe sinal do pai para imprimir a matriz
            signal(SIGSYS, imprimeResultado);
            pause();
		}
}

int main(){

    scanf(" %d", &tam_matriz);
    //ler matriz1
    for(int i=0; i<tam_matriz;i++)
        for(int j=0; j<tam_matriz; j++)
            scanf(" %d", &matriz1[i][j]);
    //ler matriz2
    for (int i = 0; i < tam_matriz; i++)
        for (int j = 0; j < tam_matriz; j++)
            scanf(" %d", &matriz2[i][j]);

    idPai = getpid();

    filho1 = fork(); //criar filho 1

    if(filho1==0){ // filho 1 calcula da linha 0 ate a tam_matriz/2 -1
        printf("sou o filho 1 : %d\n e meu pai e : %d\n", getpid(), getppid());
        for (int linha = 0; linha < tam_matriz; linha++){
            if(linha > (tam_matriz/2)-1 )
                break;
            for (int coluna = 0; coluna < tam_matriz; coluna++){
                for (int var = 0; var < tam_matriz; var++){
                    matrizResultado[linha][coluna] += matriz1[linha][var] * matriz2[var][coluna];
                }
            }
        }
        //enviar o sinal para papai
        kill(idPai, SIGALRM);
        // recebe sinal do pai para imprimir a matriz
        signal(SIGPIPE, imprimeResultado);
        pause();

    }//end filho 1


	else{//pai fica aqui
        //printf("sou o pai : %d\n", getpid());
    	signal(SIGALRM, imprimeResultado); //quando filho 1 avisa que terminou a conta
        signal(SIGTERM, imprimeResultado); //quando filho 2 termina a conta
        signal(SIGSEGV, imprimeResultado); //quando filho 1 imprime e morre
        signal(SIGBUS, imprimeResultado); //quando filho 2 imprime e morre
        pause();
        wait(NULL);
    }//end pai

return 0;
}
