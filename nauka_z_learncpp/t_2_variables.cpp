#include <iostream>
#include <limits>

void typyProste();
void zmienneZeStalymRozmiarem();
void zmienneZmiennoPrzecinkowe();
void boole();
void chars();
void literals();
void constAndSymbolic(int param);
void t_nicNieRob(void*){};

void t_2_variables()
{
    std::cout << "\n\n-----chapter 2 started-----\n";

    typyProste();
    zmienneZeStalymRozmiarem();
    zmienneZmiennoPrzecinkowe();
    boole();
    chars();
    literals();
    constAndSymbolic(44);
}

void typyProste()
{
    //bool
    //char, wchar_t, char32_t, char16_t
    //float, double, long double
    //!!!short, int, long, long long

    //!!!zmienna to alias na adres w pamięci

    //int i = 5; //copy initialization
    //int i(5);  //direct initialization LEPSZE
    //int i{5};  //uniform initialization NAJLEPSZE
    //int i{};   //inicjalizuje zerem
    //!!!uniform initialization nie pozwala na narrowing int i {4.5}

    //int i;
    //i = 4; //copy assigment

    //int e{9}, f{10};
    //!!!int a, b = 5; a jest niezainicjalizowane

    //!!!nie deklarować wielu zmiennych w jednej lini jeżeli są tam inicjalizowane
    //!!!definiować zmienne jak najbliżej ich użycia

    //void oznacza brak typu
    //function(void) -> przykładowa funkcja zgodna z c z opcjonalnym void

    //bool, char, wchar_t -> 1 bajt minimum
    //char16_t, short, int -> 2 bajty minimum
    //char32_t, long, float -> 4 bajty minimum
    //long long, double, long doubl0e(16) -> 8 bajtów minimum

    std::cout << "Size of int is: " << sizeof(long double) << " bytes" << std::endl;
    //on x64 int is still 4 bytes

    //!!!use "long" instead "long int" etc
    unsigned char uchar = std::numeric_limits<unsigned char>::max();
    printf("Max unsigned char value is %d", uchar);

    //używać signed zmiennych zamiast unsigned jeżeli nie ma powodu
}

void zmienneZeStalymRozmiarem()
{
    uint64_t ui64t {std::numeric_limits<unsigned long long>::max()};
    std::cout << "Max size of ull is: " << ui64t << std::endl;

    //uint8_t i int_8t mogą być traktowane jako char ale to błąd kompilatorów

    //zmienne z zafixowanym rozmiarem mogą być wolne i mogą nie odpalić
    //się na jakiś architekturach które nie wspierają takiego rozmiaru zmiennej
    //po to zostąły stworzone poniższe zmienne

    int_fast32_t if32 {}; //zmienna która ma minimum 32 bajty i jest szybka 
        //(najszybsza dostępna)
    int_least32_t il32 {}; //zmienna która ma minimum 32 bajty 
        //(najmniejsza dostępna)
    t_nicNieRob(&if32);
    t_nicNieRob(&il32);
}

void zmienneZmiennoPrzecinkowe()
{
    //!!!double jest zawsze signed
    long double ld {std::numeric_limits<long double>::max()};
    std::cout << "long double max w naukowej notacji: " << ld << std::endl;

    //preferowć double zamiast floatów
    //budowa doubla opiera się na naukowej notacji i znaczących bitach
    double d {0.1}; //= 0.100000000000001 rounding error
    printf("double(0.1) = %.17g\n", d);

    double zero = 0.0;
    printf("double(0.0) = %.17g\n", zero);
    double negativeInfinity = -5.0/zero;
    printf("double(-5.0/zero) = %.17g\n", negativeInfinity);//positife analogicznie
    printf("Not A Number double(0.0/0.0) = %.17g\n", 0/0.0);
    //printf("int(1/0) %d", 1/0); inta nie wolno dzielić przez 0
}

void boole()
{
    std::cout << "True = " << true << std::endl;
    std::cout << std::boolalpha;
    std::cout << "True = " << true << std::endl;
}

void chars()
{
    printf("sizeof(char) = %lu\n", sizeof(char));
    //int8_t jest zwykle traktowany jako char ale to błąd
    printf("w ASCII litera a ma liczbę: %d\n", static_cast<int>('a'));

    //std::endl w przeciwieństwie do \n gwarantuje że jeżeli są 
        //jakieś skolejkowane bufory będą wyautputowane przed kontynuacją

    //wchar_t nie używać tylko do windows api
    //char16_t & char32_t są do utf16/32

    std::string stringg = "cześć";
    printf("String ma zawartość: %s\n", stringg.c_str());
}

void literals()
{
    //!!!w c++ są 2 typy stałych literals i symbolic
    //literal constants są nazywane literals, są wpisane w kod i nie da 
        //się zmienić ich wartości
    //np true, 5, 3.14159, 6.02e22, 'a', "Hello"

    //numeric literals powinny mieć sufixy np
    //int l lub L, long long ll lub LL
    //są opcjonalne jeżeli domyślne bo kompilator wie
    unsigned int uintt = 5u;
    t_nicNieRob(&uintt);

    int sysLiczbowe = 12;
    sysLiczbowe = 010;//prefix 0 
    sysLiczbowe = 0xF;//prefix 0x
    sysLiczbowe = 0b10100;
    printf("0b10100 = %d\n", sysLiczbowe);
    sysLiczbowe = 0b1000'1010;
    sysLiczbowe = 2'321'123; //dziesiętnie
    //!!!nie używać magic numberów
}

void constAndSymbolic(int param)
{
    int a {param}; //lepsze niż int const a {param};
    t_nicNieRob(&a);

    constexpr int constExprInt {5};
    char tab[constExprInt];//ze zwykłym constem byłoby to niedozwolone
                           //mimo że się kompiluje
    t_nicNieRob(tab);

    //zmienne powinny być najpierw constexpr -> const -> bez, jeżeli możliwe

    //SYMBOLIC CONSTANTS
    #define MAX_COSTAM 5 //nie używać bo brak w debuggerze i mają zawsze file scope
    //czyli mogą wystąpić np konflikty nazw
    //lepiej użyć constexpr

    //ciekawa opcja zrobić heder na consty i zrobić w nim namespace
}