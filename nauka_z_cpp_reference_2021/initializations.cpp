#include <iostream>
#include <functional>
#include <atomic>
#include <utility>
#include <thread>
#include <cstddef>
#include <map>
#include <boost/type_index.hpp>
using namespace std;

class T{

};

class Y{
    public: Y(int a ) {}
};

struct X{
    int a;
    int b;
};

int main1212()
{
    //Default
    T t1;
    T* t2 = new T(); delete t2;
    const T t3;

    //Value
    double f = double();    // scalar => zero-initialization, the value is 0.0
    int* a = new int[10](); // array => value-initialization of each element
    T t4{};         

    //Copy
    T t5 = t4;
    int i = 6;
    T t6 = {t5};

    //Direct
    Y y1(4);
    Y y2{5};
    cout << "initialization end\n";

    //Aggregate
    X x {4,5};

    //initializer list
    std::vector<int> mem = {1,2,3};
    int n2 = {1}; // copy-list-initialization
    std::map<int, std::string> m = { // nested list-initialization
           {1, "a"},
           {2, {'a', 'b', 'c'} },
           {3, "ss"}
    };

    //reference initialization
    int zz = 5;
    int& zz2 = zz;
    int&& zz3 = std::move(zz);
}