#include <iostream>
#include <string>
#include "Token.h"
using std::string;
using std::cout;
using std::endl;
int main()
{
	string s = "string";
	Sales_data item("c++ primer 5", 12, 128.0);
	int i = 12;
	char c = 'c';
	double d = 1.28;
	Token t;
	t = i;
	cout << t << endl;
	t = c;
	cout << t << endl;
	t = d;
	cout << t << endl;
	t = s;
	cout << t << endl;
	t = item;
	cout << t << endl;
	Token t2 = t;
	cout << t2 << endl;
	t2 = s;
	cout << t2 << endl;
	t2 = t;
	cout << t2 << endl;
	t2 = c;
	cout << t2 << endl;
	t = s;
	t2 = std::move(t);
	cout << t2 << endl;
	Token t3 = std::move(t2);
	cout << t3 << endl;
	t3 = t3;
	cout << t3 << endl;
	t3 = item;
	cout << t3 << endl;
	t2 = std::move(t3);
	cout << t2 << endl;

	return 0;
}
