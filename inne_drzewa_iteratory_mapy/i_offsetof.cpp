#include <iostream>
#include <memory>
#include <cassert>
using namespace std;


struct S1
{
    int aMember;
    char bMember;
    char b2Member;
    int cMember;
};
#define ADDRESOF(ClassName, FieldName)\
    (unsigned long long)(&(((ClassName*)0)->FieldName))
void i_offsetof()
{
    cout << "----------------i_addressof_member_offset-----------" << endl;
    //jak pobrać offset pola w klasie
    //jest takie macro, które na to pozwala o nazwie addressof
    long long offsetCinS1 = reinterpret_cast<long long>(
        &(static_cast<S1*>(0)->cMember)
    );
    cout << "cMember klasy S1 ma offset: " << offsetCinS1 << endl;
    cout << "b2Member klasy S1 ma offset: " << ADDRESOF(S1, b2Member) << endl;
    //cout << &(((C*)0)->b);

}
