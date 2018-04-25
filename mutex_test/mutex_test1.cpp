#include<iostream>
#include<thread>
#include<mutex>

using namespace std;

std::mutex mtx;     //互斥量

void thread_id() {
    mtx.lock();     //当前线程获取互斥量并加锁，则其他线程不会获取
    cout << std::this_thread::get_id() << endl;
    mtx.unlock();
}

int main() {
    std::thread ths[10];

    for (int i = 0; i < 10; ++i) {
        ths[i] = std::thread(thread_id);    //为每个线程赋值初始化
    }

    for (int i = 0; i < 10; ++i)
        ths[i].join();


    return 0;
}
