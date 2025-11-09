#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>
#define BUFFER_SIZE 5
int buffer[BUFFER_SIZE];
int in=0,out=0;

sem_t empty;
sem_t full;
pthread_mutex_t mutex;


void* producer(void* args){
    for(int i=0;i<10;i++){
        int item;
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        buffer[in]=i;
        printf("producer created : %d\n",buffer[in]);
        in=(in+1)%BUFFER_SIZE;

        
        pthread_mutex_unlock(&mutex);
        sem_post(&full);

        sleep(2);
    }

    pthread_exit(NULL);
}

void * consumer(void* args){
    for(int i=0;i<10;i++){
        int item;

        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        item=buffer[out];
        printf("consumer got : %d\n",item);
        out=(out+1)%BUFFER_SIZE;

        
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);

        sleep(3);
    }
    pthread_exit(NULL);
}
int main(){
    pthread_t prod;
    pthread_t con;

    sem_init(&empty,0,BUFFER_SIZE);
    sem_init(&full,0,0);
    pthread_mutex_init(&mutex,NULL);

    pthread_create(&prod,NULL,producer,NULL);
    pthread_create(&con,NULL,consumer,NULL);

    pthread_join(prod,NULL);
    pthread_join(con,NULL);

    sem_destroy(&full);
    sem_destroy(&empty);
    pthread_mutex_destroy(&mutex);
    return 0;
}