#include <iostream>
#include <typeinfo>

class C {
	int c;
};

class A : public C {
	int a;
};

class V {
	int v;
	virtual void f(){}
};


int main()
{
  C c;
  A a;
  V v;

  A *p = static_cast<A*> (&c);


  std::cout << "pointer = " << p << "  " << typeid(*p).name() <<  std::endl;
}
