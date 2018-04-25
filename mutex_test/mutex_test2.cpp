/* thread::try_lock */

/* try_lock试图为mutex加锁
 * 若互斥对象当前没有被任何线程锁定，则调用线程成功加锁；
 * 若已被其他线程锁定，则函数返回false，没有阻塞；
 * 若调用线程本身已经锁定mutex，则产生死锁
*/

#include<iostream>
#include<thread>
#include<mutex>

using namespace std;

volatile int counter = 0;   //volatile与const相反

std::mutex mtx;

void attemp_increases ()
{

    if (mtx.try_lock())
    {
        ++counter;
        mtx.unlock();
    }

}

int main() {
    std::thread ths[10];

    for (int i = 0; i < 10; ++i) {
        ths[i] = std::thread(attemp_increases);
    }

    for (int i = 0; i < 10; ++i) {
        ths[i].join();
    }

    cout << counter << " successful increases of the counter" << endl;

    return 0;
}
