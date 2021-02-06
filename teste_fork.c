#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
	
	pid_t p = fork();
	if(p>0){
		printf("Meu filho é %d\n", p);
		sleep(30);
	}
	
	else if(p==0){
		printf("Eu sou o filho\n");
		sleep(10);
	}
	
	else if(p<0){
		printf("Fork não funcionou\n");
	}

return 0;
}
