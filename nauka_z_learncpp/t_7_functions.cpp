#include <iostream>
#include "all.hpp"

void funParamsAndArgs(int);
void zwracanieWartosci();
void inlineFunc();
void functionOverloading();
void defaultParameters();
void functionPointers();
void stackAndHeap();
void vectorAndStack();
void recursion();
void errorsCerrExit();
void assertStaticAssert();
void commandLineArgs(int argc, char** argv);
void ellipsisVaList();

void t_7_functions(int argc, char** argv)
{
    std::cout << "\n\n-----chapter 7 started-----\n";
    funParamsAndArgs(5);//5 to argument
    zwracanieWartosci();
    inlineFunc();
    functionOverloading();
    defaultParameters();
    functionPointers();
    stackAndHeap();
    vectorAndStack();
    recursion();
    errorsCerrExit();
    assertStaticAssert();
    commandLineArgs(argc, argv);
    ellipsisVaList();
}


void funRef(int& i)
{
}
void funRefConst(const int& i)
{
}
void vunPtr(int* ptr)
{
    ptr = nullptr; //nie zadziala
        //!!!pointery są przekazywane przez wartość więc adres jest kopiowany
        //!!!funkcja otrzymala kopie adresu
}
void funRefPtr(int*& ptrRef)
{
        //tu może zmienić adres wskaźnika
    ptrRef = nullptr;
}
void funParamsAndArgs(int i)//parameter -> zadeklarowany w deklaracji funkcji
{
    //przez wartośc można przekazać wszystko zmienne, literały, wtrażenia ...
    //kopiowanie dużych obiektów jest czasochłonne
    //przez wartość dla typów prostych, i enumów

    //funRef(4); -> compilation error

    //!!!warto dodawać Out sufix jeżeli jest to parametr wyjściowy

    funRefConst(4);

    //!!!non-const references mogą jedynie wskazywać na l-calues
    //!!!const references za to r-values, l-values i const l-values

    //!!!przez referencję do klas, struktur, jeżeli trzeba modyfikować,
        //jeżeli potrzebny dostęp do danych o tablicy """int (&array)[5]"""

    int* ii = new int[1];
    *ii = 5;
    vunPtr(ii);
    printf("i is still: %d\n", i);
    delete[] ii;

    //przekazywanie przez pointer działa tak samo jak przez referencję
    //wszystko w c++ jest przekazywane przez wartość -> jest kopiowane

    //!!!przekazywać przez pointery gdy: przekazujemy wbudowane tablice i
    //pointery które mogą być nullptr
}


#include <tuple>
int* getMemory(int size)
{
    return new int[size];
}
int& getRef()
{
    static int i = 5;
    return i;
}
std::tuple<int, int> getTwoVal()
{
    return std::make_tuple(5, 43);
}
void zwracanieWartosci()
{
    //zwracanie przez wartość jest najbezpieczniejsze
    //!!!zwykle działą RVO więc przy wracaniu nie ma kopiowania itp
    //używać do zmiennych zadeklarowanych wewnątrz funkcji i
        //argumentów otrzymanych przez wartość

    //nie można zwracać lokalnych zmiennych przez wskaźnik bo będą już skasowane
    //można zwracać przez wskaźnik pamięć zaalokowaną dynamicznie
    int* z = getMemory(55);
    delete[] z;
    //używać do zmiennych zaalokowanych dynamicznie zwracających pamięć
        //i argumentów otrzymanych przez ptr

    //zwracanie przez referencję używać do
        //parametrów otrzymanych jako referencję i klas które nie będą zniszczone

    const int& x = getRef();//!!!musi być const bo funkcja zwraca r-val
    //const& wydłuża czas życia r-value

    t_nicNieRob((void*)&x);

    //aby zwrócić kilka wartości: struktura, touple
    std::tuple<int, int> tuple2val = getTwoVal();
    printf("Pierwsza zwrócona wartosc: %d, druga: %d\n",
            std::get<0>(tuple2val), std::get<1>(tuple2val));

    auto [a, b] = getTwoVal(); //od c++17
    t_nicNieRob(&a);
    t_nicNieRob(&b);
    //jeżeli zwracanie kilku wartości następuje w kilku miejscach lepiej
        //zrobić strukturę
        //dla pojedynczych tuple
}


void inlineFunc()
{
    //funlcje zwykłe spowalniają program bo procesor musi do nich skoczeć
        //i odłożyć wartości, dla dużych funkcji jest to OK

    //funkcje inlineowe są kopiowane w miejsce wywołania
    //zwiększa to rozmiar aplikacji
    int x = t_getNum();
    t_nicNieRob(&x);

    //na upartego inline func może być też w c++ file jeśeli jest tylko tam użyta

    //!!!inline to tylko rekomendacja kompilator sam zdecyduje
    //!!!jak nie jest inline kompilator może sam dodać

    //normalne funkcje z external linkage nie powinny mieć ciała w hpp bo każdy
        //plik cpp który je includuje, skompuluje a linkerwywali błąd, że 
        //jest ich wiele
    //!!!z funkcjami inlinowymie nie ma tego problemu bo kompilator
    //nie traktuje ich jako funkcje
}


int funA(int a){ return 5; }
int funA(int& a){ return 6;}
//int funA(const int& a){ return 6;} -> ambigous z int a
void functionOverloading()
{
    //umożliwia tworzenie wielu funkcji o tej samej nazwie

    //kompilator może znaleźć przeciążoną funkcję, nie znaleźć albo ambiguous
    //szuka funkcji po
        //dokłądnym typie   0 -> int
        //później po promocji typów 'c' -> int bo brak chara
        //później po standardowej konwersji 0 -> nullptr
        //później po konwersji zdefiniowanej przez programistę dom -> int

    int e = funA(444);
        //można wykonać bo 444 nie może być nie const referencją bo jest r-value

    //int e2 = funA(z);//nie można wykonać bo dwuznaczne
    printf("funA(444) = %d\n", e);

    //dwuznaczne -> nie wykona się
    //printf("funA(i) = %d\n", funA(e));

    //wywołanie może być ambiguous jeżeli są 2 funkcje które pasują do
        //np standardowej czy developera konwersji
    //abo ominąć można np scastować argument przy wywołaniu, dodać nową fun
        //lub dodać np 0u czy 5.5f

    //przy wielu parametrach funkcja musi mieć przynajmniej jeden parametr
        //lepszy i resztę nie gorszą
}

void defParam(int i=55){}
void forwartFun2(int z = 55){}
void forwartFun2(){}
void defaultParameters()
{
    //domyślny/opcjonalny parametr funkcji
    //domyślne parametry muszę być po prawej stronie
    defParam();

    //nie można redeklarować domyślnych parametrów
    //czyli może byc albo w definicji funkcji albo w forward deklaracji

    //!!!jeżeli funkcja ma forward deklaracje to tam dodać domyślne parametry
        //a nie w definicji

    forwartFun2(44);
    //forwartFun2(); AMBIGOUS
}


#include <functional>
void funPtrTest(){}
const int funPtrTestI()
{
    printf("Funkcja zwracajaca const int\n");
    return 4;
}
void callFunc(const int (*const fun)())
    {fun();}
void callFuncDefaultParam(const int (*const fun)() = funPtrTestI)
    {fun();}
int funPtrD(int* i, double d)
{
    printf("Wywolano mnie przez wskaznik d = %f\n", d);
    return 555;
}
void functionPointers()
{
    //!!!funkcje mają własny l-value typ
    //nazwa funkcji jest wskaźnikiem na funkcję
    printf("Fun addr = %p\n", funPtrTest);
    printf("Fun addr = %p\n", reinterpret_cast<void*>(funPtrTest));

    //nieconstowy wskaźnik na funkcję, która nie przyjmuje parametrów
        //i zwraca voida
    //nawiasy potrzebne bo interpretowałoby jako forward deklarację
    void (*funPtr)() {funPtrTest};

    //constowy wskaźnik
    void (*const funPtr2)() {funPtrTest};
    funPtr();
    funPtr2();

    //zwraca const inta
    const int (*const funPtr3)() {funPtrTestI};
    (*funPtr3)();//wykonanie funkcji przez jawną dereferencję
    funPtr3();//wykonanie przez niejawną dereferencję

    //!!!c++ niejawnie konwertuje funkcje do wskaźników na funkcje więc
    //nie potrzeba dodawać & aby uzyskać adres
    //!!!jednak niejawnie kompilator nie scastuje wskaźnik na funkcje
    //na wskaźnik na voida i odwrotnie

    //!!!domyślne parametry nie działają ze wskaźnikami na funkcję
        //bo są wstawiane na etapie kompilacji w miejsca gdzie ich nie ma
        //a wskaźniki na funkcje są rozwiązywane w runtime

    //!!!callback function przekazanie wskaźnika do funkcji jako parametru
    callFunc(funPtrTestI);

    //dobre np przy sortowaniu dać wskaźnik na funkcję asc/dsc
    callFuncDefaultParam();

    //int funPtrD(int* i, double d);
    typedef int(*funPtr_Int_intP_double)(int*, double);
    funPtr_Int_intP_double funPtr5 {funPtrD};
    funPtr5(nullptr, 5.0);

    using funPtr_i_ip_d = int(*)(int*, double);
    funPtr_i_ip_d funPtr6 {funPtrD};
    funPtr6(nullptr, 5.55);

    //od c++ 11
    std::function<int(int*, double)> funPtrr {funPtrD};
    funPtrr(nullptr, 55);

    //bind to function template który generuje forwarding call wrapper
    //wywołanie go jest równoznaczne z wywołaniem funkcji
    auto aaa {std::bind(funPtrD, nullptr, std::placeholders::_1)};
    aaa(44.3);
}

void stackAndHeap()
{
    //Pamięć używana przez program jest podzielona na obszary:
    //CODE SEGMENT (TEXT) -> read only miejsce gdzie skompilowany kod
                             //jest w pamięci
    //BSS SEGMENT (UNITIALIZED) -> dla globalnych i statycznych zmiennych 
                                   //zainicjalizowanych zerami
    //DATA SEGMENT (INITIALIZED) -> dla zainicjalizowanych zmiennych 
                                    //globalnych i statycznych

    //np 3, "Hello workd" is stored in text and copied to Data on startup
    //HEAP -> dla zmiennych alokowanych dynamicznie
        //wolna alokacja
        //konieczna dealokacja
        //dostępna tylko przez pointer
        //dereferencja pointera trwa
        //duży obszar pamięci
    //CALL STACK (STACK) -> dla zmiennych lokalnych, parametrów funkcji,
                            //i innych informacji związanych z funkcjami
        //szybka alokacja
        //automatyczna dealokacja
        //pamięć zaalokowana jest znana na etapie kompilacji
        //mały
        //pilnuje informacji o wszystkich wywołanych funkcjach
        //alokuje zmienne lokalne i dealokuje
        //jest zaimplementowany jako stos
        //fixed size

    //stos -> struktura danych
        //nie ma random access
        //LIFO
        //top, peek, pop, push
        //ma zafixowany rozmiar (w programowaniu)


    //Zasada działania
    //trzymamy info gdzie się zaczyna np nr 0 (w REJESTRZE)
    //wypełniamy nr stosu 0 więc przenosimy się do nr 1 REJESTR=1
    //jak usuwamy element ze stosu przenosimy się w dół do nr 0 REJESTR=0
        //!!!pamięć zdjętego elementu nie jest czyszczona jest tam później spam
        //!!!powinna być nadpisana ale aktualnie "nie jest na stosie"
    //wszystko co jest poniżej jest "on the stack"

    //REJESTR w tym wypadku (małą pamięć w procesorze)
    //trzyma informacje o SP (stack pointerze) czyli gdzie jest top()


    //jak program się zaczyna system operacyjny wrzuca main na stos
    //jak wywołanie funkcji jest znajdowane jest ona wrzucana na stos
            //-> widać całą kolejność wywołania
    //jak wywołanie się kończy jest zdejmowana ze stosu
    //domyślny rozmiar stosu to 1-8MB
    //jak będzie za dużo zmiennych lokalnych/wywołań funkcji to STACK OVERFLOW

    //STACK FRAME -> element wrzucany na stos
        //pilnuje informacji o wszystkich elementach powiązanych
        //z wywołaniem funkcji


    //flow
    /*
        -> wywołanie funkcji znalezione
        -> konstruujemy STACK FRAME i wrzucamy na stos
           stack frame zawiera
            -> return address (gdzie CPU ma wrócić po wywołaniu funkcji)
            -> argumenty funkcji
            -> pamięć dla zmiennych lokalnych
            -> kopie zmodyfikowanych rejestrów, które po wykonaniu funkcji powinny zostać przywrócone
        -> CPU skacze do funkcji start pointu
        -> CPU wykonuje instrukcje funkcji
        -> funkcja się kończy
        -> przywracanie rejestrów
        -> STACK FRAME jest zdejmowany ze stosu (zwalnia zmienne lokalne...)
        -> return value jest obsługiwane
        -> CPU wykonuje kod od return address
        ---> return value jest różnie obsługiwane czasami jako część 
             //STACK FRAME czasami jako osobny rejestr
        ---> stos może rosnąć o adresu 0 w górę lub z góry do 0 zależy od arch
    */

    //new zwraca adres do zmiennych zaalokowanych na HEAP
    //dwa new po sobie mogą zwrócić adresy nie następujące po sobie
}

#include<vector>
void vectorAndStack()
{
    //w tablicach trzeba pamiętać ile elementów używamy bo może być większa
        //zaalokowana pamięć niż potrzebna

    //vector lenght -> ile elementów używamy, capacity -> ile jest zaalokowane

    std::vector<int> vec;
    vec.resize(5);//zmieniło length na 5
    for (auto const& elem : vec)
    {
        printf("%d ", elem);
    }
    printf("\n");

    std::vector<int> vec2 {1,2,3,4,5,6,7,8,9,10,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    vec2.reserve(1000);//zaalokuj pamięć na przyszłość
    printf("Vector length: %lu, capacity: %lu\n", vec2.size(), vec2.capacity());
    //capacity może być równa lub większa size żeby nie allokować ciągle
    //[] .at bazuje na size a nie capacity
    //można działać na nim jak na stosie:
    //push_back, back(return element not pop), pop_back
}

void recursion()
{
    //łatwo przegiąć bo stos mały...
    //każdy problem rekurencyjny można rozwiązać iteracyjnie ale
        //czasami bardzo trudno
    //iteracyjne prawie zawsze są bardziej wydajne
    //!!!unikać rekurencji chyba że implementacja będzie znacznie prostsza
}

void errorsCerrExit()
{
    //syntax error -> niezgodny z gramatyką -> proste do znalezienia/naprawy
    //semantic error -> kod robi coś źle crasch, złe dane ...

    //BLEDY SEMANTYCZNE
    //logiczne -> x>=5 x print x>5
    //naruszone założenie -> np string zamiast inta wprowadzony przez usera

    //Defensive programming 
    //metodyka programowania identyfikuje założenia które mogą być naruszone
        //sprawdzanie parametrów funkcji np czy nie nullptr
        //sprawdzanie zwróconej wartości np czy funkcja nie zwróciła -1
        //sprawdzanie inputu

    //jak coś nie tak można zwrócić -1 lub std::exit() z cstdlib
    //jak zły input zapytać ponownie
    //w graficznych popup
    //wypisać błąd
    fprintf(stderr, "%s", "sample error\n");
    std::cerr << "sample error 2" << std::endl;
}


#define NDEBUG //ignoruje teraz wszystkie asserty
#include <cassert>
void assertStaticAssert()
{
    //assert statement -> makro preprocesora -> ewoluuje do
    //conditional statement w runetime

    //true -> nic nie robi, false wyświetla error i zabija program
    assert(5 < 4); //poda nr linii, finkcję plik itp
    assert((5 < 4) && "dodatkowe info o bledzie"); //więcej info
    assert(5 < 6);

    //!!!3 powyższe zignorowane macrem NDEBUG

    //od c++11 STATIC ASSERT -> działą na etapie kompilacji
    //powoduje error kompilacji
    //nie wyłacza go macro NDEBUG
    //static_assert(5 < 5, "error");
}


void commandLineArgs(int argc, char** argv)
{
    printf("Ilosc argumentow programu %d, pierwszy parametr %s\n", argc, argv[0]);
    //argv[1] tp pierwszy argument z uruchomienia programu
    //argumenty zą zawsze przekazowane jako cstring
}


#include <cstdarg>
int returnSum(int ilosc, ...)
{
    int sum {0};
    va_list list;//element do odostępu do danych
    va_start(list, ilosc);//inicjalizacja pierwszym parametrem
                          //jest konieczny do inicjalizacji

    for (int i = 0; i < ilosc; ++i)
        sum+=va_arg(list,int);//zdejmujemy pierwszy parametr z listy

    va_end(list);//czyścimy

    return sum;
}
int returnSum2(int firstParam, ...)
{
    int sum {0};
    va_list list;//element do odostępu do danych
    va_start(list, firstParam);//inicjalizacja pierwszym parametrem

    for (;;)
    {
        int elem = va_arg(list, int);//zdejmujemy pierwszy parametr z listy
        if (elem == -1)
            break;
        sum+=elem;
    }

    va_end(list);//czyścimy

    return sum;
}
void ellipsisVaList()
{
    //!!!funkcja która używa elipsis "..." musi mieć chociaż jeden normalny
        //parametr
    //... muszą być na końcu
    printf("Suma to %d\n", returnSum(8,1,2,3,4,5,6,7,8));

    //zadziała bo potraktuje bity jako int
    //prawdopodobnie czyta przedostatni parametr jako aaaa zamiast 7
    printf("Suma to %d\n", returnSum(8,1,2,3,4,5,"aaaaaaaaaaaaaaaaaaaaaaaaaa",7,8));

    //!!!można przesłać argumenty różnych typów i różną ilość
    //!!!możemy podać zbyt mało argumentów i odczyta spam ze stosu

    //też chujnia bo wymaga podania -1 na końcu
    printf("Suma to %d\n", returnSum2(1,2,3,4,5,6,7,8,-1));

    //!!!nie używać w ogóle ellipsis
}