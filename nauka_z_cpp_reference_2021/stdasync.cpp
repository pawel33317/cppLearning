#include <iostream>
#include <future>
#include <list>
using namespace std;

std::list<std::string> strings;
std::mutex g_pages_mutex;

void save_page(const std::string &url)
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    //std::lock_guard<std::mutex> guard(g_pages_mutex);
    strings.push_back(url);
}
 
int mainasync() 
{
    auto future1 =  std::async(save_page, "string a");
    auto future2 =  std::async(save_page, "string b");
    auto future3 =  std::async(save_page, "string c");
    auto future4 =  std::async(save_page, "string d");

    future4.wait();
    future3.wait();
    future2.wait();
    future1.wait();
    
    // safe to access g_pages without lock now, as the threads are joined
    for (const auto &str : strings) {
        std::cout << str << '\n';
    }
}
