#include <iostream>

//  /usr/bin/g++-11 -std=c++2a -Wall -O0 -o interfaces 2_interfaces.cpp && ./interfaces


int main()
{
    //interfejsy - kontrakt między częściami programu

    //1 rób jawne interfejsy
        //kontrolowanie funkcji przez jakąś zmienną globalną - 2 wywołania mogą dać inne wyniki
            /*int round(double d)
            {
                return (round_up) ? ceil(d) : d;    // don't: "invisible" dependency
            }*/
        //raportowanie błędu przez printfa czyli log, które może być przeoczone zamiast np przez exception
        //!!!!!unikaj przenoszenia informacji między interfejsami inaczej niż przez zmienne lokalne

    //2 unikać non-const globalnych zmiennych
        //struct Data {} date; //bad
        //void fun(){} //bad
        //!!!inicjalizacja zmiennych globalnych nie jest całkowicie ordered więc lepiej robić const
        //globalny obiekt jest często lepszy niż singleton
        //używać do globalnych namespaców lub umieszczać w klasach 
        //nie ma race condition na immutable data

    //3 unikać singletonów (skomplikowanych globalnych obiektów w przebraniu)
        //ciężkie w testowanie, łatwo coś przeoczyc
        /*
            X& myX()
            {
                static X my_x {3};
                return my_x;
            }
        */ 
       //przez to że statyczna rozwiązany jest problem z kolejnością inicjalizacji nawet wielowątkowo
       //bo wątek czeka na inicjalizację statycznej ale w poniższym przypadku będzie problem z destrukcją
       //jakiś wątek to musi zrobić więc trzeba synchronizację napisać
        /*X& myX()
        {
            static auto p = new X {3};
            return *p;  // potential leak
        }*/












    //KONIEC
    std::cout << "\nEND\n";
}


