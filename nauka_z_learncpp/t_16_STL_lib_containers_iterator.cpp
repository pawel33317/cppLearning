#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <forward_list>
using namespace std;

void stlContainers();
void stlIterators();
void stlAlgorithms();

void t_16_STL_lib_containers_iterator()
{
    cout << "\n\n-----chapter 16 started-----\n";
    stlContainers();
    stlIterators();
    stlAlgorithms();
}

void stlContainers()
{
    //3 główne rodzaje: sequence kontenery, asocjacyjne, adaptery


    //SEKWENCYJNE: utrzymują kolejność elementów, można wybrać miejsce
        //wstawienia elementu
        //vector, deque, array, list, forward_list, basic_string

    //vector - dynamiczna array, która umie rosnąć,
        //pozwala na random access (i[6])
        //pozwala na SZYBKIE dodawanie i usuwanie elementów na końcu
        //.push_back(), pop_back()
    vector<int> vec;
    vec.push_back(5);

    //deque - czyt deck (desk) - podwójnie zakończona dynamiczna array
        //może rosnąć
        // .push_back(), .push_front()
    deque<int> deq;
    deq.push_back(5);
    deq.push_front(25);
    cout << deq.front() << endl;
    deq.pop_front();

    //list - double linked list, każdy element listy posiada wskaźnik na kolejny
        //i poprzedni element w liście, lista daje dostep tylko do pierwszego
        //i ostatniego elementu czyli brak random access,
        //aby znalźć element pośrodku trzeba przechodzić po kolei
        //dodawanie elementów do listy jest bardzo szybkie
            //(o ile wiemy gdzie chcemy dodać)
        //używa się iteratorów do chodzenia po liście
    list<int> l;
    l.push_back(5);
    l.push_front(4);
    auto it = l.begin();
    l.insert(++it, 100);
    for(auto& elem : l){
        cout << elem << ", ";
    }

    //string i wstring niby nie są uwzględnione jako kontenery sekwencyjne
        //ale tak naprawdę są nimi można je rozważać jak wektory
        //z elementami typu char
    string st = "abcde"s;

    //forward_list - singly-linked list ma tylko 1 pointer a nie jak lista 2
        //czyli iteracja tylko z początku do końca
    forward_list<int> fl {12};
    fl.push_front(5);//nie ma back
    fl.push_front(4);
    fl.insert_after(fl.begin(), 100);
    for(auto& elem : fl)
        cout << elem << ", ";
    cout << endl;


    //ASOCJACYJNE - automatycznie sortują dane wejściowe podczas wstawiania
    //elementy są porównywane przez operator<

    //set - trzyma unikalne elementy, nie pozwala na duplikaty,
        //kolejność zgodna z wartościami
        //prawie jak binarne drzewo przeszukiwań
    set<int> s {1,2,3,4,3,2,1};
    s.insert(5);
    s.insert(1);
    for(auto& elem : s)
        cout << elem << ",";
    cout << endl;

    //multiset - set pozwalający na duplikaty
    multiset<int> ms {1,2,3,4,3,2,1};
    ms.insert(5);
    ms.insert(1);
    for(auto& elem : ms)
        cout << elem << ",";
    cout << endl;

    //map - associative array - set w którym każdy element jest parą
        //zwaną klucz/wartość
        //klucz jest używany do sortowania i indexowania danych, musi być unikalny
        //wartość jest rzeczywistą wartością
    map<int, string> m {{1, "jeden"}};
    m[2] = "dwa"s;
    m[3] = "trzy"s;
    m[3] = "cztery"s;
    for(auto& elem : m)
        cout << "[" << elem.first << "]" << ": " << elem.second << ", ";
    cout << endl;

    //multimap - dictionary - mapa pozwalająca na zduplikowane klucze
        //(jak przwdziwy słownik)
        //elementy uporządkowane rosnąco
    multimap<int, string> mm {{1, "jeden"}};
    mm.insert(make_pair<int, string>(2, "dwa"s));
    mm.insert(make_pair<int, string>(3, "trzy"s));
    mm.insert(make_pair<int, string>(3, "cztery"s));
    for(auto& elem : mm)
        cout << "[" << elem.first << "]" << ": " << elem.second << ", ";
    cout << endl;


    //ADAPTERS - specjalnie zdefiniowane kontenery przystosowane do
        //specjalnego użycia
        //w kontenerach adapterach można wybrać kontener sekwencyjny,
        //którego chce sie używać

    //stack - elementy działają jak kolejka LIFO, push, pop
        //elementy są wrzucane i ściągane z końca kontenera
        //stack domyślnie uπywa deque co jest dziwne może też używać vector, list
    stack<int> stk;
    stk.push(1);
    stk.push(2);
    stk.push(3);
    cout << stk.top();
    stk.pop();
    cout << stk.top();
    stk.pop();
    cout << stk.top();
    stk.pop();
    cout << endl;

    //queue - elementy działaja jak kolejka FIFO, elementy są pushowane
        //na koniec kontenera i popowane z początku kontenera,
        //queue domyslnie używa deque może też używać listy
    queue<int> que;
    que.push(1);
    que.push(2);
    que.push(3);
    cout << que.front();
    que.pop();
    cout << que.front();
    que.pop();
    cout << que.front();
    que.pop();
    cout << endl;

    //priority_queue ekementy sa sortowane poprzez operator< podczaas
        //pushowania elementu
        //usuwanie elementu z początku zwraca item najwyższego
        //priorytetu w kolejce
    queue<int> pque;
    pque.push(1);
    pque.push(2);
    pque.push(3);
    cout << pque.front();
    pque.pop();
    cout << pque.front();
    pque.pop();
    cout << pque.front();
    pque.pop();
    cout << endl;
}



void stlIterators()
{
    //Iterator - obiekt, który umie iterować (przechodzić) po klasie kontenera
        //bez konieczności posiadania wiedzy jak działa kontener
        //w przypadku wielu klas (szczególnie asocjacyjne i listy) iteratory
        //są podstawowym sposobem dostepu do klas

    //można go sobie wyobrazić jako wskaźnik do elementu w konterze z
        //zestawem funkcji

    //operator* - dereferencja iteratora - zwraca aktualnny element
    //operator++/-- przenosi się na kolejny element
    //operator==/!= sprawdzenie czy 2 iteratry wskazują na to samo
    //operator= - przypisanie do iteratora nowej pozycji

    //begin() zwraca iterator na początek
        //end() iterator na element ZA ostatnim, dzięki temu łatwo iterować pętlą
        //cbegin(), cend() zwraca constowe iteratory (na const wartości)

    //każdy kontener dostarcza iterator
        //container::iterator, container::const_iterator
    vector<int> vec {1,2,3,4,5,6};

    for(vector<int>::const_iterator vecIt = vec.begin(); vecIt != vec.end(); ++vecIt)
    {
        cout << *vecIt << ", ";
    }
    cout << endl;

    list<int> ll {10,20,30,40,50,60};
    for(list<int>::const_iterator llIt = ll.begin(); llIt != ll.end(); ++llIt)
    {
        cout << *llIt << ", ";
    }
    cout << endl;

    map<int, int> mp {{10,20},{30,40},{50,60}};
    for(map<int, int>::const_iterator mpIt = mp.begin(); mpIt != mp.end(); ++mpIt)
    {
        cout << "[" << mpIt->first << "," << mpIt->second << "] , ";
    }
    cout << endl;

    //iteratory dostarczają prosty sposób iteracji po kontenerze co z algorytmami
        //stl'a jest dobre

    //Iteratory muszą być zaimplementowane na podstawie klasy, iterator jest
        //silnie związany z kontenerem
}


#include <algorithm>
#include <functional>
void stlAlgorithms()
{
    //algorytmy działajace z kontenerami
        //np: search sort, insert, reorder, copy

    //algorytmy są zaimplementowane jako globalne funkcje i operują na iteratorach
        //tak więc jednokrotnie zaimplementowany algorytm działa na wszystkich
        //kontenerach, które dostarczają zbiór iteratorów
    //jest to super ale może też prowadzić do sytuacji, że np część algorytmów nie
        //działa z częścią kontenerów prawidłowo, lub wolno

    list<int> l1 {1,2,3,4673456,345,523,434,4};
    cout << "Max: " << *max_element(l1.begin(), l1.end()) << endl;
    cout << "Min: " << *min_element(l1.begin(), l1.end()) << endl;

    list<int>::iterator l1it = find(l1.begin(), l1.end(), 345);

    l1.insert(l1it, 100000);

    for_each(l1.begin(), l1.end(), [](int val){ cout << val << ", "; });
    cout << endl;

    //sort(l1.begin(), l1.end()); -> nie działa dla list, lista ma własny sort
    l1.sort();
    for_each(l1.begin(), l1.end(), [](int val){ cout << val << ", "; });
    cout << endl;

    vector<int> v1 {5234,51,5,54,5,43,343,4,15,65,767};
    sort(v1.begin(), v1.end());
    reverse(v1.begin(), v1.end());
    for_each(v1.begin(), v1.end(), [](int val){ cout << val << ", "; });
    cout << endl;
}