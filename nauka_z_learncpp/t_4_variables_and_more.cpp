#include <iostream>
#include <bitset>
#include <typeinfo>
#include <cstdint>
#include <limits>
#include <vector>

void blokiILokalneZmienne();
void zmienneGlobalneILinkage();
void t_nicNieRob(void*);
void namespaces();
void rzutowanieNiejawne();
void rzutowanieJawne();
void stringi();
void enumy();
void typedesfIaliasy();
void struktury();
void rozmiaryKlas();
void autoKeyword();

void t_4_variables_and_more()
{
    std::cout << "\n\n-----chapter 4 started-----\n";

    blokiILokalneZmienne();
    zmienneGlobalneILinkage();
    namespaces();
    rzutowanieNiejawne();
    rzutowanieJawne();
    stringi();
    enumy();
    typedesfIaliasy();
    struktury();
    rozmiaryKlas();
    autoKeyword();
}

void blokiILokalneZmienne()
{
    //jeżeli mamy zagnieżdżone 4 bloki to wypada pomyśleć o funkcji

    //SCOPE określa gdzie zmienna jest dostępna
    //DURATION określa kiedy zmienna jest tworzona i niszczona
    //LINKAGE określa czy wiele wystąpień identyfikatora odnosi się do tej samej
        //zmiennej czy nie 
                //internal, external, no linkage

    //LOCAL VARIABLES   -> duration AUTOMATIC
    //                  -> scope BLOCK (local)
    //                  -> linkage NO LINKAGE -> może odnosić się tylko do
        //ogriczonego zakresu w którym istnieje, czyli np zmienne o tych
        //samych nazwach w innych funkcjach są niezależne

    //zmiennt wewnątrz inner bloków widzą zmienne z outer bloków
    //shadowing zmienne wewnątrz nested bloków mogą mieć nazwy jak z outer bloków

    int zmienna = 5;
    t_nicNieRob(&zmienna);
    {
        int zmienna = 3;
        t_nicNieRob(&zmienna);
    }

    //!!!nie używać zmiennych o tych zamych nazwach wewnątrz zagnieżdżonych bloków
    //!!!zmienne powinny być w jak najmniejszych scope'ach
    //parametry funkcji mają block scope
}



int global_zmienna {5}; //powinna być zadeklarowana na górze pliku
                        //domyślnie EXTERNAL
const int const_global_zmienna{2}; //domyślnie INTERNAL bo const

//UŻYCIE STATIC POZA BLOKIEM
static int static_global_zmienna{10}; 
        //INTERNAL linkage -> widoczna tylko w tym pliku

//extern int extern_global_zmienna{11};
    //EXTERNAL linkage -> widoczna również poza tym plikiem
    //jeżeli chcę zrobić niezainicjalizowaną zmienną non-const nie używać
        //extern bo kompilator pomyśli że jest to forward declaration

//UŻYCIE STATIC POZA BLOKIEM
static int getNewID()
{
    static int i{0};
    return ++i;
}
    //funkcje mają domyślne linkage extern
    //w forward deklaracji extern nie jest potrzebne bo kompilator 
        //umie rozróżnić bo brak ciała
    //w każdym pliku może być o takiej nazwie nowa, tak samo ze zmiennymi


void zmienneGlobalneILinkage()
{
    //GLOBAL VARIABLES  -> duration STATIC od początku do końca programu
    //                  -> scope FILE (global)
    //                  -> linkage EXTERNAL | INTERNAL

    //!!!zmienne globalne są domyślnie inicjalizowane

    int global_zmienna{10};//przesłonięcie
    ::global_zmienna++;
    printf("::global_zmienna = %d, global_zmienna = %d\n",
        ::global_zmienna, global_zmienna);

    //::powoduje odwołanie się do zmiennej globalnej
    t_nicNieRob(&static_global_zmienna);

    //!!!aby użyć zmiennej z linkage External trzeba zrobić jej forward declaration
    //extern int extern_global_zmienna;
        //forward declaration extern robi co innego w zależności od kontekstu
    //printf("%d\n", extern_global_zmienna);

    //!!!nie używać non-const zmiennych globalnych bo to sens głównie przy
        //logach i np uchwycie do bazy danych, uchwycie do dźwięku itp

    //!!!zmienne globalne powinny być w namespace ewentualnie prefix g_
    //!!!zamiast zmiennej globalnej lepiej zrobić statyczną i zrobić funkcję
        //extern która umożliwia robić na niej zmiany, w razie czego
        //będzie tylko jedna funkcja w kodzie do zmiany

    //!!!przekazywać zmienne globalne do funkcji które jej potrzebują
        //nie używać w nich bezpośrednio

    //JOKE: what is the best prefix for global variable ?
        //"//"

    //!!!ZMIENNE STATIC DURATION
        //!!!użycie słowa static na zmiennych lokalnych nie zmienia ich 
        //LINKAGE a DURATION

    //zmienne statyczne są tworzone i inicjalizowane tylko raz i trzymają swoją
        //wartość nawet po wyjściu z własnego scope
    //można użyć prefixu s_

    printf("genId: %d, genId: %d, genId: %d\n", getNewID(), getNewID(), getNewID());
}


//Constants.hpp -> za każdym razem będą wczytane wszystkie zmienne z namespace
        // namespace Constants
        // {
        //     const double pi{3.14159}...
        // }
//INNE rozwiązanie zamienić w hpp na "extern const double pi" a zainicjalizować
//w constatns.cpp, dodatkowo zmiana stałych nie będzie w hpp więc nie będzie
//wymagana rekompilacja wszystkich plików które includują constants.hpp
    //ZLE bo nie mogą być constexpr i może to być wolniejsze
    //jak nie ma powodu oryginalne rozwiązanie z initjalizacją constów w hpp lepsze



namespace NS1 //lepiej jakby było w hpp
{
    int ns1Var {5};//zmienna globalna

    static int ns1Var2;


    namespace //wewnątrz anonimowego namespace tworzone są tylko zmienne
              //statyczne z internal linkage
    {
        int ns1Var3Statyczna;
    }

}
namespace NS1//to samo namespace może być w innym pliku
{
    const int kolejnaZmienna = 55;
    namespace Details
    {
        const int details = 55;
    }
}
int cout(){return 5;}
void namespaces()
{
    //wszystko bez namespace jest zadeklarowane w domyślnym namespace ::
        //(resolution operator)
    ::t_nicNieRob(&NS1::ns1Var2);
    ::t_nicNieRob(&NS1::ns1Var3Statyczna);

    printf("NS1::ns1Var = %d\n", NS1::ns1Var);
    //!!!to samo namespace może być zadeklarowane  w wielu miejscach

    namespace NSAlias = NS1::Details;
    printf("Namespace alias NSAlias = BS1::Details %d\n", NSAlias::details);

    using std::cout;//odnosi się tylko do tego bloku
    cout << "using std::cout; użycie std przed cout niepotrzebne\n";
    //nawet jeżeli będzie konflikt użyje std::cout

    using namespace std;//używa bez namespace funkcji i zmiennych z namespace std
    //zadeklarowano używanie namespace std bez konkretnych funkcji
    //tu jeżeli wykryje konflikt nazw wysypie się

    //!!! nie używać using w globalscope poza blokiem a najlepiej w ogóle
    //nie da się scancelować using, musi dojść do końca bloku
}



void rzutowanieNiejawne()
{
    float f {3};//implicit conversion, działa tylko na typach prostych
    t_nicNieRob(&f);

    //niejawna konwersja dzieli się na 2 rodzaje PROMOTION i CONVERSION
    //integral promotion z mniejszych fo int lub uint
    //floating promotion z mniejszych fo double
    long l{44};//numeric promotion

    short s{2};
    double d{3};//numeric conversion z większego do mniejszego lub różne typy
    t_nicNieRob(&l);
    t_nicNieRob(&d);
    t_nicNieRob(&s);

    //WYRAŻENIA oba typy są rzutowane do tego samego
    //!!!jeżeli operandy są mniejsza od int operator wyrażenia zmienia je na int
    //short + short ==> int + int = int
    //jeżeli operandy dalej się nie zgadzają są rzutowane na najeikszy typ operandu
    //int < uint < lomg < ulong < long long < ulong long < float 
            //< double < long dluble
    printf("short + short = %s\n", typeid(s+s).name());

    std::cout << "5u-10=" << 5u-10 << std::endl;
        //bo typy zostały zrzutowane na uint

    //unsigned int value = 10; while (value-- >= 0) {}//ENDLESS LOOP
}

void rzutowanieJawne()
{
    //!!!unikać const_cast i reinterpret_cast
    //!!!unikać C-style casts -> (float)5, float(5)
    //static_cast najlepszy dla typów prostych -> sprawdza typ podczas kompilacji
    //static_cast nie pozwala zdjąć consta
}

void stringi()
{
    printf("to jest string\n");
    std::string helloString{"HelloString"};
    printf("%s\n", helloString.c_str());

    std::string str;
    //std::cin >> str;//cin pobiera tylko do whitespace dla stringa
    //więc jeżeli będzie np IMIE Nazwisko to pobrane zostanie tylko Imie
        //a nazwisko zostanie w buforze
    //std::getline(std::cin, str);//pobiera całą linię
    printf("Domyślna wartość stringa to \"%s\"\n",str.c_str());

    //użycie getline nie zadziała po cin(dla inta) bo cin pozostawi \n
        //a getlina od razu go wczyta

    //!!!użtwając cin dla numerycznych wartości warto dodać
        //std::cin.ignore(32767, '\n') aby kasował kończący znak \n

    //std::cin.ignore mówi jak wiele znaków należy zignorować

    std::string length {"duzo znakow .........."};
    printf("text \"%s\" ma %lu znakow\n", length.c_str(), length.length());
}

void enumy()
{
    enum Color //nie alokuje pamięci, wartości domyślnie od 0++
    {
        COLOR_BLACK, //Dobrze dodać prefix bo enumerator ma taki sam scope jak enum
                    //i nie można by było mieć 2 enumów z tym samym enumeratorem
        COLOR_RED,//, dozwolony od C++11
    };
    printf("COLOR_RED = %d\n", COLOR_RED);

    enum Zwierze
    {
        ZWIERZE_PIES = -5,
        ZWIERZE_KOT, //-4
        ZWIERZE_KROWA = 11,
        ZWIERZE_KROWA2 = 11,
        ZWIERZE_KON, //12
        ZWIERZA_WAZ = 0,
    };
    printf("KOT: %d, KON %d\n", ZWIERZE_KOT, ZWIERZE_KON);
    //!!!warto NIE używać specyficznych wartości dla enumeratora
    //!!!nie używać tych samych wartości w jednym enumie
    //!!!enum ewoluuje do typu z rodzaju integer głównie inta

    int zwierzeVar {ZWIERZE_KROWA2};
    t_nicNieRob(&zwierzeVar);

    //!!!można tworzyć zmienne typu enuma ale trzeba castować
    Zwierze zwierzee = static_cast<Zwierze>(-5);//wartości nie mogą się powtarzać w enumie
    t_nicNieRob(&zwierzee);

    //Zwierze noweZwierze = COLOR_BLACK; ERROR
    //!!!Każdy enum jest rozważany jako różny typ nie można przypisać zwierze
        //do kolor
    //enum powinien być w hpp wczytywany wiele razy bo nie zużywa ramu
    //warto używać np przy zwracaniu błędów ERR_BUFFER, ERR_WRITE, ERR_READ

    // if (ZWIERZA_WAZ == COLOR_BLACK and 1 == 1)//compilator warning
    // {//zgodnie z promocją typów będą traktowane jako inty
    //     printf("Porownanie enumeratorów z różnych enumów ZWIERZE == KOLOR\n");
    // }

    enum class Kolor
    {
        BIALY,
        CZARNY,
    };//za enumami i enum clasami muszą być średniki
    enum class Ptak
    {
        SKOWRONEK,
        SROKA
    };

    //!!!enum clasy są silnie typowane więc nie można porównać 2 enumeratorów
        //z różnych enumów
    //if (Kolor::BIALY == Ptak::SKOWRONEK);

    //!!!enumeratory w enum class są jego częścią nie mają jego scopu
    //słowo class przy enum znów jest w innym contekście podobnie jak static
}

void typedesfIaliasy()
{
    typedef double distance_t;//type def jest nieładny dla wskaźników do funkcji
    distance_t dt = 4.44;
    t_nicNieRob(&dt);
    typedef std::vector<std::pair<int, int> > wektorParIntInt;
    wektorParIntInt vpii {std::make_pair(4,4), std::make_pair(4,4)};
    printf("Pierwszy element pierwszej pary w wektorze to %d\n", vpii.front().first);
    //!!!dodawać sufix _t dla typedefów

    std::int16_t int16 {222};//cstdint + cpp11
    std::uint64_t uint64 { std::numeric_limits<std::uint64_t>::max() };
    t_nicNieRob(&int16);
    std::cout << "maksymalna wartość uint64 to: " << uint64 << std::endl;

    //lepsze od typedef jest using
    using wektorParIntInt2 = std::vector<std::pair<int,int> >;
    //!!!to using nie jest związane z automatycznym użyciem namespaców
    wektorParIntInt2 wpii2 {std::make_pair(3,3)};
    t_nicNieRob(&wpii2);
    //!!!używać type aliases zamiast typedefs
}

struct Czlowiek //!!!deklaracja struktury nie zajmuje pamięci
{
    int wiek;
    std::string imie;
    int wysokosc;
    std::string getImie(){
        return imie;
    }
};
struct Czlowiek2
{
public:
    //!!!  the non-static member initialization
    int wiek {11};
    //!!! w cpp11 można zainicjalizować pole struktury/klasy
    //!!! w cpp11 i niżej jeżeli zainicjalizujemy domyślną wartością
        //pole nie używając uniform initialization,
        //nie będzie możliwości zainicjalizowania pól przy tworzeniu zmiennej
        //trzeba pisać konstruktor

    std::string imie {"Marian"};
    struct Czlowiek {};
    std::string getImie(){
        return imie;
    }
};
void struktury()
{
    //!!!struktura to agregowany typ danych

    Czlowiek pawel {99, "Pawel"};
        //!!!można zainicjalizować strukturę czy klasę przez initializer list
        //poniżej cpp11 tak samo tylko z "="

    printf("Wiek %s to %d\n", pawel.imie.c_str(), pawel.wiek);
    Czlowiek2 pawel2 {99, "Pawel"};
    Czlowiek pawel3;
    Czlowiek pawel4 {};
    printf("Niezainicjalizowana struktura: Wiek %s to %d wysokosc %d\n",
        pawel3.imie.c_str(), pawel3.wiek, pawel3.wysokosc);
    printf("Pusta struktura uniform initialization: Wiek %s to %d wysokosc %d\n",
        pawel4.imie.c_str(), pawel4.wiek, pawel4.wysokosc);
}

class A
{
    int a;      //4  4
    bool b;     //1  6
    short c;    //2  8
    double d;   //8  16
    int* e;     //8  24
};

class B
{
    bool a;      //1  1
    bool b;      //1  2
    bool c;      //1  3
    short d;     //2  6
    int* e;      //8  16
    bool* f;     //8  24
};

class C
{
    long double a;      //16   16
    int* b;             //8    24
    bool c;             //1    28  [padding[3]] do floata
    float d;            //4    32
    int* e;             //8   40
    int* f;             //8   48
};

class __attribute__((packed)) D
{
    long double a;      //16   16
    int* b;             //8    24
    bool c;             //1    25
    float d;            //4    29
    int* e;             //8   37
    int* f;             //8   45
};

void rozmiaryKlas()
{
    printf("Size of int is %lu\n", sizeof(int));
    printf("Size of short is %lu\n", sizeof(short));
    printf("Size of bool is %lu\n", sizeof(bool));
    printf("Size of double is %lu\n", sizeof(double));
    printf("Size of int* is %lu\n", sizeof(int*));
    printf("Size of class A is %lu\n", sizeof(A));
    printf("Size of class B is %lu\n", sizeof(B));
    printf("Size of long long double is %lu\n", sizeof(long double));
    printf("Size of class C is %lu\n", sizeof(C));
    printf("Size of class D is %lu\n", sizeof(D));
}


auto autoTest()
{
   return 5;//od c++14 ale lepiej nie używać bo nie wiadomo co zwraca od razu
}
auto autoTest2() -> int
{
   //przy decl type może być pomocne ??? ogólnie nie używać
   return 5;
}
void autoKeyword()
{
    //przed c++11 auto znaczyło automatic duration

    //type inference
    auto d = 5.5;
    t_nicNieRob(&d);
    //auto b; b=5; musi być zainicjalizowane
    autoTest();
}