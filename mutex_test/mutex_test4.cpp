/*lock_guard*/
/* lock_guard��һ��ͨ�����������������������������Ķ���
 * ������󱻵����߳�����������������ʱ����������������
 * �Ᵽ֤�����׳��쳣ʱ��������ȷ�������������
 *
 * ���ʼ����ʽ����ֱ����mutex��ʼ������ʾ����mutex������������
 * Ҳ���Բ���adopt_lock�ķ�ʽ����ʾ����mutex���������Ѿ�����ǰ�߳�����
*/

#include<iostream>
#include<thread>
#include<mutex>     //lock_guard, adopt_lock

using namespace std;

std::mutex mtx;

void print_thread_id(int id) {
    mtx.lock();
    std::lock_guard<std::mutex> lck(mtx, std::adopt_lock);  //��Ϊmtx�Ѿ���ռ�У��������adopt_lock�����������

    /*�൱��
     std::lock_guard<std::mutex> lck(mtx);
    */
    cout << "thread #" << id << endl;

    //�Զ�����
}

int main() {
    std::thread ths[10];

    for (int i = 0; i < 10; ++i)
        ths[i] = std::thread(print_thread_id, i+1);

    for (int i = 0; i < 10; ++i)
        ths[i].join();

    return 0;

}
