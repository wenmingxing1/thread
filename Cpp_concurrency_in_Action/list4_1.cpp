#include<iostream>
#include<mutex>
#include<condition_variable>
#include<queue>
#include<thread>

using namespace std;

std::mutex mut;
std::queue<data_chunk> data_queue;  //数据队列
std::condition_variable data_cond;

void data_preparation_thread() {
    while (more_data_to_prepare()) {
        data_chunk const data = prepare_data();
        std::lock_guard<std::mutex> lk(mut);    //对队列上锁，然后添加数据
        data_queue.push(data);  //
        data_cond.notify_one(); //通知等待线程
    }
}

//data处理线程
void data_processing_thread() {
    while (true) {
        std::unique_lock<std::mutex> lk(mut);   //对互斥量上锁,保护条件变量

        /* wait传入一个互斥量和检查条件
         * wait检查这些条件，如果条件不满足（为false）
         * wait将解锁互斥量，并将这个线程置于阻塞或等待状态。
         * 当准备数据的线程调用notify通知条件变量时，处理数据的线程从休眠中苏醒，重新获取互斥锁。
         * 并对条件再次检查，在条件满足的情况下，从wait返回并继续持有锁。当条件不满足时，线程对互斥量解锁，并重新开始等待。

         * 如果互斥量在线程休眠期间保持锁住状态，准备数据的线程将无法锁住互斥量，也就无法添加新的数据到队列中。

        */
        data_cond.wait(lk, []{return !data_queue.empty();});    //等待条件
        data_chunk data = data.front();
        data_queue.pop();
        lk.unlock();    //
        process(data);

        if (is_last_chunk(data))
            break;
    }
}
