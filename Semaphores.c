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
  __sync_fetch_and_add(*sem->value, 1);
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
