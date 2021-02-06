#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t num_threads;
sem_t controll;

int resultado, max, min, x;
int semente_temp, i=0;

typedef struct params{
	int i;
	int n;
}params;

void *thread_func(void* var){
	
	sem_wait(&controll);
	
	params *values = (params *)var;
	int semente_temp = values->n;

	for(int j=1;j<100000;j++)
      	rand_r(&semente_temp);
	if(resultado == rand_r(&semente_temp)%8)
		printf("%d\n", values->n);
        
	sem_post(&controll);
    sem_post(&num_threads);
}

int main(void){

	pthread_t thread[1000000];
	
	sem_init(&num_threads, 0, 2);
    sem_init(&controll, 0, 10);
    
    scanf("%d %d %d", &min, &max, &resultado);
 	
 	params *data = malloc((max-min+1) * sizeof(params));
	for(int i=0; i<(max-min+1);i++){
		data[i].i = i;
		data[i].n = i+min;
	} 	
 	
 	for(int i=0; i<(max-min+1);i++){
	 	sem_wait(&num_threads);
		pthread_create(&thread[i], NULL, thread_func, (void*)&data[i]);
	}
	for(int i=0; i<(max-min+1);i++){
		pthread_join(thread[i], NULL);
	}
	
   return 0;
}












