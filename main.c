#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <windows.h>
int patessri[] = {0,0,0,0,0};
sem_t full ;
sem_t empty ;
sem_t mu;
sem_t sem;





int size(){
    int i;
    int som = 0;
    for(i = 0; i<5; i++){
       som = som + patessri[i];
    }
    return som;
}

void* prod(void *args)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    int Id = *(int*) args;
    int i;
    sem_wait(&full);
	sem_wait(&mu);
    


        for(i = 0; i<5; i++){
            if(patessri[i] == 0){
               patessri[i] = 1;
               break;
            }

    }
    SetConsoleTextAttribute(h, 3);
    printf("prod %d : space occupied : %d\n ",Id, size());
    
    sem_post(&mu);
     sem_post(&empty);
}

void* cons(void *args)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    int Id = *(int*) args;
    int i;
    sem_wait(&empty);
    sem_wait(&mu);
    

        for(i = 0; i<5; i++){
            if(patessri[i] == 1){
               patessri[i] = 0;
               break;
            }

    }
    SetConsoleTextAttribute(h, 6);
    printf("cons %d : space occupied : %d\n",Id, size());
    sem_post(&mu);
    sem_post(&full);
}



int main()
{


    sem_init(&full, 0,5);
    sem_init(&empty, 0,0);
    pthread_t prodTab[100];
    pthread_t consTab[100];
    sem_init(&mu, 0, 1);
    int i;

    for(i = 0; i< 100; i++){
        int *a = malloc(sizeof(int));
        *a = i + 1;
        pthread_create(&prodTab[i], NULL, prod,a);
    }
    for(i = 0; i< 100; i++){
        int *a = malloc(sizeof(int));
        *a = i + 1;
        pthread_create(&consTab[i], NULL, cons,a);
    }
    for(i = 0; i< 100; i++){
        pthread_join(prodTab[i], NULL);
    }

    for(i = 0; i< 100; i++){
        pthread_join(consTab[i], NULL);
    }
    return 0;
}
