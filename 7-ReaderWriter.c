#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>

int data=0;
int readCount=0;

pthread_mutex_t mutex;
pthread_mutex_t wrt;

void* readerFun(void* args){
    int id=*((int*)args);
    while(1){
        pthread_mutex_lock(&mutex);
        readCount++;
        if(readCount==1){
            pthread_mutex_lock(&wrt);
        }
        pthread_mutex_unlock(&mutex);

        printf("reader %d read %d \n",id,data);

        pthread_mutex_lock(&mutex);
        readCount--;
        if(readCount==0){
            pthread_mutex_unlock(&wrt);
        }
        pthread_mutex_unlock(&mutex);

        sleep(rand()%3);
    }
    pthread_exit(NULL);
}
void* writerFun(void* args){
    int id=*((int*)args);
    while(1){
        pthread_mutex_lock(&wrt);

        data++;
        printf("writer %d produced %d\n",id,data);

        pthread_mutex_unlock(&wrt);

        sleep(rand()%3);
    }
    pthread_exit(NULL);
}
int main(){
    pthread_mutex_init(&wrt,NULL);
    pthread_mutex_init(&mutex,NULL);

    pthread_t writer[2];
    pthread_t reader[3];
    int writerid[2];
    int readerid[3];

    for(int i=0;i<2;i++){
        writerid[i]=i;
        pthread_create(&writer[i],NULL,writerFun,&writerid[i]);
    }
    for(int i=0;i<3;i++){
        readerid[i]=i;
        pthread_create(&reader[i],NULL,readerFun,&readerid[i]);
    }

    for(int i=0;i<2;i++){
        pthread_join(writer[i],NULL);
    }
    for(int i=0;i<5;i++){
        pthread_join(reader[i],NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&wrt);
    return 0;
}