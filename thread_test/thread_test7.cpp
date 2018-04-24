/*thread::detach*/

#include<iostream>
#include<thread>
#include<chrono>

using namespace std;

void pause_thread(int n) {
    std::this_thread::sleep_for(std::chrono::seconds(n));
    cout << "Pause for " << n << " seconds" << endl;
}

int main() {
    cout << "Spawning and detaching 3 threads" << endl;

    std::thread th1(pause_thread, 1);
    std::thread th2(pause_thread, 2);
    std::thread th3(pause_thread, 3);

    th1.detach();
    th2.detach();
    th3.detach();

    //��Ϊdetach���ں�̨���У����Կ���Ȩ��������main thread�У��������join������
    cout << "the main thread will now pause for 5 seconds to watch the result:" << endl;
    pause_thread(5);

    return 0;
}
