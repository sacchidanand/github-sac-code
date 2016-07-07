#define _GNU_SOURCE
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#define SLEEPTIME_SMALL 5
#define SLEEPTIME_BIG 10
/*  
 *  apply to process level, even if command is intended for single thread.
 *  kill -SIGSTOP 27547
 *       -SIGCONT
 *       -SIGKILL
 */

pthread_t threads[4];
void thread_start(pthread_t *thread);
void thread_run(pthread_t *thread);
static int start=0, end=0;

void displayThreadId(pthread_t tid){
  if(pthread_equal(tid, threads[0]))
    printf("\n\n1st Thread running");
  else if(pthread_equal(tid, threads[1]))
    printf("\n\n2nd Thread running");
  else if(pthread_equal(tid, threads[2]))
    printf("\n\n3rd Thread running");
  else if(pthread_equal(tid, threads[3]))
    printf("\n\n4th Thread running");
}

void* startRoutine(void *data) {
      int state=0;

      pthread_t tid = pthread_self();
      displayThreadId(tid);

      printf("\n Running startRoutine()...: %d ************", start++); 
      //sleep(SLEEPTIME_SMALL);

      pthread_attr_t myattr;
      pthread_getattr_np(pthread_self(), &myattr);
      pthread_attr_getdetachstate(&myattr, &state);
      
      if(state == PTHREAD_CREATE_JOINABLE) {
        printf("\n Joinable thread ! state=%d", state);
      }

      printf("\n Leaving startRoutine()... : %d************\n",end++);
     return 0; 
}

void thread_run(pthread_t *thread) {
  void *status;
  thread_start(thread);
  //printf("\nWaiting for join %d", i++);
  //Block execution of all threads in this current process until this thread terminates.
  //kindof makes it serialize
  //allow this thread to run completely first
  pthread_join(*thread,&status);
}

void thread_start(pthread_t *thread) {
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
  pthread_create(thread, &attr, startRoutine, NULL);
  pthread_attr_destroy(&attr);  
}

int main(int argc, char *argv[]) {  
  void *status= 0;
  int t = 0; 
  if(argc==2)
    t = atoi(argv[1]);

  //thread_start(&threads[0]);
  thread_run(&threads[0]);
  printf("\nDone-0\n");
 
  //thread_start(&threads[1]); 
  thread_run(&threads[1]); 
  printf("\nDone-1\n");

  //thread_start(&threads[2]);
  thread_run(&threads[2]);
  printf("\nDone-2\n");

  //thread_start(&threads[3]); 
  thread_run(&threads[3]); 
  printf("\nDone-3\n");
 
  //pthread_join(threads[2], &status);
  //pthread_join(threads[3], &status);
  //pthread_join(threads[1], &status);
  //pthread_join(threads[0], &status);

  printf("\nMain() exiting\n");

  return 0;
}
