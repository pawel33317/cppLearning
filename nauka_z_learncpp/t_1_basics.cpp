#include <iostream>//dodaj zawartość tego pliku tutaj

void strukturaProgramu();
void zmienneInicjalizacjaiPrzypisanie();
void funkcje();
void zasadyNazwenictwa();
void operatory();
void bialeZnaki();
void forwardDeclaration();
void t_functionWithoutDeclarationInHpp();
void headerFiles();
void preprocesor();
void headerGuards();


void t_1_basics()
{
    std::cout << "-----chapter 1 started-----\n";
    strukturaProgramu();
    zmienneInicjalizacjaiPrzypisanie();
    funkcje();
    zasadyNazwenictwa();
    operatory();
    bialeZnaki();
    forwardDeclaration();
    headerFiles();
    preprocesor();
    headerGuards();
}

void strukturaProgramu()
{
    //int x; //declaration statement
    //2 + 3; //expression statement

    //biblioteka prekompilowany kod zawierający np funkcje
    //i spakowany do ponownego użycia

    //syntax - składnia opisuje jak sentencje są skonstruowane w języku
}

void zmienneInicjalizacjaiPrzypisanie()
{
    //obiekt kawałek pamięci służący do przechowywania wartości
    //zmienna to obiekt który ma nazwę np int x;

    //definicja spowoduje odłożenie miejsca w pamięci
    int x; //np adres 0x1111
    x = 5; //zapisz pod adresem 0x1111 wartość 1

    //!!!zmienne w c++ są l-value --> bo mają trwały adres w pamięci
    //!!!jeżeli chcemy zrobić przypisanie lewa strona musi być l-value

    //!!!r-values wskazuje na wartości nie powiązane z trwałym adresem w pamięci
    //!!!np pojedyncze liczby "6", wyrażenia "5+5"
    //!!!r-values są tymczasowe i znikają po statement gdzie wystąpiły

    x = x + 1; //l-val + r-val evaluate to r-val and is assigned to l-val;

    //!!!lewa strona musi mieć adres a prawa produkować wartość

    //int y; //declaration
    //y = 4;//assigment
    //int u = 5;//initialization
    //inicjalizacja może być tylko po definicji

    //!!!używać inicjalizacji zamiast przypisania jak możliwe
    //zmienne lokalne nie są domyślnie inicjalizowane więc jest spam
}

void funkcje()
{
    //!!!main domyśnie zwraca zwykle 0 -> status code 0=OK 0!=ERROR
    //nie można definiować funkcji w innej funkcji

    //zalety funkcji organizacja, reużywalność, testowanie, rozszerzalność
    //!!!abstrakcja trzeba znać tylko we i wy
    //używać do: kodu który się powtarza, kodu który ma zestaw we i wy
    //funkcja powinna robić 1 rzecz
    //jak funkcja jest zbyt długa trzeba dzielić
}

void zasadyNazwenictwa()
{
    //zmienne z małych liter
    //int zmienna;

    //funkcje z małej litery i każde kolejne słowo z dużej lub separator underscore
    //nie nazywac zmiennych i funkcji zaczynając od "_" jest to zarezerwowane
}

void operatory()
{
    //!!!literał zafixowana wartość (zahardkodowana w kodzie)
    //literał zwraca siebie
    //operand - literał, zmienna i funkcja - zwracają wartość
    //operator "np +" mówi jak łączyć operandy

    //operatory są unarne "-", binarne "+", terenary ??? - 
    //"-" jest i unarny i binarny
}

void bialeZnaki()
{
    //linia powinna mieć max 80 znaków
    //wcięcia to tabulacja lub 4 spacje
    //jeżeli linia jest zbyt długa powinna być łamana a operator na końcu linii
    //jeżeli np inicjalizujemy kilka zmiennych można przesunąć spacjami
    //lub tabami wartości do tego samego poziomu
}

void forwardDeclaration()
{
    //np dla tej funkcji jest na górze tego pliku

    //forwardDeclaration(); forward declaration czyli function prototype
    //forwardDeclaration(int a);
    //forwardDeclaration(int); też ok

    //!!!jeżeli nie będzie ciała funkcji program skompiluje się poprawnie
    //!!!ale przy linkowaniu się wywali jeżeli będzie użycie

    //deklaracja mówi jedynie kompilatorowi że funkcja istnieje

    //int x; to jest i definicja i deklaracja

    //poniższa funkcja jest w innym pliku i nie jest includowana
    //więc nie można wykonać poniższej funkcji bo jest brak deklaracji
    //aby zadeklarować że istnieje można to zrobić w dowolnym pliku np w tym
    //nie musi to być hpp od pliku w którym jest funkcja
    t_functionWithoutDeclarationInHpp();
}

void headerFiles()
{
    //!!!pliki header zostały stworzone aby umieszczać w nich forward deklaracje
    //nie powinno tam być kodu bo zostanie wincludowany

    //<include> jak plik został załączony razem z kompilatorem w specjalnym
        //miejscu wyznaczonym przez system
    //"include" jak plik był dostarczony czyli powinien szukać w source kodzie
        //później w innych dołączonych lokalizacjach do kompilacji
    //"" dla wszystkich plików poza dołączonymi przez kompilator

    //nie powinno polegać się na includach w header plikach
    //jeżeli jest potrzebny w cpp powinien tam też załączony

    //"iostream.h" != "iostream"
    //iostream bez h zostałstworzony po ustandaryzowaniu ANSI cpp i funkcje
        //zostały wrzucone do std
    //stary pozostał dla kompatybilności

    //include z subkatalogu
    //#include "../headers/header.h" ZLA OPCJA
    //lepsza g++ -o main -I headers/   --> #include<header.h>
}

void preprocesor()
{
    //nie rozumie kodu traktuje go jako text

    //MAKRA
    #define AAAA 55 //object-like macro zastępuje po jego wystąpieniu każde AAAA n 55

    #define USE_ABC //każde jego wystąpienie będzie kasowane

    #ifdef USE_ABC //pozwala sprawdzić czy wartość została zdefiniowana
    printf("USE_ABC zdefiniowane przez macro\n");
    #endif
    #ifndef XXXXX
    printf("XXXXX nie zostało zdefiniowane przez macro\n");
    #endif
}

void headerGuards()
{
    //zabezpieczają przed wielokrotnym includem tego samego pliku np kiedy
        //includujemy w pliku C plik A i B a B includuje A

    #ifndef CHAPTER1_HPP //na początku pliku
    #define CHAPTER1_HPP
    printf("Wewnątrz header guarda\n");
    #endif //na końcu pliku

    //#pragma once //zastępuje header guardy ale nie jest oficjalna
}