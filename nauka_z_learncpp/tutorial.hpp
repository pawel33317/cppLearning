#include <cstdlib>

void t_main_call(int argc, char* argv[]);

void t_1_basics();
void t_2_variables();
void t_3_operators();
void t_4_variables_and_more();
void t_5_flow_control();
void t_6_arrays_and_pointers();
void t_7_functions(int argc, char** argv);
void t_8_OOP_basics();
void t_9_operator_overloading();
void t_10_ocjects_relations();
void t_11_inheritance();
void t_12_polymorphism();
void t_13_templates();
void t_14_exceptions();
void t_15_move_sem_and_smart_ptr();
void t_16_STL_lib_containers_iterator();
void t_ApB_CPP11_14_17();



void t_nicNieRob(void*);
inline int t_getNum() {return 5;}


//0 intro, kompilacja
//1 basics
//2 variables, fundamental data types
//3 operatory
//4 bloki, scope, linkagestatic, namespaces, rzutowania, 
            //enumy, typedefy, struct i auto
//5 control flow, if, switch, goto, while,break, random
//6 arrays, sorcint, c-strings, pointers, dynamic memory, 
            //referebces, foreach, void ptr, std::array, std::vector
//7 parametry/argumenty funkcji ref ptr val, inline
            //fun overloading, domyślne parametry, wskaźniki na funkcje
            //stos i sterta, vector advanced, rekursja, handling errors
            //assert, static_assert, commandline args, ellipsis
//8 OOP podstawy, klasy i membery, public/private dostęp i enkapsulacja
            //konstruktory, inicjalizacja w konstruktorze, non-static inicjalizacja
            //nakładanie się konstruktorów, destruktory, THIS, klasy i headery
            //obiekty i metody i pola, static member variables and functions
            //friend functions, anonimowe obiekty, typy zagnieżdżone
            // o kodzie
//9 przeciazenia operatorow: aryrmetyczne, używając friend funkcji,
            //uzywajac normalnych funkcji, I/O, używając metod, unarne -+!m
            //==, ++ --, [], (), operator typecast, copy constructor,
            //copy initialization, konwertowanie konstruktorów jawnych i delete
            // = operator, shallow - deep copy
//10 relacje obiektów: kompozycja, agregacja, asocjacja, zależności,
            //klasy kontenerowe, initializer_list
//11 podstawy dziedziczenia, kolejność dziedziczenia, konstruktory i inicjalizacja
            //specyfikatory dostępu, nowe moetody w klasie dziedziczącej,
            //ukrywanie odziedziczonych funkcjonalności, wielodziedziczenie
//12 pointery i referencje do klasy bazowej
            //funkcje virtual i polimorfizm
            //overrride, final, covriant return type
            //virtual destruktory assigmenty i virtualization overriding
            //early binding and late binding
            //virtual table
            //pure virtual functions, abstract clases, interfaces
            //virtual base classes
            //object slicing
            //dynamic casting
            //operator << and printing inherited classes
//15 semantyka przenoszenia i smart pointery
            //r-values, move semantics, move constructors and assigments
            //std::move, unique_ptr, shared_ptr, weak_ptr
            //circural dependency issue
//appendixB //nowe w C++11
            //C++14, C++17
//13 function templates, function templateinstances, template classes
            //template non-type parameters, function template specialization
            //class template specialization
            //partial template specialization
            //partial template specialization for pointers
//14 wyjśtki, obsługa, funkcje i zwujanie stosu
            //niezłapane wyjącki, catch-all o specyyfikatory wyjątków
            //wyjątki a klasy i dziedziczenie
            //rethrowing wyjątków
            //try bloku
            //niebezpieczeństwa i słabe strony