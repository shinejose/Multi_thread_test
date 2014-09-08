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
using namespace std ;
extern "C"
{
#include <unistd.h>
#include <pthread.h> 
}

void* function1(void* arg)
{
    cout << *(reinterpret_cast<string*>(arg)) << endl ;
    return 0;
}

void pthread_join_example_1()
{
    pthread_t  t1,t2 ;

    string msg1 ("hello")  ;
    string msg2 ("world")  ;

    int create1 = pthread_create( &t1, NULL, function1,reinterpret_cast<void*>(&msg1));
    if (create1 != 0) cout << "error" ;
    int create2 = pthread_create( &t2, NULL, function1,reinterpret_cast<void*>(&msg2));
    if (create2 != 0) cout << "error" ;
    pthread_join(t1,NULL) ;
    pthread_join(t2,NULL) ;
    
}
const int NUMBER_OF_THREADS = 5;

int some_value = 10;

void *thread_talk_without_mutex(void * thread_nr)
{
    for(int i=0;i<500;i++)
    {
        some_value=some_value * 10;
        some_value ++ ;
        some_value --;
        some_value = some_value/10;
    }
    pthread_exit(NULL);
}

void * thread_talk(void * thread_nr)
{
    int a = *(static_cast<int*>(thread_nr));
    sleep(a+1);
    cout << "Thread " <<  a <<" has finished"  << endl;

    pthread_exit(NULL);
    return 0;
}

void pthread_join_example_2()
{
    pthread_t thread[NUMBER_OF_THREADS];
    cout << "Starting all threads..." << endl;
    int temp_arg[NUMBER_OF_THREADS] ;
    for(int current_t = 0; current_t < NUMBER_OF_THREADS; current_t++)
    {
        temp_arg[current_t]   = current_t;
        int result = pthread_create(&thread[current_t], NULL,
                                    thread_talk_without_mutex,
                                    static_cast<void*>(&temp_arg[current_t]))  ;
        if (result !=0)
            cout << "Error creating thread " << current_t << ". Return code:" << result <<  endl;
    }

    for(int current_t = 0; current_t < NUMBER_OF_THREADS; current_t++)
        pthread_join(thread[current_t], NULL);

    cout << "All threads completed."<<endl ;
    cout << "some_value = " << some_value<< endl;
}
void pthread_join_example_2_wrong()
{
    pthread_t thread[NUMBER_OF_THREADS];
    cout << "Starting all threads..." << endl;
    int temp_arg[NUMBER_OF_THREADS] ;
    for(int current_t = 0; current_t < NUMBER_OF_THREADS; current_t++)
    {
        int result = pthread_create(&thread[current_t], NULL,
                                    thread_talk, static_cast<void*>(&current_t))  ;
        if (result !=0)
            cout << "Error creating thread " << current_t << ". Return code:" << result <<  endl;
    }

    for(int current_t = 0; current_t < NUMBER_OF_THREADS; current_t++)
        pthread_join(thread[current_t], NULL);

    cout << "All threads completed." ;
}


int main( void )
{
    pthread_join_example_2(); 
    return 0;
}


















