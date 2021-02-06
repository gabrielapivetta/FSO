#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

void trata_SIGALRM(int signum) {
  printf("Ai que sono! Queria dormir mais...\n");
}
int main() {

  pid_t pid;
  if ((pid = fork()) != 0) {
    signal(SIGALRM, trata_SIGALRM); /* Instalacao do tratador de sinal */
    pause();  /* Pai espera ser acordado pelo filho */
  }
  else
  kill (getppid(), SIGALRM); /* Filho envia sinal para acordar o pai */
  return 0;
} 
