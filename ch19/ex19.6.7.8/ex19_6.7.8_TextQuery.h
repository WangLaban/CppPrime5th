// ex19_6.7.8_TextQuery.h
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>
std::string make_plural(size_t, const std::string&, const std::string&);
class QueryResult;
class TextQuery {
public:
	using line_no = std::vector<std::string>::size_type;
	TextQuery(std::ifstream &is)
	{
		std::string text;
		while (getline(is, text)) 
		{
			file->push_back(text); 
			int n = file->size() - 1;
			std::istringstream line(text); 
			std::string word;
			while (line >> word)
			{
				auto &lines = wm[word];
				if (!lines)
					lines.reset(new std::set<line_no>);
				lines->insert(n);
			}
		}
	}
	QueryResult query(const std::string &sought) const;
private:
	std::shared_ptr<std::vector<std::string>> file;
	std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};
class QueryResult {
	friend std::ostream& print(std::ostream &os, const QueryResult &qr, TextQuery::line_no min, TextQuery::line_no max)
	{
		os << qr.sought << " occurs " << qr.lines->size() << " "
			<< make_plural(qr.lines->size(), "time", "s") << std::endl;
		for (auto num : *qr.lines) {
			if ((num + 1) >= min && (num + 1) <= max)
				os << "\t(line " << num + 1 << ") "
				<< *(qr.file->begin() + num) << std::endl;
			else if ((num + 1 > max))
				break;
		}
		return os;
	}
public:
	QueryResult(std::string s, std::shared_ptr<std::set<TextQuery::line_no>> p, std::shared_ptr<std::vector<std::string>> f) :sought(s), lines(p), file(f) {}
	std::set<TextQuery::line_no>::iterator begin() const { return lines->begin(); }
	std::set<TextQuery::line_no>::iterator end() const { return lines->end(); }
	std::shared_ptr<std::vector<std::string>> get_file() const { return file; }
private:
	std::string sought;
	std::shared_ptr<std::set<TextQuery::line_no>> lines;
	std::shared_ptr<std::vector<std::string>> file;
};

QueryResult TextQuery::query(const std::string &sought) const
{
	static std::shared_ptr<std::set<line_no>> nodata(new std::set<line_no>);
	auto loc = wm.find(sought);
	if (loc == wm.end())
		return QueryResult(sought, nodata, file);
	else
		return QueryResult(sought, loc->second, file);
}

std::string make_plural(size_t ctr, const std::string &word, const std::string &ending)
{
	return (ctr > 1) ? word + ending : word;
}
