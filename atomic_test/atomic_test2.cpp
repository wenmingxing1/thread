// atomic::operator=

#include<iostream>
#include<thread>
#include<atomic>

using namespace std;

std::atomic<int> foo(0);

void set_foo(int x) {
    foo = x;
}

void print_foo() {
    while (foo <= 10) {  //wait while foo == 0
        std::this_thread::yield();      //yield是让线程交出时间片，使其占用CPU时间减少
    }

    cout << "foo: " << foo << endl;
}

int main() {
    std::thread first(print_foo);
    std::thread second(set_foo,11);

    first.join();
    second.join();

    return 0;
}
