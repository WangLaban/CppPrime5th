//exercise 17.26
//Rewrite your phone program so that it writes only the second and subsequent phone numbers for people with more than one phone number.

#include <iostream>
#include <regex>
#include <string>
#include <sstream>

using namespace std;

string pattern = "(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ])?(\\d{4})";
string fmt = "$2.$5.$7";
regex r(pattern);
string s;

int main()
{
    while(getline(cin,s))
    {
        unsigned int i = 0;
        istringstream iss(regex_replace(s, r, fmt));
        string text;
        while(iss >> text)
        {
	    ++i;
            if(i != 2)
            {
                cout<<text<<" ";
	    }
	}
	if(i == 2)
	    cout<<text;
	cout<<endl;
    }

    return 0;
}
