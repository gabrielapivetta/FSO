#include <stdio.h>
#include <stdlib.h>

int main() {
	
	int tamanho_lista, tamanho_quadro, valor, j=0, i=0, x=0, pf=0, anomalia=0;
	int *vetor, *quadros, vetorzao_quadros[1000000], vetorzao_pf[1000000], mais_antigo=0;
	
	//Le tam lista
	scanf("%d", &tamanho_lista);
	//Le lista
    vetor = (int*)malloc(tamanho_lista * sizeof(int));
    for (i = 0; i < tamanho_lista; ++i) {
        scanf("%d", &valor);
        vetor[i] = valor; 
    }
    
 	//Le tamanho quadros
    while(scanf("%d", &tamanho_quadro)!=EOF){
		quadros = (int*)malloc(tamanho_quadro * sizeof(int));
		for (i = 0; i < tamanho_quadro; ++i)
			quadros[i] = 0;
		j=0;
		pf=0;
		mais_antigo=0;
		for (i=0; i<tamanho_lista; i++){
			for(j=0; j<tamanho_quadro; j++){
				
				if(vetor[i]==quadros[j]){
					break;
				}	
				if(j==tamanho_quadro-1 && vetor[i]!=quadros[j]){
					pf++;
					quadros[mais_antigo]=vetor[i];
					if(mais_antigo==(tamanho_quadro-1))
						mais_antigo=0;
					else
						mais_antigo++;
				}
			}
		}
		vetorzao_quadros[x] = tamanho_quadro;
		vetorzao_pf[x] = pf;
		x++;
    }
    
    //Checa anomalia de Belady
    for (i=0; i<x; i++){
    	for(j=0; j<x; j++){
    		if(vetorzao_quadros[i]>vetorzao_quadros[j] && vetorzao_pf[i]>vetorzao_pf[j])
    			anomalia = 1;   	
    	}
    	printf("%d %d\n", vetorzao_quadros[i], vetorzao_pf[i]); 
    }
    
    if(anomalia==1)
    	printf("Belady detectado\n");
    else
    	printf("Sem anomalia\n");
    	
    	    
	return 0;
}




