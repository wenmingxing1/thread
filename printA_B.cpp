#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>

std::mutex data_mutex;
std::condition_variable data_var;
bool label = false;

void printA() {
    std::unique_lock<std::mutex> ulock(data_mutex);
    data_var.wait(ulock, []{return label;});
    std::cout << " A " << std::endl;
    label = false;
    data_var.notify_one();
}

void printB() {
    std::unique_lock<std::mutex> ulock(data_mutex);
    std::cout <<  " B " << std::endl;
    data_var.notify_one();
    label = true;
    data_var.wait(ulock, []{return !label;});
}

int main()
{
    std::thread th1(printA);
    std::thread th2(printB);
    //for (int i = 0; i < 10; ++i) {
        th1.join();
        th2.join();
    //}
    std::cout << "end!" << std::endl;
    return 0;
}
