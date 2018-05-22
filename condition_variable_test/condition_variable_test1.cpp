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
    /* �ڵ���wait��ʱ���߳�����������֮�������������ͷ��������������̻߳�ȡ����
     * ��Ϊֻ�������̻߳�ȡ�������ܸı�ready�������������̸߳ı�notify_allʱ��
     * ��������wait�������Զ���ȡ����ִ��lock��ִ����Ӧ���������unique_lock���ͷ�����
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
    //std::unique_lock<std::mutex> lck(mtx);  //��֤�̵߳�ԭ���Բ���
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
