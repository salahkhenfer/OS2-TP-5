# OS2-TP-5


The solution includes three main functions:

- The producer adds items to the inventory.
- The consumer reads items from the store.
- The main program creates threads and waits for them to finish.


## The first step:

The first step is to define the variables and arrays that will be used.

```    
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
int head = 0
```

## The second step:

The second step is to initialize the Semaphores.
``` 
sem_init(&mutex, 0, 1);
sem_init(&full, 0, 0);
sem_init(&empty, 0, N);

```

- Semaphore mutex : is used to ensure exclusive access to the repository.
- Semaphore full : is used to track the number of items currently in stock.
- Semaphore empty : is used to track the number of items currently in stock.


## The third step:

The third step is to create the threads.

```
// Create threads
pthread_t producer_thread;
pthread_t consumer_thread;

pthread_create(&producer_thread, NULL, producer, NULL);
pthread_create(&consumer_thread, NULL, consumer, NULL);

```
## For the fourth step:

The fourth step is to wait for the threads to finish.

```
// Wait for the threads to terminate
pthread_join(producer_thread, NULL);
pthread_join(consumer_thread, NULL);

```

## For the sixth step:
The function of producer() is to add items to the repository. The function includes the following steps:

- The function waits until there is free space in the store.
- The job gets exclusive access to the repository.
- The function adds a new item to the inventory.
- The function releases exclusive access to the store.
- The function indicates that a new item is available in stock.

```
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

```


## For the seventh step:

The function of consumer() is to read items from the repository. The function includes the following steps:

The function waits until an item is available in stock.
The job gets exclusive access to the repository.
The function reads an item from the repository.
The function releases exclusive access to the store.
The function indicates that there is free space in the warehouse.
Example of running the program

When you run the program, it will produce the following output:

```
Value read: 0
Value read: 1
Value read: 2
...
Value read: 99
Value read: 100
```



This output shows that the producer and consumer are working in unison, with the producer adding items to the store and the consumer reading them



