#include<iostream>
#include<mutex>
#include<thread>
//#include<condition_variable>
#include<vector>

using namespace std;

std::mutex mtx;     //互斥量
//std::condition_variable cvar;   //条件变量

void myprint(char ch) {
    int nums = 10;

    for (int i = 0; i < nums; ++i) {
        std::unique_lock<std::mutex> ulk(mtx);

        cout << this_thread::get_id() << " : "<< ch << endl;

        //cvar.notify_one();
    }
}

int main() {

    std::thread th1(myprint, 'A');
    std::thread th2(myprint, 'B');

    th1.join();
    th2.join();

    return 0;


}
