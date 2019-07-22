#include <iostream>
#include <typeinfo>
using std::cout;
using std::endl;
class A {
public:
	A() { cout << "A()" << endl; }
	virtual ~A(){ cout << "~A()" << endl; }
};
class B :public A {
public:
	B() { cout << "B()" << endl; }
	virtual ~B() { cout << "~B()" << endl; }
};
class C :public B {
public:
	C() { cout << "C()" << endl; }
	virtual ~C() { cout << "~C()" << endl; }
};
class D :public A, public B {
public:
	D() { cout << "D()" << endl; }
	virtual ~D() { cout << "~D()" << endl; }
};

int main()
{
	A *pa = new C;
	if (B *pb = dynamic_cast<B*>(pa))  //a)   T
		cout << "a)	T" << endl;
	else
		cout << "a)	F" << endl;
	B *pbb = new B;
	if (C *pc = dynamic_cast<C*>(pbb))  //b)   F
		cout << "b)	T" << endl;
	else
		cout << "b)	F" << endl;
	A *paa = new D;  // [Error] 'A' is an ambiguous base of 'D'
	if (B *pbbb = dynamic_cast<B*>(paa))  //c)   T
		cout << "c)	T" << endl;
	else
		cout << "c)	F" << endl;


	try {
		C &cp = dynamic_cast<C&>(*pa);  // OK
		cout << "cp" << endl;
		C &ccp = dynamic_cast<C&>(*paa);  // std::bad_cast
		cout << "ccp" << endl;
	}
	catch (std::bad_cast e) {
		cout << e.what() << endl;
	}

	return 0;
}
