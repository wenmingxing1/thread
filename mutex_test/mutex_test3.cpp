/* std::timed_mutex  &  std::thread::try_lock_for */
/* timed_mutex���������������ֱ�Ϊtry_lock_for��try_lock_until
 * try_lock_for() ����ʱ��Σ���ʱ��η�Χ��δ�������������
 * �������Ϊ������������
 * ��ʱ������false��
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
