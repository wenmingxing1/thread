#include<thread>
#include<iostream>
#include<string>

using namespace std;

void print(string str) {
    cout << str << endl;
}

int main() {
    cout << this_thread::get_id() << endl;  //ͨ��this_thread��õ�ǰ�̱߳�ʶ

    thread th1(print, "id");

    cout << th1.get_id() << endl;   //ͨ��get_idʶ���߳�
    th1.join();

    return 0;
}
