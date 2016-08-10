#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#define MAX 1000
char buf[24];
int a[MAX];
//sem_t mutex;
pthread_mutex_t lock;

void* func1(void*ptr);
void* func2(void*ptr);
int main()
{
  pthread_t th1, th2;
  char* msg1="thread 1";
  char* msg2="thread 2";

  //sem_init(&mutex, 0, 1);
  memset(a, 0, sizeof(a));	

  pthread_create(&th1, NULL, (void*)&func1, (void*)msg1);
  pthread_create(&th2, NULL, (void*)&func2, (void*)msg2);

  /*
  pthread_join(th1, NULL);
*/
  pthread_join(th2, NULL);
  printf("\n1\n");
  printf("2\n");
  //sem_destroy(&mutex);

  return 0;
}

void* func1(void*ptr)
{
  char *msg = (char*)ptr;
  int i =0;

  printf("\n%s\n",msg);  

  //sem_wait(&mutex);
  pthread_mutex_lock(&lock);
  //sprintf(buf,"%s","Hello there !");
  for(i=0;i<MAX;i++)
  {
    printf("X");
    a[i] = i;
  }	


  pthread_mutex_unlock(&lock);
  //sem_post(&mutex);

  pthread_exit(NULL);
}

void* func2(void*ptr)
{
  char *msg = (char*)ptr;
  int i =0;

  printf("\n%s\n",msg);  

  //sem_wait(&mutex);
  pthread_mutex_lock(&lock);

  for(i=0;i<MAX;i++)
  {
    printf("%d, ",a[i]);  
  }

  pthread_mutex_unlock(&lock);
  //sem_post(&mutex);

  pthread_exit(NULL);
}



