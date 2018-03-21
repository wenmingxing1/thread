#include<iostream>
#include<mutex>
#include<thread>
//#include<condition_variable>
#include<vector>

using namespace std;

std::mutex mtx;     //������
//std::condition_variable cvar;   //��������

void myprint(char ch) {
    int nums = 10;

    for (int i = 0; i < nums; ++i) {
        std::unique_lock<std::mutex> ulk(mtx);  //ʹ��unique_lock���൱��ע�͵���lock��unlock
        //mtx.lock();
        cout << this_thread::get_id() << " : "<< ch << endl;
        //mtx.unlock();
    }
}

int main() {

    std::thread th1(myprint, 'A');
    std::thread th2(myprint, 'B');

    th1.join();
    th2.join();

    return 0;


}
