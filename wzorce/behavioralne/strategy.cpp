#include <iostream>
#include <vector>
using namespace std;
//  /usr/bin/g++-11 -std=c++2a -Wall -O0 -o app strategy.cpp && ./app

//umożliwia zdefiniowanie zestawu algorytmów we własnych klasach i 
//umożliwia w rtuntime wybór używanego algorytmu np na podstawie ustawień usera

struct User { std::string Name; std::string Surname; };

class UsersPrinter{
    virtual bool sortAlgorithm(User a, User b) = 0;
public:
    std::vector<User> users;
    void print(){
        std::sort(users.begin(), users.end(), [this](User& a, User& b){ return sortAlgorithm(a, b);});

        cout << "---------------------------" << endl;
        for(auto& user : users)
            cout << "Name: " << user.Name << ", surname: " << user.Surname << endl;
    };
    virtual ~UsersPrinter(){}
};

class UserPrinterNameASC : public UsersPrinter{
    bool sortAlgorithm(User a, User b) override {
        int nameCompareResult = a.Name.compare(b.Name);

        if (nameCompareResult == 0)
            return a.Surname.compare(b.Surname) < 0;

        return nameCompareResult < 0;
    };
};

class UserPrinterSurnameASC : public UsersPrinter{
    bool sortAlgorithm(User a, User b) override {
        int nameCompareResult = a.Surname.compare(b.Surname);

        if (nameCompareResult == 0)
            return a.Name.compare(b.Name) < 0;

        return nameCompareResult < 0;
    };
};
int main()
{
    UsersPrinter* up = new UserPrinterNameASC();
    up->users.insert(up->users.begin(), {{"Pawel", "Cz"}, {"Karolina", "Dyg"}, {"Robert", "Ad"}, {"Adam", "Ad"}});
    up->print();
    delete up;

    up = new UserPrinterSurnameASC();
    up->users.insert(up->users.begin(), {{"Pawel", "Cz"}, {"Karolina", "Dyg"}, {"Robert", "Ad"}, {"Adam", "Ad"}});
    up->print();
    delete up;
}


