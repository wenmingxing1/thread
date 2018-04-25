/*lock_guard*/
/* lock_guard是一个通过将互斥量保持锁定来管理互斥量的对象；
 * 互斥对象被调用线程锁定，并且在销毁时，互斥锁被解锁。
 * 这保证了在抛出异常时，可以正确的锁定互斥对象。
 *
 * 其初始化方式可以直接以mutex初始化，表示管理mutex，并锁定它；
 * 也可以采用adopt_lock的方式，表示管理mutex，并且它已经被当前线程锁定
*/

#include<iostream>
#include<thread>
#include<mutex>     //lock_guard, adopt_lock

using namespace std;

std::mutex mtx;

void print_thread_id(int id) {
    mtx.lock();
    std::lock_guard<std::mutex> lck(mtx, std::adopt_lock);  //因为mtx已经被占有，如果不加adopt_lock，会产生死锁

    /*相当于
     std::lock_guard<std::mutex> lck(mtx);
    */
    cout << "thread #" << id << endl;

    //自动解锁
}

int main() {
    std::thread ths[10];

    for (int i = 0; i < 10; ++i)
        ths[i] = std::thread(print_thread_id, i+1);

    for (int i = 0; i < 10; ++i)
        ths[i].join();

    return 0;

}
