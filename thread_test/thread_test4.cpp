/*get_id & this_thread::get_id*/
#include<iostream>
#include<thread>

using namespace std;

std::thread::id main_thread_id = std::this_thread::get_id();

void is_main_thread() {
    if (main_thread_id == std::this_thread::get_id())
        cout << "This is the main thread" << endl;
    else
        cout << "This is not main thread" << endl;
}

int main() {
    is_main_thread();

    thread th1(is_main_thread);
    th1.join();

    return 0;
}
