#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
using namespace std;

//  /usr/bin/g++-11 -std=c++2a -Wall -O0 -o app obserwator.cpp && ./app


class Obserwator
{
public:
    virtual void update(const std::string& info) = 0;
};

class Obserwowany //to może być interfejs i dać ciało w klasie
{
    vector<Obserwator*> obserwatorzy;
public:
    virtual void dodajObserwatora(Obserwator* o)
    {
        obserwatorzy.push_back(o);
    }
    virtual void usunObserwatora(Obserwator* o)
    {
        std::remove(obserwatorzy.begin(), obserwatorzy.end(), o);
    }
    virtual void powiadomObserwatorow(string s)
    {
        std::for_each(obserwatorzy.begin(), obserwatorzy.end(),
            [&s](Obserwator* o){ o->update(s); });
    }
    virtual ~Obserwowany(){};
};
class Telewizja : public Obserwowany
{
public:
    void generateNews(string s)
    {
        powiadomObserwatorow(s);
    }
};

class ObserwatorCzlowiek : public Obserwator
{
    string mName;
public:
    explicit ObserwatorCzlowiek(const string& name) : mName(name){}
    void update(const string& info) override {
        cout << mName << " otrzymal info: " << info << endl;
    }
};

int main()
{
    printf("-----w_obserwator-----\n");
    //służy do powiadamiania zainteresowanych obiektów o zmianie
    //stanu innego obiektu

    //w programowaniu obiektowym obiekty posiadają pewien stan - zbiór wartości pól
    //obiektu, od czego mogą zależeć inne obiekty, więc musi istnieć możliwość
    //ich powiadomienia

    //obserwowany - obiekt o którym chcemy uzyskać informacje
    //obserwwator - obiekt oczekujący na powiadomienie o zmianie stanu obserwowanego

    //Zalety
    //luźna relacja między obserwatorem a obserwowanym
    //relacja pomiędzy obserwatorem a obserwowanym tworzona jest na etapie
        //wykonywania programu więc może być zmieniana
    //domyslnie powiadomienie otrzymują wszystkie obiekty, obserwowany jest
        //zwolniony z zarządzania subskrypcją

    //Wady
    //obserwatorzy nie znają obserwatorów co w pewnych sytuacjach może wywołać
        //trudne do znalezienia skutki

    //Często używane w aplikacjach z GUI

    ObserwatorCzlowiek oc{"Pawel"};
    ObserwatorCzlowiek oc2{"Piotr"};
    Telewizja tv;
    tv.dodajObserwatora(&oc);
    tv.dodajObserwatora(&oc2);
    tv.generateNews("Wybrano nowego papieza");
    tv.generateNews("Tadeusz T. okazał się kobietą");
}

