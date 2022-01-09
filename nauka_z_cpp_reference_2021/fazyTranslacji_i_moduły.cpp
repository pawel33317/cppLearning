#include <iostream>
#include <functional>
#include <atomic>
#include <thread>
using namespace std;

int main3()
{
    cout << "Fazy translacji" << endl;

    //1 zamiana znaków na zrozumiałe dla kompilatora zależne od implementacji kompilatora oraz trigrapy	??= na  # - potrzebny paramet kompilacji -trigraphs
    //2 łżczy linie zakończone "\"
    //3 rozłożenie na sekwencje znaków, tokeny czy komentarze, zamiana komentarzy na spacje, cofnięcie części operacji z fazy 1 i 2 
    //4 wykonanie przprocesora i dla każdego includa zrobienie faz od 1 do 4, isunięcue dyrektyw include
    //5 wszystkie literały zamieniane na execution character sety i zamiana znaków specjalnych  też na te sety
    //6 łączenie przylegających literałów
    //7 kompilacja zamiana processing tokenów na tokeny, sprawdzanie składni i semantyki i finalna translacja tokenów do transaction unitu
    //8 sprawdzenie czy translation unit generuje wymagane templatki i generowane są instantion unity
    //9 jednostki translacji, instantion unity i biblioteki są łączone w program wraz z informacjami jak go odpalić w środowisku

    //w cpp20 wprowadzono moduły żeby dzielić deklaracje i definicje między jednostkami translacji
}