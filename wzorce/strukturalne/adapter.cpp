#include <iostream>
#include <memory>
#include <string>
using namespace std;

//  /usr/bin/g++-11 -std=c++2a -Wall -O0 -o app adapter.cpp && ./app

struct IDevice{
    virtual void on() = 0;
    virtual ~IDevice() = default;
};

struct Client{
    void work(IDevice&& device){
        device.on();
    }
};

struct NewDevice : public IDevice{
    void on() override{
        cout << "Włączam nowe urządzenie\n";
    }
};

struct OldDevice{ //no connection with IDevice
    void start(){
        cout << "Włączam stare urządzenie";
    }
};

struct OldDeviceAdapter : public IDevice{
    void on() override{
        OldDevice().start();
    }
};

int main()
{
    Client c;
    c.work(NewDevice());
    //c.work(OldDevice()); ERROR
    c.work(OldDeviceAdapter());
}
