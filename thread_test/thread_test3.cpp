/*thread::operator=*/

#include<iostream>
#include<thread>
#include<chrono>    //seconds

using namespace std;

void pause_thread(int n) {
    std::this_thread::sleep_for(std::chrono::seconds(n));
    cout << "Pause for " << n << " seconds ended" << endl;
}

int main() {
    std::thread threads[5];

    for (int i = 0; i < 5; ++i)
        threads[i] = thread(pause_thread, i+1);     //构造线程

    cout << "Done spawning thread...." << endl;

    for (int i = 0; i < 5; ++i)
        threads[i].join();

    cout << "All threads joined" << endl;

    return 0;
}
