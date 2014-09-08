#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
 
#define NUM_THREADS     5
 
void *task_code(void *argument)
{
   int tid;
 
   tid = *((int *) argument);
   printf("Hello World! It's me, thread %d!\n", tid);
 
   /* optionally: insert more useful stuff here */
 
   return NULL;
}
 
int main(void)
{
   pthread_t threads[NUM_THREADS];
   int thread_args[NUM_THREADS];
   int rc, i;
 
   // create all threads one by one
   for (i=NUM_THREADS-1; i>=0; i--) {
      thread_args[i] = i;
      printf("In main: creating thread %d\n", i);
      rc = pthread_create(&threads[i], NULL, task_code, (void *) &thread_args[i]);
      assert(0 == rc);
   }
 
   // wait for each thread to complete
   for (i=0; i<NUM_THREADS; ++i) {
      // block until thread i completes
      rc = pthread_join(threads[i], NULL);
      printf("In main: thread %d is complete\n", i);
      assert(0 == rc);
   }
 
   printf("In main: All threads completed successfully\n");
   exit(EXIT_SUCCESS);
}
