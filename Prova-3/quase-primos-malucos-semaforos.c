#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>
#include <semaphore.h>

int entrada1, entrada2;
sem_t mutex1, mutex2; 

void *eh_quase_primo()
{	
    int n = entrada1++;
    int count = 0;
    
    if (n % 2 == 0)
        n++;
	
	sem_wait(&mutex1);
	sem_wait(&mutex2);
	
    while (count <= 10)
    {
        int count = 0;
        for (int i = 3, f = floor(sqrt(n)); i < f; i += 2)
            if (n % i == 0 && i < 11)
                break;
            else if (n % i == 0 && i > 10)
                count++;

        if (count >= 10)
            return (void *)n;
        
        n+=2;
        count = 0;
    }
    sem_post(&mutex1);
    sem_post(&mutex2);
}


int main()
{

    int casos_teste;
    void *retorno1, *retorno2;
    scanf("%d", &casos_teste);

    pthread_t t1, t2;

    if (casos_teste % 2 != 0)
    {
        casos_teste--;
        scanf("%d", &entrada1);
        sem_init(&mutex1, 0, 1);
        pthread_create(&t1, NULL, eh_quase_primo, NULL);
        pthread_join(t1, &retorno1);
        printf("%d\n", (int)retorno1);
        sem_destroy(&mutex1);
    }
    while (casos_teste > 0)
    {   
        scanf("%d", &entrada1);
        scanf("%d", &entrada2);
        casos_teste = casos_teste - 2;
        
        sem_init(&mutex1, 0, 2);
        sem_init(&mutex2, 0, 10);  

        pthread_create(&t1, NULL, eh_quase_primo, NULL);
        pthread_create(&t2, NULL, eh_quase_primo, NULL);

        pthread_join(t1, &retorno1);
        printf("%d\n", (int)retorno1);
        pthread_join(t2, &retorno2);
        printf("%d\n", (int)retorno2);
        
        sem_destroy(&mutex1);
        sem_destroy(&mutex2);
    }

    return 0;
}
