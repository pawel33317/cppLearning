#include <iostream>
#include <memory>
#include <vector>
using namespace std;

//  /usr/bin/g++-11 -std=c++2a -Wall -O0 -o app kompozyt.cpp && ./app

class IInstallerComponent
{
    public:
        virtual void install() = 0;
        virtual ~IInstallerComponent() { cout << "Kasuje installer" << endl; }
};
class InstallerAudioLeaf : public IInstallerComponent
{
public:
    void install() override
    {
        cout << "Installing audio..." << endl;
    }
};
class InstallerMapLeaf : public IInstallerComponent
{
public:
    void install() override
    {
        cout << "Installing maps..." << endl;
    }
};
class InstallerSpeachLeaf : public IInstallerComponent
{
public:
    void install() override
    {
        cout << "Installing speach..." << endl;
    }
};
class InstallerComposite : public IInstallerComponent
{
    vector<unique_ptr<IInstallerComponent>> installers;
public:
    void install() override
    {
        for(auto& installer : installers)
        {
            installer->install();
        }
    }
    void addInstaller(IInstallerComponent* installer)
    {
        installers.push_back(unique_ptr<IInstallerComponent>(installer));
    }
};

int main()
{
    printf("-----w_kompozyt-----\n");

    //celem jest składanie obiektów tak aby użytkownik widział wiele
    //z obiektów jako jeden

    //składa się z:
        //abstract class Component posiada pojedyńcze obiekty Leaf jak również
            //kontenery takich obiektów, nasz INTERFEJS
        //Leaf typ prosty nie posiadający potomków
        //Composite przechowuje obiekty proste Leaf, implementuje zachowanie
            //elementów kontenera

    //composite  i leaf dziedziczą po tym samym interfejsie, co pozwala na dostęp
        //do obiektów prostych w ten sam sposób jak do grupy
    //Klasa Component oraz Composite zawiera metody operujące na komponentach
        //podrzędnych, które są przechowywane w Composite

    //Umożliwia definieowanie hierarchii obiektów prostych i złożonych
    //upraszcza kod klientów, ułatwoa dodanie nowego komponentu

    InstallerComposite ic;
    ic.addInstaller(new InstallerMapLeaf{});
    ic.addInstaller(new InstallerAudioLeaf{});
    ic.addInstaller(new InstallerSpeachLeaf{});
    ic.install();
}