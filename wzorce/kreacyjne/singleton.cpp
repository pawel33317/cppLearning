#include <iostream>
#include <memory>
using namespace std;

//  /usr/bin/g++-11 -std=c++2a -Wall -O0 -o app singleton.cpp && ./app

class SingletonPtrImp
{
    static SingletonPtrImp* s;
    SingletonPtrImp(){}
public:
    static SingletonPtrImp* getInstance()
    {
        if (!s)
        {
            s = new SingletonPtrImp();
        }
        return s;
    }
    void show() { cout << "I am a SingletonPtrImp\n";}
    SingletonPtrImp(SingletonPtrImp&) = delete;
    SingletonPtrImp operator=(SingletonPtrImp&) = delete;
};
SingletonPtrImp* SingletonPtrImp::s = nullptr;

class SingletonRefImp
{
    SingletonRefImp(){};
public:
    static SingletonRefImp& getInstance()
    {
        static SingletonRefImp sri;
        return sri;
    }
    SingletonRefImp(const SingletonRefImp&) = delete;
    SingletonRefImp operator=(const SingletonRefImp&) = delete;
    void show() { cout << "I am a SingletonRefImp\n";}
};

int main()
{
    printf("-----w_singleton-----\n");

    printf("-----w_singleton pointer implementation-----\n");
    SingletonPtrImp* s = SingletonPtrImp::getInstance();
    if(s)
        s->show();
    SingletonPtrImp* s2 = SingletonPtrImp::getInstance();
    if(s2)
        s2->show();
    cout << "singleton 1 addr: " << s << endl << "singleton 2 addr: "<< s2 << endl;
    delete s;

    printf("-----w_singleton reference implementation-----\n");
    SingletonRefImp& sri = SingletonRefImp::getInstance();
    SingletonRefImp& sri2 = SingletonRefImp::getInstance();
    sri.show();
    sri2.show();
    cout << "singleton 1 addr: " << &sri << endl << "singleton 2 addr: "<<
                &sri2 << endl;
}