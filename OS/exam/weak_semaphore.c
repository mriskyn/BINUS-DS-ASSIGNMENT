#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_THREADS 3

sem_t semaphore;

void* thread_function(void* arg) {
    int thread_id = *(int*)arg;

    printf("Thread %d waiting for semaphore.\n", thread_id);

    sem_wait(&semaphore);  // Menunggu semaphore

    printf("Thread %d got the semaphore (processed).\n", thread_id);
    
    // Simulasi pemrosesan
    sleep(2);
    
    sem_post(&semaphore);  // Lepaskan semaphore
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    sem_init(&semaphore, 0, 1);  // Inisialisasi semaphore dengan nilai 1

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&semaphore);

    return 0;
}
