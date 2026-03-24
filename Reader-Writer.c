#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int read_count = 0;
int write_count = 0;

sem_t rmutex;    // Protects the read_count variable
sem_t wmutex;    // Protects the write_count variable
sem_t read_try;  // Used by writers to block new readers
sem_t resource;  // Provides exclusive access to the shared resource

void *reader(void *arg) {
    int id = *(int *)arg;

    // --- Entry Section ---
    sem_wait(&read_try);   // Check if a writer is waiting. If so, block here.
    sem_wait(&rmutex);     // Lock the read_count

    read_count++;
    if (read_count == 1) {
        sem_wait(&resource); // First reader locks the resource from writers
    }

    sem_post(&rmutex);     // Unlock read_count
    sem_post(&read_try);   // Release read_try so other readers can try to enter

    // --- Critical Section (Reading) ---
    printf("Reader %d is READING\n", id);
    sleep(1);
    printf("Reader %d has FINISHED READING\n", id);

    // --- Exit Section ---
    sem_wait(&rmutex);     // Lock read_count
    read_count--;
    if (read_count == 0) {
        sem_post(&resource); // Last reader unlocks the resource, letting writers in
    }
    sem_post(&rmutex);     // Unlock read_count

    return NULL;
}

void *writer(void *arg) {
    int id = *(int *)arg;

    // --- Entry Section ---
    sem_wait(&wmutex);     // Lock write_count
    write_count++;
    if (write_count == 1) {
        sem_wait(&read_try); // First writer drops the gate, blocking all NEW readers
    }
    sem_post(&wmutex);     // Unlock write_count

    sem_wait(&resource);   // Wait for any currently active readers to finish

    // --- Critical Section (Writing) ---
    printf("\tWriter %d is WRITING\n", id);
    sleep(2);
    printf("\tWriter %d has FINISHED WRITING\n", id);

    // --- Exit Section ---
    sem_post(&resource);   // Release exclusive access to the resource

    sem_wait(&wmutex);     // Lock write_count
    write_count--;
    if (write_count == 0) {
        sem_post(&read_try); // Last writer lifts the gate, allowing waiting readers in
    }
    sem_post(&wmutex);     // Unlock write_count

    return NULL;
}

int main() {
    pthread_t readers[5], writers[5];
    int id[5];

    // Initialize all semaphores to 1 (unlocked)
    sem_init(&rmutex, 0, 1);
    sem_init(&wmutex, 0, 1);
    sem_init(&read_try, 0, 1);
    sem_init(&resource, 0, 1);

    // Create threads
    for (int i = 0; i < 5; i++) {
        id[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &id[i]);
        pthread_create(&writers[i], NULL, writer, &id[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < 5; i++) {
        pthread_join(readers[i], NULL);
        pthread_join(writers[i], NULL);
    }

    // Clean up
    sem_destroy(&rmutex);
    sem_destroy(&wmutex);
    sem_destroy(&read_try);
    sem_destroy(&resource);

    return 0;
}
