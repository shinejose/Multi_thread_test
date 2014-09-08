// c header 
// #include <cstdio>
// #include <cmath>
// #include <cstring>
// #include <cstdlib>
// #include <memory.h>
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

void thread1()
{
    for(int i=0;i<10;i++)
    {
    }
}
void thread2()
{
    for(int i=0;i<10;i++)
    {
        cout << "this is thread 2\n";
    }
}
void hello()
{
    cout << "this is thread " << this_thread::get_id()<<endl;
}
int main(){
    thread threads[5];
    for(int i=4;i>=0;i--)
    {
        cout << "In main create thread " <<i <<endl; 
        threads[i] = thread(hello);
    }
    for(int i=0;i<5;i++)
    {
        threads[i].join();
        cout << "Complete thread "<< i <<endl;
    }
    cout << "Done\n";
    return 0;
}









