#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t num_threads;
sem_t controll;

int max, min, x, k=0;
int semente=0, semente_temp;
int num, *intervalo;

void* acha_semente(void* intervalo[x]) {

	sem_wait(&controll);
	
	semente_temp = (int)intervalo[x];
	
	for(int j=1;j<10000;j++)
      	rand_r(&semente_temp);
	if(num != rand_r(&semente_temp)%256)
		intervalo[x] = -1;
	else{
		semente = min + x;
		intervalo[x] = semente_temp;
	}
	printf("intervalo em x e x: %d %d\n", intervalo[x], x);
	
	sem_post(&controll);
    sem_post(&num_threads);
}

int main() {
	
	pthread_t thread[1000000];
	
	sem_init(&num_threads, 0, 10);
    sem_init(&controll, 0, 2);
	
	scanf("%d %d", &min, &max);
		
	intervalo = (int*)malloc((max-min+1) * sizeof(int));
	for(int i=0; i<(max-min+1);i++)
		intervalo[i] = min+i;
	
	while(scanf("%d", &num) != EOF){
		for(x=0;x<(max-min+1);x++){
			if(intervalo[x]==-1)
				continue;
				
			sem_wait(&num_threads);
			pthread_create(&thread[k], NULL, acha_semente, (void*)&intervalo[x]);
    	
    	}
    	for(x=0;x<(max-min+1);x++){
			if(intervalo[x]!=-1)
    			pthread_join(thread[k], NULL);
    	}
    	k++;
	}
	
	printf("%d\n", semente);
	
return 0;
}


//void *intervalo[x]
//(void*)intervalo[x]
