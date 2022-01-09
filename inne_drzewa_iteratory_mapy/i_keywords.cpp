#include <iostream>
#include <memory>
#include <cassert>
using namespace std;


extern "C" int asmFunc();//definicja napisana w assemblerze

//Row string literal
asm(R"(
.globl asmFunc
    .type asmFunc, @function
    asmFunc:
    .cfi_startproc
    movl $7, %eax
    ret
    .cfi_endproc
)");

class SizeClass { double d; int i;};
class alignas(128) SizeClass2 { double d; int i;};
class alignas(1)   SizeClass3 { double d; int i;};//pominiete bo zbyt male
class alignas(32)   SizeClass4 { int i; char s; };
class alignas(8)   SizeClass5 { SizeClass2 ss; int i; char s; };

class MutableClass
{
public:
    mutable int i = 6;
    void changeConstMutableI(int newVal) const
    {
        i = newVal;
    }
};

void funcNoExcept() noexcept
{
    cout << "funcNoExcept" << endl;
    //throw 5; nie da się złapać, zabija program
}

void i_keywords()
{
    cout << "-----i_keywords-----\n";

    //alignas określa alligment
    //można dodać deklaracji zmiennej, nie-bitowego członka klasy
    //do deklaracji/definicji klasy/struktury/unii/enuma func param, exceptiona

    //!!!jak alignas jest mniejsze niż rzeczywiste będzie pominięty
    cout << "sizeof(SizeClass { double d; int i;};) = " <<
        sizeof(SizeClass) << endl;

    cout << "sizeof(alignas(128) SizeClass2 { double d; int i;};) = " <<
        sizeof(SizeClass2) << endl;

    cout << "alignas(8) SizeClass3 { double d; int i;}; = " <<
        sizeof(SizeClass3) << endl;

    cout << "alignas(32) SizeClass4 { int i; char s;}; = " <<
        sizeof(SizeClass4) << endl;

    cout << "alignas(8) SizeClass5 { int i; char s; SizeClass2 s;}; = " <<
        sizeof(SizeClass5) << endl;

    //alignof zwraca aliement w bajtach
    cout << "alignof(SizeClass) = " << alignof(SizeClass) << endl;
    cout << "alignof(SizeClass2) = " << alignof(SizeClass2) << endl;
    cout << "alignof(SizeClass3) = " << alignof(SizeClass3) << endl;
    cout << "alignof(SizeClass4) = " << alignof(SizeClass4) << endl;
    cout << "alignof(SizeClass5) = " << alignof(SizeClass5) << endl;

    //asm umożliwia osadzenie kodu assemblera w pliku cpp
    //deklaracja asm jest wspierana warunkowo więc może być nieobecna a nawet
    //mieć inne znaczenie
    int n = asmFunc();
    cout << n << endl;


    //Alternative operator representation
    //c++ może być pisany w dowolnym 7-bitowym zestawie znaków spoza ASCII, który
    //zawiera niezmienny zestaw znaków ISO 646. Jednak kilka operatorów w C++
    //wymaga znaków spoza zestawi ISO 646 {}[]#/^|~ są alternatywy
    //compl == ~
    //{ == <%
    //} == %>
    //[ == <:
    //and, xor, and_eq ...
    <%
        cout << "Inside block\n";
    %>


    //export
    //do C++11 używany aby zaznaczyć template definition jako exported, co pozwala,
    //że ta sama templatka będzie zadeklarowana ale nie zdefiniowana w innyej
    //jednostce translacji
    //odC++11 jest nieużywane


    //extern "C"
        //aby wywołać funkcję C z C++, zadeklarować C funkcję z "extern "C" i wywołać
        //extern "C" function func();
        //z kodu C++: func();

        //aby wywołać funkcję języka C++ z C analogicznie
        //zadeklarować funkcję C++ z extern "C" i wywołać
        //extern "C" function func();


    //mutable
    //umożliwia modyfikowanie zmiennej klasy, wewnątrz metody const
    //nie nadużywać, głównie stosuje się przy sekcjach krytycznych
    //tylko do niestatycznych członków, non-reference, non-const
    MutableClass mc;
    mc.changeConstMutableI(111);

    //noexcept specyfikator - specyfikuje czy funkcja może rzucać wyjątkami
    //jeżeli rzuci wyjątek program wywoła std::terminate,
    //nie da się złapać wyjątku
    funcNoExcept();

    //noexcept operator sprawdza w czasie kompilacji czy funkcja jest
    //noexceot
    cout << "Function funcNoExcept is noexcept ?: " <<
        noexcept(funcNoExcept()) << endl;
    cout << "Function asmFunc is noexcept ?: " <<
        noexcept(asmFunc()) << endl;


    //register do C++17 deprecated, Od C++17 nieużywane i zarezerwowane
    //sugerowało procesorowi do umieszczenia zmiennej w rejestrze

    //thread_local zmienia storage duration (duration) - na thread ze (static)
        //możnałączyć z static i extern keyword żeby ustawić linkage
        //tylko dla obiektów zadeklarowanych w namespace scope, block scope
        //i static data members
        //wskazuje, że obiekt ma thread duration
    thread_local int a = 5;
    cout << a << endl;

    //typeid - używana aby poznać dynamiczny typ polimorficznego obiektu
        //i do identyfikacji statycznych typów
        //konieczny include <typeinfo>, bez tego będzie źle sformatowane
    int a2;
    cout << typeid(a2).name() << endl;


    //typename || class -> do wyboru w templatkach

    //union - specjalny typ danych, który może trzymać tylko jeden ze swoich
    //niestatycznych data memberów w jednym czasie
    union Uuu
    {
        int a;
        char b;
    };//rozmiar 4B tylko inta
    Uuu uuu;
    uuu.a = 5;
    cout << sizeof(Uuu) << ", val: " << uuu.a << endl;

    //volatile - zmienna nie może zostać zoptymalizowana
        //może zmieniać pomiędzy odczytami
        //pojawiają się głównie w dostępie do sprzętu
        //spadek wydajności
    const volatile int var = 66;
    cout << "const volatile int var = " << var << endl;

    //transaction_safe_dynamic - transaction_safe
        //coś z wielowątkowością
        //--------------------------

}
