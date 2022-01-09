#include <iostream>

void halt();
void ify();
void switche();
void gotoStatement();
void petle();
void randomNumbers();
void wprowadzanieDanych();
void t_nicNieRob(void*);

void t_5_flow_control()
{
    std::cout << "\n\n-----chapter 5 started-----\n";
    halt();
    ify();
    switche();
    gotoStatement();
    petle();
    randomNumbers();
    wprowadzanieDanych();
}

void halt()
{
   //#include <cstdlib>
   //exit(0); //kończy program i zwraca 0 do systemu operacyjnego
}

void ify()
{
   if (1 == 1); //null statement
}


enum class Kolor
{
   RED,
   BLACK
};
void switche()
{
   //switch są bardziej wydajne
   //switch musi ewaluować do typu całkowitego: int, char, enum..., enum class
   switch(Kolor::BLACK)
   {
      case Kolor::RED://Kolor::RED jest zdefiniowany jako const int i 
                      //testowany operatorem==
         {
            int g = 5;
            t_nicNieRob(&g);
         }
         int z;
         printf("Kolor to red\n");
         break;//zapobiega wykonaniu kolejnego case
      case Kolor::BLACK:
         z = 4;
         t_nicNieRob(&z);
         printf("Kolor to black\n");
         break;
      //case Kolor::BLACK: //nie może się powtarzać
   }
   //default nie jest obowiązkowe

   //!!!Wszystkie wyrażenie w switchu są częścią jednego bloku !!!

    //!!!w switchu nie można inicjalizować zmiennej bo initjalizacja wymaga
        //wykonania a może nie zostać wykonana !!!
    //!!!delaracje zmiennych z innego case są widoczne w innym poniweaż:
        //!!!zmienne są tworzone na początku bloku a nie w momencie zadeklarowania
        //!!!ale są widoczne dopiero od momentu zadeklarowania,
        //więc deklaracja zmiennej mówi jedynie kompilatorowi że od tego momentu
        //może jej używać
   //!!!jeżeli deklaruje się zmienne w case dobrze jest zrobić to w bloku
}

void gotoStatement()
{
    //!!!goto jest w scope function -> nowy scope, musi być w obrębie funkcji
    goto skip;
    printf("Printf przed goto\n");
    int z;
    z = 5;
    t_nicNieRob(&z);
    //int x = 55;
    //ERROR - !!!jeżeli zmienna będzie inicjalizowana nie można skoczyć za nią
skip:
    printf("Printf za goto\n");
    //!!!goto statement w c++ nie powinno być używane
}

void petle()
{
   unsigned int i = 10;
   while (--i > 0)
   {
      //infinite loop
      break;
      //każda zmienna tworzona w pętli jest w bloku więc jest tworzona
      //i usuwana co iterację
   }

   //!!!używać signed zmiennych do pętli
   //!!!zmienne nieproste deklarować poza pętlami o ile to możliwe

   do
   {
      printf("Wewnątrz do while\n");
      bool b = false;
      t_nicNieRob(&b);
   }
   while(true == false);//nie można użyć b w tej linii bo została zniszczona

   //!!!zmienne zadeklarowane w pętli for mają spacjalny scope "for scope"
   //!!!petle warto zawsze przetestować jakimiś małymi danymi wejściowymi

   //for(;;) //nieskonczona petla //ominięty blok ewoluuje do true dla fora

   //for(i = 0, j = 10; j > i; --j, ++i)
        //"," operator jest głównie i jedynie wykorzystywany w forze

   //break jest często używany do wyjścia z nieskończonej pętli
}

#include <cstdlib>
#include <random>
int getRandomNumber(int min, int max)
    //chujowa metoda bo mniejsze liczby są bardziej prawdopodobne
    //istnieje metoda na doublach ale też jest słaba
{
   return min + (rand() % (max - min + 1));
   //      5  + (1234   % ( 10 -  5  + 1))
   //      5  + (1234   % 6)
   //      5  + 4
   //      9
}
void randomNumbers()
{
   //rand wydląda mniej więcej tak
        //srand(5)
        //rand(){static s = srand; return s++; }

   srand(0);//wywoływana raz ustawia seed 
        //(czyli jakaś zmienną statyczną counter wewnątrz siebie)
        //value na jakąś wartość ()

   int r = rand();//losuje wartość od 0 do RAND_MAX
        //ZAWSZE pierwsza i kolejne wartość BEDZIA TAKA SAMA bo jak wyżej
        //zacznie losować od init value=0 a nie np aktualny czas
        //każda wylosowana liczba jest zależna od poprzedniej
   printf("Wylosowana liczba to: %d\n", r);


   srand(static_cast<unsigned int>(time(0)));
        //teraz przy każdym uruchomieniu liczby będą inne bo wartość startowa
        //będzie inna

   r = rand();
   printf("Wylosowana liczba to: %d\n", r);
   printf("Liczba losowa z przedzuału 5-10 to: %d\n", getRandomNumber(5,10));
   //w c++11 jest dodane bardzo wiele generatorów liczb losowych
   //różnych algorytmów itp

   std::random_device rd;
        //tym będzie inicjalizowana pierwsza liczba
        //w przypadku sranda był to np czas

   std::mt19937 mersenne(rd());//jeden z algorytmów podobno dobry
   std::uniform_int_distribution<int> generator(1,10);//Generator
   std::uniform_real_distribution<double> generator2(0.3, 0.99);

   std::cout << "Liczba wygenerowana z użyciem random_device jako seeda, " <<
                "algorytmem mersenne i generatorem intow: " <<
                generator(mersenne) << std::endl;

   std::cout << "Wygenerowana liczba zmiennoprzecinkowa <0.3, 0.99>= " <<
                generator2(mersenne) << std::endl;
}

void wprowadzanieDanych()
{
   //!!!robust - program obsługujący błędy
        //(przewidujący nadużycia i obsługujący je)
   //dane odczytywane przez operator extrakcji << są tymczasowo przechowywane
        //w buforze zanim trafią do zmiennej

   //użycie operatora >> powoduje przypisanie danych z bufora do zmiennej
        //a jeżeli nie ma nic w buforze pyta użytkownika o dane
   //\n powoduje zapis do bufora

   //operator >> wyciąga tak wiele danych z bufora ile może pomieścić w zmiennej

   //!!!dane które nie mogą zostać zapisane do zmiennejsą pozostawiane w buforze

   //ekstrakcja jest udana jeżeli przynajmniej 1 znak z bufora zostanie wyciągnięty

   //std::cin.ignore(32767, '\n'); wywala z bufora wszystko poza
        //wczytaną daną do zmiennej

   //int x;
   //std::cin >> x;
   //printf("\n%d\n", x);
   //!!!jak wpiszemy jakis spam np "abc" można sprawdzić czy ekstrakcja się udała
   //while... if(std::cin.fail()){std::cin.clear(); std::cin.ignore(32767, '\n');}
}
//http://www.learncpp.com/cpp-tutorial/5-11-introduction-to-testing-your-code/