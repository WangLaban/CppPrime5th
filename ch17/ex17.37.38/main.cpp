#include <iostream>
#include <fstream>
using std::cout;
using std::cin;
using std::endl;
using std::ifstream;

int main()
{
	char sink[128];
	ifstream inFile("letter.txt");
	if(!inFile)
	{
		cout<<"Input file cannot open"<<endl;
		return -1;
	}
	while(inFile)
	{
		//inFile.getline(sink, 50);  // Exercise 17.37, stop output when the line is more than 50 character
		inFile.getline(sink, 50, ' ');  // Exercise 17.38, when read the delim character, it will insert a newline
		cout<<sink<<endl;
	}

	return 0;
}
