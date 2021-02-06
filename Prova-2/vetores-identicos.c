#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int *vetor1, *vetor2, tamanho;

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

void* ordena_t1() {
    qsort(vetor1, tamanho, sizeof(int), cmpfunc);
}

void* ordena_t2() {
    qsort(vetor2, tamanho, sizeof(int), cmpfunc);
}

int Compara(int vetor1[],int vetor2[],int tamanho) {
    int i;
	for(i=0;i<tamanho;i++){
		if(vetor1[i]!=vetor2[i])
			return 1;
	}
	return 0;
}

int main(){

    int valor, i;

    scanf("%d", &tamanho);
    vetor1 = (int*)malloc(tamanho * sizeof(int));
    vetor2 = (int*)malloc(tamanho * sizeof(int));
    for (i = 0; i < tamanho; ++i) {
        scanf("%d", &valor);
        vetor1[i] = valor; 
    }
    for (i = 0; i < tamanho; ++i) {
        scanf("%d", &valor);
        vetor2[i] = valor; 
    }

    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, ordena_t1, NULL);
    pthread_create(&thread2, NULL, ordena_t2, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    if(Compara(vetor1, vetor2, tamanho) == 0)
        printf("Mesmos elementos\n");
    else 
        printf("Diferentes\n");

    return 0;
}