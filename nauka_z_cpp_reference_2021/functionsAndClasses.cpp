#include <iostream>
#include <functional>
#include <atomic>
#include <utility>
#include <thread>
#include <cstddef>
#include <map>
#include <boost/type_index.hpp>
using namespace std;


auto fun1(){
    return 10;
}
const auto& fun2(){
    return 10;
}

//virtual mówi, że najbardziej dziedziczacy obiekt będzie zawierał tylko jedną instancję tej klasy
struct A{int a = 5;};
struct X : public virtual A {};
struct Y : public virtual A {};
struct Z : public A {};
struct TestXYZ_A : X, Y, Z{
    TestXYZ_A(){
        X::a = 1;
        Y::a = 2;
        Z::a = 3;

        //cout << "a = " << a << endl; ambigous
        cout << "X::a = " << X::a << endl;
        cout << "Y::a = " << Y::a << endl;
        cout << "Z::a = " << Z::a << endl;
    }
};

struct A2 {
    int n; 
    A2(int nn) : n(nn) {}
};
struct X2 : public virtual A2 { X2() : A2(1) {} };
struct Y2 : public virtual A2 { Y2() : A2(2) {} };
struct TestX2Y2_A2 : public X2, public Y2{
    TestX2Y2_A2() : A2(3) {};
};

struct A3_USING {
    A3_USING(int a){}
 protected:
    int m;
};
 
struct A3_USING_TEST : A3_USING {
    using A3_USING::m;
    using A3_USING::A3_USING;
};

struct Empty{};
struct WithEmptyObj1 { Empty e; int a; };//8bytes
struct WithEmptyObj2 { [[no_unique_address]] Empty e; int a;};//4bytes


class TestClass{
public:
    TestClass() { cout << "   konstruktor domyslny\n"; };
    //TestClass() = default;
    TestClass(int a) { cout << "   konstruktor parametrowy\n"; };
    ~TestClass() { cout << "   destruktor\n";} //=default/delete

    TestClass(const TestClass& o) { cout << "   konstruktor kopiujący\n"; } // default
    TestClass& operator=(TestClass& o) { cout << "   kopiujący operaor przypisania\n"; } //default

    TestClass(double a) { cout << "   konstruktor konwertujący\n"; };
    explicit TestClass(std::string s) { cout << "   konstruktor konwertujący string\n"; };

    operator bool() const { return true;}
};


int main33()
{
    cout << fun1() << endl;
    TestXYZ_A();
    cout << "TestX2Y2_A2 odpowiedzialna za wywołanie konstruktora klasy bazowej: " << TestX2Y2_A2().n << endl;
    A3_USING_TEST usingTest(4);
    usingTest.m = 55;

    cout << "sizeof(WithEmptyObj1): " << sizeof(WithEmptyObj1) << endl;
    cout << "sizeof(WithEmptyObj2): " << sizeof(WithEmptyObj2) << endl;

    cout << "--------TestClass t0;\n";
    {
        TestClass t0;
    }
    cout << "--------TestClass t1{};\n";
    {
        TestClass t1{};//    TestClass t1() <--- wft
    }
    cout << "--------TestClass t2(2);\n";
    {
        TestClass t2(2);
    }
    cout << "--------TestClass TestClass();\n";
    {
        TestClass();
    }
    cout << "-------- TestClass t3 = TestClass();\n";
    {
        TestClass t3 = TestClass(3);//RVO
    }
    cout << "-------- TestClass t3 = t;\n";
    {
        TestClass t;
        TestClass t2;
        TestClass t3 = t;//konstruktor kopiujący
        t3 = t2;//kopiujący operator przypisania
    }
    cout << "-------- TestClass t = 5.5;\n";
    {
        TestClass t = 5.5;
    }
    cout << "--------TestClass t = std::string(\"zzz\");\n";
    {
        //TestClass t = std::string("zzz");

        //not possible because explicit
    }
    cout << "--------bool b = TestClass{4};\n";
    {
        bool b = TestClass{4};
    }
}

//ostatnie The this pointer w https://en.cppreference.com/w/cpp/language