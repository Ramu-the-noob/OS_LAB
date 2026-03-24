#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int read_count = 0;
int write_count = 0;

sem_t rmutex;    
sem_t wmutex;    
sem_t read_try;  
sem_t resource;  

void *reader(void *arg) {
    int id = *(int *)arg;

    
    sem_wait(&read_try);   
    sem_wait(&rmutex);     

    read_count++;
    if (read_count == 1) {
        sem_wait(&resource); 
    }

    sem_post(&rmutex);     
    sem_post(&read_try); 

    
    printf("Reader %d is READING\n", id);
    sleep(1);
    printf("Reader %d has FINISHED READING\n", id);

   
    sem_wait(&rmutex);
    read_count--;
    if (read_count == 0) {
        sem_post(&resource); 
    }
    sem_post(&rmutex);     

    return NULL;
}

void *writer(void *arg) {
    int id = *(int *)arg;

   
    sem_wait(&wmutex);    
    write_count++;
    if (write_count == 1) {
        sem_wait(&read_try); 
    }
    sem_post(&wmutex);    

    sem_wait(&resource);   
    
    printf("\tWriter %d is WRITING\n", id);
    sleep(2);
    printf("\tWriter %d has FINISHED WRITING\n", id);

   
    sem_post(&resource);   
    
    sem_wait(&wmutex);     
    write_count--;
    if (write_count == 0) {
        sem_post(&read_try); 
    }
    sem_post(&wmutex);    

    return NULL;
}

int main() {
    pthread_t readers[5], writers[5];
    int id[5];

    
    sem_init(&rmutex, 0, 1);
    sem_init(&wmutex, 0, 1);
    sem_init(&read_try, 0, 1);
    sem_init(&resource, 0, 1);

    
    for (int i = 0; i < 5; i++) {
        id[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &id[i]);
        pthread_create(&writers[i], NULL, writer, &id[i]);
    }

   
    for (int i = 0; i < 5; i++) {
        pthread_join(readers[i], NULL);
        pthread_join(writers[i], NULL);
    }

   
    sem_destroy(&rmutex);
    sem_destroy(&wmutex);
    sem_destroy(&read_try);
    sem_destroy(&resource);

    return 0;
}
