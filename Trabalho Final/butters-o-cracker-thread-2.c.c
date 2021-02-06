#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_t thread;

int end=1, indice=0, max, min;
int semente, nums_gerados[10000000];

int loop(){
    if (scanf(" %d", &nums_gerados[indice]) != 1)
	    return 0;
	indice++;
}

void *calcula_semente(){
	
    for (int i = min; i <= max; i++){
        int semente_temp = i;
        int aux = 1;

        for (int x = 0; x < indice; x++){
            for (int j = 1; j < 10000; j++)
                rand_r(&semente_temp);
            if (rand_r(&semente_temp) % 256 != nums_gerados[x]){
                aux = 0;
                break;
            }
        }
        
        if (aux == 1)
            semente = i;
    }
}

int main(void){

    scanf("%d %d", &min, &max);

    while (end)
    	end = loop();        

    pthread_create(&thread, NULL, calcula_semente, NULL);
    pthread_join(thread, NULL);
    printf("%d\n", semente);

    return 0;
}
