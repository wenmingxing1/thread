#include<iostream>
#include<mutex>
#include<thread>
#include<condition_variable>
#include<vector>

using namespace std;

std::mutex mtx;
std::condition_variable cvar;

void myprint(char ch) {
    int nums = 10;

    for (int i = 0; i < nums; ++i) {
        std::unique_lock<std::mutex> ulk(mtx);
        cout << ch << endl;

        cvar.notify_one();
    }
}

int main() {
    /*
    vector<std::thread> threads;
    threads.push_back(std::thread(myprint, 'A'));
    threads.push_back(std::thread(myprint, 'B'));
    */
    std::thread th1(myprint, 'A');
    std::thread th2(myprint, 'B');

    th1.join();
    th2.join();

    return 0;


}
