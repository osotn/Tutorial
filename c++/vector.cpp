// vector: overloading of operator+

#include <iostream>
using namespace std;

class Vector {
private:
	double re_, im_;
	static int number;
public:
	explicit Vector(double re = 0, double im = 0) : re_(re), im_(im) {
		cout << number  << ". Constructor re = " 
			<< re << " im = " << im 
			<< ". this = " << this << endl;
		number++; 
	}
	Vector(const Vector &v) {
		cout << number  << ". Copy_Constructor re = " 
			<< v.re_ << " im = " << v.im_ 
			<< ". this = " << this << endl;
		re_ = v.re_;
		im_ = v.im_;
	}
	~Vector() {
		cout << number  << ". Destructor re = " 
			<< re_ << " im = " << im_ 
			<< ". this = " << this << endl;
	}
	Vector & operator=(const Vector &v) {
		if (&v != this) {
			re_ = v.re_;
			im_ = v.im_;
		}
		cout << number  << ". AssignOperator re = " 
			<< v.re_ << " im = " << v.im_ 
			<< ". this = " << this << endl;
		return *this;
	}

	void print () const {
		cout << re_ << " + j * " << im_ << endl;
	}
	Vector operator+(const Vector &v) {
		Vector loc;

		cout << number  << ". Operator_mem+ re = " 
			<< re_ << " + " << v.re_ << " im = " 
			<< im_ << " + " << v.im_ 
			<< ". this = " << this << endl;

		loc.re_ = re_ + v.re_;
		loc.im_ = im_ + v.im_;
		return loc;
	}
	Vector operator +(double re) {
		Vector loc(re);
		
		cout << number  << ". Operator_mem_double+ re = " 
			<< re_ << " + " << re 
			<< " im = " << im_ 
			<< ". this = " << this << endl;

		loc = loc + *this;//loc.re_ = re_ + re;
		//loc.im_ = im_;
		return loc;
	}
	friend Vector operator+(double re, const Vector &v) {
		Vector loc(re);

		cout << number  << ". Operator_doubl_Vect+ re = " 
			<< re << " + " << v.re_ << " im = " << v.im_ 
			<< ". &Vect = " << &v << endl;

		loc = loc + v;//loc.re_ = re + v.re_;
		//loc.im_ = v.im_;
		return loc;
	}
};

int Vector::number = 0;

int main()
{
	Vector a(1, 2), b(3,4);
	// 0. Constructor re = 1 im = 2. this = a
	// 1. Constructor re = 3 im = 4. this = b

	a.print(); // 1 + j * 2
	b.print(); // 3 + j * 4

	Vector c;  // 2. Constructor re = 0 im = 0. this = c

	c = a + b; 
	// 
	// 1. a.operator+(b)
	//	3. Constructor re = 0 im = 0. this = loc
        //      4. Operator_mem+ re = 1 + 3 im = 2 + 4. this = 0x7ffc68cf7530 (a)
	// 3. c.operator=
	//      4. AssignOperator re = 4 im = 6. this = c
	//      4. Destructor re = 4 im = 6. this = loc
	


	c.print();

	c = c + 5.0;
	// 1. c.operator+(5.0)
	//      4. Constructor re = 0 im = 0. this = loc2
	//	5. Operator_mem_double+ re = 4 + 5 im = 6. this = c
	// 2.  c.operator=
	//	5. AssignOperator re = 9 im = 6. this = c 
	//	5. Destructor re = 9 im = 6. this = loc2

	c.print();

	Vector d;
	// 5. Constructor re = 0 im = 0. this = d

	d = c;
	// d.operator=(c)
	// 	6. AssignOperator re = 9 im = 6. this = d
	d = 5.0 + c;
	// loc3 = operator+(5.0, c)
	// 	6. Constructor re = 0 im = 0. this = loc3
	//	7. Operator_doubl_Vect+ re = 5 + 9 im = 6. &Vec = c
	// d.opertor=(loc3)
	//	7. AssignOperator re = 14 im = 6. this = d
	//	7. Destructor re = 14 im = 6. this = loc3
	d.print();

	return 0;
}
// 7. Destructor re = 14 im = 6. this = d
// 7. Destructor re = 9 im = 6. this = c
// 7. Destructor re = 3 im = 4. this = b
// 7. Destructor re = 1 im = 2. this = a


