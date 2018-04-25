/* thread::try_lock */

/* try_lock��ͼΪmutex����
 * ���������ǰû�б��κ��߳�������������̳߳ɹ�������
 * ���ѱ������߳���������������false��û��������
 * �������̱߳����Ѿ�����mutex�����������
*/

#include<iostream>
#include<thread>
#include<mutex>

using namespace std;

volatile int counter = 0;   //volatile��const�෴

std::mutex mtx;

void attemp_increases ()
{

    if (mtx.try_lock())
    {
        ++counter;
        mtx.unlock();
    }

}

int main() {
    std::thread ths[10];

    for (int i = 0; i < 10; ++i) {
        ths[i] = std::thread(attemp_increases);
    }

    for (int i = 0; i < 10; ++i) {
        ths[i].join();
    }

    cout << counter << " successful increases of the counter" << endl;

    return 0;
}
