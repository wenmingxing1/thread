#include<iostream>
#include<thread>

using namespace std;

//ÿ���̶߳���Ҫ��һ����ʼ�����������߳̾ʹ����￪ʼִ��
void hello() {
    cout << "hello world!" << endl;
}

int main() {
    thread th1(hello);

    /* ���߳�Ϊmain�����߳���th1���������û��join
     * �����߳�main�����Լ�ִ����ͽ����ˣ���û���ֵ�th1ִ��
     * join��Ŀ�ľ��������̵߳ȴ������߳�ִ�����֮����һ����к���������
    */
    th1.join();

    return 0;
}
