#include <iostream>
#include <typeinfo>
using namespace std;

void cpp11();
void cpp14();
void cpp17();

void t_ApB_CPP11_14_17()
{
    cout << "\n\n-----chapter appendixB started-----\n";
    cpp11();
    cpp14();
    cpp17();
}

void cpp11()
{
    //ISO zaakceptowało w 2011
    //dodano ogromną liczbę funkcjinalności

    //auto 4.8
    //char_16_t, char32_t ----------------------------
    //constexpr
    //decltype
    struct
    {
        string name;
    } object1;
    object1.name = "nazwa1";
    cout << "object1.name = " << object1.name << endl;
    decltype(object1) object2 {"nazwa2"};
    cout << "object2.name = " << object2.name << endl;

    //default wymusza utworzenie metody np konstruktora
        //domyślnego mimo, że zadeklarowaliśmy inny

    //delegating constructors - wywołanie innego konstruktora na
        //liście inilizacyjnej 8.6
        //konstruktor delegujący nie może nic inicjalizować na liście

    //converting konstruktor - konstruktory zdolne do niejawnej konwersji 9.13
        //np przekazujemy int 5 do funkcji przyjmującej typ ObjectX i int
        //zostanie do niego skonwertowany

    //explicit zabrania niejawnej konwersji w konstruktorach np przekazany
        //chara 9.13 nie zostanie zrzutowany na inta

    //delete konstruktor lub metoda każde użycie takiej funkcji jest rozważane
        //jako compilation error (zamiast robienia metod private) 9.13

    //enum clases 4.5a

    //extern templates ----------------------------

    //lambda expressions
        //[przechwytywanie](parametry)->returnType{ciało}
        //[]<tparams>()exceptionSpecifier->{}   //od C++20
        //[]()->{}   //const lambda obiekty pobierane przez kopię (tylko niektóre)
            //np statyczne czy constexpr chyba) są const w lambdzie
        //[](){}   //return type traktowany jako auto, czyli pobrany z returna
        //[]{}   //funkcja bez argumentów

        //przechwytywanie
        int l1 = 0;
        int l2 = 0;
        int l3 = 0;
        //auto lambda1 = []() { //nie widzi l1 i l2
        //auto lambda1 = [=](){ //nie pozwala na modyfikację l1 i l2
        auto lambda1 = [&, l3](){ //wszystko przez referencje oprocz l3
                                  //które jest przez wartość
            cout << l1++ << ++l2 << l3 << endl;
        };
        cout << ++l1 << ++l2 << endl;
        cout << typeid(lambda1).name() << endl;
        lambda1();

        void (*lambda2)() = []{ cout << "lambda2\n";};
        lambda2();
        [&l1](int& l2){ cout << ++l1 << ++l2 << "lambda3" << endl; }(l2);

    //long long (8b) 2.3

    //move constructor and move assigment 15.3

    //noexcept ----------------------------

    //nullptr 6.7a

    //override - sprawdzenie czy rzeczywiście coś overridujemy 12.2a
    
    //final - aby nie nadpisać wirtualnej dunkcji lub dziedziczyć z klasy 12.2a

    //foreach 6.12a

    //r-value references 15.2

    //static_assert - w przeciwieństwie do assert działa na etapie kompilacji 7.12a

    //std::initializer_list - IntArray(const std::initializer_list<int> &list) 10.7

    //trailing return type - auto add(int x, int y) -> int; 4.8

    //type aliases - using distance_t = double 4.6

    //typedef can not typedef template class ----------------------------

    //uniform initialization - {} zeruje, nie poazwla na narrowing 2.1

    //user-defined literals ----------------------------

    //variadic templates ----------------------------

    //>> naprawiony dla templatek ----------------------------

    //MASA NOWYCH KLAS W STL'u ----------------------------

    //lepszy multithreading i local-thread storage ----------------------------

    //hash tables ----------------------------

    //random number generation chapter 5

    //reference wrappers 12.8 vector<reference_wrapper<int>> vec;
        //int i = 5; vec.push_back(i);
        //functional header

    //regular expressions ----------------------------

    //auto_ptr deprecated 15.1

    //std::tuple 7.4a
        //std::tuple<int, double> returnTuple()
        //std::make_tuple(5, 6.7);
        //std::tuple<int, double> s = returnTuple();
        //std::tie(a, b) = returnTuple();
        //od cpp17 std::make_tuple(5, 6.7);

    //unique_ptr 15.5

    //unie mogą miec obiekty z nietrywialnym konstruktorem

    //nowe literały
        // u8"I'm a UTF-8 string."
        // u"This is a UTF-16 string."
        // U"This is a UTF-32 string."
        // surowe literały R"ala ma {}[]5,.kota"
}


void cpp14()
{
    cout << "--------------------cpp14-----\n";
    //mały update w większości poprawki

    //agregate member initialization
        //Rectangle x{ 2.0, 2.0 }; nawet jeżeli x.a i x.b mają domyslne wartości

    //binary literals
        int b = 0b1101;
        cout << b << endl;

    //digit separators
        int d = 1'001'001;
        cout << d << endl;

    //auto return type = auto add(int x, int y){}

    //generic lambdas and lambdas capture expressions ----------------------------

    //relaxed constexpr functions ----------------------------

    //variable templates ----------------------------

    //user-defined literals ----------------------------

    //std::make_unique 15.5
}

void cpp17()
{
    //zaakceptwana w 2017

    //__has_include preprocessor identifier to check if optional header files
        //are available

    //if statements that resolve at compile time

    //Initializers in if statements and switch statements

    //inline variables

    //Fold expressions

    //Nested namespaces can now be defined as namespace X::Y

    //Removal of std::auto_ptr and some other deprecated types

    //static_assert no longer requires a diagnostic text message parameter

    //std::any

    //std::byte

    //std::filesystem

    //std::opcional

    //std::shared_ptr can now manage C-style arrays
        //(but std::make_shared can’t create them yet)

    //Structured binding declarations

    //Template deduction for constructors

    //Trigraphs have been removed

    //typename can now be used (instead of class) in a template template parameter

    //UTF-8 (u8) character literals
}