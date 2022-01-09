#include <iostream>
#include <memory>
#include <vector>
using namespace std;

// /usr/bin/g++-11 -std=c++2a -Wall -O0 -o app dekorator.cpp && ./app

class Figura_WD //Interface
{
public:
    virtual void rysuj() = 0;
    Figura_WD() { cout << "Tworze figura" << endl; }
    virtual ~Figura_WD(){ cout << "Figura zniszczona" << endl; }
};

class Prostokat_WD : public Figura_WD //Konkretna klasa
{
public:
    void rysuj() override
    {
        cout << "Figura: prostokat" << endl;
    }
    virtual ~Prostokat_WD(){}
};

class Kolo_WD : public Figura_WD
{
public:
    void rysuj() override
    {
        cout << "Figura: kolo" << endl;
    }
};

class FiguraDekorator_WD : public Figura_WD //Abstrakcyjny dekorator
{                                           //nie jest potrzebny często
protected:
    shared_ptr<Figura_WD> dekorowanaFigura;
public:
    FiguraDekorator_WD(shared_ptr<Figura_WD> figura)
    {
        dekorowanaFigura = figura;
    }
    void rysuj() override
    {
        dekorowanaFigura->rysuj();
    }
};

class NiebieskaFiguraDekorator_WD : public FiguraDekorator_WD
{
public:
    NiebieskaFiguraDekorator_WD(shared_ptr<Figura_WD> f)
    : FiguraDekorator_WD(f) {}

    void rysuj() override
    {
        dekorowanaFigura->rysuj();
        setNiebieskieObranowanie();
    }
    void setNiebieskieObranowanie()
    {
        cout << "Ustawiam niebieskie obranowanie" << endl;
    }
};

int main()
{
    cout << "-----w_dekorator-----\n";
    //pozwala na dynamiczne dodanie nowej funkcjonalności w trakcie
    //działania programi

    //polega na opakowaniu klasy w nową klasę dekorującą,
    //zwykle przekazuje się oryginalny obiekt jako parametr konstruktora

    //alternatywa dla dziedziczenia
    //wykorzystuje kompozycję

    //np klasa okno (dla gui), chcemy mieć okno z ramką i okno
    //z paskiem przewijania, trzeba by dużo klas bo dużo kombinacji

    //ZALETY
    //większa elastyczność niż dziedziczenie
    //pozwala uniknąć tworzenia przeładowanych funkcji klas
        //na wysokim poziomie hierarchii
    //dekorator i powiązany z nim komponent nie są identyczne
    //powstaje wiele małych obiektów

    shared_ptr<Figura_WD> kolo {make_shared<Kolo_WD>()};
    shared_ptr<Figura_WD> niebieskieKolo {
        make_shared<NiebieskaFiguraDekorator_WD>(
            make_shared<Kolo_WD>()
        )};

    shared_ptr<Figura_WD> niebieskiProstakat {
        make_shared<NiebieskaFiguraDekorator_WD>(
            make_unique<Prostokat_WD>()
        )};

    cout << "----------" << endl;
    kolo->rysuj();
    cout << "----------" << endl;
    niebieskieKolo->rysuj();
    cout << "----------" << endl;
    niebieskiProstakat->rysuj();
    cout << "----------" << endl;
}