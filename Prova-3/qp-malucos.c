#include <semaphore.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <stdio.h>

sem_t num_threads;
sem_t controll;

typedef struct Parameter{
    int number;
    int tid; 
    int answer;
} Parameter;

typedef struct thread{
    pthread_t tid;
    int i;
} Thread;

Parameter *Parameters;

Thread threads[10];

int is_crazy_cousin(int number){
     if(number == 1 || number%2 == 0){
        return 0;
    }

    int aux = 0;
    for(int i = 3, f = floor(sqrt(number)); i < f; i+=2){
        if(number%i == 0 && i < 11){
            return 0;
        } else if(number%i == 0 && i > 10){
            aux++;
        }
    }

    if(aux >= 10){
        return 1;
    }
    return 0;
}

void *cousin_get(void *arg){
    sem_wait(&controll);
    int i = ((int)arg);

    while(is_crazy_cousin(Parameters[i].number) == 0){
        Parameters[i].number++;
    }
    Parameters[i].answer = Parameters[i].number;

    sem_post(&controll);
    sem_post(&num_threads);
}

int main(){
    sem_init(&num_threads, 0, 10);
    sem_init(&controll, 0, 2);

    int N, num, aux = 0;
    Parameter *answers;

    scanf("%d", &N);
    Parameters = (Parameter*) malloc(N*sizeof(Parameter));

    for(int i = 0; i < N; i++){
        scanf("%d", &num);

        if(num < 508079){
            Parameters[i].answer = 508079;
        } else {
            Parameters[i].number = num;
            Parameters[i].tid = aux;

    
            sem_wait(&num_threads);
                threads[aux].i = i;
                pthread_create(&threads[aux].tid, NULL, &cousin_get, (void*)&threads[aux].i);
                if(aux == 9){
                    aux = 0;
                } else {
                    aux++;
                }
        }
    }

    for(int i = 0; i < 10; i++){
        pthread_join(threads[i].tid, NULL);
    }

    answers = Parameters;

    for(int i=0; i < N; i++){
        printf("%d\n", answers[i].answer);
    }

    return 0;
}
