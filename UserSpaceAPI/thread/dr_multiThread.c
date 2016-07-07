#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>
using namespace std;

void *do_stuff(void *t) {
  sleep(5);                     // Sleep for 5 seconds
  pthread_exit(NULL);
}

void thread_start(pthread_t *thread) {
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
  pthread_create(thread, NULL, do_stuff, NULL);
  pthread_attr_destroy(&attr);
}

void thread_run(pthread_t *thread) {
  void *status;
  thread_start(thread);
  pthread_join(*thread, &status);
}

int main ()
{
  pthread_t threads[4];

  thread_start(&threads[0]);
  thread_start(&threads[1]);

  cout << "Done-1" << endl;
  thread_run(&threads[2]);
  thread_run(&threads[3]);

  cout << "Done-2" << endl;
  pthread_exit(NULL);
}
