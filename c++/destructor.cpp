// Tutorial: call a destructor explicitly

#include <iostream>
using namespace std;

struct Class {
	int a_;

	Class(int a = 0);
	~Class();
};

Class::Class(int a) : a_(a) {
	cout << "Call constructor, addr = " << this 
	<< "value a = " << a << endl;
}

Class::~Class() {
	cout << "Call destructor, addr = " << this << endl;
}

int main ()
{
	Class s = {5}, s2(6), s3, s4[3];
//	Class::Class();

	s.~Class();
//	Class::~Class(&s);
}


