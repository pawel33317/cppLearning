#include <iostream>
#include <functional>
#include <atomic>
#include <thread>
#include <cstddef>
#include <boost/type_index.hpp>
using namespace std;

class AlignasStandard{
    int a;
    int b;
};

class alignas(128) AlignasDefined {
    int a;
    int b;
};

void throww(){}
void nothtoww() noexcept { if (5 ==5 ) throw std::runtime_error("xx");}

int mainxxx()
{
    cout << "Fazy translacji" << endl;
    cout << "AlignasStandard size: " << sizeof(AlignasStandard) << endl;
    cout << "AlignasDefined size: " << sizeof(AlignasDefined) << endl;

    cout << "AlignasStandard alignof: " << alignof(AlignasStandard) << endl;
    cout << "AlignasDefined alignof: " << alignof(AlignasDefined) << endl;
    std::cout << alignof(std::max_align_t) << '\n';

    //Value categories
    //każde wyrazenie ma typ i i value category: prvalue, xvalue, and lvalue.
    //glvalue - generalized lvaue - wyrażenie, którego wykonanie określa tożsamość obiektu
        //referencja do istniejącego już obiektu lub odnoszenie się do zmiennej przez jej nazwę
    //lvalue - glvalue, które dodatkowo nie przenosi wartości zmiennych (nie jest x-value)
        //static int i; return i;
        //int a;
        //A a; a->x

    //xvalue - glvalue, które oznacza obiekt jako możliwy do reuzycia
        //static_cast<Foo&&>(a);
        //std::move(a).member; //bo a jest zrzutowane do &&
    //rvalue - każde prvalue lub xvalue
    //prvalue - pure rvalue - wyrazenie, które zwraca wartość również vpod
        //5
        //struct Foo{};  Foo{};
        //Foo foo(); foo();
    




    //decltype
    //jeżeli argument jest identyfikatorem bez dodatkowych naziwsów (zwraca typ)
    int i;
    int& j = i;
    std::cout << "decltype(i) ->" << typeid(decltype(i)).name() << '\n';//int
    std::cout << "decltype((i)) ->" << typeid(decltype((i))).name() << '\n';//int&
    std::cout << boost::typeindex::type_id_with_cvr<decltype(i)>().pretty_name() << '\n';
    std::cout << boost::typeindex::type_id_with_cvr<decltype((i))>().pretty_name() << '\n';
    //jeżeli jest innym wyrażeniem
    //jak argument to xvalue zwraca T&&
    cout << "------------\n";
    std::cout << boost::typeindex::type_id_with_cvr<decltype(static_cast<int&&>(i))>().pretty_name() << '\n';
    //jak argument to lvalue zwraca T&
    std::cout << boost::typeindex::type_id_with_cvr<decltype(j)>().pretty_name() << '\n';
    std::cout << boost::typeindex::type_id_with_cvr<decltype((i))>().pretty_name() << '\n';
    //jak argument to prvalue zwraca T
    std::cout << boost::typeindex::type_id_with_cvr<decltype(5)>().pretty_name() << '\n';
    cout << "------------\n";


    static_assert(5 == 5);

    //CV types
    //każdy typ poza funkcjami i referencjami ma dodatkowo odrębny typ
    //const stały obiekt lub niemutuwalny subtobject const obiektu - modyfikacja powoduje comilation error
            //a zmiana trukiem np przez referencje powoduje undefined behavior
    //volatile do optymalizacji głónie
    //const vilatile zachowuje się jak oba powyższe
    //mutable umożliwia zmianę membera naet jeżeli jego obiekt jest const
    //mutable w lambdach umożliwia modyfikacje obiektów przechwyconych przez kopię


    cout << "noexcept(5)" << noexcept(5) << endl;
    cout << "noexcept(5)" << noexcept(throw std::runtime_error("xx")) << endl;
    cout << "noexcept(throww())" << noexcept(throww()) << endl;
    cout << "noexcept(nothtoww())" << noexcept(nothtoww()) << endl;
    //nothtoww();//rzuca wyjatek
    cout << "po funkcji ktora rzucila wyjatek";
    //ZNAM
    //and, and_eq, bitand, bitor, not, not_eq, or, or_eq, xor, xor_eq
    //asm
    //auto
    //bool, char, char8_t/16/32, double, float, int, long, short, void, wchar
    //break, switch, case
    //catch, try
    //class, enum, struct, union
    //compl - ~
    //const
    //constexpr
    //const_cast, dynamic_cast, reinterpret_cast, static_cast
    //continue
    //default, delete
    //do, for, while
    //else, if
    //explicit - konstruktor/funkcja nie może być wywołany przez niejawną konwersję obiektu
    //false, true
    //friend
    //goto
    //namespace
    //new, delete
    //nullptr
    //operator
    //private, protected, public
    //register
    //return
    //signed, unsigned
    //sizeof
    //static
    //template
    //this
    //typedef
    //virtual
    //override


    //CZESCIOWO ZNAM
    //+decltype
    //+export w templatkach umożliwia teh samej templatce być zadeklarowaną ale nie zdefiniowaną w innym translation unicie
    //+extern przy deklaracji ustawia linkage i nie wpłyta na linkage (static lub thread)
    //+inline - musi być dostępna w danym translation unicie, of 17 można robić inline funkcje i zmienne które mogą miec inne definicje w innych translation unitach
    //+mutable
    //+static_assert sprawddzenie w czasie kompilacji
    //+thread_local - czas życia zmiennej
    //+throw - jako wyrażenie rzuca lub rerzuca otrzymany wyjątek jako specyfikator deprecated
    //+typeid - ma informacje o obiekcie, używany gdy dynamiczny typ polimorficznego obiektu musi być znany
    //+using 1. do namespaców, 2. zmienia z protected na public "using B::m;", w enumach do wkopiowywania ich memberów do klas
        //4. Jako alias podobnie jak typedef do skracania nazw np długich templatek
    //+volatile
    //final wirtualna funkcja nie może być overridowana kub że z klasy nei można dziedziczyć

    // int g;
    // transaction_safe   {
    //     g++;
    //     g++;

    // }
    //NIE ZNAM
    //+typename 1. parametr templatki jak calsss. 2. wewnątrz templatek
    //+noexcept
        //jako operator robie compile-time check  czy wyrażenie nie zadeklarowane jako nierzucające wyjątków
        //jako specyfikator chyba tylko rzuca ostrzeżenie jak funkcja może rzucić wyjątek
    //+synchronized - nie są transakcjami jak poniższe atomowe bloki i mogą wykonać niebezpieczne dla transakcji funkcje
    //+atomic_cancel, atomic_commit, atomic_noexcept - - tranzakcyjne synchronizacje - inne zachowanie w zależności jakby poszedłwyjątek w transakcji
    //_Pragma
    //reflexpr
    //concept - cpp20
    //constint, consteval - cpp20
    //co_await co_return co_yield - corutine cpp20
    //requires - cpp20
    //ID: impott, module
    //ID: transaction_safe, transaction_safe_dynamic

}