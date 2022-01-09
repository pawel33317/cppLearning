#include <iostream>
#include <bitset>

void priorytetOperatorow();
void incrementDecrementOperatory();
void t_nicNieRob(void*);
void sizeOfComaCondtional();
void relationOperators();
void logicalOperators();
void operatoryBitowe();


void t_3_operators()
{
    printf("\n\n-----chapter 3 started-----\n");

    priorytetOperatorow();
    incrementDecrementOperatory();
    sizeOfComaCondtional();
    relationOperators();
    logicalOperators();
    operatoryBitowe();
}

void priorytetOperatorow()
{
    //::
    //L->R (), {}, [], ., ->, ++, --, type(), type{}, typeid i casty np static_cast
    //R->L +, -, ++, --, !, ~, (type), sizeof, &, *, new, new[], delete, delete[]
    //L->R ->*, .*
    //L->R *, /, %
    //L->R +, -
    //L->R <<, >>
    //L->R <, <=, >, =>
    //L->R ==, !=
    //L->R &
    //L->R ^
    //L->R |
    //L->R &&
    //L->R ||
    //R->L ?:, =, *=, /=, %=, +=, -=, <<=, >>=, &=, |=, ^=
    //R->L throw
    //L->R ,

    //!!!używać () jeżeli wyrażenie ma więcej niż 1 operator nawet
        //jeżeli jest to niekonieczne
    //^ XOR operator
    int x = 5;
    x = 6 - -6;
    printf("x = 6 - -6; x=%d\n", x);
    printf("4/0.0 = %f\n", 4/0.0);
    //printf("4/0.0 = %f", 4/static_cast<int>(0.0)); crash
    printf("7 %% 5 = %d\n", 7%5);
    //przed c++11 nie było sprecyzowane jak dzielić inty więc wynik mógł być
    //ujemny lub dodatni a zaokrąglenie w górę lub w dół
    //teraz zaokrągla się w kierunku 0 czyli ucina ułamek i znak jest liczby a (a%b)
}

void incrementDecrementOperatory()
{
    int x = 5;
    int y = x++; 
    //kompilator tworzy tmpX inkrementuje x i zwraca tmpX, póxniej ją kasuje
    t_nicNieRob(&x);
    t_nicNieRob(&y);

    //stosować pre inkrementację zamiast post, bardziej odporna na błądy i szybsza

    //int value = add(x, ++x); nie jest zdefiniowane w której kolejności
        //argumenty są zdefiniowane -> wynik nieznany
    //x = x++; wynik nieznany

    //funkcja ma side-effect jeżeli: modyfikuje stan, input, output lub
        //wywołuje inną funkcję
    //!!!zmienna z side-effect nie powinna być użyta więcej niż raz w 1 statement
}

void sizeOfComaCondtional()
{
    int z[15] {};
    printf("sizeof int[15] = %lu\n", sizeof(z));

    //przecinek ewolułuje do najbardziej prawej wartości, ma też najniższy prio
    int g = (z[0]++, 6);
    printf("int g = (5++, 6++) = %d\n", g);

    //fun(a, b); --> to nie jest coma operator -> to zwykły separator
    //int x(5), y(4); -> to też nie coma tylko separator

    //Operator conditional ?: -> terenary operator czyli bierze 3 argumenty
    //std::cout << (x > y) ? x : y; wyewoluuje do poniższego bo ?: ma mały prio
    //(std::cout << ( x > y)) ? x : y;

    //!!!conditional operatora używać tylko do prostych operacji żeby
        //zwiększyć czytelność
    //conditional operator ewoluuje jako wyrażenie więc można użyć do consta np
    //if/else ewoluuje jako zbiór statement
}

void relationOperators()
{
    printf("(100-99.99) == (10-9.99) = %s\n", 
        ((100-99.99) == (10-9.99) ? "true" : "false"));
}

void logicalOperators()
{
    //! && ||
    //wszystko !0 == true
    //!!! jeżeli ! jest stosowane do wyniku, wyrażenie powinno być w nawiasach

    //short circuit evaluation (if a++ && b++), jak a != true to b się nie wywoła
    //!!! && ma wyższy prio

    //De Morgan's law
    //!( x && y )  == !x || !y
    //!( x || y )  == !x && !y

    //nie ma XOR operatora porównania zamiast tego poniższe i tylko na boolach
    //if (a != b != c ...)
}

void printBinary(uint8_t zmienna)
{
    for (int i = 0; i < 4; ++i)
    {
        printf("%c", (zmienna & 0b1000u ) ? '1' : '0');
        zmienna = zmienna << 1;
    }
    printf("b\n");
}

void operatoryBitowe()
{
    //bool zajmuje 1 bajt bo potrzebuje adresu a adresowane są całe bajty
    // >> << ~ & | ^
    //!!!operacje bitowe powinny odbywać sie na zmiennych unsigned co c++ nie gwarantuje jak przechowywane są signed
    uint8_t u = 1;
    printf("u = 1 binarnie to ");
    printBinary(u);

    u <<= 2;
    printf("1 << 2: ");
    printBinary(u);

    u = 0b0100 >> 2;
    printf("u = 0b0100 >> 2: ");
    printBinary(u);

    u = ~0b0100;
    printf("u = ~0b0100: ");
    printBinary(u);

    printf("1 | 2 : ");
    printBinary(static_cast<uint8_t>(1 | 2));

    printf("1 & 2 : ");
    printBinary(static_cast<uint8_t>(1 & 2));

    printf("1 ^ 2 : ");
    printBinary(static_cast<uint8_t>(1 ^ 2));

    printf("3 ^ 2 : ");
    printBinary(static_cast<uint8_t>(3 ^ 2));

    constexpr uint8_t bit1 = 1 << 0;//bit 1
    constexpr uint8_t bit2 = 1 << 1;//bit 2
    constexpr uint8_t bit3 = 1 << 2;//bit 3

    u = 0u;
    u |= bit3;
    printf("Włączenie 3 bitu: u=0; u |= 0b0100: ");
    printBinary(u);

    u = 15u;
    u &= ~bit3;
    printf("Wyłączenie 3 bitu: u=15(1111); u &= ~0b0100: ");
    printBinary(u);

    u = 0u;
    u |= (bit1 | bit2 | bit3);
    printf("Włączenie bitu 1, 2, 3; u=0: ");
    printBinary(u);

    u = 15u;
    u &= ~(bit2 | bit3);
    printf("Wyłączenie bitu 2, 3; u=15: ");
    printBinary(u);

    u=15u;
    u ^= (bit1 | bit2);
    printf("Zamiana bitu 1, 2; u=15: ");
    printBinary(u);

    //maski oszczędzają pamięć i funkcja nie bedzie musiała mieć wielu parametrów
        //ponieważ np 1 int czyli 1 parametr może mieć w sobie 32 ustawienia

    std::bitset<4> bits;
    printf("bitset<4> = %s\n", bits.to_string().c_str());

    bits.set(2);
    printf("bits.set(2); = %s\n", bits.to_string().c_str());

    bits.reset(0);
    bits.flip(0);
    printf("bits.test(2); = %s\n", bits.test(2) ? "True" : "False");
}