#include <iostream>
using namespace std;

class Counter
{
    long counter = 0;
public:
    void operator++(int) noexcept { //post
        counter++; 
        cout << "[INCREASING] counter val: " << counter << endl;
    }
    void operator--(int) noexcept {
        counter--;
        cout << "[DECREASING] counter val: " << counter << endl;
    }
    operator bool() const noexcept {
        return counter !=0;
    }
    long count() const noexcept {
        return counter;
    }
    void reset() noexcept {
        counter = 0;
        cout << "[RESET] counter val: " << counter << endl;
    }
};

template <class T>
class SP
{
    Counter* c;
    T* p;
public:
    SP(SP&&) = delete;
    SP<T>& operator=(SP&&) = delete;

    SP(const SP<T>& o){
        cout << "   SP(const SP<T>& o)" << endl;
        c = o.c;
        (*c)++;
        p = o.p;
    }
    SP(T* t) noexcept {
        cout << "   SP(T* t)" << endl;
        c = new Counter;
        p = t;
        (*c)++;
    }
    SP(std::nullptr_t) noexcept {
        cout << "   SP(std::nullptr_t)" << endl;
        c = new Counter;
        p = nullptr;
    }
    ~SP(){
        cout << "   ~SP()" << endl;
        if (p == nullptr)
            return;

        (*c)--;
        if (!c){
            delete p;
            delete c;
            p = nullptr;
        }
    }
    
    SP<T>& operator=(const SP<T>& o) noexcept {
        cout << "   operator=(const SP<T>& o)" << endl;
        c = o.c;
        (*c)++;
        p = o.p;
        return *this;
    }

    void reset() noexcept {
        c->reset();
        delete p;
        p = nullptr;
    }
    void swap(SP& o) noexcept {}
    T* get()  const noexcept { return p; }
    T& operator*()  const noexcept { return *p; }
    T* operator->()  const noexcept { return p; }
    long use_count() const noexcept { return c->count(); }
    operator bool() const noexcept{ return p != nullptr; }
};
 
int mainsp() 
{
    SP<int> sp1(new int);
    SP<int> sp2(nullptr);
    sp2 = sp1;
    SP<int> sp3 = sp2;
}
