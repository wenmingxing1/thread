#include<iostream>
#include<thread>
#include<string>

using namespace std;

void thread_test1() {
    //使用get_id()函数
    cout << this_thread::get_id() << " : Hello World!" << endl;
}

void thread_test2(string str) {
    cout << this_thread::get_id() << " : " << str << endl;
}

int main()
{
    thread th1(thread_test1);   //调用thread的默认构造函数
    thread th2(thread_test2, "Hello World Again!");     //调用thread含参数的构造函数

    th1.join();
    th2.join();


    return 0;
}
