// ex19_6.7.8_Test.cpp
#include <iostream>
#include <typeinfo>
#include "ex19_6.7.8_Query.h"
using std::cout;
using std::endl;
using std::bad_cast;
void cast_test()
{
	// 19.6
	Query_base *pb1 = new AndQuery(Query("value1"), Query("value2"));
	Query_base *pb2 = new OrQuery(Query("value1"), Query("value2"));
	if (AndQuery *pa1 = dynamic_cast<AndQuery*>(pb1)) {
		cout << "Success" << endl;
	}
	else {
		cout << "Fail" << endl;
	}
	if (AndQuery *pa2 = dynamic_cast<AndQuery*>(pb2)) {
		cout << "Success" << endl;
	}
	else {
		cout << "Fail" << endl;
	}
	// 19.7
	try {
		AndQuery &ra1 = dynamic_cast<AndQuery&>(*pb1);
		cout << "Success" << endl;
	}
	catch (bad_cast e) {
		cout << e.what() << endl;
	}
	try {
		AndQuery &ra2 = dynamic_cast<AndQuery&>(*pb2);
		cout << "Success" << endl;
	}
	catch (bad_cast e) {
		cout << e.what() << endl;
	}
	// 19.8
	if (typeid(*pb1) == typeid(*pb2))
		cout << "pb1 and pb2 point to the same object" << endl;
	else
		cout << "pb1 and pb2 point to the different object" << endl;
	if (typeid(*pb1) == typeid(AndQuery))
		cout << "*pb1's run-time type is AndQuery" << endl;
	else
		cout << "*pb1's run-time type is not AndQuery" << endl;
	if (typeid(*pb2) == typeid(AndQuery))
		cout << "*pb2's run-time type is AndQuery" << endl;
	else
		cout << "*pb2's run-time type is not AndQuery" << endl;
}
int main()
{
	cast_test();

	return 0;
}
