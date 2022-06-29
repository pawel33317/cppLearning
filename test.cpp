#include <iostream>
#include <type_traits>
#include <cstring>
using namespace std;




int main(){
short s = 5;
char c = 6;
auto a = s + c;
cout << a << endl << typeid(a).name();
}