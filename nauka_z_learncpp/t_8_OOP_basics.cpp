#include <iostream>
#include "all.hpp"

void klasy();
void konstruktory();
void listaInicjalizacyjnaKonstruktora();
void wywolanieKonstruktorawKonstruktorze();
void destruktory();
void thisHiddenPtr();
void klasywCppiHpp();
void constKlasy();
void staticMember();
void staticMethod();
void friendKlasy();
void obiektyAnonimowe();
void obiektyAnonimowe2();
void typyZagniezdzone();
void czasWykonaniaKoduChrono();


void t_8_OOP_basics()
{
    std::cout << "\n\n-----chapter 8 started-----\n";
    klasy();
    konstruktory();
    wywolanieKonstruktorawKonstruktorze();
    destruktory();
    thisHiddenPtr();
    klasywCppiHpp();
    constKlasy();
    staticMember();
    staticMethod();
    friendKlasy();
    obiektyAnonimowe();
    obiektyAnonimowe2();
    typyZagniezdzone();
    czasWykonaniaKoduChrono();
}

class A
{
private:
    int z;
public:
    A(int val) : z(val) {};
    void printZ(){printf("private z = %d\n",z);};
    void printZ(A a){printf("private z z innego obiektu = %d\n",a.z);};
    void listaInicjalizacyjnaKonstruktora();
};
void klasy()
{
    //średnik na końcu
    //używać m_ prefix  dla memberów ...
    //!!!nazwu klas z dużych liter
    //struct i class to to samo w c++ poza public/private access specifier
    //oraz struktury dziedziczą publicznie a klasu prywatnie

    //!!!używać struct tylko do danych
    //vector, string, array ... to klasy

    //!!!robić zmienne prywatne
    //access controll np private, public działa na klasach a nie obiektach
    //!!!więc funkcja, która ma dostęp do prywatnych pól ma też dostęp do tych pól
        //dla innego obiektu, dobre do kopiowania

    A a {22};
    a.printZ();
    A b {33};
    a.printZ(b);//ma dostęp do prywatnych pól innego obiektu

    //enkapsulacja - ukrywanie szczegółów przed użytkownikiem i udostępnianie
        //tylko publicznego interfejsu

    //ograniczać dostęp do funkcji jeżeli niepotrzebny
    //!!!getter powinny zwracać przez vartość lub const reference a nie
        //przez non-const ref
}



class C {
public:
    C(int g){printf("Wykonuje sie konstruktor\n");}
    void metoda() const {}; //constowy obiekt wywola constowa metode
};
class E {
public:
    E(){printf("E constructor\n");}
    E(const E& e){printf("E constructor kopiujacy\n");}//nie copy initialization
};
class FconstinsE{
public:
    E e;
    FconstinsE(){printf("FconstinsE constructor\n");};
    FconstinsE(const E& ee) : e(ee) {printf("FconstinsE constructor\n");};
};
void konstruktory()
{
    //!!!jak zmienne są prywatne nie zadziała initializer list ani
        //uniform initialization

    //konstruktor ma nazwe klasy i brak typu zwracanego
    //!!!default construktor, bezparametrowy

    C c{4};//!!!uniform initialization odpala konstruktor
    //!!!używać direct lub uniform initialization dla klas

    C e(5); //direct initialization

    C q = C(55);//copy initialization CHUJNIA
    C d = 7;//copy initialization CHUJNIA
    //odpali  C d = C(7) -> bedzie konwertowal do klasy C
    //!!!copy initialization dla klas może być wolniejsza !!!

    //!!!nie używać copy initialization

    C g = c;//konstruktor kopiujący wciąż istnieje
    t_nicNieRob(&d);
    t_nicNieRob(&g);
    t_nicNieRob(&q);

    E ee;//odpala konstruktor domyslny czyli bezparametrowy

    //!!!jak napiszemy dowolny konstruktor domyślny się nie wygeneruje
    //!!!ale copy constructor move constructor i assigmenty tak

    //!!!zawsze podawać konstruktor nawet jak jest pusty

    printf("=====1\n");
    FconstinsE f;//wykona konstruktor E a później konstruktor FconstinsE
    printf("=====2\n");

    FconstinsE f2{ee};
    //wykona konstruktor kopiujący E a później konstruktor FconstinsE
    //jeżeli nie było by listy inicjalizujątej wywołałby się domyślny konstruktor

    //!!!najpierw inicjalizowane są zmienne później wykona się konstruktor

    //!!!konstruktor nie tworzy obiektu tylko kompilator
    //konstruktor służy do inicjalizacji obiektów i umożliwia stworzenie obiektu
    //!!!klasa bez publicznych konstruktorów nie może zostać utworzona
}



class PP
{
public:
    PP(double p){}
};
class QQ
{
public:
    const int a;
    const int arr[5];
    PP p;


    //!!! int g2(44); direct initialization nie zadziała
    int g1 = 44;//od C++11 
    int g {44};//od C++11 
    //!!!jeżeli będzie na liście inicjalizacyjnej g() to konstruktor
        //pominie wartość domyślną
    //!!!używać wartości domyślnych, konstruktor ich użyje

    QQ(int i) : a{i}, arr{1,2}, p(3.14) {};
        //przed c++11 działało tylko {} do zerowania

    //są inicjalizowane w kolejności deklaracji w klasie najpierw a -> arr -> p
    //!!!dobrze dać je na liście w tej samej kolejności
};
void listaInicjalizacyjnaKonstruktora()
{
    QQ q{55};
    //!!!uzywac list inicjalizacyjnych zamiast przypisania
}


class WW
{
    int z = 5;
public:
    WW(){printf("WW empty\n");}
    WW(int) : WW() {printf("WW int\n");}
        //od C++11 constructor delegatings
    //WW(bool) : WW(), z(4) {} //nie można zainicjalizowac pola bo
        //delegujemy konstruktor
    WW(double) {WW(); printf("WW double\n");}
        //od C++11 -> nie robić tak, lepiej lista inicjalizacyjna
};

void wywolanieKonstruktorawKonstruktorze()
{
    WW ww(0);
    //!!!przed c++11 nie wolno bylo wywolywac konstruktora w konstruktorze
        //tworzylo to tymczasowy obiekt i go inicjalizowało i odrzucało
        //a oryginalny obiekt zostawał niezmieniony

    //przed c++11 trzeba użyć np:
        //funkcji "init" którą wykonają oba konstruktory
        //albo parametrów domyślnych

    //!!!wywołanie konstruktora klasy z metody -> undefined behavior

    //!!!konstruktor który odpala inny konstruktor nie może inicjalizować pól
    //!!!można zapętlić delegowanie konstrukrowów a->b b-> ale stack overflow
}




class AAA
{
    int* i;
public:
    AAA(): i (new int[10]) {printf("Konstruktor\n");}
    ~AAA(){delete[] i;printf("Destruktor\n");}
};

void destruktory()
{
    printf("===========destruktory\n");
    //!!!tylko jeden dla klasy
    {
        AAA aaa;
    }

    //!!! RAII -> technika programowania w której użycie zasobu jest powiązane
        //z czasem życia obiektu z obiektem z automatycznym czasem trwania
    //Zasób jest pozyskiwany w konstruktorze new, i zwalniany w destruktorze delete
        //zapobiega wyciekom pamięci, zasobów

    //Obiekty trzymające zasoby nie powinny być tworzone dynamicznie

    //!!!używać RAII

    //przy exit() -> nie wywołają się destruktory trzeba to obsłużyć
}



class EE
{
    int mId;
    int index;
    int mSuma {0};
public:
    int getSuma(){return mSuma;}

    void setID(int id){ mId = id;}
    //powyższa funkcja jest konwertowana przez kompilator do
    // void setID(EE* const this, int id) { this->mId = id;};

    void setIndex(int index){ this->index = index;}
    //!!!nie używać this w klasach chyba że konieczne

    EE& dodaj(int val) {mSuma+=val; return *this;}
    //!!!w tym wypadku robienia łańcucha można używać "this"
    //!!!analogicznie działą std::cout
};
void thisHiddenPtr()
{
    EE eee;
    eee.setID(444);
    //!!!kompilator zamieni powyższą funkcję na:
    //setID(&instance, 444);

    //kompilator dodaje niejawnie do każdej metody parametr
        //-> constowy wskaźnik "this"
        //który trzyma adres do obiektu metody na którym została wykonana
        //kompilator zamienia odniesienia do pól w metodach
            //mId = 3; ==> this->mId = 5

    //*this nie zużywa pamięci w klasie, jedynie przy wywołaniu metody
    //ponieważ jest odkładany na stosie

    //this jest dokładany tylko do non-static metod
    //this to constowy pointer

    eee.dodaj(5).dodaj(44).dodaj(-33);
    printf("Suma to: %d\n", eee.getSuma());
}



void klasywCppiHpp()
{
    //One definition rule:
        //w każdej jednostce translacji np funkcja, obiekt, templatka może mieć
        //tylko jedną definicję i wiele deklaracji

    //inline funkckcje są wyłączone z one definition rule bo to nie funkcje

    //w programie obiekty lub non-inline functions nie mogą mieć więcej
        //niż jednej definicji

    //deklaracja klasy w headerze o nazwie klasy i dodatkowo header guardy
    //definicje w cpp o nazwie klasy

    //umieszczenie dużego kodu metody w cpp powoduje:
        //duży rozmiar hpp
        //bądą inline ...
        //zmiana czegokolwiek w hpp będzie wymagała przekompilowania
            //innych które ją includują
        //jak zmienimy cpp to tylko ten cpp będzie rekompilowany

    //!!!paramery domyślne dla metod powinny być w defunicji metody w hpp

    //includowanie standardowych bibliotek np jest potrzebne aby kompilator
    //zwalidował czy program jest składniowio poprawny, ich implementacja jest
    //w prekompilowanym pliku i jest dołączana do kompilacji, nie zobaczymy kodu

    //3rd company często nie dołączają cpp tylko prekompilowane biblioteki i hpp
    // -> szybsze do zlinkowania, nie wymaga kompilacji
    // -> aby ludzie nie kradli kodu
}



class RR
{
public:
    int z;
    RR(int initVal) : z(initVal) {}
    const int& getZ() const { return z; }
    int& getZ() { return ++z; }
    //void setZ(int zz) const { z = zz; };
        //nie skompiluje sie bo modyfikuje member var
    void setZ(int zz) { z = zz; }
    int setZ(int zz, double b) { z = zz; return 0; }
        //ovewrloadowane fun mogą mieć inne typy
};
class GG
{
public:
    const int a;
    //const int b; 
        //jeżeli b byłoby const byłaby wymagana inicjalizacja w konstruktorze
    int b;
    GG(int abc) : a(44) {}
};
void constKlasy()
{
    //!!!const member funkcja gwarantuje że nie modyfikuje obiektu
        //i nie wywołuje non-const metod

    //jeżeli funkcja ma definicje w pliku cpp const ma być
        //dodane do obu hpp i cpp

    //konstruktor nie może być const bo inicjalizuje pola
    //const obiekt nie musi inicjalizować wszystkich pól jak zwykły
    const RR rr(123);
    GG gg {8};
    printf("niezainicjalizowany member a: %d\n", gg.a);
    printf("niezainicjalizowany member b: %d\n", gg.b);

    //!!!jak metoda nic nie zmienia robić ją const

    //częściej niż tworzenie const obiektów przekazuje się zwykłe
        //jako const referencję

    //!!!można overloadować funkcje const
        //!!!wersja const wywoła się na obiekcie const a non-const na non-const
        //!!!overloadowanie funkcji const -> non-const zwykle robi się aby zwrócić
        //inną zawartość np zamiast const ref -> non-const

    RR r2{123};
    r2.getZ() = 55555;
    printf("R2.getZ() = %d\n", r2.getZ());
    //wersja const metody zadziała z obiektami const oraz non-const
}


class SS
{
public:
    static int staticVar;
        //zmienna współdzielona przez wszystkie obiekty
    static const int constStatic = 12345;
        //CONST STATICA można zdefiniować w klasie
    static constexpr int constExprStaticVar = 123;
    int uniqueId;
private:
    static int privateStaticVar;
    static int uniqueIdGenerator;
public:
    SS() : uniqueId{uniqueIdGenerator++} {}
};
int SS::uniqueIdGenerator = 1;
int SS::staticVar = 1234;
    //obowiązkowe -> definicja zmiennej statycznej klasy
//int SS::staticVar;//inicjalizacja zerem
int SS::privateStaticVar;
    //prywatną też trzeba zdefiniować i zainicjalizować
void staticMember()
{
    //!!!nie można inicjalizować zmiennych statycznych w klasie
    SS ss1;
    SS ss2;
    ss1.staticVar = 333;
    printf("ss1=%d, ss2=%d, SS::=%d\n",
        ss1.staticVar, ss2.staticVar, SS::staticVar);

    //statyczne zmienne nie są powiązane z obiektami
    //żeby żyć nie potrzebuje obiektu
    //!!!używać resolution operatora -> SS::staticVar

    //!!!deklaracja zmiennej statycznej w klasie jest podobna do forward deklaracji
    //jedynie mówi kompilatorowi, że istnieje
    //w związku z tym że nie należą do obiektu trzeba je zdefiniować poza klasą

    //printf("%d", SS::privateStaticVar); -> brak dostępu

    //!!!definiować i inicjalizować zmienne w cpp nie w hpp bo multiple definition

    SS ss3;
    printf("s1.id, s2.id, s3.id = %d %d %d\n",
        ss1.uniqueId, ss2.uniqueId, ss3.uniqueId);
}




class KlasaZeZmiennaStaticDoZainicjalizowania
{
    public:
        class _inicjalizator
        {
        public:
            _inicjalizator()
            {
                //printf("Inicjalizuje zmienna statyczna\n"); !!!odkomentowac
                tablicaDoZainicjalizowania[0] = 11;
                tablicaDoZainicjalizowania[1] = 22;
                tablicaDoZainicjalizowania[2] = 33;
            }
        };
    private:
        static int tablicaDoZainicjalizowania[3];
        static _inicjalizator init;
            //tylko poto aby wykonać konstruktor klasy nested
};
KlasaZeZmiennaStaticDoZainicjalizowania::_inicjalizator
    KlasaZeZmiennaStaticDoZainicjalizowania::init;
        //wywołuje konstruktor klasy nested _inicjalizator a ten inicjalizuje
            //też inne pola
int KlasaZeZmiennaStaticDoZainicjalizowania::tablicaDoZainicjalizowania[3];

class DD
{
private:
    static int staticVar;//brak dostępu bo jest prywatna
public:
    int getDDStaticVar() {return staticVar;}
    static int getDDStaticVarStatic() {return staticVar;}
};
int DD::staticVar;
void staticMethod()
{
    printf("Zeby odczytac wartosc stworzyłem obiekt %d\n", DD().getDDStaticVar());
        //!!!statyczne funkcje nie należą do obiektu
    printf("Zeby odczytac wartosc nie tworzylem obieku %d\n",
        DD::getDDStaticVarStatic());

    //!!!funkcje statyczne nie mają wskaźnika this
    //!!!funkcje statyczne mają dostęp tylko do statycznych pól i statycznych metod
    //!!!funkcje statyczne można definiować poza klasą tak samo jak normalne
    //przy definicji nie dodajemy już słówka static

    //!!!klasy z tylko statycznymi memberami są nazywane monostates,
    //nie można mieć ich kopii -> trzeba robić nowy plik z inną nazwą
    //każdy może zmienić pole statyczne tak samo jak globalną zmienną

    //funkcje z tylko statycznymi danymi są jak zmienne globalne w namespace
    //nie powinno się robić

}

class RRR;
    //class prototype aby PPP wiedziala ze jest takie cos jak RRR
    //mówi kompilatorowi że w przyszłości zdefiniujemy klasę RRR
    //odpowiednik prototypu funkcji
class DisplayClass;
class DisplayClass2;
    //void DisplayClass2::printfPPP2(const PPP& p);
    //nie da się zrobić forward deklaracji samej metody...
    //trzeba oddzielić definicje od deklaracji i deklarację klasy dać wyżej
class PPP
{
public:
    PPP(int i) : privateVar{i}{}
private:
    int privateVar;
    friend void displayPppContent(const PPP& ppp);
        //oznacz displayPPPContent jako friend
    friend bool isEqual(const PPP& p1, const PPP& p2, int spam);
    friend void printPPPRRR(const PPP& ppp, const RRR& rrr);
    friend class DisplayClass;

    //friend void DisplayClass2::printfPPP2(const PPP& p);
    //trzeba przenieść deklarację klasy DisplayClass2 wyżej a definicje niżej
};
class RRR
{
public:
    RRR() : privateVar{88}{}
private:
    int privateVar;
    friend void printPPPRRR(const PPP& ppp, const RRR& rrr);
};
void displayPppContent(const PPP& ppp)
{
    printf("Prywatne pole klasy PPP privateVar ma wartosc: %d\n", ppp.privateVar);
}
bool isEqual(const PPP& p1, const PPP& p2, int spam)
{
    return p1.privateVar == p2.privateVar;
}
void printPPPRRR(const PPP& ppp, const RRR& rrr)
{
    printf("ppp.privateVar = %d, rrr.privateVar = %d\n",
                ppp.privateVar, rrr.privateVar);
}
class DisplayClass
{
public:
    void printfPPP(const PPP& p)
    {
        printf("PPP private wal is %d\n", p.privateVar);
    }
};

void friendKlasy()
{
    //!!!friend klasa/funkcja to funkcja/klasa która ma dostęp do prywatnych
        //memberów tak jakby sama była członkiem
    //friend funkcja może być inną normalną funkcją lub metodą
    //!!!nie ma znaczenia czy friend funkcja będzie w public czy private

    PPP ppp{343};
    displayPppContent(ppp);//trzeba przekazać PPP bo funkcja disp... nie ma this
    RRR rrr;
    printPPPRRR(ppp, rrr);
    DisplayClass().printfPPP(ppp);

    //DisplayClass2().printfPPP2(ppp);//trzebaby przenieść klasę
    //jakby był podział na hpp i cpp byłoby ok

    //można zrobić całą klasę friend do innej ale i tak nie ma dostępu do this
    //to że PPP ma klasę zaprzyjaźnioną Display nie działa w drugą stronę
    //jeżeli A is friend B and B is friend C -> A is not friend C

    //!!!limitować friend funkcje i klasy bo naruszają enkapsulecję
    printf("======================\n");
}


class AnonymousObj
{
public:
    AnonymousObj(){printf("AnonymousObj constructor\n");}
    ~AnonymousObj(){printf("AnonymousObj destructor\n");}
};
class NonAnonymousObj
{
public:
    NonAnonymousObj(){printf("NonAnonymousObj constructor\n");}
    ~NonAnonymousObj(){printf("NonAnonymousObj destructor\n");}
};

void obiektyAnonimowe()
{
    //obiekty anonimowe to wartości bez nazwy, nie ma możliwości
        //aby się do nich odnieść

    //mają expression zakres, są tworzone, wykonywane i niszczone
        //w pojedynczym wyrażeniu
    printf("Function start\n");
    NonAnonymousObj nao;
    AnonymousObj();//tworzony i niszczony w tej linii //OBIEKT ANONOIMOWY
    printf("Function end\n");

    //są traktowane jako R-VALUES
}

void obiektyAnonimowe2()
{
    printf("======================\n");
    printf("Function start\n");
    const AnonymousObj& ref = AnonymousObj();
    //chyba można zrobić podobnie używając move semantic
    //AnonymousObj obj = AnonymousObj(); -> konstruktor kopiujący/przenoszący
    std::cout << "Przedluzony czas życia obiektu anonimowego poprzez"
              << "przypisanie const ref" << std::endl;
    printf("Function end\n");
}

class SSS
{
public:
    class CCC
    {
        int z;
    };
    enum Kolor
    {
        RED,
        YELLOW,
        PINK
    };
    void func(Kolor k)
    {
        printf("Kolor to: %d\n", k);
    }
    CCC ccc;
};
void typyZagniezdzone()
{
    SSS sss;
    sss.func(SSS::PINK);

    //funkcje nie mogą być zagnieżdżone w funkcjach
    //!!!klasy działają jak namespace dla typów zagnieżdżonych
    //można umiesczać inne typy np: typedefy, aliasy, klasy

    //klasy zagnieżdżone mają taki sam dostęp do elementów klasy otaczającej
        //jakie obejmuje klasa otaczająca
    //!!!klasa zagnieżdżona nie ma thisa do klasy otaczającej

    //rzadko stosowane, np do iteratorów
}

#include <chrono>
#include <thread>
class Timer
{
private:
    using clock_t = std::chrono::high_resolution_clock;
        //precyzyjny zegar ale może być to alias na
        //std::chrono::system_clock lub steady_clock
    using second_t = std::chrono::duration<double, std::ratio<1> >;
        //ratio współczynnik
        //std::chrono::duration -> double -> ilość ticks, 
        //std::ratio -> współczynnik pomnożenia reprezentuje czas trwania ticka

    std::chrono::time_point<clock_t> mBeg;
        //reprezentuje punkt w czasie
public:
    Timer() : mBeg(clock_t::now()) {}

    void reset(){mBeg = clock_t::now();}
    double elapsed() const
    {
        return std::chrono::duration_cast<second_t>(clock_t::now() - mBeg).count();
    }
};
void czasWykonaniaKoduChrono()
{
    //dobre do mierzenia wydajności

    Timer timer;
    std::this_thread::sleep_for(std::chrono::milliseconds(66));
        //tu np sortowanie
    printf("Zmierzony czas po sleep 66ms: %f\n", timer.elapsed());

    //testować na release a nie debug
}