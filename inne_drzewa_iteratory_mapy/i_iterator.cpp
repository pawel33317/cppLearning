#include <iostream>
#include <memory>
#include <cassert>
using namespace std;

template<class T, unsigned int S>
class StackArray final
{
    using size_type = unsigned int;
    T mData[S];
    size_type mSize = S;
public:
    size_type getSize(){ return mSize; }
    T& operator[](size_type index) { assert(index < mSize); return mData[index]; }
    const T& operator[](size_type index) const { return operator[](index); }
    StackArray(std::initializer_list<T> il)
    {
        assert(il.size() <= mSize);
        int i = 0;
        for(auto& elem : il)
            mData[i++] = elem;
        //for(auto it = il.begin(); it != il.end(); ++it, ++i) mData[i] = *it;
    }

    class iterator : public std::iterator<std::forward_iterator_tag, T>
    {
        T* mPtr;
    public:
        explicit iterator(T* ptr) : mPtr{ptr}{}
        iterator& operator++() { ++mPtr; return *this; }//pre
        iterator operator++(int) { auto tmp = *this; ++mPtr; return tmp; }//post
        T& operator*() { return *mPtr; }
        T* operator->() { return mPtr; }
        bool operator==(const iterator& other) const { return mPtr == other.mPtr; }
        bool operator!=(const iterator& other) const { return mPtr != other.mPtr; }
    };
    class const_iterator{};
    //const_iterator begin();
    //const_iterator end();

    iterator begin(){ return iterator(mData); }
    //iterator begin(){ StackArray::iterator it{mData}; return it; }
    iterator end(){ return iterator(mData + mSize); }
};

void i_iterator()
{
    cout << "-----i_iterator-----\n";

    StackArray<int, 10> sa {10,11,12,13,14,15,16,17,18,19};
    for(StackArray<int, 10>::iterator it = sa.begin(); it != sa.end(); ++it)
    {
        cout << *it << ",";
    }
    cout << endl;
    for(auto& elem : sa)
        cout << elem++ << ",";
    cout << endl;
    for(const auto& elem : sa)
        cout << elem << ",";
    cout << endl;
}
