
#include <iostream>
#include <memory>
using namespace std;

//  /usr/bin/g++-11 -std=c++2a -Wall -O0 -o app fabryki_i_metody_fabrykujace.cpp && ./app

void w_prostaFabryka();
void w_statycznaFabryka();
void w_metodaFabrykujaca();
void w_fabrykaAbstrakcyjna();

int main()
{
    printf("-----fabryki_i_metody_fabrykujace-----\n");

    //Uzywając New uzależniamy się od konkretnej implementacji a jedna reguła:
    //dependency inversion principle mówi:

    //!!!Uzależniaj kod od abstrakcji a nie rzeczywistych klas

    //kolejna zasada
    //!!!System powinien być otwarty na rozbudowę a zamknięty na modyfikację

            /*
                void doAction(String type) {
                Product product;
                if (type.equals("round")) {
                    product = new RoundProduct();
                } else if (type.equals("square")) {
                    product = new SquareProduct();
                }
                
                product.doSomething();
                product.doSomethingElse();
                //i mnóstwo innych operacji...
                }
            */

    //Powyższy kod jest słaby bo przy rozbudowie programu trzeba będzie zmienić
    //kod powyższego if'a, dodatkowo kod nie jest zamknięty na zmiany, jak
    //będziemy chcieli wywalić produkt lub dodać będziemy musieli zmieniać
    //powyższy kod

    //Rodzaje fabryk
    //Prosta - simple factory
    //Statyczna - static factory
    //Metofda fabrykująca - factory method
    //Fabryka abstrakcyjna - abstract factory

    //dostarcza interfejs do tworzenia różnych obiektow jednego typu
    //bez specyfikowania ich konkretnych klas
    //umożliwia jednemu obiektowi tworzneie innych, powiązanych ze sobą

    w_prostaFabryka();
    w_statycznaFabryka();
    w_metodaFabrykujaca();
    w_fabrykaAbstrakcyjna();
}





class Figura
    { public: virtual void show() const { std::cout << "I am Figura\n"; } 
      virtual ~Figura(){}};
class Kolo : public Figura
    { public: virtual void show() const override { std::cout << "I am Kolo\n"; }
    virtual ~Kolo(){}};
class Kwadrat : public Figura
    { public: virtual void show() const override { std::cout << "I am Kwadrat\n"; }
    virtual ~Kwadrat(){}};
class SimpleFactory
{
public:
    std::unique_ptr<Figura> virtual getFigura(int type)
    {
        if (type == 1)
            return std::make_unique<Kolo>();
        else
            return std::make_unique<Kwadrat>();
    }
};
class FiguraHandler
{
public:
    std::unique_ptr<Figura> f;
    FiguraHandler() = delete;
    FiguraHandler(SimpleFactory&& sf)
    {
        f = sf.getFigura(1);
        f->show();
    }
};
void w_prostaFabryka()
{
    printf("-----w_prostaFabryka-----\n");
    //FiguraHandler fh(SimpleFactory()); //to traktuje jako deklarację czegoś oO

    FiguraHandler fh {SimpleFactory()};
    //Prosta fabryka jest wywoływana bezpośrednio przez klasę, która chce
    //utworzyć obiekt
}




class StaticFactory
{
public:
    std::unique_ptr<Figura> static getFigura(int type)
    {
        if (type == 1)
            return std::make_unique<Kolo>();
        else
            return std::make_unique<Kwadrat>();
    }
};
class FiguraStaticHandler
{
public:
    FiguraStaticHandler()
    {
        auto figura = StaticFactory::getFigura(1);
        figura->show();
    }
};
void w_statycznaFabryka()
{
    printf("-----w_statycznaFabryka-----\n");
    //prosta fabryka mająca metodę statyczną więc nie trzeba robić obiektu
    //fabryki, jednak nie można zastosować dziedziczenia, żeby przekazać
    //dodatkowe parametry w konstruktorze

    //!!!Czyli słabe rozwiązanie !!!

    //np chcielibyśmy dodać możlowośc utworzenia klasy Koło na podstawie kąta
    //np trójkąt, wykorzystując prosta fabrykę możnaby zrobić klasę:
    //TriangleSimpleFactory dziedziczacą po SimpleFactory i przekazać taki obiekt
    //do FiguraHandler

    //łamiemy w fabryce statycznej zasadę
    //!!!staraj się aby współpracujące obiekty były ze sobą luźno powiązane

    FiguraStaticHandler fh {};
}




class FiguraFactoryHandler2
{
public:
    virtual ~FiguraFactoryHandler2(){}
    FiguraFactoryHandler2() {};
    void handle() { Figura f = createFigura(); f.show();}
    virtual Figura createFigura() = 0;//metoda fabrykująca
};
class KoloFiguraFactoryHandler2 : public FiguraFactoryHandler2
{
public:
    virtual ~KoloFiguraFactoryHandler2(){}
    Figura createFigura() override { return Kolo{}; }
};
class KwadratFiguraFactoryHandler2 : public FiguraFactoryHandler2
{
public:
    virtual ~KwadratFiguraFactoryHandler2(){}
    Figura createFigura() override { return Kwadrat{}; }
};
void w_metodaFabrykujaca()
{
    printf("-----w_metodaFabrykujaca-----\n");
    FiguraFactoryHandler2&& fh = KoloFiguraFactoryHandler2{};
    const FiguraFactoryHandler2& fh2 = KoloFiguraFactoryHandler2{};
    fh.handle();
    //gh2.handle();

    //Wzorzec definiuje 2 równoległe hierarhie klas
    //definiuje interfejs pozwalający na tworzenie obiektów, pozwalając klasom podrzędnym
    //decydować jakie będa to obiekty
    //klasy podrzędne odpowiadają za tworzenie obiektu

    //zalety - usunięcie zależności pomiędzy implementacją kodu a jego zastosowaniem
    //hermetyzacja tworzenia obiektów
    //możliwość wprowadzenia wielu metod tworzących obiekty na różne sposoby

    //!!!wykorzystuje dziedziczenie
    //!!!tworzy się metodę abstrakcyjną i implementuję w klasie dziedziczącej
}




class Dzialka { public: virtual void show() = 0; };
class DzialkaDuza : public Dzialka { public: void show() { cout << "DzialkaDuza"; } };
class DzialkaMala : public Dzialka { public: void show() { cout << "DzialkaMala"; } };
class Dom { public: virtual void show() = 0; };
class DomBlizniak : public Dom { public:void show() {cout << "DomBlizniak"; } };
class DomWolnostojacy : public Dom { public:void show() {cout << "DomWolnostojacy"; } };
class Developer {public://fabryka abstrakcyjna
    virtual unique_ptr<Dom> createDom() = 0;
    virtual unique_ptr<Dzialka> createDzialka() = 0;};
class DeveloperViralex : public Developer {public:
    unique_ptr<Dom> createDom() override { return make_unique<DomWolnostojacy>(); }
    unique_ptr<Dzialka> createDzialka() override { return make_unique<DzialkaDuza>(); } };
class DeveloperUnigrup : public Developer {public:
    unique_ptr<Dom> createDom() override { return make_unique<DomBlizniak>(); }
    unique_ptr<Dzialka> createDzialka() override { return make_unique<DzialkaMala>(); } };
class Nieruchomosc
{
    int mId;
    unique_ptr<Dom> mDom;
    unique_ptr<Dzialka> mDzialka;
public:
    Nieruchomosc(int id, Developer& dev)
    {
        mId = id;
        mDom = dev.createDom();
        mDzialka = dev.createDzialka();
    }
    void show()
    {
        cout << "Nieruchomosc id: " << mId << ", dom: ";
        mDom->show();
        cout << ", dzialka: ";
        mDzialka->show();
        cout << endl;
    }
};

void w_fabrykaAbstrakcyjna()
{
    printf("-----fabrykaAbstrakcyjna-----\n");
    //idea - tworzenie rodzin spokrewnionych obiektów
    //uzależnienie od abstrakcji a nie implementacji klas

    //wiele możliwych implementacji:
    /*1:
        Posiada 2 metody zwracające obiekty tego samego typu ale są niezależne Np:
        Samochod Audi, Samochod Fiat
        interface FiguraFactory {
            Figura createFiguraKolo();
            Figura createFiguraKwadrat();
        }

        Jak trzeba dodać nowy samochod BMW lepiej zmienić matody na jedną parametryzującą
        interface FiguraFactory {
            Figura createFigura(TypeEnum){}
        }

        Nowa funkcja jest szkieletem metody fabrykujacej
    */

    /*2:
        Tworzenie produktów, które są od siebie zależne
        Tal aby powstał produkt finakny składający się z produktow A i B

        interface {
            PolePowierzchni createPolePowierzchni();
            Obwod createObwd();
        }
    */

    /*3:
        hybrydy
        interface ProductFactory {
            ProductA createProductA(ProductAVersionEnum);
            ProductB createProductB(ProductBVersionEnum);
        }
    */

    DeveloperUnigrup du{};
    DeveloperViralex dv{};
    Nieruchomosc n1 {1, du};
    Nieruchomosc n2 {2, du};
    Nieruchomosc n3 {3, dv};
    n1.show();
    n2.show();
    n3.show();
}