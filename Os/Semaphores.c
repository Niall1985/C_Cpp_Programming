//counting semaphore without threads
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int value;
} CountingSemaphore;


void initCountingSemaphore(CountingSemaphore *sem, int value){
  sem->value = value;
}

void wait(CountingSemaphore *sem){
  while(1){
    if(__sync_fetch_and_sub(&sem->value, 1) > 0){
      return;
    }
    else{
      __sync_fetch_and_add(&sem->value, 1);
    }
  }
}

void signal(CountingSemaphore *sem){
  __sync_fetch_and_add(&sem->value, 1);
}

int main(){
  CountingSemaphore sem;
  initCountingSemaphore(&sem, 3);
  printf("Initializing semaphore\n");
  wait(&sem);
  printf("Semaphore acquired\n");
  printf("Releasing semaphore\n");
  signal(&sem);
  printf("Semaphore released\n")
  return 0;
}

// Binary semaphore without threads
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int value;
} BinarySemaphore;

void initBinarySemaphore(BinarySemaphore *sem, int value){
  sem->value = value;
}

void wait(BinarySemaphore *sem){
  while(__sync_lock_test_and_set(&sem->value, 0) == 0){
    //
  }
}

void signal(BinarySemaphore *sem){
  __sync_lock_release(&sem->value);
}

int main(){
  BinarySemaphore sem;
  initBinarySemaphore(&sem, 1);
  printf("Initializing semaphore\n");
  wait(&sem);
  printf("Semaphore acquired\n");
  printf("Releasing semaphore\n");
  signal(&sem);
  printf("Semaphore released\n");
  return 0;
}


//binary semaphore with threads
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define MAX 5

sem_t binarySemaphore;

void* Binary_Semaphore_Function(void *arg){
  int id = *(int*)arg;
  printf("Thread %d is waiting for the semaphore\n", id);
  sem_wait(&binarySemaphore);
  printf("Thread %d is in the critical section\n", id);
  sleep(1);
  printf("Thread %d is ready to leave the critical section\n", id);
  sem_post(&binarySemaphore);
  printf("Thread %d has finished it's execution\n", id);
  return NULL;
}

int main(){
  pthread_t threads[MAX];
  int threadIds[MAX];
  
  sem_init(&binarySemaphore, 0, 1);
  for(int i = 0 ; i < MAX ; i++){
    threadIds[i] = i;
    pthread_create(&threads[i], NULL, Binary_Semaphore_Function, &threadIds[i]);
  }
  
  for(int i = 0 ; i < MAX ; i++){
    pthread_join(threads[i],NULL);
  }
  sem_destroy(&binarySemaphore);
  return 0;
}

//counting semaphore with threads
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define MAX 5

sem_t CountingSemaphore;

void Counting_Semaphore_Function(void *arg){
  int id = *(int*)arg;
  printf("Thread %d is waiting for the semaphore\n", id);
  sem_wait(&CountingSemaphore);
  printf("Thread %d is in the critical section\n", id);
  sleep(1);
  printf("Thread %d is ready to leave the critical section\n", id);
  sem_post(&CountingSemaphore);
  printf("Thread %d has finished it's execution\n", id);
  return NULL;
}

int main(){
  pthread_t threads[MAX];
  int threadIds[MAX];
  
  sem_init(&CountingSemaphore, 0, 5);
  for(int i = 0 ; i < MAX ; i++){
    threadIds[i] = i;
    pthread_create(&threads[i], NULL, Counting_Semaphore_Function, &threadIds[i]);
  }
  
  for(int i = 0 ; i < MAX ; i++){
    pthread_join(threads[i],NULL);
  }
  sem_destroy(&CountingSemaphore);
  return 0;
}


//reader-writer
#include <stdio.h>
#include <semaphores.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

sem_t mutex;
sem_t wrt;
int readcount = 0;
int shared_data = 0;

void *readFunc(void *arg){
  int readerId = *(int*)arg;
  sem_wait(&mutex);
  readcount++;
  if(readcount == 1){
    sem_wait(&wrt);
  }
  sem_post(&mutex);
  
  printf("Perform the operation\n");
  sleep(1);
  
  sem_wait(mutex);
  readcount--;
  if(readcount == 0){
    sem_post(&wrt);
  }
  sem_post(&mutex);
  return NULL;
}

void *writerFunc(void *arg){
  int writerID = *(int*)arg;
  sem_wait(&wrt);
  shared_data++;
  printf("Writer is modifying the critical section\n");
  sleep(1);
  sem_post(&wrt);
  return NULL;
}
int main() {
    int n_readers = 5, n_writers = 3;
    pthread_t readers[n_readers], writers[n_writers];
    int reader_ids[n_readers], writer_ids[n_writers];

    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    // Create reader threads
    for (int i = 0; i < n_readers; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < n_writers; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < n_readers; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < n_writers; i++) {
        pthread_join(writers[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}

//dining philospher's problem

#include <stdio.h>
#include <semaphores.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define N 5
sem_t forks[N];
sem_t mutex;

void *philosopher(void *arg){
  int id = *(int*)arg;
  while(1){
    printf("Thinking\n");
    sleep(1);
    
    sem_wait(&mutex);
    sem_wait(&forks[id]);
    sem_wait(&forks[id] % N);
    sem_post(&mutex);
    
    printf("Eating\n");
    sleep(1);
    sem_post(&forks[id]);
    sem_post(&forks[id] % N);
    }
    return NULL;
}

int main(){
  pthread_t philosophers[N];
  int ids[N];
  
  sem_init(&mutex, 0, 1);
  
  for(int i = 0 ; i < N ; i++){
    sem_init(&forks[i], 0, 1);
  }
  
  for(int i = 0 ; i < N ; i++){
    ids[i] = i;
    pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
  }
  
  for(int i = 0 ; i < N ; i++){
    pthread_join(philosophers[i], NULL);
  }
  
  for(int i = 0 ; i < N ; i++){
    sem_destroy(&forks[i]);
  }
  sem_destroy(&mutex);
}

//producer consumer 
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5  // Size of the buffer
#define NUM_ITEMS 10   // Number of items to produce/consume

int buffer[BUFFER_SIZE];
int in = 0;  // Producer index
int out = 0; // Consumer index

// Semaphores
sem_t mutex;  // To ensure mutual exclusion in critical section
sem_t empty;  // Counts empty slots in the buffer
sem_t full;   // Counts full slots in the buffer

// Producer function
void *producer(void *arg) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        int item = rand() % 100;  // Produce a random item

        sem_wait(&empty);         // Wait if buffer is full
        sem_wait(&mutex);         // Enter critical section

        // Produce item
        buffer[in] = item;
        printf("Producer produced: %d\n", item);
        in = (in + 1) % BUFFER_SIZE;

        sem_post(&mutex);         // Leave critical section
        sem_post(&full);          // Increase count of filled slots

        sleep(1);  // Simulate time taken to produce item
    }
    return NULL;
}

// Consumer function
void *consumer(void *arg) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        sem_wait(&full);          // Wait if buffer is empty
        sem_wait(&mutex);         // Enter critical section

        // Consume item
        int item = buffer[out];
        printf("Consumer consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;

        sem_post(&mutex);         // Leave critical section
        sem_post(&empty);         // Increase count of empty slots

        sleep(1);  // Simulate time taken to consume item
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;

    // Initialize semaphores
    sem_init(&mutex, 0, 1);       // Binary semaphore for critical section
    sem_init(&empty, 0, BUFFER_SIZE);  // Initially, buffer is empty
    sem_init(&full, 0, 0);        // Initially, buffer has no filled slots

    // Create producer and consumer threads
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
