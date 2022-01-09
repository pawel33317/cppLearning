#include <iostream>
#include <mutex>
#include <thread>
#include <mutex>
using namespace std;

mutex m1, m2;

void doOperation1(int i)
{
    lock_guard<mutex> g1(m1);
    std::this_thread::sleep_for (std::chrono::seconds(1));
    lock_guard<mutex> g2(m2);
    std::cout << "doOperation1, thread: " << std::this_thread::get_id() << endl;
}

void doOperation2(int i)
{
    lock_guard<mutex> g2(m2);
    std::this_thread::sleep_for (std::chrono::seconds(1));
    lock_guard<mutex> g1(m1);
    std::cout << "doOperation2, thread: " << std::this_thread::get_id() << endl;
}

// void doOperation1(int i)
// {
//     lock(m1, m2);
//     lock_guard<mutex> g1(m1,std::adopt_lock);
//     std::this_thread::sleep_for (std::chrono::seconds(1));
//     lock_guard<mutex> g2(m2,std::adopt_lock);
//     std::cout << "doOperation1, thread: " << std::this_thread::get_id() << endl;
// }

// void doOperation2(int i)
// {
//     lock(m2, m1);
//     lock_guard<mutex> g2(m2,std::adopt_lock);
//     std::this_thread::sleep_for (std::chrono::seconds(1));
//     lock_guard<mutex> g1(m1,std::adopt_lock);
//     std::cout << "doOperation2, thread: " << std::this_thread::get_id() << endl;
// }
// //std::lock_guard objects that the mutexes are already locked, and they should just adopt the ownership of the existing lock on the mutex rather than attempt to lock the mutex in the constructor.

int maindeadlock()
{
    thread t1([](int i){doOperation1(i);}, 10);
    thread t2([](int i){doOperation2(i);}, 20);

    t1.join();
    t2.join();
    return 0;
}