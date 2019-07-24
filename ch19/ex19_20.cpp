#include <string>
using std::string;

#include <vector>
using std::vector;

#include <memory>
using std::shared_ptr;

#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <sstream>
#include <algorithm>
#include <iterator>

//class QueryResult;
class TextQuery {
public:
	class QueryResult;  // nested class
    using LineNo = vector<string>::size_type;
    TextQuery(std::ifstream&);
    QueryResult query(const string&) const;

private:
    shared_ptr<vector<string>> input;
    std::map<string, shared_ptr<std::set<LineNo>>> result;
};

class TextQuery::QueryResult {
public:
    friend std::ostream& print(std::ostream&, const QueryResult&);

public:
    //QueryResult(const string& s, shared_ptr<std::set<TextQuery::LineNo>> set,
    QueryResult(const string& s, shared_ptr<std::set<LineNo>> set,
                shared_ptr<vector<string>> v)
        : word(s), nos(set), input(v)
    {
    }

private:
    string word;
    //shared_ptr<std::set<TextQuery::LineNo>> nos;
    shared_ptr<std::set<LineNo>> nos;
    shared_ptr<vector<string>> input;
};

TextQuery::TextQuery(std::ifstream& ifs) : input(new vector<string>)
{
    LineNo lineNo{0};
    for (string line; std::getline(ifs, line); ++lineNo) {
        input->push_back(line);
        std::istringstream line_stream(line);
        for (string text, word; line_stream >> text; word.clear()) {
            // avoid read a word followed by punctuation(such as: word, )
            std::remove_copy_if(text.begin(), text.end(),
                                std::back_inserter(word), ispunct);
            // use reference avoid count of shared_ptr add.
            auto& nos = result[word];
            if (!nos) nos.reset(new std::set<LineNo>);
            nos->insert(lineNo);
        }
    }
}

TextQuery::QueryResult TextQuery::query(const string& str) const
{
    // use static just allocate once.
    static shared_ptr<std::set<LineNo>> nodate(new std::set<LineNo>);
    auto found = result.find(str);
    if (found == result.end())
        return QueryResult(str, nodate, input);
    else
        return QueryResult(str, found->second, input);
}

std::ostream& print(std::ostream& out, const TextQuery::QueryResult& qr)
{
    out << qr.word << " occurs " << qr.nos->size()
        << (qr.nos->size() > 1 ? " times" : " time") << std::endl;
    for (auto i : *qr.nos)
        out << "\t(line " << i + 1 << ") " << qr.input->at(i) << std::endl;
    return out;
}

void runQueries(std::ifstream& infile)
{
    TextQuery tq(infile);
    while (true) {
        std::cout << "enter word to look for, or q to quit: ";
        string s;
        if (!(std::cin >> s) || s == "q") break;
        print(std::cout, tq.query(s)) << std::endl;
    }
}

int main()
{
    std::ifstream file("letter.txt");
    runQueries(file);
}
