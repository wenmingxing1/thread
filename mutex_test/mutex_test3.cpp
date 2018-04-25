/* std::timed_mutex  &  std::thread::try_lock_for */
/* timed_mutex多了两个函数，分别为try_lock_for，try_lock_until
 * try_lock_for() 传入时间段，在时间段范围内未获得锁就阻塞；
 * 获得锁则为互斥量加锁；
 * 超时，返回false；
*/

#include<iostream>
#include<thread>
#include<mutex>
#include<chrono>

using namespace std;

std::timed_mutex mtx;

void fireworks() {
    //waiting to get the mtx, every thread prints "wait" every 200ms
    while (!mtx.try_lock_for(std::chrono::milliseconds(2)));
        cout << "wait" << endl;

    //get mtx, wait for 1s, then this thread prints "successful"
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    cout << "successful" << endl;

    mtx.unlock();

}

int main() {
    std::thread ths[10];

    for (int i = 0; i < 10; ++i)
        ths[i] = std::thread(fireworks);

    for (int i = 0; i < 10; ++i)
        ths[i].join();

    return 0;
}
