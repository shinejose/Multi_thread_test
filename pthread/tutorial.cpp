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

extern "C"
{
    #include <pthread.h>
    #include <unistd.h>
}
using namespace std;

typedef long long  ll;
typedef unsigned long long ull;

    void * function1(void *argument )
{

    cout << "hello..." << endl ;
    sleep(2); // fall asLeep here for 2 seconds...

}

    void * function2(void *argument)
{
    cout << " ....world" << endl ;
}

int main(){
    // ios::sync_with_stdio(false);
    pthread_t t1, t2 ; // declare 2 threads.
    pthread_create( &t1, NULL, function1,NULL); // create a thread running function1
    pthread_create( &t2, NULL, function2,NULL); // create a thread running function2

    // Because all created threads are terminated when main() finishes, we have
    // to give the threads some time to finish. Unfortunately for function1, main()
    // will give only 1 second, but function1 needs at least 2 seconds. So function1 will
    // probably be terminated before it can finish. This is a BAD way to manage threads.
    sleep(1);    
    return 0;
}









