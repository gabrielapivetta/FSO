#include <stdio.h>
#include <stdlib.h>

int main(){

	int num_comandos, *click, contador=0;
	
	while(scanf("%d", &num_comandos)!=0){
	
		click = malloc(num_comandos * sizeof(int));
	
		for(int i=0;i<num_comandos;i++)	
			scanf("%d", &click[i]);
	
		for(int i=0;i<num_comandos;i++){
	
			click = realloc(click, (num_comandos+1) * sizeof(int));
			click[num_comandos+i] = click[i];
			
			for(int j=num_comandos+i-1;j>num_comandos;j--){
				if(click[i]==click[j])
					contador = contador + (num_comandos-j);
				else
					contador = click[i] + i + contador;
				
			}
		}
	
		free(click);
		printf("%d\n", contador);
	}


return 0;
}
