#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>

char buf[24];
sem_t mutex;

void* func1(void*ptr);
void* func2(void*ptr);
int main()
{
  pthread_t th1, th2;
  char* msg1="thread 1";
  char* msg2="thread 2";

  sem_init(&mutex, 0, 1);

  pthread_create(&th1, NULL, (void*)&func1, (void*)msg1);
  pthread_create(&th2, NULL, (void*)&func2, (void*)msg2);
  
  pthread_join(th2, NULL);
  pthread_join(th1, NULL);

  sem_destroy(&mutex);

  return 0;
}

void* func1(void*ptr)
{
  char *msg = (char*)ptr;

  printf("%s\n",msg);  

  sem_wait(&mutex);
  sprintf(buf,"%s","Hello there !");
  sem_post(&mutex);

  pthread_exit(NULL);
}

void* func2(void*ptr)
{
  char *msg = (char*)ptr;

  printf("%s\n",msg);  
  
  sem_wait(&mutex);
  printf("buf=%s\n",buf);  
  sem_post(&mutex);

  pthread_exit(NULL);
}



