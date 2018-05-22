/* 原子类型是封装了一个值的类型，它保证不会导致数据的竞争
 * 并可以用于在不同线程之间同步内存访问
 *
*/

#include<iostream>
#include<thread>
#include<atomic>
#include<vector>

using namespace std;

std::atomic<bool> ready(false);
std::atomic_flag winner = ATOMIC_FLAG_INIT;     //初始化atomic_flag为false， flag为无锁布尔原子类型

void countlm(int id) {
    while (!ready) {std::this_thread::yield();}     //wait for the ready signal
    for (int i = 0; i < 1000000; ++i) { }  //count to 1 million

    //test_and_set函数将flag设置为true，并返回先前的值
    if (!winner.test_and_set()) {cout << "thread #" << id << " won!" << endl;}
}

int main() {
    std::vector<std::thread> threads;
    cout << "spawning 10 threads that count to 1 million..." << endl;

    for (int i = 1; i <= 10; ++i) {
        threads.push_back(thread(countlm, i));
    }

    ready = true;
    for (auto& th:threads) th.join();

    return 0;
}
