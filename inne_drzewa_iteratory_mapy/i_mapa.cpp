#include <iostream>
#include <memory>
#include <cassert>
using namespace std;


template<class K, class V>
class MyMap
{
public:
    class Node
    {
    public:
        K* mKey;
        V* mVal;
        Node* mNext = nullptr;
        Node(const K& key, const V& val) : mKey(new K), mVal(new V){
            *mKey = key;
            *mVal = val;
        }
        ~Node() { delete mKey; delete mVal; }
    };
    Node* mFirstNode = nullptr;
    MyMap(){}
    ~MyMap(){
        Node* current = mFirstNode;
        while(current != nullptr)
        {
            cout << "[DES]Kasuje noda: " << *current->mKey << endl;
            Node* tmp = current->mNext;
            delete current;
            current = tmp;
        }
    }

    void insert(const K key, const V val)
    {
        //jeżeli nie ma jeszcze żadnego noda
        if (!mFirstNode)
        {
            cout << "[0]Dodaje noda: " << key << endl;
            mFirstNode = new Node{key, val};
        }
        //jeżeli jest już jakiś node
        else
        {
            Node* current = mFirstNode;

            //ustaw current na ostatni mniejszy/równy element
            while(current->mNext != nullptr && *(current->mNext->mKey) <= key)
            {
                current = current->mNext;
            }
            //jeżeli element równy nie dodawaj bo duplikat
            if (*(current->mKey) == key)
            {
                cout << "Node: " << key << " istnieje ERROR" << endl;
                //throw ("Node exists"s);
            }
            //jeżeli już pierwszy jest mniejszy
            else if(*(current->mKey) > key)
            {
                cout << "[1]Dodaje noda: " << key << endl;
                mFirstNode = new Node{key, val};
                mFirstNode->mNext = current;
            }
            //jeżeli różny dodaj
            else
            {
                cout << "[2]Dodaje noda: " << key << endl;
                Node* newNode = new Node{key, val};
                newNode->mNext = current->mNext;
                current->mNext = newNode;
            }
        }
    }

    void remove(const K& key)
    {
        Node* current = mFirstNode;
        Node* previous = nullptr;
        while(current && *current->mKey != key)
        {
            previous = current;
            current = current->mNext;
        }
        if(!current)
        {
            cout << "Brak noda, nie mozna usunac" << endl;
        }
        else
        {
            if(previous)
            {
                cout << "[0] Kasuje noda" << *current->mKey << endl;
                previous->mNext = current->mNext;
            }
            else
            {
                cout << "[1] Kasuje noda" << *current->mKey << endl;
                mFirstNode = current->mNext;
            }
            delete current;
        }
    }

    void listNodes()
    {
        Node* current = mFirstNode;
        cout << "------------------Node list------------------" << endl;
        while(current != nullptr)
        {
            cout << "Node val: " << *current->mKey << ": " << *current->mVal << endl;
            current = current->mNext;
        }
        cout << "------------------Node list END------------------" << endl;
    }

    V& operator[](const K& key)
    {
        Node* current = mFirstNode;
        while(current != nullptr)
        {
            if (*current->mKey == key)
            {
                cout << "Znaleziono element: " << key << endl;
                return *current->mVal;
            }
            current = current->mNext;
        }
        cout << "Nie znaleziono elementu: " << key << endl;

        throw("Nie znaleziono"s);
    }
};
void i_mapa()
{
    cout << "----------------i_mapa-----------" << endl;

    //algorytm dodawania itp jest słaby
    //jest zaimplementowany na liście jednokierunkowej
    //a powinien być na binarnym drzewie poszukiwań
    //ale nie to było celem więc zostaje
    MyMap<int, double> map;
    map.insert(11, 11.32);
    map.insert(4, 144.232);
    map.insert(33, 144.232);
    map.insert(111, 21.232);
    map.listNodes();
    map.remove(123);
    map.remove(4);
    map.remove(33);
    map[11] = 4321.997;
    try{map[4444];}
    catch(const std::string&){}
    map.listNodes();
}
