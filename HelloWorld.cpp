#include<iostream>
#include<thread>
#include<string>

using namespace std;

void thread_test1() {
    //ʹ��get_id()����
    cout << this_thread::get_id() << " : Hello World!" << endl;
}

void thread_test2(string str) {
    cout << this_thread::get_id() << " : " << str << endl;
}

int main()
{
    thread th1(thread_test1);   //����thread��Ĭ�Ϲ��캯��
    thread th2(thread_test2, "Hello World Again!");     //����thread�������Ĺ��캯��

    th1.join();
    th2.join();


    return 0;
}
