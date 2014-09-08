// c header 
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <memory.h>
// c++ header
#include <iostream>
#include <algorithm>
#include <deque>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <bitset>
#include <utility>
#include <iomanip>
// c++11 header
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <thread>
#include <chrono>
#include <atomic>
using namespace std;

typedef long long  ll;
typedef unsigned long long ull;

extern "C"
 {
    #include <pthread.h>
 }

using namespace std;

pthread_mutex_t cnt_mutex     = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t  condition_var   = PTHREAD_COND_INITIALIZER;

void * function1(void * arg);
void * function2(void * arg);

int  cnt = 0;

const int CNT_DONE  = 10;

main()
{
   pthread_t thread1, thread2;

   pthread_create( &thread1, NULL, &function1, NULL);
   pthread_create( &thread2, NULL, &function2, NULL);

   pthread_join( thread1, NULL);
   pthread_join( thread2, NULL);

  cout << "Final cnt: " <<  cnt << endl;

   return 0;
}

// Write numbers 1-3 and 8-10 as permitted by function2()

void *function1(void * arg)
{
    // function1 (thread1) likes to add 1 to cnt regardless of it's current value,
    // but will only do it if function2 is done working with cnt.

   for(;;)
   {
      // Lock mutex and then wait for signal to relase mutex
      pthread_mutex_lock( &cnt_mutex );


      // frunction1 gives control over cnt to function2 to see if function2 wants to do anything
      // with cnt. It will unlock cnt until function2 signals it's done working with cnt.
      pthread_cond_wait( &condition_var, &cnt_mutex );

      // add this point function2 has given back control of cnt to funciton1 and
      // has either added 1 to cnt or gave back control to function1 without changing cnt.
      cout << "function1 looks at cnt (" << cnt << ") and just adds 1 to it." << endl;
      cnt++;

      pthread_mutex_unlock( &cnt_mutex );

      if(cnt >= CNT_DONE) pthread_exit(NULL);
    }
}



void *function2(void * arg)
{
    // function 2 only likes to add 1 to odd numbers and will leave even numbers alone.

    for(;;)
    {
       pthread_mutex_lock( &cnt_mutex );

       if( cnt & 1 ) // check if cnt is odd
       {
          cout << "function2 detected cnt (" << cnt << ") is odd, so it adds 1 to it." << endl;
          cnt++;
       }
       else
       {

          // function 2 detected the number is even, and will leave it alone and signal function1
          // it has control back over cnt.
          pthread_cond_signal( &condition_var );

       }

       pthread_mutex_unlock( &cnt_mutex );

       if(cnt >= CNT_DONE)
       {
           pthread_cond_signal( &condition_var );
           pthread_exit(NULL);
       }
    }

}









