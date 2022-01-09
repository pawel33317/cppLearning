#include <iostream>
#include <functional>
#include <atomic>
#include <thread>
#include <cstddef>
#include <boost/type_index.hpp>
using namespace std;



int mainsd()
{
    int i[2] {1,2};
    auto [a, b] = i;
    auto& [c, d] = i;
    i[0] = 3; i[1] = 4;
    cout << a << b << c << d << endl;

    std::tuple<int, int&, int&&, const int> t {5,d,7,8};
    auto& [a1,a2,a3,a4] = t;
    cout << "a1: " << a1 << " - "<< boost::typeindex::type_id_with_cvr<decltype((a1))>().pretty_name() << endl;
    cout << "a2: " << a2 << " - "<< boost::typeindex::type_id_with_cvr<decltype((a2))>().pretty_name() << endl;
    cout << "a3: " << a3 << " - "<< boost::typeindex::type_id_with_cvr<decltype((a3))>().pretty_name() << endl;
    cout << "a4: " << a4 << " - "<< boost::typeindex::type_id_with_cvr<decltype((a4))>().pretty_name() << endl;
}