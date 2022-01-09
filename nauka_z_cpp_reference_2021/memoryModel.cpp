#include <iostream>
#include <functional>
#include <atomic>
#include <thread>
using namespace std;

int main2()
{
    cout << "Memory model" << endl;
    cout << "Number of bits in unsigned char: " << std::numeric_limits<unsigned char>::digits << endl;

    atomic<int> aa;//bezpieczne watkowo //int aa niebezpieczne
    aa = 15;
    aa.fetch_add(6);//zamienia wartość aa na simę aa + 6 // działą dla niektórych typów prostych - template specialization

    //try to block thread via atomic wait >= c++20

    {
        std::atomic<int> x = 5;

        std::jthread t1{[&]{
            std::this_thread::sleep_for(500ms);
            cout << "Thread t1" << endl;
            x = 10;
            x.notify_all();
            std::this_thread::sleep_for(500ms);
            x = 11;
        }};

        cout << "x value: " << x << endl;
        cout << "waiting until x value will be changed from 5 " << x << endl;
        x.wait(5);
        cout << "x value: " << x << endl;

        std::this_thread::sleep_for(800ms);
        cout << "x value 800 ms later: " << x << endl;
    }
    cout << "end of memory model" << endl;
}