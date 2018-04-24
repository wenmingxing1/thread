/*thread::joinable*/

#include<iostream>
#include<thread>

using namespace std;

void mythread() {
    //do stuff...
}

int main() {
    std::thread th1;
    std::thread th2(mythread);

    cout << "Joinable after construction:" << endl;
    cout << "th1: " << th1.joinable() << endl;  //th1为不可加入的
    cout << "th2: " << th2.joinable() << endl;

    if (th1.joinable()) th1.join();
    if (th2.joinable()) th2.join();

    cout << "Joinable after joining" << endl;
    cout << "th1: " << th1.joinable() << endl;
    cout << "th2: " << th2.joinable() << endl;  //每个线程只能被join一次，然后就变成不可加入的

    return 0;
}
