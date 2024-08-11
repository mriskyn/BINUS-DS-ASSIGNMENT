#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_THREADS 3

sem_t semaphore;
pthread_mutex_t mutex; // Mutex untuk melindungi antrian FIFO
int queue[NUM_THREADS];
int front = 0, rear = 0;

// Fungsi untuk memasukkan ke antrian
void enqueue(int thread_id) {
    pthread_mutex_lock(&mutex);
    queue[rear++] = thread_id;
    pthread_mutex_unlock(&mutex);
}

// Fungsi untuk mengeluarkan dari antrian
int dequeue() {
    pthread_mutex_lock(&mutex);
    int thread_id = queue[front++];
    pthread_mutex_unlock(&mutex);
    return thread_id;
}

void* thread_function(void* arg) {
    int thread_id = *(int*)arg;

    enqueue(thread_id);  // Masukkan thread ke dalam antrian
    printf("Thread %d waiting in queue.\n", thread_id);

    sem_wait(&semaphore);  // Menunggu semaphore

    int queued_thread_id = dequeue(); // Ambil thread dari antrian
    printf("Thread %d got the semaphore (processed).\n", queued_thread_id);
    
    // Simulasi pemrosesan
    sleep(2);
    
    sem_post(&semaphore);  // Lepaskan semaphore
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    sem_init(&semaphore, 0, 1);  // Inisialisasi semaphore dengan nilai 1
    pthread_mutex_init(&mutex, NULL);  // Inisialisasi mutex

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&semaphore);
    pthread_mutex_destroy(&mutex);

    return 0;
}
