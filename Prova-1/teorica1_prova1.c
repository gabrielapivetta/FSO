#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

void trata_SIGTERM(int signum) {
	if (fork()) {
	printf("Meu filho continuara a tradicao da familia!\n");
	signal(SIGTERM, SIG_DFL); /* Reinstala tratador padrao e */
	printf("To vivo\n");
	raise(SIGTERM);           /* levanta SIGTERM para encerrar execucao*/
	printf("To vivãooo!\n");
	}
}

int main() {
	
	signal(SIGTERM, trata_SIGTERM); /* Instala o tratador de sinal */
	while(1)
		pause(); /* Interrompe a execucao e aguarda um sinal */	
return 0;
}
