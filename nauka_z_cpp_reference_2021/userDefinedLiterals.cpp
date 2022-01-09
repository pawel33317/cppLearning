#include <iostream>
#include <functional>
#include <atomic>
#include <thread>
#include <cstddef>
#include <boost/type_index.hpp>
using namespace std;


constexpr long double operator"" _m_to_cm(long double meters)
{
    return meters*100;
}
int operator"" _m_to_cm_int(unsigned long long int meters )
{
    cout << "converting" << endl;
    return meters*100;
}
int main2323()
{
    cout << 10.5_m_to_cm << endl;
    cout << 10_m_to_cm_int << endl;
    [[maybe_unused]] int i = 5;
}