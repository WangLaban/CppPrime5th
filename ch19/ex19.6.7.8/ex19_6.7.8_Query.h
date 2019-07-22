// ex19_6.7.8_Query.h
#include <cstddef>
#include <string>
#include <utility>
#include <algorithm>
#include <iterator>
#include "ex19_6.7.8_TextQuery.h"
class Query_base {
	friend void cast_test();
	friend class Query;
protected:
	using line_no = TextQuery::line_no;
	virtual ~Query_base() = default;
private:
	virtual QueryResult eval(const TextQuery&) const = 0;
	virtual std::string rep() const = 0;
};

class WordQuery : public Query_base {
	friend void cast_test();
	friend class Query;
	WordQuery(const std::string &s) : query_word(s) {}
	QueryResult eval(const TextQuery &t) const
	{
		return t.query(query_word);
	}
	std::string rep() const { return query_word; }
	std::string query_word;
};

class Query {
	friend Query operator~(const Query&);
	friend Query operator|(const Query&, const Query&);
	friend Query operator&(const Query&, const Query&);
public:
	Query(const std::string &s) : q(new WordQuery(s)), cnt(new std::size_t(1)) {}; 
	QueryResult eval(const TextQuery &t) const
	{
		return q->eval(t);
	}
	std::string rep() const { return q->rep(); }
	Query(const Query &query) : q(query.q), cnt(query.cnt) { ++*cnt; }
	Query(Query &&query) noexcept : q(query.q), cnt(query.cnt) { query.q = 0; }
	Query& operator=(const Query&);
	Query& operator=(Query&&) noexcept;
	~Query();
private:
	Query(Query_base *query) : q(query), cnt(new std::size_t(1)) {}
	Query_base *q;
	std::size_t *cnt;
};
inline
Query& Query::operator=(const Query &rhs)
{
	++*rhs.cnt;
	if (--*cnt == 0)
	{
		delete q;
		delete cnt;
	}
	q = rhs.q;
	cnt = rhs.cnt;
	return *this;
}
inline
Query& Query::operator=(Query &&rhs) noexcept
{
	if (this != &rhs) {
		cnt = rhs.cnt;
		q = rhs.q;
		rhs.q = 0;
	}
	return *this;
}
inline
Query::~Query()
{
	if (--*cnt == 0) {
		delete q;
		delete cnt;
	}
}
inline std::ostream& operator<<(std::ostream &os, const Query &query)
{
	return os << query.rep();
}

class BinaryQuery : public Query_base {
	friend void cast_test();
protected:
	BinaryQuery(const Query &l, const Query &r, std::string s) :
		lhs(l), rhs(r), opSym(s) {}
	std::string rep() const {
		return "(" + lhs.rep() + " "
			+ opSym + " "
			+ rhs.rep() + ")";
	}
	Query lhs, rhs;
	std::string opSym;
};

class OrQuery : public BinaryQuery {
	friend void cast_test();
	friend Query operator|(const Query&, const Query&);
	OrQuery(const Query &left, const Query &right) :
		BinaryQuery(left, right, "|") {}
	QueryResult eval(const TextQuery &text) const
	{
		auto left = lhs.eval(text), right = rhs.eval(text);
		auto ret_lines = std::make_shared<std::set<line_no>>(left.begin(), left.end());
		ret_lines->insert(right.begin(), right.end());
		return QueryResult(rep(), ret_lines, left.get_file());
	}
};

class AndQuery : public BinaryQuery {
	friend void cast_test();
	friend Query operator&(const Query&, const Query&);
	AndQuery(const Query &left, const Query &right) :
		BinaryQuery(left, right, "&") {}
	QueryResult eval(const TextQuery &text) const
	{
		auto left = lhs.eval(text), right = rhs.eval(text);
		auto ret_lines = std::make_shared<std::set<line_no>>();
		std::set_intersection(left.begin(), left.end(), right.begin(), right.end(),
			std::inserter(*ret_lines, ret_lines->begin()));
		return QueryResult(rep(), ret_lines, left.get_file());
	}
};

class NotQuery : public Query_base {
	friend void cast_test();
	friend Query operator~(const Query&);
	NotQuery(const Query &q) : query(q) {}
	std::string rep() const {}
	QueryResult eval(const TextQuery &text) const
	{
		auto result = query.eval(text);
		auto ret_lines = std::make_shared<std::set<line_no>>();
		auto beg = result.begin(), end = result.end();
		auto sz = result.get_file()->size();
		for (std::size_t n = 0; n != sz; ++n) {
			if (beg == end || *beg != n)
				ret_lines->insert(n);
			else
				++beg;
		}
		return QueryResult(rep(), ret_lines, result.get_file());
	}
	Query query;
};

inline Query operator|(const Query &lhs, const Query &rhs)
{
	return (new OrQuery(lhs, rhs));
}

inline Query operator&(const Query &lhs, const Query &rhs)
{
	return (new AndQuery(lhs, rhs));
}

inline Query operator~(const Query &operand)
{
	return (new NotQuery(operand));
}
