#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <algorithm>
using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::function;
using std::mem_fn;

int main()
{
	vector<string> svec;
	svec.push_back("");
	svec.push_back("c++");
	svec.push_back("primer");
	svec.push_back("hello");
	svec.push_back("");
	svec.push_back("");
	svec.push_back("world");

	function<bool (const string &)> func = &string::empty;
	int cnt = count_if(svec.begin(), svec.end(), func);
	cout << cnt << endl;

	cnt = count_if(svec.begin(), svec.end(), mem_fn(&string::empty));
	cout << cnt << endl;

	cnt = count_if(svec.begin(), svec.end(), bind(&string::empty,std::placeholders::_1));
	cout << cnt << endl;;
	
	return 0;
}
