#include<iostream>
#include<thread>

using namespace std;

void test1() {
    cout << "foo is called" << endl;
}

void test2(int x) {
    cout << "test2 is called:" << x << endl;
}

int main() {
    thread th1(test1);
    thread th2(test2, 100);

    th1.join();
    th2.join();

    return 0;
}
