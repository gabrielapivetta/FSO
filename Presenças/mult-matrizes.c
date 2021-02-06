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
    
    if(signal == SIGALRM){
        fork_filho2();
    }
    
    else if(signal == SIGTERM){
        kill(filho1, SIGPIPE);
    }
    
    else if(signal == SIGPIPE){ 
        for (int i = 0; i < tam_matriz; i++){
            if (i > (tam_matriz / 2) - 1)
                break;
            for (int j = 0; j < tam_matriz; j++){
                printf("%d ", matrizResultado[i][j]);
            }
            puts("");
        }
        kill(idPai, SIGSEGV);
        exit(0);
    }
    
    else if(signal == SIGSEGV){ 
        kill(filho2, SIGSYS);
        pause();
    }
    
    else if (signal == SIGSYS){ 
        for (int i = (tam_matriz/2); i < tam_matriz; i++){
            for (int j = 0; j < tam_matriz; j++){
                printf("%d ", matrizResultado[i][j]);
            }
            puts("");
        }
        kill(idPai, SIGBUS);
        exit(0);
    }
    
    else if(signal == SIGBUS)
        exit(0);
}


void fork_filho2() {
		filho2 = fork();
        if(filho2==0){ 
            for (int linha = (tam_matriz/2); linha < tam_matriz; linha++){
                for (int coluna = 0; coluna < tam_matriz; coluna++){
                    for (int var = 0; var < tam_matriz; var++){
                        matrizResultado[linha][coluna] += matriz1[linha][var] * matriz2[var][coluna];
                    }
                }
            }
            kill(idPai, SIGTERM);
            signal(SIGSYS, imprimeResultado);
            pause();
		}
}

int main(){

	idPai = getpid();

    scanf(" %d", &tam_matriz);
  
    for(int i=0; i<tam_matriz;i++)
        for(int j=0; j<tam_matriz; j++)
            scanf(" %d", &matriz1[i][j]);

    for (int i = 0; i < tam_matriz; i++)
        for (int j = 0; j < tam_matriz; j++)
            scanf(" %d", &matriz2[i][j]);

    filho1 = fork();

    if(filho1==0){
        for (int linha = 0; linha < tam_matriz; linha++){
            if(linha > (tam_matriz/2)-1 )
                break;
            for (int coluna = 0; coluna < tam_matriz; coluna++){
                for (int var = 0; var < tam_matriz; var++){
                    matrizResultado[linha][coluna] += matriz1[linha][var] * matriz2[var][coluna];
                }
            }
        }
        kill(idPai, SIGALRM);
        signal(SIGPIPE, imprimeResultado);
        pause();
    }

	else{
    	signal(SIGALRM, imprimeResultado);
        signal(SIGTERM, imprimeResultado); 
        signal(SIGSEGV, imprimeResultado); 
        signal(SIGBUS, imprimeResultado);
        pause();
        wait(NULL);
    }

return 0;
}
