#include <iostream>

void infroductionOperatorOverrloading();
void operatoryArytmetyczne_uzywajac_FriendOrMemberOrExternalFunc();
void operatortIO();
void operatoryUnarneIPorownania();
void operatoryInkrementacji();
void operatorSubscript();
void operatorNawiasow();
void typeCastOverloading();
void konstruktorKopiujacy();
void explicitDelete();
void operatorPrzypisania();
void shallowVsDeepCopying();

void t_9_operator_overloading()
{
    std::cout << "\n\n-----chapter 9 started-----\n";
    infroductionOperatorOverrloading();
    operatoryArytmetyczne_uzywajac_FriendOrMemberOrExternalFunc();
    operatortIO();
    operatoryUnarneIPorownania();
    operatoryInkrementacji();
    operatorSubscript();
        //dodatkowo inicjalizacja tablicy obiektow bez domyslnego konstruktora
    operatorNawiasow();
    typeCastOverloading();
    konstruktorKopiujacy();
    explicitDelete();
    operatorPrzypisania();
    shallowVsDeepCopying();
}

void infroductionOperatorOverrloading()
{
    //operatory to funkcje
    //x+y => można tłumaczyć na -> operator+(x,y)

    //!!!jeżeli oba operandy są typu prostego kompilator odpali wbudowaną procedurę
    //lub error

    //!!!dowolny operand jest typem użytkownika -> kompilator szuka przeciążenia
    //operatora zdefiniowanego przez użytkownika, jak nie znajdzie spróbuje
    //zmienić typ użytkownika na prosty jak nie to error

    //przeciążać nie można tylko -> ?:, ::, ., .*
    //nie można stworzyć nowych operatorów lub zmienić nazwy

    //!!!chociaż jeden operand musi być typem użytkownika
    //!!!nie można zmienić ilości operandów operatora
    //!!!precendence operatorów się nie zmienia

    //!!!jeżeli operator nie mówi jednoznacznie co robi użyć funkcji

    //!!!OPERATORY MOZNA PRZECIAZAC NA 3 SPOSOBY:
    // -> member function
    // -> friend function
    // -> normal function
}


class Cents
{
private:
    int mCents;
    int mRest;
public:
    Cents(int cents, int rest) : mCents(cents), mRest(rest){}
    int getCents() const {return mCents;}

    friend Cents operator+(const Cents& c1, const Cents& c2);
    friend Cents operator*(const Cents& c1, const Cents& c2)
        //tak raczej nie robić
        //ciało robić poza klasą
    {
        return Cents(c1.mCents*c2.mCents, 0);
    }

    //JAKO MEMBER FUNC
    //lewy parametr jest usunięty ponieważ jest niejawnie traktowany jako *this
    Cents operator/(const Cents& c2)
    {
        return Cents(mCents/c2.mCents,0);
    }
};
//Cents operator-(const Cents& c1, const Cents& c2);
    //DODAC W HPP bo nie ma deklaracji
    //JAKO FRIEND FUNC
Cents operator+(const Cents& c1, const Cents& c2)
{
    return Cents(c1.mCents + c2.mCents, 0);
}
//JAKO ZEWNETRZNA FUNC
Cents operator-(const Cents& c1, const Cents& c2)//preferować normalne nad friend nie dodając dodatkowych getterów
{
    return Cents(c1.getCents() - c2.getCents(), 0);
}
Cents operator+(const Cents& c1, int i)
{
    return Cents(c1.getCents() + i, 0);
}
Cents operator+(int i, const Cents& c1)
{
    return operator+(c1, i);//użycie innego operatora -> warto tak robić
}

void operatoryArytmetyczne_uzywajac_FriendOrMemberOrExternalFunc()
{
    Cents c1{50, 0};
    Cents c2{12, 0};
    Cents c3 = c1 + c2;
    printf("Przeciazenie operatora binarnego + c1+c2=%d\n", c3.getCents());
    c3 = c1 - c2;
    printf("Przeciazenie operatora binarnego - c1-c2=%d\n", c3.getCents());
    c3 = c1 * c2;
    printf("Przeciazenie operatora binarnego * c1*c2=%d\n", c3.getCents());
    c3 = c1 + 99;
    printf("Przeciazenie operatora binarnego + c1+int=%d\n", c3.getCents());
    c3 = 99 + c1;
    printf("Przeciazenie operatora binarnego + int+c1=%d\n", c3.getCents());
    c3 = c1/c2;
    printf("Przeciazenie operatora binarnego / c1/c2=%d\n", c3.getCents());

    //!!!nie wszystko może być przeciążone jako friend funkcja
    // = [] () -> muszą być przeciążone jako member funkcja bo tak wymaga język

    //!!!nie wszystko może być przeciążone jako member funkcja
    // << >> -> bo std::ostream (lewy parametr) nie jest *this
    // operator(Cents, int) -> możemy jako member
    // operator(int, Cents) -> NIE możemy jako member bo int nie jest typu Cents
    // !!!nie da się zrobić przeciążenia operatora jako member jeżeli
    // lewy operator nie jest klasą bądź też nie jest klasą którą możemy modyfikować

    //dla operatorów binarnych które nie modyfikują lewego operandu np
    //operator+ preferowane są zwykłe lub friend funkcje zamiast memberów
    //bo można zrobić (int, cents) (cents, int) wszystkie parametry są widoczne
        //i nie ma this

    //dla operatorów które modyfikują lewy operand np operator +=
    //preferowana jest member function bo lewy operand musi być typu klasy

    //unarne jako member bo nie mają parametrów

    //= [] () -> jako member
    //unarne jako member
    //binarne modyfikujące np += jako member
    //binarne niemodyfikujące np + jako normal lub friend func
}



class Point3D
{
    int x,y,z;
public:
    Point3D(int xx, int yy, int zz) : x{xx}, y{yy}, z{zz} {}

    //!!!std::ostream -> nie pozwala na kopiowanie, więc trzeba zwrócić
        //przez wartość
    //!!!można też zwrócić void ale późnie nie zadziała kolejne <<
    //!!!pozwala to na łańcuch
    friend std::ostream& operator<<(std::ostream& o, const Point3D& p);
    friend std::istream& operator>>(std::istream& i, Point3D& p);
        //może zwracać void
};
std::ostream& operator<<(std::ostream& o, const Point3D& p)
{
    o << "Point(x=" << p.x << ", y=" << p.y << ", z=" << p.z << ")";
    return o;
}
std::istream& operator>>(std::istream& i, Point3D& p)
{
    std::cout << "Enter x, y, z values:" << std::endl;
    i >> p.x >> p.y >> p.z;
    return i;
}
void operatortIO()
{
    //!!!std::cout jest typu std::ostream
    Point3D p {4, 5, 6};
    std::cout << p << std::endl;
    //!!!jeżelie chcemy aby operator binarny był chainable trzeba zwracać
        //lewy operator przez referencję -> w tym wypadku parametr był
        //przekazany do funkcji więc musi istnieć, nie musimy się obawiać
        //że zostanie zniszczony

    Point3D p2 {0,0,0};
    //std::cin >> p2; //ODKOMENTOWAC
    std::cout << p2 << std::endl;
}



#include <algorithm>
#include <vector>
class CentX
{
public:
    int val;
    CentX operator-() const
    {
        return CentX{-val};
    }
    bool operator!() const
    {
        return val == 0;
    }

    //binarny nie modyfikujący wartości więc friend
    friend bool operator==(const CentX& c1, const CentX& c2);
    friend bool operator!=(const CentX& c1, const CentX& c2);
    friend bool operator<(const CentX& c1, const CentX& c2);
};
bool operator==(const CentX& c1, const CentX& c2)
{
    return c1.val == c2.val;
}
bool operator!=(const CentX& c1, const CentX& c2)
{
    return !(c1==c2);
}
bool operator<(const CentX& c1, const CentX& c2)
{
    return c1.val < c2.val;
}
void operatoryUnarneIPorownania()
{
    // - + !
    CentX a {11};
    CentX b = -a;
    printf("Wartosc -CentX: %d\n", b.val);
    printf("CentX a != Centx b: %d\n", a != b);
    //! operator głównie to zmiany zwracanej wartości boola

    //!!! nie definiować operatorów które nie mają sensu dla danej klasy
    //!!! warto przeciążać operator < bo umożliwiaja sortowanie
    std::vector<CentX> vec {CentX{11}, CentX{1}, CentX{5}};
    std::sort(vec.begin(), vec.end());
    for (const auto& elem : vec)
        printf("%d ", elem.val);
    printf("\n");

    //operator > i <= są logicznie przeciwne więc warto implementować jeden
    //a w drugim wywołać !pierwszy
}




class CentY
{
public:
    int val;
    CentY& operator++()//prefix
    {
        ++val;
        return *this; //chainable
    }

    CentY operator++(int)
        //postfix -> placeholder brak nazwy mówi kompilatorowi,
        //że nie będziemy używać tej zmiennej
        //int to fake argument tylko po to aby rozróżnić pist i pre inkrementację
    {
        CentY tmp{val};
        ++(*this);//++val;
        return tmp;
    }
};
void operatoryInkrementacji()
{
    CentY c {10};
    ++c;
    ++c;
    printf("++CentY %d\n", c.val);
    printf("++CentY %d\n", ++c.val);
    printf("CentY++ %d\n", c++.val);
}




#include <cassert>
class IntList
{
    int* mList;
public:
    IntList(int size, int spam) : mList(new int[size] {1,2,3,4,5,6,7,8,9}) {}
    ~IntList() {delete[] mList;}
    //w operatorze subscript parametrem może być cokolwiek
    //int& operator[](std::string) 
    int& operator[](const int index)
        //zwraca referencję żeby można było coś tam wpisać
    {
        return mList[index];
    }

    int operator[](const int index) const
        //może zwracać też const int&
    {
        assert(index <= 10);
        return mList[index];
    }

};
void operatorSubscript()
{
    IntList il {10, 0};
    il[3] = 888;
    printf("IntList[3] = %d\n", il[3]);
    const IntList il2 {10, 0};
    printf("const IntList[3] = %d\n", il2[3]);

    //!!!uważać żeby nie wykonać [] operatora na pointerze
    IntList* ilptr = new IntList(10, 5);
    printf("(*ilptr)[3]: %d\n", (*ilptr)[3]);
    printf("ilptr[0][3]: %d\n", ilptr[0][3]);

    //IntList* ilList = new IntList[3](10, 5);
    //!!!nie da się zainicjalizować tablicy obiektów alokowanych dynamicznie
    //jeżeli obiekt nie ma domyślnego konstruktora :(, poniżej workaround
    int liczbaObiektow = 10;
    IntList* ilList = 
        reinterpret_cast<IntList*>(new char[sizeof(IntList) * liczbaObiektow]);
    for (int i = 0; i < liczbaObiektow; ++i)
    {
        new(&ilList[i]) IntList{10, 5};
        //delete &ilList[i];
    }
    printf("ilList[1][1]: %d\n", ilList[1][3]);
}




class Matrix
{
    int content [4][4];
public:
    int operator()(int col, int row)
    {
        return content[col][row];
    }
    int operator()()
    {
        return content[0][0];
    }
};
class Functor
{
    int i = 10;
public:
    int operator()(int addVal)
    {
        return (i+=addVal);
    }
};
void operatorNawiasow()
{
    //!!!pozwala wybrać typ parametrów i ilość
    //!!!obowiązkowo jako member
    //!!!w przypadku funkcji operator () jest operatorem wywołania funkcji
    //!!!w przypadku klas operator () jest zwykłym operatorem,
        //który wywołuje funkcję operator()

    Matrix m {};
    printf("m(3,3) = %d\n", m(3,3));
    printf("m() = %d\n", m());

    //!!!Operator() jest często używany do roienia funktorów
        //czyli klas które działają jak funkcje -> ich zaletą jest to że mogą
        //przechowywać dane

    Functor f;
    std::cout << "f(5): " << f(5);
    std::cout << ", f(6): " << f(6) << std::endl;
    //funktory są lepsze od funkcji ze staticami bo można robić więcej
        //niż 1 instancję
}



class CentQ
{
public:
    int mCents = 0;
    operator int() { return mCents; } //!!!spacja po operator i brak return type
};
class Dolar
{
public:
    double mDolar;
    operator CentQ() {return CentQ {(int)(mDolar*100)}; }
};
void typeCastOverloading()
{
    CentQ c {55};
    int i = c;
    Dolar d {5.0};
    std::cout << "(int)(CentQ c) = " << i << std::endl;
    std::cout << "(CentQ c) = " << c << std::endl;
    std::cout << "static_cast<int>(CentQ) = " << static_cast<int>(c) << std::endl;
    std::cout << "(CentQ)Dolar = " << (CentQ)d << std::endl;
}



class Fraction
{
private:
    int mNumerator;
    int mDenominator;
public:
    Fraction(int numerator=0, int denominator=1):
        mNumerator(numerator), 
        mDenominator(denominator)
    {
        assert(denominator != 0); 
        printf("Konstruktor Fraction(numerator=%d, denominator=%d)\n",
                    mNumerator, mDenominator);
    }

    Fraction(const Fraction& other):
        mNumerator(other.mNumerator*100), 
        mDenominator(other.mDenominator*100)//działa dokładnie tak jak domyślny
    {
        printf("Konstruktor kopiujacy Fraction (numerator=%d, denominator=%d)\n",
                    mNumerator, mDenominator);
    }

    friend std::ostream& operator<<(std::ostream& o, const Fraction& fraction);
};
std::ostream& operator<<(std::ostream& o, const Fraction& fraction)
{
    o << "Fraction[" << fraction.mNumerator << "/" << fraction.mDenominator<< "]\n";
    return o;
}

class Fraction2
{
private:
    int mNumerator;
    int mDenominator;
public:
    Fraction2(int numerator=0, int denominator=1)
        :mNumerator(numerator), mDenominator(denominator)
    {
        printf("Konstruktor Fraction2(numerator=%d, denominator=%d)\n",
                mNumerator, mDenominator);
    }
private:
    Fraction2(const Fraction2& other){ }
};
void konstruktorKopiujacy()
{
    //Do tworzenia nowego obiektu na bazie starego
    //tworzony domyślnie, brak tylko gdy zrobimy swój lub move constructor
        //!!!ponieważ nie wie dużo o klasie wykorzystuje memberwise initialization
        //!!!czyli inicjalizuje każdy member nowej klasy starym memberem

    //!!!COPY ELISION (opuszczenie) -> RVO
        //pominięcie przez kompilator copy konstruktora głównie dla
        //obiektów anonimowych -> więc treść copy konstruktora się nie wywoła
    //!!!wylaczenie RVO (copy elision) -fno-elide-constructors

    Fraction f1 {4,5};//uniform initialization KONSTRUKTOR ZWYKLY
    Fraction f2 (6,7);//direct initialization KONSTRUKTOR ZWYKLY

    Fraction f3 = 8;//copy initialization -> konwertuje 8 na Fraction
                    //KONSTRUKTOR ZWYKLY (dla prawej strony) i KOPIUJACY dla lewej
                    //PRZEZ ELISION RVO copy constructor się nie wywoła

    Fraction f4 = Fraction(9, 10);//copy initialization
                    //KONSTRUKTOR ZWYKLY (dla prawej strony) i KOPIUJACY dla lewej
                    //PRZEZ ELISION RVO copy constructor się nie wywoła

    std::cout << f1 << f2 << f3 << f4;

    Fraction f5 (f1);//direct initialization calls only COPY CONSTRUCTIR
                     //TU RVO się nie wywoła bo f1 nie jest tymczasowe
                     //więc wykona się copy konstruktor

    Fraction f6 (Fraction(11, 12));//direct initialization calls COPY CONSTRUCTIR
                                   //oraz Konstruktor zwykły
                                   //PRZEZ ELISION RVO copy constructor
                                   //się nie wywoła


    //Fraction six = Fraction(6);   //ELISION
    //Fraction six(Fraction(6));    //ELISION
    //Fraction six = getFraction(){return Fraction()}; //ELISION
    //std::cout << getFraction(){return Fraction()}; //BRAK ELISION

    //!!!Unikać copy initialization bo nie wiadomo czy RVO się wykona
    //!!!constructor elision nie jest gwarantowane

    //!!!czesto używa się domyślnego konstruktora kopiującego i jest to OK
    printf("===============================\n");

    Fraction2 f21 {13, 14};
    //Fraction2 f22 = 11; //!!!nie dziala bo copy konstruktor PRIVATE
    //Fraction2 f23 = Fraction2(13, 14);//!!!jak wyżej
}




class MyString
{
private:
    std::string  mString;
public:
    explicit MyString(int size)
    {
        mString.resize(size);
        printf("Set size to: %d\n", size);
    }
    explicit MyString(const MyString& os)
    {
        std::cout << "MyString copy constructor\n";
    }
};

class MyString2
{
private:
    std::string  mString;
    //MyString2(char){}; -> lepsze rozwiązanie to delete
public:
    MyString2(char) = delete;
    explicit MyString2(int size)
    {
        mString.resize(size);
        printf("Set size to: %d\n", size);
    }
    explicit MyString2(const MyString2& os)
    {
        std::cout << "MyString copy constructor\n";
    }
};
void explicitDelete()
{
    printf("===============================\n");
    //!!!C++ traktuje konstruktor jako operator niejawnej konwersji
    //Fraction f = 6; -> 6 zostanie niejawne przekonwertowane
        //na Fraction konstruktorem

    //void printx(Fraction f){}... -> printx(9); jak wyżej
        //ta niejawna konwersja działa zawsze: dla uniform, direct,
        //copy initialization

    //!!!Konstruktory, które można wykorzystać do niejawnej konwersji
        //są nazywane konstruktorami konwertującymi
        //przed C++11 tylko konstruktor jedno parametrowy był konwertujący

    //MyString ms1 = 'x';
        //set size to 120 -> bo implicit conversion czyli chujnia

    //MyString ms1 = 'x'; -> nie zadziała bo dodano słówko explicit do konstruktora
        //!!!zabrania to wykonania niejawnej konwersji do typu MyString
        //czyli nie rozwinie się do MtString ms1 = MyString('x');
        //direct i uniform dalej działa

    MyString ms1('x');
    MyString ms2{'x'};//uniform zabrania tylko narrowing konwersji
    static_cast<MyString>('x');//jawna konwersja dalej działa

    MyString ms4 = MyString(111); //EXPLICIT COPY CONSTRUCTOR
        //!!!zabrania niejawnego wykonania copy konstruktora

    MyString ms3(MyString(111));
    //!!!rozważać robienie konstruktorów explicit

    //MyString2 ms21('x'); -> prywatny konstruktor zablokowana możliwość
        //inicjalizacji charem
    //!!!ale wciąż można wykonać prywatny konstrujktor będąc wewnątrz klasy
        //!!!lepiej użyć delete
        //!!!delete można użyć też do copy konstruktora, operatorów, ...
}





class Contener
{
public:
    int content;
    Contener& operator=(const Contener& other)
    {
        if(this == &other)
            return *this; //zapobiega self assigment
        std::cout << "Operator przypisania Contener\n";
        content = other.content;
        return *this;
    }
};
void operatorPrzypisania()
{
    //!!!assigment operator jest używane do skopiowania wartości z jednego
        //obiektu do innego

    //!!!cele copy construktora i operatora przypisania są prawie takie same
    //jednak copy constructor inicjalizuje nowy obiekt a operator przypisania
    //zmienia content istniejącego

    //jeżeli nowy obiekt musi zostać utworzony przed kopiowaniem używany
        //jest copy construktor
    //jeżeli nie musi być tworzony używany jest operator przypisania

    //copy assigment nie jest domyślnie tylko gdy user zadeklarował
        //move constructor lub inny copy assigment

    //operator przypisania musi beć jako member
    Contener c {55};
    Contener c2 {33};
    Contener c3;
    c3 = c2 = c;
    printf("C3.content = %d\n", c3.content);

    //c = c; -> self assigment bezsensowne i groźne z dynamiczną pamięcią
    //w operatorze rozwiązanie

    //dla copy konstruktora nie ma sensu tego sprawdzać bo niema możliwości
        //przypisania nowo tworzonego obiektu do siebie

    //!!!domyślnie iestnieje copy assigment, działa jako copy constructor
        //czyli używa memberwise assigment

    //!!!można usunąć
        //Contener& operator=(const Contener& other) = delete;
}


#include <cstring>
//#include <memory>
class Data
{
private:
    int mSize;
    char* mData;
public:
    Data(const char* string) :
        mSize(std::string(string).length()),
        mData(new char[mSize+1])
    {
        std::strcpy(mData, string);
    }
    ~Data() { delete[] mData; }

    Data(const Data& src)
    {
        mSize = src.mSize;
        if(src.mData)
        {
            mData = new char[mSize+1];
            std::strcpy(mData, src.mData);
        }
        else
        {
            mData = nullptr;
        }
    }

    Data& operator=(const Data& src)
    {
        if (this == &src)
            return *this;
        delete[] mData; //!!!ważne

        mSize = src.mSize;
        if(src.mData)
        {
            mData = new char[mSize+1];
            std::strcpy(mData, src.mData);
        }
        else
        {
            mData = nullptr;
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& o, const Data& data);
};
std::ostream& operator<<(std::ostream& o, const Data& data)
{
    o << "Data size: " << data.mSize << ", val: " << data.mData << std::endl;
    return o;
}
void shallowVsDeepCopying()
{
    //!!!shallow copy == memberwise copy
    //to co domyślnie dostarcza copy assigment oraz copy konstruktor
        //czyli c++ przy assigment operatorze kopiuje każdy obiekt indywidualnie
        //a przy konstruktorze kopiującym inicjalizuje kżde pole
            //direct inicjalizacją

    //!!!shallow - płytka kopia kopiuje wskaźniki a nie alokuje nowej pamięci

    Data data {"Jakis tekst"};
    std::cout << data;
    {
        Data data2 = data;
    }

    //jakby konstruktor kopiujacy byl domyslny czyli robil plytka kopie
        //tutaj by się wysypało bo data2 -> skasowałaby mData na które wskazywałyby
        //oba obiekty data i data2
    std::cout << data;
    Data data3 {""};
    data3 = data;
    std::cout << data3;

    //!!!w implementacji operatora jest dodatkowo w stosunku do copy konstruktora:
    //self-assigment check, return *this
    //dealokacja pamięci -> obowiązkowe bo memory leak,
        //mógł wcześniej mieć wartość
        //lepiej użyć np wektora
}