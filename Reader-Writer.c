#include "stdio.h"
#include "semaphore.h"
#include "unistd.h"
#include "pthread.h"

int readCount = 0;
int writeCount = 0;

sem_t reader;
sem_t writer;
sem_t resource;
sem_t readTry;

void read(*args){
    int id = *(int*)args;
    
    sem_wait(readTry);
    sem_wait(reader);
    
    readCount++;
    if(readCount == 1){
        sem_wait(resource);
    }
    
    sem_post(reader);
    sem_post(readTry);
    
    printf("reading\n");
    sleep(1);
    printf("stopped reading \n");
    
    sem_wait(reader);
    readCount--;
    
    if(readCount == 0){
        sem_post(resource);
    }
    
    sem_post(reader);
}
void write(*args){
    int id = *(int*)args;
    
    sem_wait(writer);
    
    writeCount++;
    if(writeCount == 1){
        sem_wait(resource);
    }
    
    sem_post(writer);
    
    printf("writing");
    sleep(2);
    printf("stopped writing");
    
    sem_wait(writer);
    writeCount--;
    
    if(writeCount == 0){
        sem_post(resource);
    }
    
    sem_post(writer);
    
}
int main(){
    
    pthread readers[5], writers[5];
    int id[5];
    
    sem_init(reader,0,1);
    sem_init(writer,0,1);
    sem_init(read_try,0,1);
    sem_init(resource,0,1);
    
    for(int i = 0; i < 5; i++){
        id[i] = i+1
        pthread_create(&readers[i], nullptr, reader, &id[i]);
        pthread_create(&writers[i], nullptr, writer, &id[i]);
    }
    for(int i = 0; i < 5; i++){
        pthread_join(readers[5], nullptr);
        pthread_join(writers[5], nullptr);
    }
    
    return 0;
}
//learnt
