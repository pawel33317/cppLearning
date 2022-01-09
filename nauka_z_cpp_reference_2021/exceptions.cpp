#include <iostream>
#include <functional>
using namespace std;


struct S
{
    std::string mS;
    S(const std::string& s, int t) try : mS(s, t){

    }catch (...){ cout << "-------------wyjatek\n"; }// i tak rzuca tutaj
};

void noexceptFunc() noexcept{ //przez noexcept nie da się złapać wyjątku
    throw std::runtime_error("sss");
}

int mai232n()
{
    try 
    {
        S("xxx", 5);
    }catch(...){
        cout << "tutaj tez lapac trzeba\n";
    }

    try 
    {
        //noexceptFunc();
    }catch(...){
        cout << "noexceptFunc() throws";
    }
}