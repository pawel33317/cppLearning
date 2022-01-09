#include <iostream>

//  /usr/bin/g++-11 -std=c++2a -Wall -O0 -o philosophy 1_philosophy.cpp && ./philosophy



int main()
{
    //1 - wyrażaj pomysły w kodzie
        /*
            Month month() const; - DOBRZE
            int month(); - ZLE

            change_speed(Speed s); 
                change_speed(2.3); - ZLE
                change_speed(23_m / 10s); - DOBRZE
        */
        /*
            int index //lepiej z GSL
            for ...
                if ...
                    index = ...
            ^---ZLE używać funkcji języka jak find zamiast szukać ręcnie
                    każdy programosta powinien znać podstawy STL'a

            auto p = find(begin(v), end(v), val); - DOBRZE
        */
        //1 !!!
            // używać const konsekwentnie
            // lag uses of casts (casts neuter the type system)
            // detect code that mimics the standard library (hard)


    //2 - pisz w standardzie ISO C++
        //jeżeli są rozszerzenia języka któe nie mogą wspierać ISO - robić do nich interfejsy jak możlowe
        //unikać undefined behaviour "v[i] = ++i;" i implementation defined "sizeof(int)"
        //używać nowoczesnych kompilatorów


    //3 - wyrażaj zamiary
        //żeby każdy rozumiał co kod robi
        /*
            gsl::index i = 0;
            while (i < v.size()) {
                // ... do something with v[i] ...
            ZLE - bo nie wiadomo czy ktoś chce tylko przeiterować p otablicy czy coś zmieniać
                - więc może to być nadużyte
                - i przeżyje zakres pętli co też może być niezamierzone
            
            DOBRE - const mówi że chcemy tylko przeiterować a brak consta, że chcemy modyfikować
            for (const auto& x : v) { do something with the value of x }
            for (auto& x : v) { modify x }

            czasami warto też użyć for_each bo jawnie mówi co robi i mówi że kolejność nie jest istotna
            for_each(v, [](int x) { do something with the value of x });
            for_each(par, v, [](int x) { do something with the value of x });
        */
        /*
            koordynaty łączyć
            draw_line(int, int, int, int);  // obscure
            draw_line(Point, Point);        // clearer
        */

       //3 !!!
            // programiśco powinni znać The guidelines support library i The ISO C++ Standard Library
                // i inne biblioteki używane w projekcie
            // preferować range-for loops
            // zmienne z pętli są często w zbyt dużym zakresie
            // f(T*, int) interfaces vs. f(span<T>) interfaces
            // naked new and delete
            // funkcje z zbyt dużą liczbą parametrów typów wbudowanych


    //4 - w idelnam świecie program program byłby całkowicie statycznie (w czasie kompilacji) 
        // bezpieczny typem ale przez poniższe nie może:
            // unie, casty, array decay, range errors, narrowing
        //te obszary powodują ogromne problemy i powinno się ich unikać

        //4 !!!
            //variant zamiast unii
            //minimalizacja cast
            //array decat - używać span z gsl
            //range errors - używać span z gsl
            //narrowing - unikać

    
    //5 - preferuj compile-time checking zamiast run-time
        //wydajność i obsługa błędów uproszczona
        /*
            // Int is an alias used for integers
            int bits = 0;         // don't: avoidable code
            for (Int i = 1; i; i <<= 1)
                ++bits;
            if (bits < 32)
                cerr << "Int too small\n";
            ZLE - bo buffer overflow jest undefined

            DOBRZE
            static_assert(sizeof(Int) >= 4);    // do: compile-time check 

            NAJLEPIEJ
            użyć int32_t
         */
        /*
            void read(int* p, int n);   // read max n integers into *p
            int a[100];
            read(a, 1000);    // bad, off the end
         
            DOBRZE-
            void read(span<int> r); // read into the range of integers r
            int a[100];
            read(a);        // better: let the compiler figure out the number of elements
        */
        //5 !!!!
            //to co się da zrobić w czasie kompilacji warto tam robić
            //Look for pointer arguments.
            //Look for run-time checks for range violations.

        
    //6 - co nie można sprawdzić w czasie kompilacji powinno być sprawdzalne w run time
        //idealnie powinniśmy łąpać wszystkie błędy ale nie jest to możliwe
        /*
            // separately compiled, possibly dynamically loaded
            extern void f(int* p);
            void g(int n)
            {
                // bad: the number of elements is not passed to f()
                f(new int[n]);
            }

            //LEPIEJ ALE DALEJ SŁABO bo się można pomylić

            extern void f2(int* p, int n);
            void g2(int n)
            {
                f2(new int[n], m);  // bad: a wrong number of elements can be passed to f()
            }

            //ZLE

            // NB: this assumes the calling code is ABI-compatible, using a
            // compatible C++ compiler and the same stdlib implementation
            extern void f3(unique_ptr<int[]>, int n);
            void g3(int n)
            {
                f3(make_unique<int[]>(n), m);    // bad: pass ownership and size separately
            }

            //DOBRZE bo przekazujemy obiekt i rozmiar jako jedność

            extern void f4(vector<int>&);   // separately compiled, possibly dynamically loaded
            extern void f4(span<int>);      // separately compiled, possibly dynamically loaded
                                            // NB: this assumes the calling code is ABI-compatible, using a
                                            // compatible C++ compiler and the same stdlib implementation
            void g3(int n)
            {
                vector<int> v(n);
                f4(v);                     // pass a reference, retain ownership
                f4(span<int>{v});          // pass a view, retain ownership
            }
        */

    // 7 - łap run time błędy wcześnie
        //unikanie crashy
        //podwójna nadmiarowa walidacja
        /*
            Date read_date(istream& is);    // read date from istream
            Date extract_date(const string& s);    // extract date from string

            void user1(const string& date)    // manipulate date
            {
                auto d = extract_date(date);
                // ...
            }

            void user2()
            {
                Date d = read_date(cin);
                // ...
                user1(d.to_string());
                // ...
            }

            NADMIAROWA WALIDACJA PRZEZ KONSTRUKTOR DATE
            NIE UŻYWAC STRINGÓW DO PRZESYŁANIA USTRUKTURYZOWANYCH DANYCH
        */
        //7 !!!
            //dla pointerów i arrays rób range checking wcześnie i bez powtórzeń
            //eliminować narrowing
            //uważać na niesprawdzone wartości przychodzące
            //uważać na strukturyzowne dane przesyłane jako string i unikać


    //8 nie rób wycieków zasobów
        /*
            void f(char* name)
            {
                FILE* input = fopen(name, "r");
                // ...
                if (something) return;   // bad: if something == true, a file handle is leaked
                // ...
                fclose(input);
            }

            DOBRZE - UŻYWAĆ RAII
            void f(char* name)
            {
                ifstream input {name};
                // ...
                if (something) return;   // OK: no leak
                // ...
            }
        */
        //wyciek zasobu (utrata pointera) np do pliku przez długo żyjący program to nic złego
            //system go zamknie po wyłączeniu apki jest akceptowalne
        //8 !!!
            // uważać na pointery i klasyfikować jako ownery i nie ownery 
            // zamieniać takie ownery na uchwyty stl'a jak w ww przykładzie lub oznaczać jako gls::owner
            // Look for naked new and delete
            // uważać na funkcje alukujące coś i zwracające ptr


    //9 - nie marnuj czasu lub miejsca
        //czas spędzony na osiągnięcie celu np na szxybkość dewelopmentu, uproszczenia testowania
        //bezpieczeńśtwo zasobów w c++ nie jest zmarnowany :)
        //częste błędy
            //źle ułożone zmienne marnujące miejsce - padding
            //definicje copy wyłączające semantyke przenoszenia
            //kod nie gwarantujący RVO
            //niepotrzbne zmienne i alokacje
        /*
            void lower(zstring s)
            {
                for (int i = 0; i < strlen(s); ++i) s[i] = tolower(s[i]);
            }
            ZLE BRAK CACHOWANIA WARTOSCI STRLEN I WYWOŁYWANIE CO ITERACJE
        */
        //9 !!!
            //uważać na niepotrzebne elementy:
                //unused return value np z user defined operator++


    //10 preferować niezmienne dane zamiast zmiennych (immutable)
        //lepsza optymalizacha i uniemożliwia niecelową zmianę


    //11 enkapsulować messy konstrukcje zamiast rozprzestrzeniać je w kodzie
        //messy code jest zły - lepiej używać intergejsów
        /*
            int sz = 100;
            int* p = (int*) malloc(sizeof(int) * sz);
            int count = 0;
            // ...
            for (;;) {
                // ... read an int into x, exit loop if end of file is reached ...
                // ... check that x is valid ...
                if (count == sz)
                    p = (int*) realloc(p, sizeof(int) * sz * 2);
                p[count++] = x;
                // ...
            }
            
            DOBY:

            vector<int> v;
            v.reserve(100);
            // ...
            for (int x; cin >> x; ) {
                // ... check that x is valid ...
                v.push_back(x);
            }
        */


    //12 używać tooli wspierających
        //analiza statyczna
        //cocncurrency tools
        //testing tools
        //repos, build tools

    
    //13 - używać wspierających bibliotek (sprawdzonych i udokumentowanych)
        //bezpieczne, szybkie, lepsze


    //KONIEC
    std::cout << "\nEND\n";
}


