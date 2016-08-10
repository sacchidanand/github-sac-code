/*
 *  Solution to Producer Consumer Problem
 *  Using Ptheads, a mutex and condition variables
 *  From Tanenbaum, Modern Operating Systems, 3rd Ed.
 */

/*
   In this version the buffer is a single number.
   The producer is putting numbers into the shared buffer
   (in this case sequentially)
   And the consumer is taking them out.
   If the buffer contains zero, that indicates that the buffer is empty.
   Any other value is valid.
 */

#include <stdio.h>
#include <pthread.h>

/*
struct node{
  int data;
  int sum;
};
typedef struct node node;
*/
//#define MAX 10000000000     /* Numbers to produce */
#define MAX 10     /* Numbers to produce */
pthread_mutex_t the_mutex;
pthread_cond_t cond_consumer, cond_producer;
int buffer = 0;
/*int buffer[20];
node node[5];
0-4, 5-9, 10-14, 15-19
 1 Producer, 5 Consumer
*/

void* producer(void *ptr) 
{
  int i;

  for (i = 1; i <= MAX; i++) 
  {
    //create thread before mutex
    pthread_mutex_lock(&the_mutex); /* protect buffer */

    /* wait for cond_producer, i.e. consumer will signal this channel 
     *  if there is nothing in the buffer then wait */
    while(buffer != 0) 
    {      
      pthread_cond_wait(&cond_producer, &the_mutex);
    }

    buffer = i;
    printf("Producer %d\n",buffer);
    
    /* signal the consumer data is available; wake up consumer */
    pthread_cond_signal(&cond_consumer);  

    /* release the mutex  i.e. critical section =  buffer is free for modification*/
    pthread_mutex_unlock(&the_mutex); 
  }//end-of-loop

  pthread_exit(0);
}

/*
void* compute(void *node)
{
  struct node *p = (node*)node;
  //process something
  p->sum += (p->data) * (p->data);
  pthread_exit(NULL);
}
*/

void* consumer(void *ptr) {
  int i, sum=0;

  for (i = 1; i <= MAX; i++) 
  {
    pthread_mutex_lock(&the_mutex); /* protect buffer */
    
    while (buffer == 0)
    {    
      /* wait for cond_consumer channel, i.e. when Producer will signal this channel 
       *  if there is nothng in the buffer then wait */
      pthread_cond_wait(&cond_consumer, &the_mutex);
    }

    sum +=buffer;
    printf("Consumer %d\n",sum);
    buffer = 0;

    /* signal the Producer data is consumed; wake up producer */
    pthread_cond_signal(&cond_producer); 

    /* release the mutex  i.e. critical section =  buffer is free for modification*/
    pthread_mutex_unlock(&the_mutex);  
  }//end-of-loop

  pthread_exit(0);
}

int main(int argc, char **argv) {
  pthread_t pro, con;

  // Initialize the mutex and condition variables
  /* What's the NULL for ??? */
  pthread_mutex_init(&the_mutex, NULL); 

  pthread_cond_init(&cond_consumer, NULL);    /* Initialize consumer condition variable */
  pthread_cond_init(&cond_producer, NULL);    /* Initialize producer condition variable */

  // Create the threads
  pthread_create(&con, NULL, consumer, NULL);
  pthread_create(&pro, NULL, producer, NULL);

  // Wait for the threads to finish
  // Otherwise main might run to the end
  // and kill the entire process when it exits.
  pthread_join(con, NULL);
  pthread_join(pro, NULL);

  // Cleanup -- would happen automatically at end of program
  pthread_mutex_destroy(&the_mutex);  /* Free up the_mutex */
  pthread_cond_destroy(&cond_consumer);   /* Free up consumer condition variable */
  pthread_cond_destroy(&cond_producer);   /* Free up producer condition variable */

}
























/*    
    for(j=0; j<5; j++)
    {
      local[j] = buffer[j];
      node[j].data = buffer[j];
      node[j].sum = 0;
      pthread_create(&thread[j], NULL, compute, &node[j]);
      buffer[j]=0;
    }  

    for(j=0; j<5; j++)
    {
      pthread_join(thread[j], NULL);
    }

    for(j=0; j<5; j++)
    {
      result += node[j].sum;
    }
    */
