#define _GNU_SOURCE
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#define SLEEPTIME_SMALL 5
#define SLEEPTIME_BIG 10
/*  
 * apply to process level, even if command is intended for single thread.
 *  kill -SIGSTOP 27547
 *       -SIGCONT
 *       -SIGKILL
 */

pthread_t threads[4];

void* do_stuff_1(void *data){  
  while(1) {
    printf("\n\t1");
  } 
}

void* do_stuff_2(void *data){  
  while(1) {
    printf("\n\t\t\t2");
  } 
}

int main(int argc, char *argv[]) {  
  
  pthread_create(&(threads[0]), NULL, do_stuff_1, NULL);
  pthread_create(&(threads[1]), NULL, do_stuff_2, NULL);
  
  while(1){
    printf("\n \t\t\t\tMain"); 
  }

  printf("\nMain() exiting\n");
  return 0;
}
