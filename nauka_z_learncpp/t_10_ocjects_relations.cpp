#include <iostream>
#include "all.hpp"

void kompozycja();
void agregacja();
void asocjacja();
void dependency();
void klasyKontenerowe();
void initializerList();

void t_10_ocjects_relations()
{
    printf("\n\n-----chapter 10 started-----\n");
    kompozycja();
    agregacja();
    asocjacja();
    dependency();
    klasyKontenerowe();
    initializerList();
}


class KompozycjaCzlowiek
{
public:
    ~KompozycjaCzlowiek()
    {
        delete[] umiejetnosci;
    }
    KompozycjaCzlowiek(int iloscUmiejetnosci)
    {
        umiejetnosci = new int[iloscUmiejetnosci];
    }
    void print(std::string daneZewnetrzne) { printf("%s", daneZewnetrzne.c_str());}
    int wiek;
    std::string imie;
    std::string nazwisko;
    int* umiejetnosci;
};
void kompozycja()//composition
{
    //part of: //!!!jest częścią
        //budowanie złożonego obiektu z prostych np:
        //komputer -> płyta, cpu, karta...

    //klasy i struktury sączęsto nazywane composite type

    //!!!kompozycja ma dwa typy kompozycję i agregację

    //!!!kompozycja warunki relacji
        //member jest częścią obiektu
        //member może należeć tylko do jednej klasy w danym czasie
        //życie membera zależy od klasy -> tworzony i niszczony z obiektem
        //member nic nie wie o klasie UNDIRECTIONAL -> relacja jednokierunkowa
            //-> obiekt nie wie że jest częścią klasy

    //Kompozycja nie mówi nic o przenoszeniu części
        //można przenosić pola
        //może mieć jedno pole danego typu lub WIELE
        //NP klasa ulamek ma licznik i mianownik
            //licznik i mianownik nie wiedza ze sa czescia klasy

    //!!!kompozycją są klasy i struktory z normalnymi danymi stosowymi
        //oraz dynamicznymi ale klasa musi nimi zarządzać
        //danymi klasy zarządza tylko klasa w przypadku kompozycji

    //kompozycja może korzystać z części które dostała jako dane wejściowe
        //zamiast tworzyć własną część
        //kompozycja może przekazać destrukcję memberów innemu obiektowi
            //np garbage collector

    //Kiedy tworzyć klasy i subklasy zamiast bezpośredniej implementacji ?
        //Np klasa CREATURE ma w sobie klasę LOCATION która ma 2 inty x i y
        //można zrobić CREATURE które ma 2 inty zamiast klasy LOCATION (gorsze)
        //rozwiązanie z klasą LOCATION lepsze bo klasa jest prostsza łatwiejsza
            //do zrozumienia bardziej skoncentrowana
        //może być reusable nawet do innych celów
        //klasa zawierająca LOCATION będzie mniej złożona bo location może
            //robić ciężką pracę
        //dobrze żeby jedna klasa robiła jedną pracę i nie martwić się
            //o pracę subklas
}



class Teacher
{
public:
    Teacher() {};
};
class Department
{
    Teacher* t;
public:
    Department(Teacher* q) : t(q) {}
};
void agregacja()
{
    //has-a: //!!!obiekt ma
    //agregacje -> drugi rodzaj kompozycji

    //warunki
        //member lub wiele memberów jest częścią klasy 
        //member może należeć do więcej niż jednego obiektu klasy
            //w tym samym czasie pointery i referencje
        //życie membera nie jest zarządzane przez obiekt
        //member nie wie o istnieniu klasy

    //undirectional relation
    //agregacja nie jest odpowiedzialna za tworzenie i niszczenie memberów

    Teacher* t1{};
    Department d1 {t1};

    delete[] t1; //jeszcze żyje

    //!!!jak robimy program zaimplementujmy NAJPROSTSZA relację,
        //która spełnia nasze potrzeby a nie taką,
        //która wydaje się być poprawna w realnym świecie

    //agregację można mieszać z kompozycją
    //agregacja jest niebezpieczniejsza bo nie kasuje memberów
        //i może być memory leak
    //faworyzować kompozycję nad agregacją
}



#include<vector>
class Doktor;
class Pacjent
{
    std::string mImie;
    std::vector<Doktor*> lekarze;
public:
    Pacjent(std::string imie) : mImie(imie) {}
    void dodajLekarza(Doktor* doktor) {lekarze.push_back(doktor);};
    friend std::ostream& operator<<(std::ostream& o, const Doktor& d);
};
class Doktor
{
    std::string mImie;
    std::vector<Pacjent*> pacjenci;
public:
    Doktor(std::string imie) : mImie(imie) {}
    void dodajPacjenta(Pacjent* pacjent) {pacjenci.push_back(pacjent);};
    friend std::ostream& operator<<(std::ostream& o, const Doktor& d);
};
std::ostream& operator<<(std::ostream& o, const Doktor& d)
{
    o << "Lekarz: " << d.mImie << " ma pacjentow: ";
    for (const auto& pacjent : d.pacjenci)
    {
        o << pacjent->mImie << " ";
    }
    o << std::endl;
    return o;
}

struct Car
{
    int id;
    std::string nazwa;
};
struct CarWarehause
{
    Car cars[4] {Car{1, "Toyota"}, Car{2, "VAG"},
                 Car{3, "Mercedes"}, Car{4, "BMW"}};
};
struct Driver
{
    int carID;
    std::string imie;
};
using namespace std;
void asocjacja()
{
    //brak domniemanych relacji całość <-> część

    //warunki
        //member nie jest związany z klasą
        //member może należeć do więcej niż jednej klasy w danym czasie
        //obiekt nie zarządza czasem życia membera
        //member może ale nie musi wiedzieć o życiu obiektu

    //np doktor ma relacje z pacjentem ale pacjentem ale
        //pacjent nie jest częścią doktora
        //pacjent może mieć wielu doktorów a doktor pacientów
        //ich czas życia nie jest powiązany

    //uses-a -> doktor używa pacjenta do zarobku
    //pacjent używa doktora do leczenia

    //asocjacje mogą być implementowane na wiele sposobów
    Pacjent* p1 = new Pacjent("pMarek");
    Pacjent* p2 = new Pacjent("pStasiek");
    Doktor* d1 = new Doktor("dZbyszek");
    Doktor* d2 = new Doktor("dSeba");
    p1->dodajLekarza(d1);
    p2->dodajLekarza(d1);
    p2->dodajLekarza(d2);
    d1->dodajPacjenta(p2);
    d2->dodajPacjenta(p1);
    d2->dodajPacjenta(p2);
    std::cout << *d2;

    //unikać dwukierunkowych relacji bo łatwo o błąd

    //obiekty mogą mieć relacje z obiektami tego samego typu
        // -> reflexife associaton == zwrotne powiązanie
        //np trening ma w sobie powiązanie do obiektu trening -> wymagania wstępne


    //Inny pokaz asocjacji jednokierunkowej bez pointerów z klasą pośrednią
    Driver r {3, "Pawel"};
    CarWarehause cw;
    cout << r.imie << " ma samochod " << cw.cars[r.carID].nazwa << endl;
        //zamiast pointera Driver ma id obiektu
        //lepsze gdy mamy coś w bazie lub pliku

    // property          COMPOSITION         AGGREGATION         ASSOCIATION
    // relation          WHOLE/PART          WHOLE/PART          UNRELATED
    // member can belong
    // to many classes   NO                  YES                 YES
    // manage member
    // existence         YES                 NO                  NO
    // directionaly      UNDIRECTIONAL       UNDIRECTIONAL       UNDIRECTIONAL OR BIDIRECTIONAL
    // relation verb     PART OF             HAS A               USES A
}

void dependency()
{
    //np kwiat pszczoła -> kolejny najprostszy typ relacji
        //obiekt wywołuje funkcjonalność innego obiektu do ukończenia zadania
        //najsłabsza relacja jednokierunkowa

    cout << "cout jest powiązany z tym tekstem" << endl;

    //różnice z asocjacją
        //w asocjacji jedna klasa trzyma pośredni lub bezpośredni link do drugiej
        //np doktor ma array pacjentów i może zawsze ich sprawdzić

    //dependency nie są reprezentowane na poziomie klasy
        //zależny obiekt nie jest zlinkowany jako member
        //potrzebny obiekt jest tworzony na potrzebę np otwarcie pliku
}

#include <cstring>
class IntArray
{
private:
    int mSize;
    int* mData;
public:
    IntArray() : mSize(0), mData(nullptr) {}
    IntArray(int size) : mSize(size), mData(new int[size]) {}
    ~IntArray()
    {
        delete[] mData;
    }
    void erase()
    {
        delete[] mData;
        mData = nullptr;
        mSize = 0;
    }
    int& operator[](int index)
    {
        return mData[index];
    }
    void realocate(int newSize)
    {
        erase();
        mData = new int[newSize];
        mSize = newSize;
    }
    void resize(int newSize)
    {
        int* newData = new int[newSize];
        std::memcpy(newData, mData, (mSize<newSize?mSize:newSize)*sizeof(int));
        delete[] mData;
        mData = newData;
    }
    void insertBefore(int val, int index)
    {
        int* newData = new int[mSize+1];
        std::memcpy(newData, mData, index*sizeof(int));
        std::memcpy(newData + index + 1, mData + index, (mSize-index)*sizeof(int));
        newData[index] = val;
        delete[] mData;
        mData = newData;
        ++mSize;
    }
    void remove(int index)
    {
        int* newData = new int[mSize-1];
        std::memcpy(newData, mData, index*sizeof(int));
        std::memcpy(newData + index, mData + index + 1, (mSize-index)*sizeof(int));
        delete[] mData;
        mData = newData;
        --mSize;
    }
    friend std::ostream& operator<<(std::ostream& o, const IntArray& ia);
};
std::ostream& operator<<(std::ostream& o, const IntArray& ia)
{
    o << "IntArray size: " << ia.mSize << ", data: ";
    for(int i = 0; i < ia.mSize; ++i)
    {
        o << ia.mData[i] << " ";
    }
    o << std::endl;
    return o;
}

void klasyKontenerowe()
{
    //mają:
        //tworzenie pustego kontenera
        //insert obiektu
        //remove obiektu
        //raport ilości obiektów
        //czyszczenie kontenera
        //dostarczają dostęp do obiektów
        //sortują elementy

    //konterner klasy występują zwykle w 2 wariantach
    //Value containers -> compositions trzymają kopie obiektów
        //i zarządzają ich życiem

    //Reference containers -> aggregations -> trzymają pointery
        //i nie odpowiadają za życie

    //kontenery mogą trzymać jeden typ danych w c++

    IntArray ia(4);
    ia[0] = 0;
    ia[1] = 1;
    ia[2] = 2;
    ia[3] = 3;
    std::cout << ia;
    ia.insertBefore(9, 1);
    ia.insertBefore(7, 0);
    std::cout << ia;
    ia.remove(0);
    ia.remove(1);
    std::cout << ia;
    ia.erase();
    std::cout << ia;
}

#include <initializer_list>
class IntArray2 : public IntArray
{
public:
    explicit IntArray2(const std::initializer_list<int>& il)
        : IntArray(il.size())
    {
        std::cout << "IntArray2 Initializer list\n";
        int iterator = 0;
        for (const auto& elem : il)
        {
            (*this)[iterator++] = elem;
        }
    }
    IntArray2(const IntArray2&) = delete;
    IntArray2& operator=(const std::initializer_list<int>& il)
    {
        realocate(il.size());
        int iterator = 0;
        for (const auto& elem : il)
            (*this)[iterator++] = elem;
        return *this;
    }
};
void initializerList()
{
    cout << "==========================\n";
    int array[5] {1,2,3,4,5};
        //uniform initialization or initializer_list ??
    int array2[5] = {1,2,3,4,5};
        //initializer_list
    int* array3 = new int[5] {1,2,3,4,5};
        //int* array4 = new int[5] = {1,2,3,4,5}; ERROR

    t_nicNieRob(array);
    t_nicNieRob(array2);
    t_nicNieRob(array3);
    delete[] array3;

    //przed c++11 list initialization była dostępna tylko dla
        //statycznych i dynamicznych tablic

    //!!!gdy kompilator widzi initializer list antomatycznie konwertuje
        //go do obiektu std::initializer_list

    //std::initializer_list ma metodę size która zwraca ilość elementów
    //std::initializer_list nie ma przeciazonego operatora [] nie wiadomo czemu

    //!!!Przy implementacji konstruktora z std::initializer_list powinno się dodać
        //!!!list assigment operator
        //!!!deep copy
        //!!!zrobić konstruktor explicit

    IntArray2 ia2 {1,22,33,4,5};

    //IntArray2 ia3 = {1,2,3,4,5};
        //nie zadziala tylko przez explicit

    //std::initializer list można użyć też dla operatora przypisania
        //żeby zmienić aktualne wartości
    ia2 = {55,66,77,88,99,999,888,777,666};//operator przypisania
    cout << ia2;
}