#include<iostream>
#include<thread>
#include<mutex>

using namespace std;

std::mutex mtx;     //������

void thread_id() {
    mtx.lock();     //��ǰ�̻߳�ȡ���������������������̲߳����ȡ
    cout << std::this_thread::get_id() << endl;
    mtx.unlock();
}

int main() {
    std::thread ths[10];

    for (int i = 0; i < 10; ++i) {
        ths[i] = std::thread(thread_id);    //Ϊÿ���̸߳�ֵ��ʼ��
    }

    for (int i = 0; i < 10; ++i)
        ths[i].join();


    return 0;
}
