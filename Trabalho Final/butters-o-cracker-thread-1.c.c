#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int max, min;
int semente=0;

typedef struct params{
	int i;
	int n;
	int v;
}params;

void *acha_semente(void* var) {
	
	params *values = (params *)var;
	int semente_temp = values->n;

	
	for(int j=1;j<10000;j++)
      	rand_r(&semente_temp);
	if(values->v != rand_r(&semente_temp)%256)
		values->n = -1;
	else{
		semente = min + values->i;
		values->n = semente_temp;
	}
	
}

int main() {
	
	pthread_t thread[1000000];
	
    int num;
	
	scanf("%d %d", &min, &max);
		
	params *data = malloc((max-min+1) * sizeof(params));
	/*for(int i=0; i<(max-min+1);i++){
		data[i].i = i;
		data[i].n = i+min;
	}*/
	
	while(scanf("%d", &num) != EOF){
		for(int i=0;i<(max-min+1);i++){
			data[i].i = i;
			data[i].n = i+min;
			data[i].v = num;
			if(data[i].n==-1)
				continue;
			
			pthread_create(&thread[i], NULL, acha_semente, (void*)&data[i]);
    	
    	}
    	for(int i=0;i<(max-min+1);i++){
			if(data[i].n!=-1)
    			pthread_join(thread[i], NULL);
    	}
	}
	
	printf("%d\n", semente);
	
return 0;
}

