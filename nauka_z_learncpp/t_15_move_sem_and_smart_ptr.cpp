#include <iostream>
#include "all.hpp"
using namespace std;

void smartPointersAndMoveSemanticsIntro();
void rvalueReferences();
void moveConstructorAndAssigment();
void stdMove();
void uniquePointer();
void sharedPtr();
void sharedWeakPointer();

void t_15_move_sem_and_smart_ptr()
{
    cout << "\n\n-----chapter 15 started-----\n";
    smartPointersAndMoveSemanticsIntro();
    rvalueReferences();
    moveConstructorAndAssigment();
    stdMove();
    uniquePointer();
    sharedPtr();
    sharedWeakPointer();
}

class Resource
{
public:
    Resource(){ cout << "Resource constructor\n";}
    ~Resource(){ cout << "Resource destructor\n";}
    void show(){ cout << "I am resource\n";};
};
template<class T>
class MyPtr
{
    T* mPtr;
public:
    MyPtr(T* ptr=nullptr) : mPtr(ptr) {}
    ~MyPtr() {delete mPtr;}
    T& operator*() {return *mPtr;}
    T* operator->() {return mPtr;}
};

class Resource2
{
public:
    Resource2(){ cout << "Resource constructor2\n";}
    ~Resource2(){ cout << "Resource destructor2\n";}
    void show(){ cout << "I am resource2\n";};
};
template<class T>
class MyPtr2
{
    T* mPtr;
public:
    MyPtr2(T* ptr=nullptr) : mPtr(ptr) {}
    ~MyPtr2() {delete mPtr;}
    T& operator*() {return *mPtr;}
    T* operator->() {return mPtr;}
    string isNull()
    {
        return mPtr?"NO":"YES";
    }
    MyPtr2(MyPtr2& other)
    {
        cout << "Transfering ownership using constructor\n";
        mPtr = other.mPtr;
        other.mPtr = nullptr;
    }
    MyPtr2& operator=(MyPtr2& other)
    {
        if(this == &other)
            return *this;
        cout << "Transfering ownership using operator=\n";
        delete mPtr;
        mPtr = other.mPtr;
        other.mPtr = nullptr;
        return *this;
    }
};
void smartPointersAndMoveSemanticsIntro()
{
    //często zdarza się zapomnieć zwolnić pamięć
        //nawet jak zwalaniamy w na końcu funkcji może gdzieś nastąpić wcześniej
        //return lub throw

    //!!!dobrym rozwiązaniem jest użycie destruktorów, które wykonają się
        //po wyjściu ze scope
        //!!!jest to sercem RAII
    {
        MyPtr<Resource> mptr1{new Resource};
            //alokacja pamięci, brak jawnego delete
            //nie potrzebna* (<Resource*>) jako specyfikator typu dla MyPtr
                //ponieważ templatka ma już* (T*)

        //po wyjsciu ze scope resource będzie skasowane bo myptr jest
            //zmienną lokalną
        (*mptr1).show();
        mptr1->show();
        (mptr1.operator->())->show();
    }

    //!!!kompozycja - MyPtr jest właścicielem Resource
    //!!!taka klasa jak MyPtr jest nazywana smart_pointerem
        //composition class zarządzająca dynamicznie zaalokowanymie zmiennymi
        //gwarantuje że zmienne zalokowane dynamiczne zostaną zdealokowane
            //po wyjściu ze scope

    //!!!destruktor obiektów lokalnych zostanie wykonany nawet jeśli nastąpi
        //wcześniejsze niespodziewane wyjście z funkcji

    //!!!poniższa linia bez semantyki przenoszenia lub licznika referencji
        //spowoduje critical flow bo zdealokuje pamięć, która już
        //została zdealokowana
    //MyPtr<Resource> mptr2{mptr1};

    //!!!ponieważ nie napisaliśmy operatora przypisania i konstruktora
        //kopiującego C++ dostarczył domyślne i jest robiona płytka kopia

    //Podobnie będzie jezeli przekażemy nasz obiekt mptr1 do funkcji przez wartość
        //Opcja 1: żeby rozwiązać ten problem można np usunąć operator
            //przypisania i konstruktor kopiujący
            //ale wtedy nie będziemy mogli zwrócić MyPtr przez wartość przez
            //referencję czy pointer też bo będzie w jakiejś funkcji alokowana
            //lokalnie i po wyjściu czyszczona więc trzeba zwrócić przez wartość
            //co spowoduje shallow copies zduplikowane pointery i crashe

        //Opcja2: zoverridować konstruktor kopiujący i operator przypisania
            //aby robił głębokie kopie, ale kopie są drogie i czasami
            //mogą być niemożliwe, ale po co robić głęboką kopię tylko żeby
            //móc zwracać przez wartość i dodatkowo przy przypisaniu
            //raczej nie spodziewamy się, że będzie robiona kopia

    cout << "----------------\n";
    //Rozwiązanie - semantyka przenoszenia
    //SEMANTYKA PRZENOSZENIA oznacza że klasa przejmie własność obiektu
        //zamiast robić kopię

    //główną różnicą nad "copy semantics" jest to, że nie kopiujemy resourców
        //a przenosimy ich prawo własności

    MyPtr2<Resource2> mptr2{new Resource2};
    MyPtr2<Resource2> mptr22;
    MyPtr2<Resource> mptr33;
    cout << "Is mptr2 null: " << mptr2.isNull() << endl;
    cout << "Is mptr22 null: " << mptr22.isNull() << endl;
    mptr22 = mptr2;
    cout << "Is mptr2 null: " << mptr2.isNull() << endl;
    cout << "Is mptr22 null: " << mptr22.isNull() << endl;

    //!!!std::auto_ptr -> UNIKAĆ został wprowadzony w C++98 jako pierwsza
        //próba sdandaryzacji smart pointerów działał jak klasa nasza MyPtr2
        //jednak auto_ptr i nasza klasa ma masę problemów
            //po piwersze: w związku z tym, że auto_ptr czy też MyPtr2
                //implementuję move semantics powoduje że przekazanie tego obiektu
                //do funkcji spowoduje przeniesienie prawa własności do parametru
                //funkcji i zostanie on zniszczone na koniec funkcji i powyjściu
                //z funkcji nastąpi prawdopodobnie próba dereferencji
            //po drugie: auto_ptr kasuje resource używając nietablicowego delete
                //więc nie będzie działał dla dynamicznie zaalokowanych tablic
                //i dodatkowo nie zapobiega przekazaniu tablic więc
                //będą memory leaks
            //po trzecie: auto_ptr nie działa dobrze z klasami standardowymi
                //włączając większość kontenerów i algorytmów, ponieważ zakładają
                //one, że kiedy wykonują kopię jest rzeczywiście robiona kopia
                //a nie przenoszone prawo własności
        //!!!std::auto_ptr zostało deprecated w C++11 i nie powinno być używane
            //i prawdopodobnie będzie usuniętew Cpp17

    //!!!problem z C++11 wynikał z tego, że przed C++11 nie było mechanizmu
        //do odróżnienia "copy semantics" od "move semantics"
        //można było jedynie overridować copy semantykę move semantyką co
            //prowadziło do wielu problemów i dziwnych zachowań
        //nie dało się okreslić czy res1 = res2 zmodyfikowało obiekt res2 czy nie
    //w c++11 zosta rozróżniona semantyka przenoszenia od kopiowania
    //auto_ptr został zastąpiony przez: scoped_ptr, unique_ptr,
        //weak_ptr oraz shared_ptr
}



//!!!! kiedy przekazywana jest r-value jest wykonywana jest funkcja przujmująca
    //r-value reference bo jest rozważana że ma większą zgodność niż
    //const l-value reference
void fun1(const int& i) //void fun1(int& i) też ok //void fun1(int i) ambigous
{
    cout << "Wywolanie funkcji przyjmujacej l-value reference\n";
}
void fun1(int&& i) //bez tej funkcji zawsze wykonałavy się funkcja 
                   //przyjmujaca const l-value reference
{
    cout << "Wywolanie funkcji przyjmujacej r-value reference\n";
}

void rvalueReferences()
{
    //l-values & r-values nie są właściwościami wartości a raczej właściwościami
        //wyrażeń

    //każde wyrażenie w C++ ma 2 właściwości: typ (do sprawdzenia typu) i
        //value category (do pewnego rodzaju sprawdzenia składni np czy
            //wynik wyrażenia może zostać przypisany do)

    //Do C++03 VALUE CATEGORY były tylko 2: l-values i r-values
    //aktualnie definicja, które wyrażenie jest r-value a które r-value jest
        //skomplikowana

    //!!!L-value (locator value) -> można rozważyć jako funkcja lub obiekt
        //(lub wyrażenie które ewoluuje do funkcji lub obiektu)
    //wszystkie L-values mają przypisane adres w pamięci

    //początkowo l-values były zdefiniowane jako wartości, które są do bycia po
        //lewej stronie przy wyrażeniu przypisania
    //później dodane zostało słowo const i l-values zostały podzielone na
        //modifable l-values i non-modifable l-values które są const


    //R-values w skrócie są tym czym nie są l-values. Czyli w szczególności:
        //literały(5), wartości tymczasowe(x+1), anonimowe obiekty(Object(5,6))

    //R-values są ewaluowane do ich wartości, mają expression scope
        //(umierają na końcu expression) i nie mogą być przypisane
        //to że nie mogą być przypisane ma sens bo przypisanie ma side
            //effect obiektu
        //w związku z tym, że r-values mają expression scope, jeżeli
            //przypisalibyśmy value do r-value, r-value wyszłoby poza scope
            //zanim mielibyśmy szansę użyć przypisanej wartości 
            //do kolejnego wyrażenia lub musielibyśmy zrobić side effect 
            //co powoduje undevined behavior

    //żeby wspierać semantyke przenoszenia C++11 wprowadziło 3 nowe
        //VALUE CATEGORY: pr-values, x-values, gl-values
    //!!!https://en.cppreference.com/w/cpp/language/value_category


    //!!!L-value REFERENCES -> przed c++11 istniała tylko "reference"
        //teraz jest ich więcej

    //L-value reference może jedynie być inicjalizowana jedynie
        //modyfikowalną l-value
    //|----------------------------------------------------------------------|
    //|L-value reference               |Can be initialize with |Can modify   |
    //|----------------------------------------------------------------------|
    //|Modifable l-values              |Yes                    |Yes          |
    //|Non Modifable l-values          |No                     |No           |
    //|R-values                        |No                     |No           |
    //|----------------------------------------------------------------------|

    //L-value reference to const objects może być inicjalizowana
        //l-value i r-value jednak wartość nie może być modyfikowana
    //|----------------------------------------------------------------------|
    //|L-value reference to const      |Can be initialize with |Can modify   |
    //|----------------------------------------------------------------------|
    //|Modifable l-values              |Yes                    |No           |
    //|Non Modifable l-values          |Yes                    |No           |
    //|R-values                        |Yes                    |No           |
    //|----------------------------------------------------------------------|

    //L-value references do constowych obiektów są szczególnie użyteczne
        //bo pozwalają nam przekazać dowolny argument l-value i r-value do funkcji
            //bez kopiowania argumentu

    //W C++11 został dodany nowy typ referencji -> R-value reference
        //R-value reference jest zaprojektowana aby być inicjalizowana 
            //JEDYNIE przez R-Value

    int x = 5;
    int& lref = x;
        //l-value reference initialized with l-value
    //int& lref2 = 5;
        //cannot bind non-const lvalue reference to rvalue
    const int& lref3 = 5;
        //l-value reference to const initizlized with r-value 
        //przedłuża czas życia r-value

    int&& rref = 5;
        //r-value reference initialized with r-value
        //int&& rref2 = x;//cannot bind rvalue reference to lvalue

    int&& ref2 = std::move(x);
    int&& ref22 = static_cast<int&&>(int(5));
        //chyba równoważne z powyższym move
    cout << ref22 << endl;

    t_nicNieRob(&lref);
    t_nicNieRob((void*)&lref3);
    t_nicNieRob(&rref);
    t_nicNieRob(&ref2);

    //Rvalue references cannot be initialized witch L-values
    //|----------------------------------------------------------------------|
    //|R-value reference               |Can be initialize with |Can modify   |
    //|----------------------------------------------------------------------|
    //|Modifable l-values              |No                     |No           |
    //|Non Modifable l-values          |No                     |No           |
    //|R-values                        |Yes                    |Yes          |
    //|----------------------------------------------------------------------|
    //|----------------------------------------------------------------------|
    //|R-value reference to const      |Can be initialize with |Can modify   |
    //|----------------------------------------------------------------------|
    //|Modifable l-values              |No                     |No           |
    //|Non Modifable l-values          |No                     |No           |
    //|R-values                        |Yes                    |No           |
    //|----------------------------------------------------------------------|

    //R-value references mają dwie użyteczne właściwości:
        //wydłuzają żywotność obiektu dla którego zostały zainicjalizowane
        //do czasu życia odwołania r-value (tak jak l-value do const wartości)
    //!!!non-const r-value references pozwalają modyfikować r-value
    int&& rref3 = 7;
    rref3 = 8;

    string&& str = string("ala ma kota");
        //r-value reference to temporary object
        //zniszczony zostanie jak referencja str będzie niszczona
            //czyli po wyjściu z bloku

    int&& rref4 = 4;
    t_nicNieRob(&rref4);
        //kiedy inicjalizujemy r-velue literałem obiekt tymczasowy jest tworzony
            //z literału więc referencja wskazuje na tymczasowy obiekt

    //!!!R-value referencje nie są często stosowane w taki sposób jak były
        //stosowane powyżej

    //!!!R-value references są często używane jako parametry funkcji,
        //często stosuje się przeciążenia funkcji jezeli chcemy inne
        //zachowanie dla r-value a inne dla l-value

    int x3 = 55;
    fun1(x3);
    fun1(55);
    fun1(move(x3));

    //!!!nie powinno się prawie nigdy zwracać l-value reference ani r-value
        //reference bo w większości przypadków skończy sie z wiszącą referencją
        //kiedy obiekt wyjdzie poza scope
}



class ResourceMCAA
{
public:
    ResourceMCAA(){ cout << "ResourceMCAA countructor\n"; }
    void show(){cout << "show\n";}
    ~ResourceMCAA(){ cout << "ResourceMCAA destructor\n"; }
};
template<class T>
class MyAutoPtrMCAA
{
    T* mPtr;
public:
    MyAutoPtrMCAA(T* initVal=nullptr):mPtr(initVal){}

    MyAutoPtrMCAA(const MyAutoPtrMCAA&) = delete;
        //zapobiega robieniu kopii np bo zbyt droga
    MyAutoPtrMCAA(MyAutoPtrMCAA&& other)
    {
        mPtr = other.mPtr;
        other.mPtr = nullptr;
    }

    MyAutoPtrMCAA& operator=(const MyAutoPtrMCAA&) = delete;
        //zapobiega robieniu kopii np bo zbyt droga
    MyAutoPtrMCAA& operator=(MyAutoPtrMCAA&& other)
    {
        if(this==&other)
            return *this;
        delete mPtr;
        mPtr = other.mPtr;

        //bez poniższej linii byłoby źle bo wykonałby się destruktor
            //po np std::move
        other.mPtr = nullptr;
        return *this;
    }
    MyAutoPtrMCAA& operator*() const { return *mPtr;}
    MyAutoPtrMCAA* operator->() const { return mPtr;}
    void show(){mPtr->show();}
    ~MyAutoPtrMCAA(){ delete mPtr;}
};
MyAutoPtrMCAA<ResourceMCAA> generateMCAAResource()
{
    MyAutoPtrMCAA<ResourceMCAA> gmr{new ResourceMCAA};
    return gmr;
}
#include <chrono>
template<class T>
class DynamicArrayCA
{
    int mSize;
    T* mArray;
public:
    DynamicArrayCA(int size):mSize(size),mArray(new T[size]){}
    ~DynamicArrayCA(){ delete[] mArray;}
    // DynamicArrayCA(const DynamicArrayCA& other):
    //          mSize(other.mSize),mArray(new T[mSize])
    // {
    //     for(int i=0; i<mSize; ++i)
    //         mArray[i] = (other.mArray)[i];
    // }
    // DynamicArrayCA& operator=(const DynamicArrayCA& other)
    // {
    //     if(this == &other)
    //         return *this;
    //     delete[] mArray;
    //     mSize = other.mSize;
    //     mArray = new T[mSize];
    //     for(int i=0; i<mSize; ++i)
    //         mArray[i] = (other.mArray)[i];
    //     return *this;
    // }
    DynamicArrayCA(const DynamicArrayCA& other) = delete;
    DynamicArrayCA& operator=(const DynamicArrayCA& other) = delete;
    DynamicArrayCA(DynamicArrayCA&& other):mSize(other.mSize),mArray(other.mArray)
    {
        other.mArray = nullptr;
        other.mArray = 0;
    }
    DynamicArrayCA& operator=(DynamicArrayCA&& other)
    {
        if(this == &other)
            return *this;
        delete[] mArray;
        mSize = other.mSize;
        mArray = other.mArray;
        other.mArray = nullptr;
        other.mSize = 0;

        return *this;
    }
    T& operator[](int index){ return mArray[index];}
    const T& operator[](int index) const { return mArray[index];}
    int getLength() const {return mSize;}
};
class TimerCA
{
    chrono::time_point<chrono::high_resolution_clock> mStartTimePoint;
public:
    TimerCA():mStartTimePoint(chrono::high_resolution_clock::now()){}
    void reset(){mStartTimePoint = chrono::high_resolution_clock::now();}
    double elapsed()
    {
        return chrono::duration_cast<std::chrono::duration
            <double, std::ratio<1> > >(
                chrono::high_resolution_clock::now() - mStartTimePoint).count();
    }
};
DynamicArrayCA<int> cloneArrayAndDouble(const DynamicArrayCA<int>& src)
{
    DynamicArrayCA<int> newArr{src.getLength()};
    for(int i = 0; i < src.getLength(); ++i)
        newArr[i] = src[i] * 2;
    return newArr;
}
void moveConstructorAndAssigment()
{
    //!!!konstruktor kopiujący jest używany aby zainicjalizować klasę robiąc
        //kopię obiektu tej samej klasy
    //Copy assigment jest używany aby skopiować klasę do innej istniejącej klasy
        //C++ dostarcza domyślnie copy constructor i copy assigment jezeli nie
        //podamy wlasnego które robią shallow copy
    {
        cout << "=============MCAA================\n";
        MyAutoPtrMCAA<ResourceMCAA> mapm;
        mapm = generateMCAAResource();
        mapm.show();
    }
    /* Bez move constructora i assigmentu był by poniższy output
        a nawet więcej bez compiler elidingu
            ResourceMCAA countructor
            ResourceMCAA countructor
            ResourceMCAA destructor
            ResourceMCAA destructor

        z move konstruktorem i move assigmentem wykona się tylko raz
    */

    //move konstruktor i assigment przenoszą prawa do obiektu zamiast kopiować
    //move konstruktor i assigment są wywoływane gdy parametrem jest r-value

    //w większości przypadków move konstruktor i move assigment nie bedą
        //generowane automatycznie
    //domyślny move constructor i assigment robią to samo co copy konstruktor
        //i assigment czyli robią kopię

    //!!!jeśli chcemy aby move konstruktor i assigment robiły przeniesienie
        //trzeba je zrobić ręcznie

    //!!!
    //jeżeli wywołujemy konstruktor kopiujący lub assigment operator dla
        //l-value jedyna rozsądna rzecz to kopiowanie (a nie przenoszenie)
        //bo parametr do kopiowania może być później używany więc
        //nie powinniśmy go zmieniać

    //jeżeli jednak argimentem jest r-value wiemy, że jest tymczasowy więc zamiast
        //kopiowania, które jest drobgie możemy zrobić przeniesienie zasobów,
        //jest to bezpieczne bo tymczasowy obiekt będzie zniszczony na końcu
        //expression i nie będzie już używany

    //!!!
    //w przykładzie powyżej w move funkcjach robimy: "other.mPtr = nullptr;"
        //bo kiedy other wyjdzie poza scope jego destruktor zostanie wywołany więc
        //other.mPtr zostanie skasowany, więc jeżeli nasz mPtr i otherPtr
        //wskazują na to samo nasz mPtr zostanie dangling pointerem

    //!!!
    //w funkcji generateMCAAResource kiedy wartość jest zwracana jest przenoszona
        //a nie kopiowana mimo że gmr jest l-value

    //Specyfikacja C++ mówi, że automatyczne obiekty zwracane przez funkcję mogą
        //być przenoszone mimo, że są l-value, ma to sens bo res byłoby i tak
        //zniszczone na koniec funkcji

    //mimoże kompilator może przenosić zwracane wartości w niektórych przypadkach
        //jest w stanie zrobić nawet więcej poprzez eliding 
        //(nie trzeba robić kopii i przenoszenia)
        //więc żaden konstruktor (copy/move) nie będzie wywołany

    //czasami kasuje się copy konstructor i assigment jak nie ma potrzeby
        //bo np jest zbyt kosztowne

    //!!!
    //nasza klasa MyAutoPtrMCAA to prawie uniquePtr (nie znam dużych różnic teraz)

    {
        // cout << "=============CA================\n";
        // TimerCA timer;
        // DynamicArrayCA<int> arr(1000000);
        // for (int i =0; i < arr.getLength(); ++i)
        //     arr[i] = i;
        // arr = cloneArrayAndDouble(arr);
        // cout << "Czas kopiowania i mnożenia tablicy 1mln elementow: " 
        //      << timer.elapsed();
        cout << "Czas kopiowania i mnożenia tablicy 1mln elementow:   0.0410538\n";
    }

    {
        TimerCA timer;
        DynamicArrayCA<int> arr(1000000);
        for (int i =0; i < arr.getLength(); ++i)
            arr[i] = i;
        arr = cloneArrayAndDouble(arr);
        //cout << "Czas kopiowania i mnożenia tablicy 1mln elementow: " << timer.elapsed() << endl;
        cout << "Czas przenoszenia i mnożenia tablicy 1mln elementow: 0.034841\n";
    }
}



#include<vector>
template<class T>
void mySwap(T& a, T& b)
{
    T tmp = move(a);
    a = move(b);
    b = move(tmp);
}
void stdMove()
{
    //zdarza się, że chcemy wywołać semantyke przenoszenia a mamy l-value
    string a = "abc";
    string b = "cde";
    mySwap(a,b);
    cout << a << b << endl;

    vector<string> vs;
    string s = "string content";
    cout << s << endl;
    vs.push_back(move(s));
    cout << "Zawartość stringa po dodaniu do wektora z std::move: \""
         << s << "\"" << endl;
    //std::move daje wskazówke kompilatorowi, że programista już nie potrzebuje
        //tego obiektu
    //po std::move nie można oczekiwać ze stan obiektu będzie taki sam

    //przedmioty, które kradziemy (otrzymujemy) przez std::move powinny być
        //pozostawione w null state (np powyższy string)
        //pozwala to na ponowne użycie zminnej (s), można jej też nie używać

    //move może byc przydatne też np w sortowaniu, selection sort,
        //bubble sort działają poprzez swap
        //jest też przydatne gdy chcemy przenieść zawartość zarządzaną przez
        //smart pointery
}


class ResourceUP
{
public:
    ResourceUP(){ cout << "ResourceUP constructor\n"; }
    ResourceUP(int i){ cout << "ResourceUP constructor 2\n"; }
    ~ResourceUP(){ cout << "ResourceUP destructor\n"; }
};
ostream& operator<<(ostream& o, ResourceUP& res)
{
    cout << "I am resource\n";
    return o;
}
#include <memory>
unique_ptr<ResourceUP> getUniquePtrResourceUP()
{
    return make_unique<ResourceUP>();
}
void takeOwnership(unique_ptr<ResourceUP> res)
{
    cout << "koniec takeOwnership func\n";
}
void useResource(ResourceUP& res){}
void uniquePointer()
{
    //zarządza czasem życia dynamicznie zaalokowanego obiektu
    //!!!smart pointery nigdy nie powinny być tworzone dynamicznie
    //powinny być robione jako zmienne lokalne albo jako membery klasy
        //gwarantuje to dobrą dealokację smart pointera

    //w C++11 są 4 smart pointery, auto_ptr -> nie używać, będzie skasowany w 17
    //unique_ptr, shared_ptr, i weak_ptr

    //unique_ptr zastąpił auto_ptr, powinien być użyty do zarządzania dynamicznie
    //stworzonym obiektem, który nie jest współdzielony przez różne obiekty

    unique_ptr<ResourceUP> upr {new ResourceUP};
    unique_ptr<ResourceUP> upr2 = move(upr);
    //jak upr wyjdzie poza scope destruktor unique pointera obsłuży
        //kasowanie resourca
    //unique_ptr w przeciwieństwie do auto_ptr prawidłowo implementuje
        //move semantic
    //w unique pointerze kopiujacy operator przypisania i konstruktor są disabled
        //trzeba więc użyć semantyki przypisania
    //unique pointer ma przeciążone operatory * oraz -> zwracają zarządzany obiekt
        //* zwraca referencję a -> wskaźnik

    //unique_ptr może nie zarządzać niczym jeżeli został przezkazany nullptr lub
        //został wywołany konstruktor domyślny lub bo resource został
        //przeniesiony do innego unique pointera
    unique_ptr<ResourceUP> upr3 = move(upr2);

    //trzeba więc sprawdzić czy unique pointer zarządza czymś
    //unique_ptr ma przeciążony operator castowania do boola
    if (!upr3)
    {
        cout << "upr3 nie zarzadza zadnym obiektem\n";
    }
    else
    {
        cout << "upr3 zarzadza obiektem\n";
        cout << *upr3;
    }

    //unique_ptr (auto_ptr nie) rozróżnia skalary i tablice
    unique_ptr<int[]> up_i3 {new int[3] {10,20,30}};
    cout << up_i3[1] << endl;
        //dodatkowy operator dla tablic
    //!!!jednak prawie zawsze lepiej zrobić std::array, lub wector lub string

    //c++14 wprowadza make_unique -> przyjmuje argumenty resourca
    unique_ptr<ResourceUP> up4 = make_unique<ResourceUP>(6);
    //używanie make_unique jest opcjonalne ale rekomendowane ponieważ jest
        //prostsze, i wymaga mniej typowania prz używaniu z auto type deduction
    auto up5 = make_unique<ResourceUP>(6);
    //!!!preferować make_unique zamiast ręcznego tworzenia i new

    //bezpieczeństwo ze względu na exceptiony
    //callFunction(unique_ptr<T>(new T), functionThrowsException());
        //teoretycznie może być wyciek bo kompilator może utworzyć najpierw
        //T później exception a dopiero później byłoby tworzenie unique_ptr
        //z make_unique nie ma tego problemu bo jest to poprostu 1
        //wywołanie funkcji

    //unique pointer może być bezpiecznie zwracany przez funkcję
    up5 = getUniquePtrResourceUP();
    //getUniquePtrResourceUP zwraca tmyczasową wartość która jest przypisana z
        //użyciem semantyki przenoszenia do up5, bez przypisania byłaby skasowana

    //!!!generalnie nigdy nie powinno się zwracać unique pointera przez wskaźnik
        //lub referencje, chyba, że jest powód

    //!!!jeżeli chcemy przekazać unique_ptr do funkcji to:
    //jeżeli chcemy aby ta funkcja przejeła własność nad pointerem, przekazujemy
    //unique_ptr przez wartość (trzeba użyć move bo unique ptr nie ma copy semantic)
    {
        cout << "---------------\n";
        auto up6 = getUniquePtrResourceUP();
        takeOwnership(std::move(up6));
        cout << "koniec funkcji narzednej uniquePointer\n";
        cout << "---------------\n";
    }

    //!!!często jednak nie będziemy chcieli przekazywać własności
    //!!!przekazywanie unique_ptr przez referencję powinniśmy robić tylko wtedy
    //!!!gdy funkcja chce zmienić zarządzany obiekt czyli nasze Resource na inne

    //!!!lepiej zamiast tego przekazać sam Resource przez pointer lub referencję
        //pozwoli to finkcji nie wiedzieć jak wywołujący zarządza obiektem
        //trzeba użyć .get()
    useResource(*(up5.get()));

    //można tworzyć unique_ptr jako membery klas, nie trzeba się wtedy martwić o
        //dealokację, trzeba jednak pamiętać, że jeżeli obiekt klasy jest tworzony
        //dynamicznie trzeba go zwolnić

    //!!!nadużywanie unique_ptr
    ResourceUP* r = new ResourceUP();
    unique_ptr<ResourceUP> upru1(r);
        //unique_ptr<ResourceUP> upru2(r); -> undevined behavior
            //bo 2 unique_pointery będą kasować ten sam obiekt
            //delete r; -> undevined behavior bo unique_ptr też
                //będzie kasować obiekt
    //make_unique zapobiega temu
}


void testMyShareedPtr();
class ResourceSP
{
public:
    ResourceSP(){ cout << "ResourceSP constructor\n"; }
    void show(){ cout << "I am ResourceSP\n"; }
    ~ResourceSP(){ cout << "ResourceSP destructor\n"; }
};
void sharedPtr()
{
    //wiele shared_ptrow może wskazywać na ten sam obiekt
    //wewnątrz trzyma info jak wiele shared_ptr współdzieli zasób
    //dopóki chociaż 1 shared_ptr wskazuje na resource,
        //resource nie zostanie skasowane
    //skasowanie bedzie po wyjściu ze scope ostatniego shared_ptr
    //też z memory headera
    shared_ptr<ResourceSP> sp1 = make_shared<ResourceSP>();
    {
        shared_ptr<ResourceSP> sp2 = sp1;
        cout << "Ilosc referencji do resourca: " << sp2.use_count() << endl;
    }
    sp1->show();

    //uzywac make_shared -> prostsze, bezpieczniejsze - nie da się bezpośrednio
        //zrobić 2 shared ptr wskazujących na ten sam obiekt,
        //jest też wydajniejszy

    //sharedPtr w przeciwieństwie do uniquePtr używa wewnętrznie 2 pointerów
        //1 na resource a drugi na obiekt (blok kontrolny) włączając w to
        //licznik referencji

    //!!!podczas tworzenia shared_ptr przez konstruktor pamięć na resource i
        //"controll block" są alokowane oddzielnie
        //jednak poprzez użycie make_shared pamięć na obie dane jest alokowana
        //razem przez co jest szybciej

    //tak więc stworzenie 2 niezależnych shared_ptr na resource doprowadzi do
        //kłopotów bo będą miały niezależne control bloki i będą myśleli że
        //są jedynym zarządcą resourca

    //iedy shared_ptr jest klonowany poprzez copy assigment dane w control bloku
        // są aktualizowane aby wskazać, że są teraz współzarządcy

    //unique_ptr mogą być konwertowane do shared_ptr przez konstruktor
        //w shared_ptr który akceptuje r-value
    unique_ptr<ResourceSP> up1 = make_unique<ResourceSP>();
    shared_ptr<ResourceSP> sp3 = move(up1);
        //przenosi zawartość uniquePtr do sp3
    //nie da się jednak bezpiecznie przekonwertować unique_ptr do shared_ptr

    //!!!tak więc jeżeli zamierzamy zrobić funkcję, która zwraca smart pointer
        //lepiej jest zwracać unique_ptr i przypisywać go do shared_ptr
        //jeżeli jest to dla nas poprawne

    //NIEBEZPIECZEŃSTWA shared_ptr
        //ma te co w unique -> nie będędzie prawidłowo usunięty jeżeli
            //był zaalokowany dynamicznie lub był częścią dynamicznie
            //zaalokowanego obiektu niezdealokowanego
        //w smart pointerze dodatkowo trzeba się martwić aby wszystkie
            //shared_ptr'y zostały zdeletowane

    //shared ptr i array do cpp14 włącznie nie ma obsługi shared ptr dla array
    //w cpp17 jest taka obsługa jednak make_shared dalej nie ma obsługi dla array

    cout << "---------test my shared ptr-----------";
    testMyShareedPtr();
    cout << "---------test my shared ptr-----------";
}



class ResourceSPtest
{
public:
    ResourceSPtest(){ cout << "ResourceSPtest constructor\n"; }
    void show() { cout << "I am a ResourceSPtest\n"; }
    void operator()() { cout << "Functional operator\n"; }
    void operator++() { cout << "++ operator\n"; }
    ~ResourceSPtest(){ cout << "ResourceSPtest destructor\n"; }
};
template<class T>
class sp
{
    int* mCounter { nullptr};
    T* mValue { nullptr };
public:
    sp<T>(){}
    sp<T>(T* resource) : mCounter(new int), mValue(resource)
    {
        *mCounter=1;
    }
    sp<T>(const sp<T>& other):mCounter(other.mCounter), mValue(other.mValue)
    {
        (*mCounter)++;
    }
    sp<T>& operator=(const sp<T>& other)
    {
        if(this == &other)
            return *this;
        if(mCounter && --(*mCounter) == 0)
        {
            delete mCounter;
            delete mValue;
        }
        mCounter = other.mCounter;
        mValue = other.mValue;
        if (mCounter)
            ++(*mCounter);
        return *this;
    }
    T* operator->(){ return mValue; }
    T& operator*(){ return *mValue; }
    void operator->*(int a){ cout << "chujniaaaaaa\n"; }
    ~sp<T>()
    {
        if(!mCounter)
            return;
        --(*mCounter);
        if(*mCounter <= 0)
        {
            delete mCounter;
            delete mValue;
            mCounter = nullptr;
            mValue = nullptr;
        }
    }
    int getReferenceCount()
    {
        cout << "Reference count: " << *mCounter << endl;
        return *mCounter;
    }
};
void testMyShareedPtr()
{
    sp<ResourceSPtest> sp1;
    sp<ResourceSPtest> spam;

    sp<ResourceSPtest> sp2(new ResourceSPtest);
    sp2.getReferenceCount();//1

    sp<ResourceSPtest> sp3(sp2);
    sp2.getReferenceCount();//2

    {
        sp<ResourceSPtest> sp4(sp2);
        sp2.getReferenceCount();//3
    }
    sp2.getReferenceCount();//2

    sp1 = sp2;
    sp2.getReferenceCount();//3

    sp1 = spam;
    sp2.getReferenceCount();//2

    sp2->show();
    (*sp2).show();

    sp2->*(0);
    (*sp2)();

    sp2->operator()();
    (*sp2).operator()();
    sp2->operator++();
    //sp2->++;
}



class PersonSWP
{
    string mName;
    shared_ptr<PersonSWP> mPartner;
    weak_ptr<PersonSWP> mPartnerWeak;
public:
    PersonSWP(const string& name):
        mName(name)
    {
        cout << "created " << mName << endl;
    }
    ~PersonSWP()
    {
        cout << "destroyed " << mName << endl;
    }
    void setPartner(shared_ptr<PersonSWP>& partner){mPartner = partner;}
    void showName()
    {
        cout << "I am " << mName << endl;
    }
    friend ostream& operator<<(ostream& o, const PersonSWP& p)
    {
        o << p.mName;
        return o;
    }
    friend bool partnerUp(shared_ptr<PersonSWP>& a, shared_ptr<PersonSWP>& b);
    friend bool partnerUpWeak(shared_ptr<PersonSWP>& a, shared_ptr<PersonSWP>& b);
    weak_ptr<PersonSWP> getWeakPtr(){return mPartnerWeak;}
};
bool partnerUp(shared_ptr<PersonSWP>& a, shared_ptr<PersonSWP>& b)
{
    if(!a || !b)
        return false;
    a->mPartner = b;
    b->mPartner = a;
    cout << *a << " is connected with " << *b << endl;
    return true;
}
bool partnerUpWeak(shared_ptr<PersonSWP>& a, shared_ptr<PersonSWP>& b)
{
    if(!a || !b)
        return false;
    a->mPartnerWeak = b;
    b->mPartnerWeak = a;
    cout << *a << " is WEAK connected with " << *b << endl;
    return true;
}
void sharedWeakPointer()
{
    cout << "---------------sharedWeakPointer\n";

    auto pawel = std::make_shared<PersonSWP>("Pawel");
    auto karolina = std::make_shared<PersonSWP>("Karolina");
    partnerUp(pawel, karolina);
        //nigdy zasoby się nie zwolnią
    //nie zostaną zwolnione PersonSWP pawel i karolina bo pawel ma w sobie
    //smart wskaźnik na karolinę a karolina na pawła jest to
    //cykliczna referencja A wskazuje na B, B na C a C na A
        //czyli seria referencji w której jeden obiekt wskazuje na kolejny 
        //a ostatni na pierwszy czyli pętla referencji czy też wskaźników

    //PROBLEM CYKLICZNEJ REFERENCJI MOŻE NAWET WYSTĄPIĆ Z JEDNYM SHARED POINTEREM
    auto pawel2 = std::make_shared<PersonSWP>("Pawel");
    //pawel2->setPartner(pawel2);//znów wyciek

    //weak pointer został zaprojektowany aby rozwiązać problem z cykliczną
        //referencją
    //weak_ptr jest obserwatorem może obserwować i ma dostęp do tego samoego
        //zasobu co shared_ptr ale nie jest właścicielem (nie zliecza referencji)

    auto pawelWEAK = std::make_shared<PersonSWP>("pawelWEAK");
    auto karolinaWEAK = std::make_shared<PersonSWP>("karolinaWEAK");
    partnerUpWeak(pawelWEAK, karolinaWEAK);
    //!!!nie da się użyć bezpośrednio weak_ptr trzeba castować na shared_ptr

    pawelWEAK->showName();
    
    //pawelWEAK->getWeakPtr()->showName();
        //ERROR bo weak ptr nie pozwala na dostęp

    //funkcja .lock() wbudowana w weak_ptr konwertuje go do shared_ptr
    pawelWEAK->getWeakPtr().lock()->showName();
    //o zmienną shared_ptr otrzymaną przez locka nie mamy co się martwić
        //(nawet jakbyśmy ją przypisali do shared_ptr to jest lokalna i
        //wyjdzie ze scopeu)

    //mój głupi test
    //static shared_ptr<PersonSWP> ssppswp;
    //static shared_ptr<PersonSWP> ssppswp2;
    //ssppswp = pawelWEAK->getWeakPtr().lock();
    //ssppswp2 = karolinaWEAK->getWeakPtr().lock();
        ////przejdzie bo obie zostaną zwolnione przy końcu aplikajci

    //weak pointer używamy gdy chcemy współdzielić zasób ale nie zarządzać
        //jego życiem
}