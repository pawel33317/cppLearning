#include <iostream>
#include <functional>
#include <atomic>
#include <thread>
using namespace std;


template<auto...>
class Test1 {};

template<int n>
class Test1b {
    public: void run(){ cout << "n=" << n << endl; }
};

template<class T> class my_array{};
template<class KEY, class VAL, template<class> class C = my_array>
class MyMap{
    C<KEY> key;
    C<VAL> val;
};

void abbreviatedTemplateFunc(bool a)
{
    cout << "bool version of abbreviatedTemplateFunc(auto a)=" << a << endl;
}
void abbreviatedTemplateFunc(auto a)
{
    cout << "abbreviatedTemplateFunc(auto a)=" << a << endl;
}
template<class T>
void fullFuncTemplate(T t){ }

//explicit initjzlizacja
template void fullFuncTemplate(int);

template<class T>
T funcTemplateRetArgDeduction(T t){ }

int mainTemplates()
{
   //Template - jednostka definiująca rodzinę klas lub funkcji
   //parametryzowana przez 1 lub więcej parametrów
        //type template parameter
        //non-type template parameter
        //template template parameter

    //kiedy dostarczane są argumenty do templatki są podmieniane z parametrami żeby uzyskać specjalizację
    //specyficzny typ, specjalizację można tez jawnie dostarczać: full specjalizacje są dozwolone 
    //dla klas i zmiennych i funkcji a częściowe tylko dla klas i zmiennych

    //kiedy spacjalizacja templacki jest rederenced w kontekście który jej wymaga jest instancjowana
    //kod jest kompilowany chyba że była już wcześniej zinstancjowana.

    //instancjowanie templlatki klasy nie powoduje zinstancjowania member funkcji do czasu ich użycia
    //podczas linkowania identyczne instancje są generowane przez różne translation unity i mergowane

    //definicja te,platki musi być widoczna w czasie niejawnego instancjowana więc są w headerach

    //Non-type template parameter !!!!!!!!!!!!!!!
            //z opcjonalną nazwą
            //z opcjonalną nazwą i domyślną wartością
            //parameter pack ... z opcjonalną nazwą
            //placeholder: auto lub decltype
        //musi miec strukturalny type
            //lval rev
            //integral, float
            //pointer, pointer to the member
            //enum
            //nullptr
            //literal class type
    Test1<5, 'z'> test1;//"string nie valid"
    Test1b<123> test1a;
    test1a.run();

    //Type template parameter !!!!!!!!!!!!!!!!!!
        //without default 
            //template<class T> class My_vector { /* ... */ };
        //with default 
            //template<class T = void> struct My_op_functor { /* ... */ };
        //type template parameter pack 
            //template<typename... Ts> class My_tuple { /* ... */ };
        // constrained type template
            //template <My_concept T> class My_constrained_vector { /* ... */ }; //template <My_concept T = void>
            // A constrained type template parameter pack.
                //template <My_concept... Ts> class My_constrained_tuple { /* ... */ };

    //Template template parameter!!!!!
    MyMap<int, std::string, my_array> mymapp;

    //func template można skrócić żeby w ogóle nie było template
    abbreviatedTemplateFunc(4);
    //funkcje też można specjalizować

    fullFuncTemplate(4);
    fullFuncTemplate(5.5);
    fullFuncTemplate<double>(5.5);
    fullFuncTemplate<>(5.5);
}