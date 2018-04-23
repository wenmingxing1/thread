#include<iostream>
#include<thread>

using namespace std;

//每个线程都需要有一个初始化函数，新线程就从这里开始执行
void hello() {
    cout << "hello world!" << endl;
}

int main() {
    thread th1(hello);

    /* 主线程为main，新线程是th1，这里如果没有join
     * 则主线程main可能自己执行完就结束了，而没有轮到th1执行
     * join的目的就在于主线程等待调用线程执行完毕之后，再一起进行后续操作。
    */
    th1.join();

    return 0;
}
