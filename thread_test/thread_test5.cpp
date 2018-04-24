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
    cout << "th1: " << th1.joinable() << endl;  //th1Ϊ���ɼ����
    cout << "th2: " << th2.joinable() << endl;

    if (th1.joinable()) th1.join();
    if (th2.joinable()) th2.join();

    cout << "Joinable after joining" << endl;
    cout << "th1: " << th1.joinable() << endl;
    cout << "th2: " << th2.joinable() << endl;  //ÿ���߳�ֻ�ܱ�joinһ�Σ�Ȼ��ͱ�ɲ��ɼ����

    return 0;
}
