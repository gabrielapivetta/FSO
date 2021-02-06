#include <stdio.h>

int main(){

	int num_comandos, click, contador=0;
	scanf("%d", &num_comandos);
	for(int i=0;i<num_comandos;i++){
		scanf("%d", &click);
		contador = click + i + contador;
	}
	printf("%d\n", contador);


return 0;
}
