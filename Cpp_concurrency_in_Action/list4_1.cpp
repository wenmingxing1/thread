#include<iostream>
#include<mutex>
#include<condition_variable>
#include<queue>
#include<thread>

using namespace std;

std::mutex mut;
std::queue<data_chunk> data_queue;  //���ݶ���
std::condition_variable data_cond;

void data_preparation_thread() {
    while (more_data_to_prepare()) {
        data_chunk const data = prepare_data();
        std::lock_guard<std::mutex> lk(mut);    //�Զ���������Ȼ���������
        data_queue.push(data);  //
        data_cond.notify_one(); //֪ͨ�ȴ��߳�
    }
}

//data�����߳�
void data_processing_thread() {
    while (true) {
        std::unique_lock<std::mutex> lk(mut);   //�Ի���������,������������

        /* wait����һ���������ͼ������
         * wait�����Щ������������������㣨Ϊfalse��
         * wait����������������������߳�����������ȴ�״̬��
         * ��׼�����ݵ��̵߳���notify֪ͨ��������ʱ���������ݵ��̴߳����������ѣ����»�ȡ��������
         * ���������ٴμ�飬���������������£���wait���ز�������������������������ʱ���̶߳Ի����������������¿�ʼ�ȴ���

         * ������������߳������ڼ䱣����ס״̬��׼�����ݵ��߳̽��޷���ס��������Ҳ���޷�����µ����ݵ������С�

        */
        data_cond.wait(lk, []{return !data_queue.empty();});    //�ȴ�����
        data_chunk data = data.front();
        data_queue.pop();
        lk.unlock();    //
        process(data);

        if (is_last_chunk(data))
            break;
    }
}
