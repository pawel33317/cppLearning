#include <iostream>
#include <vector>
using namespace std;
//  /usr/bin/g++-11 -std=c++2a -Wall -O0 -o app iterator.cpp && ./app

//umożliwia sposób sekwencyjnego dostępu do elementów w strukturze, umożliwia jej traversing
//bez potrzeby zrozumienia wewnętrznej strukrtury

//TYPOWY ITERATOR DLA C++ jest w pliku i_iterator.cpp !!!!!!!
//TUTAJ BARDZO UPROSZCZONA WERSJA BEZ KLAS ABSTRAKCYJNUCH BO TO CPP I TRZEBA INACZEJ
// struct AggregateBase //AggregateBase baza - zawiera metody do generacji iteratora
// struct IteratorBase{ //IteratorBase baza dla iteratorów umożliwia przelecenie po kolekcji

template<class T> struct ConcreteAggregate;
template<class T>
struct ConcreteIterator {//AggregateBase baza - zawiera metody do generacji iteratora
    ConcreteAggregate<T>& mCollection;
    int pos;

    ConcreteIterator(ConcreteAggregate<T>& collection) : mCollection(collection) {}
    virtual T& First(){
         pos = 0;
         return CurrentItem();
    }
    virtual T& Next(){
        auto& prev = CurrentItem();
        pos++;
        return prev;
    }
    virtual T& CurrentItem(){
        if (IsDone())
            throw(":(");
        else
            return mCollection[pos];
    }
    virtual bool IsDone(){
        return pos >= mCollection.Count();
    }
};

template<class T>
struct ConcreteAggregate {//ConcreteAggregate 
                //rzeczywista funkcjonalnośc kolekcji
    std::vector<T> mItems;
    int Count(){ return mItems.size();}
    void Add(const T& newItem) { mItems.push_back(newItem); }
    T& operator[](int index) { return mItems[index]; }
    virtual ConcreteIterator<T> getIterator(){
        return ConcreteIterator<T>(*this);
    }
};

//Client obiekt używający iteratora
int main()
{
    ConcreteAggregate<std::string> myCollection;
    myCollection.Add("Pawel");
    myCollection.Add("Karolina");
    myCollection.Add("Marcin");
    myCollection.Add("Anna");

    auto collectionIterator = myCollection.getIterator();
    cout << "collectionIterator.First() = " << collectionIterator.First() << endl;
    cout << "collectionIterator.Next() = " << collectionIterator.Next() << endl;
    cout << "collectionIterator.CurrentItem() = " << collectionIterator.CurrentItem() << endl;
    cout << "collectionIterator.First() = " << collectionIterator.First() << endl;
    cout << "--------------------------" << endl;

    while(!collectionIterator.IsDone()){
        cout << collectionIterator.Next() << endl;
    }
}


