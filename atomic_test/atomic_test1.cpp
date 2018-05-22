/* ԭ�������Ƿ�װ��һ��ֵ�����ͣ�����֤���ᵼ�����ݵľ���
 * �����������ڲ�ͬ�߳�֮��ͬ���ڴ����
 *
*/

#include<iostream>
#include<thread>
#include<atomic>
#include<vector>

using namespace std;

std::atomic<bool> ready(false);
std::atomic_flag winner = ATOMIC_FLAG_INIT;     //��ʼ��atomic_flagΪfalse�� flagΪ��������ԭ������

void countlm(int id) {
    while (!ready) {std::this_thread::yield();}     //wait for the ready signal
    for (int i = 0; i < 1000000; ++i) { }  //count to 1 million

    //test_and_set������flag����Ϊtrue����������ǰ��ֵ
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
