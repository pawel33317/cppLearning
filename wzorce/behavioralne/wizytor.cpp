#include <iostream>
#include <vector>
using namespace std;
//  /usr/bin/g++-11 -std=c++2a -Wall -O0 -o app wizytor.cpp && ./app

//oddziela ustrultoryzowane dane od funkcjonalności która ma być wykonana na nich
//loose coupling, umożliwia dodanie dodakowych operacji bez modyfikacji klass z danymi


struct EmployeeVisitor;


struct Employee{ //ElementBase - wymusza na elementach odsługę visitora
    virtual void Accept(EmployeeVisitor* visitor) = 0;
};
struct Employee_Manager : public Employee{
    //ConcreteElement - trzyma rzeczywiste dane i przekazuje je lub siebie do visitora - callback
    int mSalary;
    Employee_Manager(int salary) : mSalary(salary){}
    void Accept(EmployeeVisitor* visitor) override;//implementacja niżej bo forward declaration
};
struct Employee_Director : public Employee{
    //ConcreteElement - trzyma rzeczywiste dane i przekazuje je lub siebie do visitora - callback
    int mSalary;
    Employee_Director(int salary) : mSalary(salary){}
    void Accept(EmployeeVisitor* visitor) override;
};


struct EmployeeVisitor{ //VisitorBase - wymusza obsługę callbacka dla każdego ConcreteElement
    virtual void Visit(Employee_Manager*) = 0;
    virtual void Visit(Employee_Director*) = 0;
};
struct BonusVisitor : public EmployeeVisitor{ //ConcreteVisitor zawiera operacje do stosowania na ConcreteElement
    void Visit(Employee_Manager* e) override {
        cout << "Increasing Manager salary from: " << e->mSalary << " to: ";
        e->mSalary *= 1.1;
        cout << e->mSalary << endl;
    };
    void Visit(Employee_Director* e) override {
        cout << "Increasing Director salary from: " << e->mSalary << " to: ";
        e->mSalary *= 1.2;
        cout << e->mSalary << endl;
    };
};
struct ReductionVisitor : public EmployeeVisitor{ //ConcreteVisitor zawiera operacje do stosowania na ConcreteElement
    void Visit(Employee_Manager* e) override {
        cout << "Decreasing Manager salary from: " << e->mSalary << " to: ";
        e->mSalary *= 1.1;
        cout << e->mSalary << endl;
    };
    void Visit(Employee_Director* e) override {
        cout << "Decreasing Director salary from: " << e->mSalary << " to: ";
        e->mSalary *= 1.1;
        cout << e->mSalary << endl;
    };
};


void Employee_Manager::Accept(EmployeeVisitor* visitor) { visitor->Visit(this); }
void Employee_Director::Accept(EmployeeVisitor* visitor) { visitor->Visit(this); }


struct EmployeesStructure{ //ObjectStructure trzyma elementy z danymi - taki helper
    //ta klasa to mógłby być jakiś pracownik który ma pod sobą innych...
    // i w accepcie przekazuje siebie a później wywołuje accept na pracownikach
    std::vector<Employee*> mEmployees;
    void addEmployee(Employee* employee) { mEmployees.push_back(employee); }
    void Accept(EmployeeVisitor* visitor) {
        for(auto& employee : mEmployees)
            employee->Accept(visitor);
    }
};

int main()
{
    Employee_Manager manager1{1000}; 
    Employee_Manager manager2{2000};
    Employee_Director director1{5000};
    Employee_Director director2{6000};

    EmployeesStructure struktura;
    struktura.addEmployee(&manager1);
    struktura.addEmployee(&manager2);
    struktura.addEmployee(&director1);
    struktura.addEmployee(&director2);

    BonusVisitor bonusVisitor{};
    ReductionVisitor reductionVisitor{};

    struktura.Accept(&bonusVisitor);
    struktura.Accept(&reductionVisitor);
    struktura.Accept(&reductionVisitor);
}


