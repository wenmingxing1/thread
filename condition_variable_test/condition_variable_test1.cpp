#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>

using namespace std;

std::mutex mtx;
std::condition_variable cv;
int flag = 0;

void thread_odd() {
    /*lock--wait(unlock--lock)--unlock*/
    //std::unique_lock<std::mutex> lck(mtx);
    /* 在调用wait的时候，线程阻塞，阻塞之后条件变量会释放锁，以让其他线程获取锁；
     * 因为只有其他线程获取锁，才能改变ready条件，当其他线程改变notify_all时，
     * 条件变量wait返回再自动获取锁，执行lock，执行相应操作，最后unique_lock再释放锁。
    */
    while (flag < 10) {
        std::unique_lock<std::mutex> lck(mtx);
        if (flag % 2 == 0) {
            cv.wait(lck);
        }
        cout << "thread odd is runing: " << flag << endl;
        ++flag;
    }

}

void thread_even() {
    //std::unique_lock<std::mutex> lck(mtx);  //保证线程的原子性操作
    while (flag < 10) {
        std::unique_lock<std::mutex> lck(mtx);
        if (flag % 2 == 1) {
            cv.notify_one();
        }
        else
            cout << "thread_even is running:" << flag << endl;
        ++flag;
    }
}

int main() {
    std::thread th1(thread_odd);
    std::thread th2(thread_even);

    th1.join();
    th2.join();

    return 0;
}
