/*unique_lock*/

/* unique_lock与lock_guard类似，但提供更灵活的上锁和解锁控制。
 * unique_lock以独占的方式管理mutex对象的上锁和解锁；
 *
 * deferred初始化，管理mutex对象，但并不锁住mutex
 * adopting初始化，与lock_guard的adopting初始化一样，mutex是一个已经被当前线程锁住的mutex对象

*/

#include<iostream>
#include<thread>
#include<mutex> //unique_lock

using namespace std;

std::mutex mtx1, mtx2;

void test1() {
    std::lock(mtx1, mtx2);
    std::unique_lock<std::mutex> lck1(mtx1, std::adopt_lock);
    std::unique_lock<std::mutex> lck2(mtx2, std::adopt_lock);

    cout << "test1_adopt" << endl;

    //自动解锁
}

void test2() {
    std::unique_lock<std::mutex> lck1, lck2;
    lck1 = std::unique_lock<std::mutex>(mtx1, std::defer_lock);
    lck2 = std::unique_lock<std::mutex>(mtx2, std::defer_lock);

    std::lock(lck1, lck2);  //因为以defer方式初始化，所以还需要加锁

    cout << "test2_defer" << endl;

    //自动解锁
}

int main() {
    std::thread th1(test1);
    std::thread th2(test2);

    th1.join();
    th2.join();

    return 0;
}

