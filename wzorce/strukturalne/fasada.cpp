
#include <iostream>
#include <memory>
#include <string>
using namespace std;

// /usr/bin/g++-11 -std=c++2a -Wall -O0 -o app fasada.cpp && ./app



class CPU {
public:
    void run(){ cout << "Starting CPU..." << endl; }
};
class Memory {
public:
    void runRam(){ cout << "Starting Ram memory..." << endl; }
    void runSSD(){ cout << "Starting SSD drive..." << endl; }
};
class Motherboard {
public:
    void run(){ cout << "Starting Motherboard..." << endl; }
};

class ComputerApiFacade
{
    string mName;
    CPU mCPU{};
    Memory mMemory{};
    Motherboard mMotherboard{};
public:
    explicit ComputerApiFacade(string name) : mName(name)
    {
        cout << "Computer created, name: " << mName << endl;
    }
    void start()
    {
        mMotherboard.run();
        mMemory.runRam();
        mCPU.run();
        mMemory.runSSD();
    }
};

int main()
{
    cout << "-----w_fasada-----" << endl;

    //tworzymy klasę, której zadaniem jest wywoływanie odpowiednich metod
    //z innych klas

    //służy do ujednolicenia interfejsu do systemu poprzez wystawienie uproszczonego
    //ujednoliconego intergejsu

    //złożony system jest reprezentowany przez fasadę czyli klasę z referencjami
    //do elementów złożonego systemu a klient wykorzystuje dasadę aby wywołać coś
    //na złożonym systemie

    //Zalety
    //zmiejszenie liczby zależności między systemem a klientem
    //wprowadzenie podziału aplikacji na warstwy ułatwia niezależny rozwój
        //klienta i serwera
    //możliwość zablokowania kllientowi bezpośredniego korzystania ze
        //złożonego systemu
    //kod klienta jest czytelniejszy i łatwiejszy w zrozumieniu

    ComputerApiFacade facade("Smok");
    facade.start();
}


