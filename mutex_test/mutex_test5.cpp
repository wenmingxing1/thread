/*unique_lock*/

/* unique_lock��lock_guard���ƣ����ṩ�����������ͽ������ơ�
 * unique_lock�Զ�ռ�ķ�ʽ����mutex����������ͽ�����
 *
 * deferred��ʼ��������mutex���󣬵�������סmutex
 * adopting��ʼ������lock_guard��adopting��ʼ��һ����mutex��һ���Ѿ�����ǰ�߳���ס��mutex����

*/

#include<iostream>
#include<thread>
#include<mutex> //unique_lock

using namespace std;

std::mutex mtx1, mtx2;

void test1() {
    std::lock(mtx1, mtx2);
    std::unique_lock<std::mutex> lck1(mtx1, std::adopt_lock);
    std::unique_lock<std::mutex> lck2(mtx2, std::adopt_lock);

    cout << "test1_adopt" << endl;

    //�Զ�����
}

void test2() {
    std::unique_lock<std::mutex> lck1, lck2;
    lck1 = std::unique_lock<std::mutex>(mtx1, std::defer_lock);
    lck2 = std::unique_lock<std::mutex>(mtx2, std::defer_lock);

    std::lock(lck1, lck2);  //��Ϊ��defer��ʽ��ʼ�������Ի���Ҫ����

    cout << "test2_defer" << endl;

    //�Զ�����
}

int main() {
    std::thread th1(test1);
    std::thread th2(test2);

    th1.join();
    th2.join();

    return 0;
}

