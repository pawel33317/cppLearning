#include <memory>
#include <iostream>

struct B;
struct A {
  std::shared_ptr<B> b;  
  ~A() { std::cout << "~A()\n"; }
};

struct B {
  std::shared_ptr<A> a;
  ~B() { std::cout << "~B()\n"; }  
};

// struct B {
//   std::weak_ptr<A> a;
//   ~B() { std::cout << "~B()\n"; }  
// };

void useAnB() {
  auto a = std::make_shared<A>();
  auto b = std::make_shared<B>();
  a->b = b;
  b->a = a;
}

int main() {
   useAnB();
   std::cout << "Finished using A and B\n";
}