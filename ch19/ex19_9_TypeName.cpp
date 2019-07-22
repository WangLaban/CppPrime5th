#include <iostream>
#include <string>
#include <typeinfo>
class Sales_data {};
class Base {
public:
	virtual ~Base() {}
};
class Derived:public Base {};
std::ostream &operator<<(std::ostream &os, const std::type_info &t) {
	if (t == typeid(int))
		os << "int";
	else if (t == typeid(int[10]))
		os << "int[10]";
	else if (t == typeid(std::string))
		os << "std::string";
	else if (t == typeid(Base))
		os << "class Base";
	else if (t == typeid(Base*))
		os << "class Base *";
	else if (t == typeid(Derived))
		os << "class Derived";
	else if (t == typeid(Sales_data))
		os << "class Sales_data";
	return os;
}
int main()
{
	int arr[10];
	Derived d;
	Base *p = &d;
	std::cout << typeid(42).name() << "\n" << typeid(arr).name() << "\n"
		<< typeid(Sales_data).name() << "\n" << typeid(std::string).name() << "\n"
		<< typeid(p).name() << "\n" << typeid(*p).name() << std::endl;
	std::cout << typeid(42) << "\n" << typeid(arr) << "\n"
		<< typeid(Sales_data) << "\n" << typeid(std::string) << "\n"
		<< typeid(p) << "\n" << typeid(*p) << std::endl;
 
	return 0;
}
