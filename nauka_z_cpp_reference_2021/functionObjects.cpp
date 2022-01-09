#include <iostream>
#include <functional>

class Test
{
private:
    std::string spamLargeObj {};
public:
    void doSomething(int a, int b){ std::cout << a << std::endl;};
    Test(const Test& t){ std::cout << "unwanted copy\n";}
    Test() = default;
};

void testfun1(int& a, int& b, int& c, int& d)
{
    std::cout << "In func: " << a << "---" << b << "---" << "---" << c << "---" << d << std::endl;
    a = 101;
    b = 102;
    c = 103;
    d = 104;
}

int main1()
{
    Test t1;
    Test t2;
    auto f1 = std::function<void(int,int)>(std::bind(&Test::doSomething, &t1, std::placeholders::_1, std::placeholders::_2));
    f1(1,0);

    // auto f2 = std::function<void(int,int)>(std::bind(&Test::doSomething, t1, std::placeholders::_1, std::placeholders::_2));//chujnia bo robi kopię t1
    // f2(2,0);
    auto funptr1 = std::mem_fn(&Test::doSomething);
    funptr1(t1, 3,0);
    auto f3 = std::function<void(int,int)>(std::bind(funptr1, &t1, std::placeholders::_1, std::placeholders::_2));
    f3(4,0);
    auto f4 = std::function<void(int,int)>([&t1](int a, int b){t1.doSomething(a, b);});
    f4(5,0);
    std::invoke(&Test::doSomething, t1, 6,0);
    auto f5 = std::function<void(int,int)>(std::bind_front(funptr1, &t1));
    f5(7,0);
    std::cout << "end\n";

    std::vector<Test> testVec1;
    testVec1.push_back(t1);//unwanted copy
    std::vector<Test*> testVec2;
    testVec2.push_back(&t1);//ok no copy
    std::vector<std::reference_wrapper<Test>> testVec3;
    testVec3.push_back(t1);//ok no copy

    std::vector<std::reference_wrapper<Test>> testVec4;
    testVec3.push_back(std::ref(t1));//ok no copy


    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;

    auto testFuncBindFunction = std::function<void()>(std::bind(&testfun1, a, std::ref(b), std::reference_wrapper<int>(c), std::reference_wrapper(d)));
    a = 11;
    b = 12;
    c = 13;
    d = 14;

    std::cout << "Before func: " << a << "---" << b << "---" << "---" << c << "---" << d << std::endl;
    testFuncBindFunction();
    std::cout << "After func: " << a << "---" << b << "---" << "---" << c << "---" << d << std::endl;
    //std::ref(x) === std::reference_wrapper<int>(x) === std::reference_wrapper(x)
}