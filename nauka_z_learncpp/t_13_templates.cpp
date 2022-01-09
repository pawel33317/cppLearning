#include <iostream>
using namespace std;

void functionTemplates();
void classTemplates();
void functionTemplateSpecialization();
void classTemplateSpecialization();
void partialTemplateSpecialization();
void partialTemplateSpecializationForPointers();

void t_13_templates()
{
    printf("-----chapter 13 started-----\n");
    functionTemplates();
    classTemplates();
    functionTemplateSpecialization();
    classTemplateSpecialization();
    partialTemplateSpecialization();
    partialTemplateSpecializationForPointers();
}


template<typename T>//template declaration, aby stworzyć templateparametr używamy
                    //słowa typename lub class (nie ma między nimi różnicyw tym kontekście)
const T& myMax(const T& a, const T& b)
{
    return a > b ? a : b;
}
void functionTemplates()
{
    //templatku funkcji - wzorzec służący do robienia podobnych funkcji
    //placeholdery (template type parameters) zamiast typów
    cout << myMax(5, 66) << endl;
    cout << myMax(5.44, 66.19) << endl;//zostanie stworzona nowa funkcja
    cout << myMax<double>(5, 12) << endl;
    //w związku, że parametrami mogą być obiekty lepiej przekazać obiekty przez
    //referencje

    //dla więcej typów tamplate<typename T1, typenameT2>

    //templatki sa dobre bo nie trzeba powielać funkcji i przez to można uniknąć
    //błędów

    //stare kompilatory miały problemy z templatkami
    //kompilatory w przypadku błędów potrafią pokazywać szalone info dla templatek
    //mogą zwiększają czas kompilacji i rozmiar kodu jeżeli nie będzie więcej
    //niż jednego użycia (templatka będzie rekompilowana dla każdego pliku)

    //kompilator kompiluje templatki po napotkaniu na wszystkie wywołania
    //tak stworzona funkcja nazywa się function template instance

    //kiedy kompilator napotyka myMax(4,3); kompilator replikuje templatekę i tworzy
    //jej instancję: const int& myMax(const int& a, const int& b){...}

    //jeżeli nie wywołamy nigdy funkcji z templatki, żadna jej istancja nie będzie utworzona
    //oczywiście obiekt przekazany do templatki musi mieć operatory/metody
    //wykorzystywane w templatce
}

#include<assert.h>
template <class T>
class MyArray
{
    int mSize;
    T* mData;
public:
    MyArray(int size):mSize(size),mData(new T[size]){}
    ~MyArray(){delete[] mData;}
    T& operator[](int index)
    {
        assert(index >=0 && index < mSize); 
        return mData[index];
    }
    void erase(){ delete[] mData; mData = nullptr; mSize = 0; }
    //int getLength(){ return mSize; }
    int getLength();
};
template<class T>
int MyArray<T>::getLength(){ return mSize; }
//bez <T> error: ‘template<class T> class MyArray’ used without template parameters

template<class T, int size>
class StaticArray
{
    T mArr[size];
public:
    T* getArray();
    T& operator[](int index){return mArr[index];}
};

template<class T, int size>
T* StaticArray<T, size>::getArray() { return mArr; }

void classTemplates()
{
    MyArray<double> myArr(5);
    myArr[4] = 4;

    //każda meber funkcja template klasy deklarowana poza klasą musi mieć
    //własną template deklarację

    //template klasy są tworzone w ten sam sposób czyli na żądanie w miejscu
    //wywołania

    //np vector jest template klasą vector<int>

    //templatki są szablonami do tworzenia klas i funkcji

    //w przypadku normalnych klas i funkcji umieszcza się headery w plikach hpp
    //a definicje w plikach cpp o tej samej nazwie, więc źródło klasy jest
    //kompilowane jako osobny plik projektu
    //!!!w przypadku tamplatek to nie zadziała
    //jeżeli wywołamy funkcję z template klasy, która była zdefiniowana w pliku cpp
    //dostaniemy linker error:
    //unresolved external symbol "public: int __thiscall Array::getLength(void)" (?GetLength@?$Array@H@@QAEHXZ)

    //aby kompilator użył templatki musi widzieć definicje, deklarację
    //i typ templatki

    //C++ kompiluje pliki indywidualnie kiedy Array.h jest inkludowana przez main
    //zawartość templatki ląduje w pliku main.cpp kiedy kompilator widzi, że jest
    //potrzebna instancja MyArray<int> tworzy ich instancje i kompiluje jako
    //część main.cpp,   jednak gdy dojdzie do osobnego skompilowania pliku MyArray.cpp
    //zapomni on, że potrzebujemy tablicy dla <int> więc funkcja szablonu nigdy
    //nie zostanie stworzona i będzie błąd linkera bo nie będzie definicji dla
    //MyArray<int>

    //abo powyższy problem rozwiązać można np dać cały kod w pliku header
    //wada tego jest taka, że będzie wiele lokalnych kopii co prawdopodobnie
    //wydłuży czas kompilacji i linkowania (linker powinien usunąć duplikaty
    //więc sam plik .exe powinien być ok) - jest to preferowane rozwiązanie !!!!!

    //inne rozwiązanie to zmienić rozeszrzenie .cpp na inl (pd inline) i wpliku
    //.hpp robić include pliku .inl (zadziała tak samo jakby było w pliku .cpp)

    //inne podejscie: three-file approach, definicja klasy template w headerze
    //template class membery w .cpp i trzeci plik templates.cpp, który zweiera
    //wszystkie użycia templatki:
    //template class Array<int>; // Explicitly instantiate template Array<int>
    //template class Array<double>; // Explicitly instantiate template Array<double>
    //template class command wymusi na kompilatorze jawne zinstancjowanie klasy
    //template, ponieważ templates.cpp jest w naszym projekcje zpstanie
    //skompilowane i zlinkowane wszędzie -> bardziej wydajna metoda ale wymaga
    //utrzymywania pliku templates.cpp




    //!!!!!templatki mogą przyjąć też inny parametr zwany non-type parameter
    //jest on specjalnym typem parametru, który nie zastępuje typu ale WARTOŚĆ
    //np: wartość całkowita lub enumerator, pointer lub referencja do const obiektu
    //pointer lub referencja do funkcji lub metody, std::nullptr_t
    StaticArray<int, 10> sa;
    sa[4] = 4;
    cout << sa[4] << endl;
    //!!!nie musieliśmy dynamicznie alokować mArr, ponieważ dla każdej instancji
    //klasy StaticArray size jest constant
    //!!!!!!!!!teh ficzer jest używany w bibliotece standardowej w klasie array
    //std::array<int, 60> arr;
}



#include <cstring>
template<class T>
class Storage1
{
private:
    T m_value;
public:
    Storage1(T value){m_value = value;}
    ~Storage1(){}
    void print(){std::cout << m_value << '\n';}
};

template<>
void Storage1<double>::print()
{
    std::cout << std::scientific << m_value << endl;
}
template<>
Storage1<char*>::Storage1(char* value)
{
    m_value = new char[std::strlen(value) + 1];
    std::strcpy(m_value, value);
}
template<>
Storage1<char*>::~Storage1()
{
    delete[] m_value;
}
void functionTemplateSpecialization()
{
    cout << "-----------------function specialization-------\n";
    //function templates służą do wygenerowania wielu funkcji o takiej
    //samej implementacji ale różnych typach

    //czasami jednak chcemy zrobić inną implementację dl jakiegoś typu
    Storage1<int> iVal{5};
    Storage1<double> dVal{5.23};
    iVal.print();
    dVal.print();//wykona się specjalizowana

    //aby zrobić specjalizację: zdefinuiwać spacjalizowaną funkcję (jeżeli jest to
    //metoda to zrobić to poza klasą), zmieniając typ templatki na nasz

    //gdy kompilator zacznie tworzyć Storage1<double>::print zauważy, że istnieje
    //jawnie zdefiniowana funkcja i uzyje naszej jawnej zamiast generować z
    //templatki

    //template,. mówi kompilatorowi że chodzi o function template ale nie przyjmuje
    //template parametrów (bo w tym przypadku wszystkie parametry określiliśmy
    //jawnie)

    char* stringg = new char[40];
    std::strcpy(stringg, "ala ma kota");
    cout << stringg << endl;
    Storage1<char*> cVal {stringg};
    delete[] stringg;
    //cVal.print();//śmieci bo jest po delete trzeba spacjalizację

    cVal.print();//po dodaniu specjalizacji
}

template <class T>
class Storage8
{
private:
    T m_array[8];
public:
    void set(int index, const T &value){m_array[index] = value;}
    const T& get(int index){return m_array[index];}
};
template <>
class Storage8<bool>
{
private:
    unsigned char m_data = 0;
public:
    void set(int index, bool value)
    {
        if(value)
            m_data |= 1 << index;
        else
            m_data &= ~(1 << index);
    }
    const bool get(int index)
    {
        return m_data & (1 << index);
    }
};
void classTemplateSpecialization()
{
    Storage8<int> si;
    for(int i = 0; i < 8; ++i)
        si.set(i, i);

    //dla bool'a jest małowydajne, można zrobić nową klasę ale będzie lipa
    //bo ta będzie służyła dla wszystkich poza boolami a dla booli będzie inna
    //klasa z inną nazwą

    //class template specializationa pozwala na specjalizacje template class
    //dla szczególnego typu
    //specialized functions/classes mają pierwszeństwo nad ogólnym template
    //!!!class template specializations są traktowane nak całkowicie niezalezne klasy
    //wiec możemy zmienić wszystko

    Storage8<bool> sb;
    for(int i = 0; i < 8; ++i)
        sb.set(i, true);

    for(int i = 0; i < 8; ++i)
        cout << sb.get(i) << ",";
    cout << endl;

    //template<> mówi kompilatorowi, że poniższe dotyczy szablonu
    //dodaliśmy <bool> do klasy aby pokazać, że dotyczy to tylko boola
    //warto utrzymywać wspólny interfejs między templatkami a ich specjalizacjami
}









#include <cstring>
template<class T, unsigned int size>
class StaticArrayT
{
    T mData[size];
public:
    StaticArrayT(){}
    T& operator[](unsigned int index)
    {
        assert(index < size);
        return mData[index];
    }
    const T& operator[](unsigned int index) const
    {
        assert(index < size);
        return mData[index];
    }
    T* getArray() { return mData; }
    void print();
};
template<class T, unsigned int size>
void StaticArrayT<T, size>::print()
{
    for(unsigned int i=0; i < size; ++i)
    {
        cout << mData[i] << ", ";
    }
}
//template<> --- TO DZIALA !!!!! ale chujnia bo size zawsze = 10
//void StaticArrayT<char, 10>::print()
//template<unsigned int size> --- CZESCIOWA SPECJALIZACJA FUNKCJI - NIEDOZWOLONE
//void StaticArrayT<char, size>::print() {} --- CZESCIOWA SPECJALIZACJA FUNKCJI - NIEDOZWOLONE



template<class T, unsigned int size>
void printT(const StaticArrayT<T, size>& array)
{
    for(unsigned int i=0; i < size; ++i)
    {
        cout << array[i] << ", ";
    }
}
//specialna wersja dla chara
    //template<>
    //void printT(const StaticArrayT<char, 14>& array) --> troche słaba
template<unsigned int size> //nie jest to cześciowa specjalizacja funkcji
                            //częściowa specjalizacja funkcji jest niedozwolona
                            //jest to jedynie przeciążenie funkcji przy użyciu
                            //częściowo specjalizowanego parametru klasy
void printT(const StaticArrayT<char, size>& array)
{
    for(unsigned int i=0; i < size && array[i] != 0; ++i)
    {
        cout << array[i];
    }
}


//rozwiązanie problemu z niemożliwością częściowej specjalizacji funkcji
//i metod poprzez dziedziczenie
template <class T, int size>
class StaticArrayT2_Base
{
protected:
    T mArray[size];
public:
    T* getArray() { return mArray; }
    T& operator[](int index) { return mArray[index]; }
    virtual void print() const {
        for (int i = 0; i < size; ++i)
            std::cout << mArray[i] << ", ";
        std::cout << "\n";
    }
};
template <class T, int size>
class StaticArrayT2: public StaticArrayT2_Base<T, size>
{};
template <int size>
class StaticArrayT2<char, size> : public StaticArrayT2_Base<char, size>
{
public:
    void print() const override{
        for (int i = 0; i < size && this->mArray[i] != 0; ++i)
            std::cout << this->mArray[i];
        std::cout << "\n";
    }
};
void partialTemplateSpecialization()
{
    StaticArrayT<int, 4> sa1;
    sa1[0] = 10;
    sa1[1] = 20;
    sa1[2] = 30;
    sa1[3] = 40;
    printT(sa1);
    cout << endl;

    StaticArrayT<char, 14> sa2;
    strncpy(sa2.getArray(), "Hello world!", 14);
    printT(sa2); //H, e, l, l, o,  , w, o, r, l, d, !,  ,  ,
                 //a dla chara lepiej bez przecinkow i pustych znakow
                 //po dodanie funkcji ze specjalizacją dla chara zadziała lepiej
    cout << endl;

    //partial template specialization plzwala na specjalizację klas
    //!!!ale nie indywidualnych funkcji!!!
    //gdzie któreś ale nie wszystkie parametry templatki został jawnie zdefiniowane

    //od C++14, partiale template specialization może być użyte jedynie z klasami!!!
    //funkcje muszą być w pełni specjalizowane.

    //!!!nasza funkcja printT(const StaticArrayT<char, size>& array)
    //działa ponieważ funkcja printT nie jest częściowo specjalizowana
    //jedt jedynie przeciążoną funkcją używając parametru klasy, który
        //jest częściowo specjalizowany ??????????????????

    //Powyższy limit prowadzi do problemów z member funkcjami
    //np jeżeli print byłaby memberem:
        //template<class T, int size>
        //class StaticArray_Base {
        //void print() {...} --> member wewnątrz klasy

        //template <int size>
        //void StaticArray<double, size>::print(){...} -> nie zadziała bo to
        //jest próba częściowej specjalizacji funkcji!!!!, czyli niedozwolone

        //obejście ww problemu np zrobienie częściowej specjalizacji całej klasy
        //ale to też chujnia bo trzeba przepisać cały kod
            //template <class T, int size>
            //class StaticArray {...}

            //template <int size>
            //class StaticArray<char, size> {...w większości kopia ww klasy}

    sa1.print();
    cout << endl;
    sa2.print();//nie da się zrobić cześciowej specjalizacji dla metody ani funkcji
    cout << endl;

    StaticArrayT2<int, 4> saT21;
    saT21[0] = 10;
    saT21[1] = 20;
    saT21[2] = 30;
    saT21[3] = 40;
    saT21.print();

    StaticArrayT2<char, 14> saT22;
    strncpy(saT22.getArray(), "Hello world!", 14);
    saT22.print();
}










template<class T>
class Storage2
{
private:
    T mValue;
public:
    Storage2(T value){
        mValue = value;
        cout << "Odpalila sie wersja bezwskaźnikowa\n";
    }
    ~Storage2(){}
    void print(){std::cout << mValue << '\n';}
};
template<class T>
class Storage2<T*>//częściowo specjalizowana klasa bo mówimy kompilatorowi,
                  //że jest tylko do użycia dla typów pointerowych
{
private:
    T* mValue;
public:
    Storage2(T* value){
        mValue = new T{*value};//umożliwia deep copy jednej wartości
        cout << "Odpalila sie wersja wskaźnikowa\n";
    }
    ~Storage2(){ delete mValue; }
    void print(){std::cout << *mValue << '\n';}
};

void partialTemplateSpecializationForPointers()
{
    //w poprzednich lekacjach stworzona była klasa,
        //template<class T>
        //class Storage1
    //która przechowywała jakiś obiekt
    //pojawił się problem np dla char* bo robiło płytką kopię, więc problem został
    //naprawiony poprzez pełną specjalizację konstruktora i destruktora
        //template<>
        //Storage1<char*>::Storage1(char* value)
    //ale co z innymi pointerami np int* ???

    //w związku z tem, że full template specialization zmusza nas do pełnego
    //rozwiązywania typów musielibysmy przeciążyć konstruktor i destruktor
    //dla każdego możliwego typu pointera

    //Partial template specializatjion dostarcza wygodne rozwiązenie tego problemu
    //Możemy zdefiniować wersję klasy, która działą tylko z pointerami
    int x = 55;
    Storage2<int>  s2i {x};
    Storage2<int*> s2ip{&x};
    x=999;//s2ip zrobiło kopię więc ta linia nic nie zmieni
    s2i.print();
    s2ip.print();

    //jakby nie było klasy ze specjalizacją dla pointerów, wykonała by się ta ogólna
    // i zrobiła shallow copy

    //klasa alokuje jedynie 1 element więc dla cstring array będzie tylko
    //pierwszy znak skopiowany

    //jeżeli zamiarem jest kopiowanie całej tablicy chara można zrobić np
    //specjalizację konstruktora i dostruktora dla char* jak w poprzenim zadaniu
}