//!
//! Exercise 17.18
//! Revise your program to ignore words that contain "ei" but are not 
//! misspellings, such as "albeit" and "neighbor."

#include <iostream>
#include <string>
#include <regex>
#include <vector>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::regex;
using std::sregex_iterator;
using std::vector;

int main()
{
    string s;
	cout << "Please input a sequence of words:" << endl;
	getline(cin, s);
	cout << endl;
	cout << "Word(s) that violiate the \"ei\" grammar rule:" << endl;

    string pattern("[^c]ei");    
    pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";    
    regex reg(pattern, regex::icase);    
 
    vector<string> vec{ "albeit","beige","feint","heir","reign","their",    
        "counterfeit","foreign","inveigh","rein","veil","deign",    
        "forfeit","inveigle","seize","veineiderdown","freight",    
        "leisure","skein","weigheight","heifer","neigh","sleigh",    
        "weighteither","height","neighbor", "neighbour", "sleight","weirfeign",    
        "heinous neither surfeit weird" };    
    for (sregex_iterator it(s.begin(), s.end(), reg), end_it; it != end_it; ++it)    
    {    
        if (find(vec.begin(), vec.end(), it->str()) != vec.end())  
            continue;    
        cout << it->str() << endl;    
    }    
 
    return 0;    
}
