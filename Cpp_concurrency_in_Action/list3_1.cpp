#include<iostream>
#include<thread>
#include<mutex>
#include<list>
#include<algorithm>

using namespace std;

//使得两个函数中对数据的访问时互斥的，list_contains不可能看到正在被add_to_list修改的列表
std::mutex some_mutex;
std::list<int> some_list;

void add_to_list(int new_value) {
    std::lock_guard<mutex> guard(some_mutex);   //用于在push_back的时候进行保护
    some_list.push_back(new_value);
}

bool list_contains(int value_to_find) {
    std::lock_guard<mutex> guard(some_mutex);   //用于在find的时候进行保护
    return find(some_list.begin(), some_list.end(), value_to_find);
}
