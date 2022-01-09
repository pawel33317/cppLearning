#include <iostream>
#include <cstdio>

void t_nicNieRob(void*);
void arrays();
void simpleSort();
void multidimensionalArrays();
void cstringi();
void wskazniki();
void pointeryWtablicach();
void arytmetykaPointerow();
void cstringiIsymbolicconstants();
void dynamicznaAlokacja();
void pointeryIconsty();
void zmienneReferencyjne();
void foreachLoops();
void wielowymiaroweTablicePointery();
void stdArrayIvector();

void t_6_arrays_and_pointers()
{
    std::cout << "\n\n-----chapter 6 started-----\n";
    arrays();
    simpleSort();
    multidimensionalArrays();
    cstringi();
    wskazniki();
    pointeryWtablicach();
    arytmetykaPointerow();
    cstringiIsymbolicconstants();
    dynamicznaAlokacja();
    pointeryIconsty();
    zmienneReferencyjne();
    foreachLoops();
    wielowymiaroweTablicePointery();
    stdArrayIvector();
}


namespace Imie
{
    enum Imie
    {
        PAWEL,
        KAMIL,
        EWA,
        WSZYSCY
    };
}
//void funChangeArray(const int arr[5])
    //zapobiega zmianom compilation error jak będzie zmiana wartości
    //przyjmuje jako wskaźnik
    //void funChangeArray(int arr[]) //tak też przekazuje wskaźnik
    //void funChangeArray(int arr[5])//tak też przekazuje wskaźnik
void funChangeArray(int* arr)
{
    arr[4] = 55;
    printf("rozmiar WSKAZNIKA przekazanej do funkcji to: %lu\n", sizeof(arr));
}
void arrays()
{
    enum Zwierze
    {
        Ptak,
    };

    int array[4];//!!!length musi bać znany na etapie kompilacji
    array[Ptak] = 55;
    printf("array[enum] = %d\n", array[Ptak]);
        //nie działa dla enum class trzeba rzutować jawnie na inta

    int z = 5;
    int array2[z];//!!!z nieznane na etapie kompilacji, nie powinno się tak robić
                  //kompilatory mogą to akceptować ze względu na standard C99
                  //robią to dynamicznie..., tak samo jest z cin
    t_nicNieRob(array2);

    int initArr1[5] = {1, 2, 3, 4, 5}; //initializer list ?
    int initArr2[5] {1, 2, 3, 4, 5}; //uniform initialization ?
    int initArr3[] = {1, 2, 3, 4, 5};
    int initArr4[] {1, 2, 3, 4, 5};
    t_nicNieRob(initArr1);
    t_nicNieRob(initArr2);
    t_nicNieRob(initArr3);
    t_nicNieRob(initArr4);

    int initArr5[5] {1, 2};//pozostałe są inicjalizowane zerami
                           //jakby było za dużo compilation error
    printf("int initArr5[5] {1, 2}, initArr5[3]=%d\n", initArr5[3]);
    int arr6[] {}; //initjalizacja zerami - to akurat pusta tablica 0B
    std::cout << "sizeof(int arr6[] {}) = " << sizeof(arr6) << std::endl;
    t_nicNieRob(arr6);

    //trik z array która ma rozmiar enuma
    int array9[Imie::WSZYSCY];
    array9[Imie::EWA] = 99;
    printf("array9[Imie::EWA] = %d\n", array9[Imie::EWA]);

    //!!!używeanie enum class jako indexów tablicy jest bolesne przez castowanie
    //mozna zrobić zwykłego enuma w namespace

    //!!!tablice są przekazywane do funkcji jako wskaźnik
    int arr10[5] {};
    //int arr11[4] {};
    funChangeArray(arr10);
    //funChangeArray(arr11); zadziała ale to błąd bo zmieniamy nie nasz
        //obszar pamięci
    printf("Wartosc arr10[0] zmieniona przez funkcje to %d\n", arr10[4]);

    int arr12[4] {};
    //!!!sizeof dla array zwraca ilość_elementów*rozmiar_elementu
    printf("sozeof(arr12) (int arr[4]) = %lu\n", sizeof(arr12));

    //!!!zadziałą tylko w funkcji w któej została stworzona bo w innej będzie przekazana jako pointer i nie da się wyciągnąć rozmiaru
    printf("ilość elementów w tablicy %lu\n", sizeof(arr12)/sizeof(arr12[0]));

    //!!!zmiana elementu w tablicy który jest większy niż rozmiar lub ujemny
    //powoduje undevined behavior
}

#include <algorithm>
void simpleSort()
{
   int arr[] {4,77,55,2,1,56,8,34,11,0};
   for(auto& val : arr)
      printf("%d ", val);
   printf("\n");
   std::sort(arr, arr + (sizeof(arr)/sizeof(arr[0])));
   for(auto& val : arr)
      printf("%d ", val);
   printf("\n");

   int arr2[] {4,77,55,2,1,56,8,34,11,0};

   //select sort
   for (auto& a : arr2)
      for (auto& a2 : arr2)
         if (a2 > a)
            std::swap(a, a2);

   for(auto& val : arr2)
      printf("%d ", val);
   printf("\n");
}

void multidimensionalArrays()
{
    int array[][2] {{1,2},{1,2}};//!!!tylko pierwszy wymiar może nie być podany
    printf("array[1][1] = %d\n", array[1][1]);

    int array2[2][2] {};
    //!!!inicjalizacja tablic zerami działa tylko przy podanych jawnie wymiarach
    //!!! inaczaj będzie jednowymiarowa
    printf("array[1][1] = %d\n", array2[1][1]);

    //inicjalizacja tablic zerami działa tylko przy podanych jawnie wymiarach
    int array3[2][2] {0};
    printf("array[1][1] = %d\n", array3[1][1]);
}

#include <cstring>
void cstringi()
{
    char cstring[] = "cstring";
        //!!!automatycznie dodany \0 na końcu null terminator
        //cstring = "sssss"; nie wolno bo to tablica
    t_nicNieRob(cstring);
    printf("strcmp(a,a) = %d\n", strcmp(cstring, cstring));
    
    //std::cin.getline(name, 255); gwarantuje pobranie max 255 znaków
    //przydatne funkcje z cstring
    //strcpy
    //strcpy_s -> nie wszystkie kompilatory mają
    //strlen
    //strcat -> append string to another
    //strncat
    //strcmp, strncmp

    //!!!używać std::string z string header zamiast c-stringów
}

struct Struktura
{
    int val1;
    int val2;
};
void ptrFun(std::nullptr_t t)
{
    printf("przyjelam jako wskaznik nullptr\n");
}
void ptrFun(int* z)
{
    printf("funkcja przujmujaca wskaznik wywolana, adres wskaznika to %p\n", z);
}
void wskazniki()
{
    //operator address-of "&" unarny tym się różni od bitowego and
    //operator dereferencji * unarny tym się różni od mnożenia
    int i = 5;
    printf("*&*&i = %d\n", *&*&i);

    //pointer -> zmienna trzymająca adres pamięci jako wartość
    //int* i; -> tutaj gwiazdka nie jest dereferencją a częścią deklaracji jedynie
    //int* z, y; -> y to już nie pointer;

    //!!!z powyższego powodu wstawiać gwiazdkę przed nazwą zmiennej
    //ale przy zwracaniu przez funkcję już nie :/, ja lubie po typie

    //pointery nie są inicjalizowane domyslnie zawierają śmieci
    double d = 555.55;
    int* z = reinterpret_cast<int*>(&d);
    printf("reinterpret_cast<int*>((double)5.5) = %d\n", *z);

    printf("%p\n%p\n", z, &z);throw 1;

    //int* z = 4 -> zabronione
    //!!!nie można przypisać ręcznie adresu do wskaźnika w c++
    //!!!rozmiar wszystkich pointerów jest taki sam 4/8 zależy od architektury

    //int*p; printf("%d", *p); //segmentation fault

    //!!!pointery poza adresem mogą jeszcze wskazywać na null value - nullptr
    //pointery konwertują się do booli więc można zrobić poniższe

    int* p {0}; //można go teraz wyłuskać
    if (p)
        printf("%d", *p);
    else
       printf("P to null pointer\n");

    //!!!używać inicjalizacji pointera zerem
    //NULL to makro na 0 i zgodne tylko z C

    //nullptr -> R-val constants i keyword jednocześnie
    int* q = 0;
    ptrFun(q);
    ptrFun(z);
    ptrFun(nullptr); //wywoła fun(std::nullptr_t t), tylko ta
        //!!!używać tylko nullptr

    Struktura* struktura = new Struktura{111,222};
    printf("s.val1 = %d, s.val2 = %d\n", struktura->val1, (*struktura).val2);
        //powyższe użycia są równoznaczne
        //!!! opcja z -> lepsza bo niema problemów z kolejnością operatorów

    //!!!używać -> zamiast (*).

    void* za; //!!!nie kasować voidowych wskaźników
    const void* zb = nullptr;
    za = q;
    t_nicNieRob(za);
    t_nicNieRob((void*)zb);
}




void f1(int* z)//traktowane jako pointer
{
    printf("sizeof( void f1(int* z)  ) = %lu\n", sizeof(z));
}
void f2(int z[])//traktowane jako pointer to samo co wyżej
{
    //printf("sizeof( void f2(int z[])  ) = %lu\n", sizeof(z));
}
void f3(int z[10])//traktowane jako pointer to samo co wyżej
{
    //printf("sizeof( void f3(int z[10])  ) = %lu\n", sizeof(z));
}
void pointeryWtablicach()
{
    //zmienna tablicowa zawiera adres pierwszego elementu
        //jakby był wskażnikiem ale nie jest

    //!!!zmienna tablicowa to nie pointer -> int* != int[4]

    //!!!często tablice są "decay" -> niejawnie konwertowane na pointer
        //tracą wtedy np informacje o długosci

    char array[] {"abcdefghijklmnopr"};
        //poniżej następuje niejawne rzutowanie na pointer
    printf("niejawnie zrzutowana na pointer %s\n", array);


    int* p = new int();
    printf("sizeof zmienna tablicowa = %lu\n", sizeof(array));
        //pointer ma 8 więc to nie pointer


    printf("pointer, &pointer %p, %p\n", p, &p);
    delete p;
    printf("array  , &array   %p, %p\n", array, &array);
        //!!!address-of operator dla tablicy dalej wskazuje na adres pierwszego
        //elementu a nie jak w przypadku pointerów adres pointera

    //przy przekazywaniu do funkcji array są niejawnie rzutowane na pointery
    int t[] {1,2,3,4,5,6,7,8,9,10};
    f1(t);
    f2(t);
    f3(t);

    //stosować dla tablic "fun(int* z)"" a nie fun(int z[]) lub fun(int z[X])
    //bo to jest równoważne wszystko to pointery

    //!!!tablice w strukturach i klasach nie rozpadają się
}


void arytmetykaPointerow()
{
    int* z = new int();
    printf("pointer     = %p \n", z);
    printf("pointer + 1 = %p \n", z + 1);
    printf("1 + pointer = %p \n", 1 + z);

    //!!!kompilator zamienia array[x] na *(array + x)
    delete z;
}

void cstringiIsymbolicconstants()
{
    char v1[] {"ala ma kota"};
        //traktowana jak zmienna więc pamięć się wyczyści po wyjściu ze scope
        //!!!automatic duration
    v1[0] = 'A';
    printf("%s\n",v1);

    const char* v2 {"ala ma kota"};
        //!!!zapisana do pamięci read-only bez consta też
    const char* v3 {"ala ma kota"};
        //!!!static duration
        //!!!lepiej dodać const na początku
        //v2[0] = 'A';//nie można użyć bo pamięć read only
    printf("%s\n",v2);
    printf("v1: %p, v2: %p, v3:%p\n", v1, v2, v3);

    //!!!można używać c-style symbolic constants ale trzeba dodać const

    //char c = 'Q';
    //std::cout << &c; -> wypisze spam bo uzna że to wskaźnik na char
    //więc potraktuje jako string
}

void dynamicznaAlokacja()
{
    //alokacja pamięci
        //static dla statycznych i globalnych zmiennych przy starcie programu
        //automatic dla parametrów funkcji i lokalnych zmiennych po wejściu w blok
        //dynamic alocation -> rozmiar nie musi być znany podczas czasu kompilacji
            //brak automatycznej dealokacji

    //rozmiar stosu jest mały kilka MB
    //pamięć na stercie przyznaje system operacyjny

    //systam ładuje aplikację przy uruchomieniu do pamięci
    //-> ta przydzielona pamięć jest podzielona na różne obszary
    //1 obszar zawiera kod, inny jest przeznaczony dla normalnych operacji
        //(śledzenia wywołań funkcji, niszczenia globalnych
        //i lokalnych zmiennych ...)

    int* z = new int {66};
    delete z;
        //z jest teraz dangling pointer -> wyłuskanie teraz undefined behavior
        //ponowny wykonanie delete undefined behavior
    z = nullptr;

    //!!!nulować zmienną po dealokacji

    //!!!new rzuca bad_alloc exception -> można to pominąć
    int* val = new (std::nothrow) int;//jak sie nie da to ustawi nullptr
    if(!val)
    {
        printf("Alokacja nieudana\n");
    }
    delete val;

    //0 lub nullptr mówi że żadna pamięć nie została przydzielona do tego pointera
    //jak są wycieki pamięci to po wyłączeniu aplikacji następuje dealokacja

    //memory leak -> utrata adresu zaalokowanej pamięci
    //!!!przy tablicach trzeba używać delete[] zamiast delete bo undefined behavior

    //!!!delete[] wie ile skasować bo new[] pilnuje to,
        //niestety nie jest to dostępne dla programisty

    int* arr = new int[10] {1,2}; //inicjalizacja 1,2,0,0,0,0 ...zerami od c++11
    printf("arr[0] = %d\n", arr[4]);

    //jedyny wyjątek nie da się zaincializować charem
    //char* cc = new char[33] {"ala ma kota"}; //użyć stringa i strcpy

    //!!!trzeba podać rozmiar wyrażnie
    //int* ii = new int[] {1,2,3,4}; ERROR

    //!!!w c++ nie ma mechanizmu do resize array -> używać vectora
}

void pointeryIconsty()
{
    const int ci = 5;
    int vi = 55;
    //int* p = &ci; //nie dziala bo różne type const
    const int* p {&ci}; //non const pointer do const value
    const int* p2 {&vi}; //ok tak można rzutować

    //const pointer
    int* const p3 {&vi}; //musi być zainicjalizowany
    //p3 = &vi; error bo const

    //const pointer do const value
    const int* const cpcv {&vi};
    t_nicNieRob((void*)p);
    t_nicNieRob((void*)p2);
    t_nicNieRob((void*)p3);
    t_nicNieRob((void*)cpcv);
}

void fun(int (&arrRef)[13])//!!!nie rozpada sie na wskaznik
{
    printf("array length is: %lu\n", sizeof(arrRef)/sizeof(arrRef[0]));
}
void zmienneReferencyjne()
{
    //referencje działają jako alias

    //rodzaje
    // do zmiennych non-const
    // do zmiennych const
    // do r-value -> od c++11 (move semantic)

    int val = 5;
    int &ref = val; //teraz to znaczy nie adres-of tylko reference to
    //ten sam adres co zmienna

    //!!!referencja musi zostać zainicjalizowana
    //referencje do non-const muszą być zainicjalizowane non-const l-values

    //l-value ma adres i czas życia
    //r-values tymczasowe bez adresu (expression scope)

    const int i = 55;
    const int& iii = i;
    const int& iii3 = 6;
    t_nicNieRob((void*)&iii);
    t_nicNieRob((void*)&iii3);
    t_nicNieRob(&val);
    t_nicNieRob(&ref);
    t_nicNieRob((void*)&i);
    //referencje nie mogą być zmieniane aby wskazywać na coś innego

    //!!!przekazanie referencji tablicy do funkcji powoduje że
    //nie rozpada się do wskaźnika
    int a[13] {1,2,3,4,5,5,5,5,5,5,5,5,5};
    fun(a);

    //!!!referencja działa jak CONSTOWY wyłuskany wskaźnik
    //kompilator implementuje referencje używając wskaźników

    //!!!używać referencji zamiast wskaźników, chyba że trzeba alokować pamięć

    int xx {99};
    const int& bb {xx}; //można przypisać const var, non const var i r-values
    const int& zz {66+66}; //przypisanie r-value 
    t_nicNieRob((void*)&bb);

    //!!! wydłużony czas życia r-value normalnie nie byłoby już możliwości 
        //odczytania wyniku
    printf("zz = %d\n",zz);

    //!!!Referencje do constowych wartości są używane często jako parametry 
        //funkcji bo nie robią kopii i mogą przyjąć zmienne, stałe i r-values

    //!!!jeżeli zmienna nie jest pointerem i typem prostym przesyłać
        //przez referencję
}

void foreachLoops()
{
    int arr[] {1,2,3,4,5,6};

    for (const auto& val : arr)
    {
        printf("%d", val);
    }
    printf("\n");
    //!!! w for-each loops używać referencji lub const referencji
    //foreach nie działa z pointerami na tablicę, czy dynamicznymi tablicami
    //w foreach nie ma możliwości pobrania indeksu bo
        //np działa na linked listach które nie mają jednoznacznych indeksów
}


void modifyPtrAddress(int*& ptr)
{
    ptr += 1;
}
void wielowymiaroweTablicePointery()
{
    int (*arr)[10] = new int[5][10] {};
        //!!!trzeba znać prawy wymiar w czasie kompilacji
    delete[] arr;

    auto arr2 = new int[2][3];
        //!!!trzeba znać prawy wymiar w czasie kompilacji
    delete[] arr2;

    int** arr3 = new int*[5];
        //!!!wymiary nie muszą być znane w czasie kompilacji
    for (int i = 0; i < 5; ++i)
    {
        arr3[i] = new int[10];
        delete[] arr3[i];
    }
    delete[] arr3;

    //!!!czesto używa się jednowymiarowych i oblicza
    int* p = new int;
    printf("Adres pointera przed modyfikacja: %p\n", p);
    modifyPtrAddress(p);
    printf("Adres pointera po modyfikacji : %p\n", p);
    delete --p;
}


#include <array>
#include <vector>
void stdArrayIvector()
{
    std::array<int, 3> arr {1,2,3};
        //rozmiar musi być znany na etapie kompilacji i nie można go ominąć
        //używa tyle pamięci co typy proste
    printf("std::Arr[2] = %d\n", arr[2]);
    arr.at(2);//tu jest sprawdzanie poprawności throws error 
        //wolniejsze ale bezpieczniejsze
    printf("Array size: %lu\n", arr.size());
        //!!!zawsze przekazywać std::array przez referencję lub const referencję
        //!!!nie rozpada się do pointerów jak tablice
    std::sort(arr.begin(), arr.end());

    std::vector<int> vec {3,2,4,1};
    printf("std::vector.at(3) = %d\n", vec.at(3));
        //[] też działa jak w array
    vec.resize(44);
        //reszta wypełniona 0   //czasochłonne
    printf("std::vector.at(3) = %d\n", vec[22]);

    //!!! !!!vector przechowuje 8 booli jako 1 bajt :)
}