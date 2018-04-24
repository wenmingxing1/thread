#include<thread>
#include<iostream>
#include<string>

using namespace std;

void print(string str) {
    cout << str << endl;
}

int main() {
    cout << this_thread::get_id() << endl;  //通过this_thread获得当前线程标识

    thread th1(print, "id");

    cout << th1.get_id() << endl;   //通过get_id识别线程
    th1.join();

    return 0;
}
