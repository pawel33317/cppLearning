#include <iostream>
#include <memory>
#include "../../helper.hpp"
using namespace std;

//  /usr/bin/g++-11 -std=c++2a -Wall -O0 -o app fabrykaAbstrakcyjna.cpp && ./app

// umożliwia stworzenie grupy powiązanych obiektów bez konieczności określenia konkretnej klasy,
// która będzie używana, klasy używane są definiowane w runtime

struct Packaging {//AbstractProduct baza dla wszystkich produktów, jedna baza dla każdego odrębnego produktu
    virtual std::string operator()() = 0;
};
struct StandardPackaging : Packaging {//ConcreteProduct rzeczywisty produkt tworzony przez fabrykę
    std::string operator()(){ return "Standardowe opakowanie"; }
};
struct DelecatePackaging : Packaging {
    std::string operator()(){ return "Odporne na uderzenia opakowanie"; }
};

struct DeliveryDocument {
    virtual std::string operator()() = 0;
};
struct ParcelLockerDeliveryDocument : DeliveryDocument {
    std::string operator()(){ return "dokument do paczkomatu"; }
};
struct CourierDeliveryDocument : DeliveryDocument {
    std::string operator()(){ return "dokument dla kuriera"; }
};

struct PurchaseFactory {//AbstractFactory - baza dla konkretnych fabryk, metoda dla każdego typu obiektu, który będzie robiony
    virtual std::unique_ptr<Packaging> CreatePackaging() = 0;
    virtual std::unique_ptr<DeliveryDocument> CreateDeliveryDocument() = 0;
    virtual ~PurchaseFactory(){}
};

struct StandardPurchaseFactory : PurchaseFactory {//ConcreteFactory dostarcza rzeczywiste obiekty
    std::unique_ptr<Packaging> CreatePackaging() override {
        return make_unique<StandardPackaging>();
    }
    std::unique_ptr<DeliveryDocument> CreateDeliveryDocument() override {
        return make_unique<ParcelLockerDeliveryDocument>();
    }
};

struct DelecatePurchaseFactory : PurchaseFactory {//ConcreteFactory dostarcza rzeczywiste obiekty
    std::unique_ptr<Packaging> CreatePackaging() override {
        return make_unique<DelecatePackaging>();
    }
    std::unique_ptr<DeliveryDocument> CreateDeliveryDocument() override {
        return make_unique<CourierDeliveryDocument>();
    }
};

struct Client{//Client of factory - używa fabryki do generowania obiektów
    std::unique_ptr<Packaging> mPackaging;
    std::unique_ptr<DeliveryDocument> mDeliveryDocument;
    Client(PurchaseFactory& purchaseFactory) : 
        mPackaging(purchaseFactory.CreatePackaging()),
        mDeliveryDocument(purchaseFactory.CreateDeliveryDocument())
    {
    }
};

int main()
{
    StandardPurchaseFactory standardPurchaseFactory;
    DelecatePurchaseFactory delecatePurchaseFactory;
    Client client1 {standardPurchaseFactory};
    Client client2 {delecatePurchaseFactory};

    cout << "Client 1: " << (*client1.mPackaging)() << " - " << (*client1.mDeliveryDocument)() << endl;
    cout << "Client 2: " << (*client2.mPackaging)() << " - " << (*client2.mDeliveryDocument)() << endl;
}