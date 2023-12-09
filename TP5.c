#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define N 10

// Declarations of semaphores
sem_t mutex;
sem_t full;
sem_t empty;

// Declarations of the shared data structure
struct data {
  int value;
};

struct data buffer[N];
int head = 0;
int tail = 0;

// Producer function
void *producer(void *arg) {
  int i;

  for (i = 0; i < 100; i++) {
    // Wait if the buffer is full
    sem_wait(&empty);

    // Exclusive access to the buffer
    sem_wait(&mutex);

    // Add the element to the buffer
    buffer[tail].value = i;
    tail = (tail + 1) % N;

    // Release the buffer
    sem_post(&mutex);
    sem_post(&full);
  }

  return NULL;
}

// Consumer function
void *consumer(void *arg) {
  int i;

  for (i = 0; i < 100; i++) {
    // Wait if the buffer is empty
    sem_wait(&full);

    // Exclusive access to the buffer
    sem_wait(&mutex);

    // Read the element from the buffer
    int value = buffer[head].value;
    head = (head + 1) % N;

    // Release the buffer
    sem_post(&mutex);
    sem_post(&empty);

    // Print the value read
    printf("Value read: %d\n", value);
  }

  return NULL;
}

int main(int argc, char *argv[]) {
  // Initialize semaphores
  sem_init(&mutex, 0, 1);
  sem_init(&full, 0, 0);
  sem_init(&empty, 0, N);

  // Create threads
  pthread_t producer_thread;
  pthread_t consumer_thread;

  pthread_create(&producer_thread, NULL, producer, NULL);
  pthread_create(&consumer_thread, NULL, consumer, NULL);

  // Wait for the threads to terminate
  pthread_join(producer_thread, NULL);
  pthread_join(consumer_thread, NULL);

  return 0;
}
