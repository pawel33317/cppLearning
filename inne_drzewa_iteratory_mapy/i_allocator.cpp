#include <iostream>
#include <memory>
#include <cassert>
#include <vector>
using namespace std;

template<class T>
class MyAllocator
{
public:
    using size_type       = size_t;
    using difference_type = ptrdiff_t;
    using pointer         = T*;
    using const_pointer   = const T*;
    using reference       = T&;
    using const_reference = const T&;
    using value_type      = T;

    template<class U>
    struct rebind //!!! ważne
                  //umożliwia kontenerowi utworzenie alokatora dla dowolnego typu
                  //np gdy kontener chce zaalokować inny typ niż T np (lista nodów)
    {
        using other = MyAllocator<U>;
    };

    //dodać obsługę operatorów == oraz != pod kątem równości

    //Constructors
    MyAllocator() throw() {};
    MyAllocator(const MyAllocator&) throw() {};
    template<class U>
    MyAllocator(const MyAllocator<U>&) {}

    //Destructor
    ~MyAllocator() {}

    //Assigment operator
    template<class U>
    MyAllocator& operator=(const MyAllocator<U>&)
    {
        return *this;
    }

    //Public member functions
    pointer address(reference r) const //zwraca adres r, konwertuje ref na ptr
    {
        return &r;
    }
    const_pointer address(const_reference r) const //zwraca adres r
                                                 //i konwertuje referencję na ptr
    {
        return &r;
    }
    pointer allocate(size_type n, const void* hint = 0) //alokuje pamięć na n T
                                                       //używa hint to optymalizacji
                                                       //o ile możliwe, hint powinno być MyAllocator<U>::const_pointer hint = 0
    {
        T* t = new T[n];
        cout << "MyAlocator: alokacja " << n << " obiektów, addr: " << t << endl;
        return t;
    }
    void deallocate(pointer p, size_type s) //dealokuje przestrzeń otrzymaną przez allocate
    {
        if(p)
        {
            delete[] p;
            cout << "MyAlocator: dealokacja n=" << s <<", addr: " << p << endl;
        }
        else
        {
            cout << "MyAlocator: brak dealokacji" << endl;
        }
    }
    size_type max_size() //zwraca max możliwe do zaalokowania przez allocate
    {
        return size_type(-1);
    }
    void construct(pointer p, const_reference val) //tworzy obiekt T pod lokalizacją
                                                  //p używając wartości val dla
                                                  //konstruktora
    {
        new(p) T{val};
    }
    void destroy(pointer p) //wywołuje destruktor obiektu pod adresem p
    {
        p->~T();
    }
};


void i_allocator()
{
    cout << "-----i_allocator-----\n";
    //można przekazać do każdego konternera stl, domyślnie
    //używają std::allocator<T> z stl

    vector<int, MyAllocator<int> > v {1,2,3,4,5};
    cout << "add elem to vec\n";
    v.push_back(5);
    cout << "add elem to vec\n";
    v.push_back(7);
}

