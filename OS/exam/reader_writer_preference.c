#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t rw_mutex;   // Semaphore untuk writers
sem_t mutex;      // Semaphore untuk readers
int read_count = 0; // Menghitung jumlah pembaca aktif
int data = 0;     // Shared resource

void* reader(void* arg) {
    int reader_id = *(int*)arg;

    while (1) {
        sem_wait(&mutex);  // Masuk ke critical section
        read_count++;
        if (read_count == 1) {
            sem_wait(&rw_mutex);  // Jika ini pembaca pertama, block writers
        }
        sem_post(&mutex);  // Keluar dari critical section

        // Membaca data
        printf("Reader %d is reading data: %d\n", reader_id, data);
        sleep(1);

        sem_wait(&mutex);  // Masuk ke critical section lagi
        read_count--;
        if (read_count == 0) {
            sem_post(&rw_mutex);  // Jika ini pembaca terakhir, unblock writers
        }
        sem_post(&mutex);  // Keluar dari critical section

        sleep(1);  // Delay sebelum pembaca membaca lagi
    }

    return NULL;
}

void* writer(void* arg) {
    int writer_id = *(int*)arg;

    while (1) {
        sem_wait(&rw_mutex);  // Block readers dan writers lain

        // Menulis data
        data++;
        printf("Writer %d is writing data: %d\n", writer_id, data);
        sleep(2);

        sem_post(&rw_mutex);  // Lepaskan block untuk readers dan writers lain

        sleep(2);  // Delay sebelum penulis menulis lagi
    }

    return NULL;
}

int main() {
    pthread_t r1, r2, r3, w1, w2;
    int r_id1 = 1, r_id2 = 2, r_id3 = 3, w_id1 = 1, w_id2 = 2;

    sem_init(&rw_mutex, 0, 1);  // Inisialisasi semaphore untuk writers
    sem_init(&mutex, 0, 1);     // Inisialisasi semaphore untuk readers

    pthread_create(&r1, NULL, reader, &r_id1);
    pthread_create(&r2, NULL, reader, &r_id2);
    pthread_create(&r3, NULL, reader, &r_id3);
    pthread_create(&w1, NULL, writer, &w_id1);
    pthread_create(&w2, NULL, writer, &w_id2);

    pthread_join(r1, NULL);
    pthread_join(r2, NULL);
    pthread_join(r3, NULL);
    pthread_join(w1, NULL);
    pthread_join(w2, NULL);

    sem_destroy(&rw_mutex);
    sem_destroy(&mutex);

    return 0;
}
