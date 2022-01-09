#include <iostream>
#include "all.hpp"

void dziedziczenie();
void konstruktoryIInicjalizacja();
void specyfikatoryDostepu();
void dodanieNowejFunkcjonalnosciIwywolywanieDziedziczonychFunkcjiIoverriding();
void ukrywaniePokazanieOdziedziczonejFunkcjonalnosci();
void wielodziedziczenie();

void t_11_inheritance()
{
    std::cout << "n\n-----chapter 11 started-----\n";
    dziedziczenie();
    konstruktoryIInicjalizacja();
    specyfikatoryDostepu();
    dodanieNowejFunkcjonalnosciIwywolywanieDziedziczonychFunkcjiIoverriding();
    ukrywaniePokazanieOdziedziczonejFunkcjonalnosci();
}


class Base
{
public:
    int i = 5;
    Base() { std::cout << "Base constructor\n"; }
    ~Base() { std::cout << "Base destructor\n"; }
    void printName() { std::cout << "Base class printName method\n";}
};
class Derived : public Base
{
public:
    Derived() { std::cout << "Derived constructor\n"; }
    ~Derived() { std::cout << "Derived destructor\n"; }
    void printName() { std::cout << "Derived class printName method\n";}
};
void dziedziczenie()
{
    //inny sposób obok kompozycji do tworzenia złożonych klas
    //is a
        //uzyskanie metod i pól z innych klas i ich rozszerzenie

    //hierarchia pokazuje połączenia obiektów
        //można dziedziczyć z klas które już dziedziczą z klas

    {
        Base b;
        b.printName();
    }

    std::cout << "1========================================\n";
    {
        Derived d; d.printName();
    }

    std::cout << "2========================================\n";
    Derived* d2 = new Derived();
    d2->printName();
    delete d2;

    std::cout << "3========================================\n";
    Base* b2 = new Derived();//Wywola sie z base bez polimorfizmu
    b2->printName();
    delete b2;//BRAK WYWOLANIA DESTRUKTORA KLASY POCHODNEJ

    std::cout << "4========================================\n";
    Derived d4;
    Base* b3 = &d4;
    d4.printName(); //z derived
    b3->printName();//z base
    t_nicNieRob(b3);
    //delete b3; -> nie wolno bo jest na stosie
    //Derived* d5 = new Base(); 
        //Derived to nie base => czlowiek to nie sportowiec

    //!!!klasa derived w rzeczywistości nie jest klasą base a składa się z dwóch
        //części: Base part oraz Derived part

    //C++ tworzy obiekty które dziedziczą po innej klasie w fazach
        //1: most-base class jest konstruowana jako pierwsza
        //2: tworzona jest każda kolejna dziedzicząca klasa w kolejności
}

using namespace std;
class Base1Member{ public:
    Base1Member(){cout << "Base1Member Constructor\n";}
    ~Base1Member(){cout << "Base1Member Destructor\n";}};
class Base1LocalConstructorVariable{ public:
    Base1LocalConstructorVariable()
        {cout << "Base1LocalConstructorVariable Constructor\n";}
    ~Base1LocalConstructorVariable()
        {cout << "Base1LocalConstructorVariable Destructor\n";}};
class Derived1Member{ public:
    Derived1Member(){cout << "Derived1Member Constructor\n";}
    ~Derived1Member(){cout << "Derived1Member Destructor\n";}};
class Derived1LocalConstructorVariable{ public:
    Derived1LocalConstructorVariable()
        {cout << "Derived1LocalConstructorVariable Constructor\n";}
    ~Derived1LocalConstructorVariable()
        {cout << "Derived1LocalConstructorVariable Destructor\n";}};

class Base1
{
    Base1Member b1;
    public:
    Base1() : b1(Base1Member())
    {
        cout << "Base1 constructor start\n"; 
        Base1LocalConstructorVariable blcv1;
        cout << "Base1 constructor end\n"; 
    }
    ~Base1(){cout << "Base1 destructor\n"; }
};
class Derived1 : public Base1
{
    Derived1Member d1m;
public:
    Derived1() : Base1(), d1m(Derived1Member())
    {
        cout << "Derived1 constructor start\n"; 
        Derived1LocalConstructorVariable blcv1;
        cout << "Derived1 constructor end\n"; 
    }
    ~Derived1(){cout << "Derived1 destructor\n"; }
};
void konstruktoryIInicjalizacja()
{
    std::cout << "-----------------konstruktoryIInicjalizacja\n\n";
    //Base1 b;
        //Przy obiekcie nie dziedziczącym kolejność
        //1. odkładanie miejsca dla base
        //2. wywołanie odpowiedzniego konstruktora
        //3. Inicjalizacja zmiennych z listy inicjalizacyjnej
        //4. wykonanie konstruktora
        //5. zrwócenie kontroli

    //Derived1 d;
        //1: odkładanie miejsca na Base i Derived (naraz)
        //2: wywołanie konstruktora Derived !!!
        //3: konstruowanie obiektu Base przy użyciu konstruktora Base !!!
        //4: inicjalizacja zmiennych z listy inicjalizacyjnej
        //5: wykonanie ciała konstruktora
        //6: zwrócenie kontroli -> poniżej lepsze rozpisanie

    //!!!nie można inicjalizować zmiennych klasy base w derived
        //bo musi być zainicjalizowany podczas tworzenia a konstruktor
        //derived odpala się po base, więc derived nie ma możliwości inicjalizacji
        //memberów klasy base

    //Kolejność z listą inicjalizacyjną i wywołaniem konkretnego konstruktora
        //1. Alokacja pamięci na Base i derived
        //2. Wywkołanie konstruktora Derived //Derived(a,b) : Base(a)
        //3. Znalezienie przez kompilator zdefiniowanego wywołania konstruktora Base
            //wywołanie konstruktora Base z parametrem a
        //4. Base konstruktor inicjalizuje zmienne (a)
        //5. Wykonanie ciała konstruktora Base
        //6. Wyjście z konstuktora Base
        //7. Derived inicjalizuje zmienne z listy inicjalizacyjnej (b)
        //8. Wykonanie ciała konstriktora Derived
        //9. Wyjście z konstruktora Derived

    //!!!konstruktory mogą wywoływać konstruktory tylko swojego rodzica (lub swoje)
    //!!!np C nie może wykonać konstruktora A jeżeli jest B pomiędzy

    //!!!Destruktory są wywoływane w odwrotnej kolejności

    {
        Derived1 d;
    }
    /*
        1 Base1Member Constructor
        2 Base1 constructor start
        3 Base1LocalConstructorVariable Constructor
        4 Base1 constructor end
        5 Base1LocalConstructorVariable Destructor
        6 Derived1Member Constructor
        7 Derived1 constructor start
        8 Derived1LocalConstructorVariable Constructor
        9 Derived1 constructor end
        10 Derived1LocalConstructorVariable Destructor
        11 Derived1 destructor
        12 Derived1Member Destructor
        13 Base1 destructor
        14 Base1Member Destructor
    */
}



void specyfikatoryDostepu()
{
    //SPECYFIKATORY DOSTEPU
        //public dostępne dla wszystkich
        //private tylko member funkcje i friend więc Derived klasy nie
        //protected widoczne dla memberów, friend oraz klas Derived
            //stosowane głównie jak klas bazowych jest mało i nie chce się
            //robić publicznego interfejsu

    //TYPY DZIEDZICZENIA: public, private, protected
        //domyślnie private
        //zmieniają specyfikator dostępu mamberów klasy bazowej

    //Dziedziczenie publiczne
        //public base member -> public
        //protected base member -> protected
        //private -> inaccessible

    //!!!używać publicznego dziedziczenia

    //Dziedziczenie private
        //protected -> private
        //public -> private
        //private -> inaccessible
        //!!!ale klasa bazowa ma i tak do tego dostęp jedynie jest
            //niewidoczne na zewnątrz
        //!!!rzadko używane, jak chcemy ukryć publiczny interfejs base

    //Dziedziczenie Protected
        //nieużywane raczej
        //public, protected -> protected
        //private -> inaccessible

    //Klasa c dziedzicząc publicznie po b nie ma dostępu do
        //memberów publicznych a jeżeli b dziedziczyło po a prywatnie

    //Klasa i friendy mają zawsze dostęp do memberów niedziedziczonych
    //!!!Specyfikator dostępu wpływa jedynie na zewnętrzne
        //wywołania i klasy dziedziczące

    //klasa dziedzicząca może zmieniać specyfikator dla memberów klasy bazowej
        //sama ma i tak do tego dostęp jedynie zewnętrzne wywołania
        //i klasy dziedziczące mogą utracić
}



class Base2
{
public:
    void identify() { cout << "I am Base\n"; }
};
class Derived2 : public Base2
{
public:
    void identify()
    {
        Base2::identify();//wywołanie metody z klasy bazowej
        cout << "I am Derived\n";
    }
};
void dodanieNowejFunkcjonalnosciIwywolywanieDziedziczonychFunkcjiIoverriding()
{
    //dziedziczy się czesto ze stadardowych bibliotek czy też 3rd kodu
        //bo nie można go zmieniać lub nie warto bo mogą przyjść poprawki

    //Obiekt klasy bazowej nie ma dostępu do memberów dodanych
        //w klasie dziedziczacej

    //!!!WYWOLANIE ODZIEDZICZONEJ METODY NA KLASIE DERIVED
        //!!!kompilator sprawdza czy nie ma tekigo membera najpierw
            //w klasie derived
        //jak nie ma idzie w górę w łańcuchu dziedziczenia
        //używa pierwszą, którą znajdzie

    //!!!Redefinicja metody w klasie DERIVED jest robiona aby zmienić
        //zachowanie tej metody

    //!!!Metody redefiniowane (overridowane) nie dziedziczą specyfikatora dostępu
        //!!!z klasy bazowej a nadają im własny, więc można zrobić z public
        //private i odwrotnie
    cout << "----------------------------\n\n";
    Base2 b2;
    b2.identify();
    Derived2 d2;
    d2.identify();
}



class Base3
{
    void privateBaseFunc() {cout << "privateBaseFunc\n";}
protected:
    void protectedBaseFunc() {cout << "protectedBaseFunc\n";}
public:
    int public_base_variable;
    void base_public_function(){}
};
class Derived3 : public Base3
{
    //using Base3::privateBaseFunc; -> nie zadziała

public: //OKRESLA TU SPECYFIKATOR DLA USINGA !!!
    //UGING DEKLARACJA
    using Base3::protectedBaseFunc;
        //!!! UWIDACZNIA PROTECTED METODE DO PUBLIC !!!
    //można też bez słówka using ale niezalecane bo robi overrida i deprecated

    //UKRYWANIE
private:
    using Base3::public_base_variable;

    void base_public_function() = delete;

    void test(){
        cout << public_base_variable;
            //po using dalej dostępna wewnętrznie

        //base_public_function(); 
            //ERROR po delete nie dostępna wewnętrznie
        Base3::base_public_function();
            //ale dostępna przez base
    }
};
void ukrywaniePokazanieOdziedziczonejFunkcjonalnosci()
{
    //Pokazanie funkcjonalności protected z base
    Derived3 d3;
    d3.protectedBaseFunc();

    //Ukrycie funkcjonalności z base
        //d3.public_base_variable; -> UKRYTA
        //d3.base_public_function(); -> skasowana
}



class Base10 {public: int getID() {return 10;}};
class Base20 {public: int getID() {return 20;}};
class Derived1020 : public Base10, public Base20 {};
class Derived21020 : public Base10, public Base20
{ public: int getID() {return Base10::getID();} };

class DaimondBase { public: int valA; };
class DaimondLeft : public DaimondBase {};
class DaimondRight : public DaimondBase {};
class DaimondDerived : public DaimondLeft, public DaimondRight {};
void wielodziedziczenie()
{
    //duże problemy -> ambigous wywołanie funkcji, jeżeli chcemy wywołać metodę 
        //np getID() a obie klasy bazowe ją mają
    Derived1020 d1020;
        //d1020.getID(); //AMBIGOUS
    t_nicNieRob(&d1020);

    Derived21020 d21020;
    d21020.getID();
        //wykonuje specjalnie dodaną funkcję w derived przesłaniającą basey
    d21020.Base20::getID();//precyzuje którą wersję wywołać

    //problemy z konfliktami nazw

    //problem diamentowy
    DaimondDerived dd;
    t_nicNieRob(&dd);
    //cout << dd.valA; DWUZNACZNE
        //problem rozwiązuje virtual dziedziczenie, będzie o tym później

        //większość problemów rozwiązywalnych przez wielodziedziczenie jest też
            //możliwe do rozwiązana przez jednoDziedziczenie

        //wielodziedziczenie komplikuje bardzo kod i zrozumienie

    //!!!unikać wielodziedziczenia
}
