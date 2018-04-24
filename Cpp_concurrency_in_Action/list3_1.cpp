#include<iostream>
#include<thread>
#include<mutex>
#include<list>
#include<algorithm>

using namespace std;

//ʹ�����������ж����ݵķ���ʱ����ģ�list_contains�����ܿ������ڱ�add_to_list�޸ĵ��б�
std::mutex some_mutex;
std::list<int> some_list;

void add_to_list(int new_value) {
    std::lock_guard<mutex> guard(some_mutex);   //������push_back��ʱ����б���
    some_list.push_back(new_value);
}

bool list_contains(int value_to_find) {
    std::lock_guard<mutex> guard(some_mutex);   //������find��ʱ����б���
    return find(some_list.begin(), some_list.end(), value_to_find);
}
