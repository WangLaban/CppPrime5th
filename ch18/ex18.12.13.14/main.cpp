/***************************************************************************
 *  @file       main.cpp
 *  @author     Queequeg
 *  @date       20  Nov 2014
 *  @remark     This code is for the exercises from C++ Primer 5th Edition
 *  @note
 ***************************************************************************/
 //!
//! Exercise 18.12
//! Organize the programs you have written to answer the questions in each
//! chapter into their own namespaces. That is, namespace chapter15 would
//! contain code for the Query programs and chapter10 would contain the
//! TextQuery code. Using this structure, compile the Query code examples.

//! Exercise 18.13
//! When might you see use an unnamed namespace?
//! http://stackoverflow.com/questions/154469/unnamed-anonymous-namespaces-vs-static-functions
//! http://stackoverflow.com/questions/5312213/uses-of-unnamed-namespace-in-c

//! Exercise 18.14
//! Suppose we have the following declaration of the operator* that is a
//! a member of the nested namespace mathLib::MatrixLib.
//! How would you declare this operator in global scope?
//! mathLib::MatrixLib::matrix mathLib::MatrixLib::operator*
//! (const mathLib::MatrixLib::matrix&, const mathLib::MatrixLib::matrix&);


#include <initializer_list>
#include <iostream>
#include <fstream>    //ifstream
#include <string>
#include <vector>
#include <sstream>    //istringstream
#include <map>
#include <set>
#include <memory> //shared_ptr

namespace chapter10
{
    class StrBlob
    {
        std::shared_ptr<std::vector<std::string>> data;
        void check(std::vector<std::string>::size_type i, const std::string &msg)const;
    public:
        using size_type = std::vector<std::string>::size_type;
        StrBlob();
        StrBlob(std::initializer_list<std::string> il);
        size_type size()const;
        bool empty()const;
        void push_back(const std::string &t);
        void pop_back();
        std::string front()const;
        std::string back()const;
        std::string &front();
        std::string &back();
        const std::shared_ptr<std::vector<std::string>> &shared_ptr()const
        {
            return data;
        }
    };

    class QueryResult;
    class TextQuery
    {
        std::shared_ptr<StrBlob> file;
        std::map<std::string, std::shared_ptr<std::set<StrBlob::size_type>>> wm;
    public:
        using line_no = std::vector<std::string>::size_type;
        TextQuery(std::ifstream &is);
        QueryResult query(const std::string &s)const;
    };
    class QueryResult
    {
        friend std::ostream &print(std::ostream &os, const QueryResult &qr);
        std::string sought;
        std::shared_ptr<std::set<StrBlob::size_type>> lines;
        std::shared_ptr<StrBlob> file;
    public:
        std::set<StrBlob::size_type>::iterator begin()const {
            return lines->begin();
        }
        std::set<StrBlob::size_type>::iterator end()const {
            return lines->end();
        }
        std::shared_ptr<StrBlob> get_file()const {
            return file;
        }
        QueryResult(std::string s, const std::shared_ptr<std::set<StrBlob::size_type>> &p, std::shared_ptr<StrBlob> f) :sought(s), lines(p), file(f) {}
    };
}

#include <algorithm>//set_intersection
#include <iterator>     //inserter

namespace chapter15
{
    using namespace chapter10;
    class Query_base
    {
        friend class Query;
        virtual QueryResult eval(const TextQuery &tq)const = 0;
        virtual std::string rep()const = 0;
    protected:
        using line_no = TextQuery::line_no;
        virtual ~Query_base() = default;
    };
    class Query
    {
        friend Query operator~(const Query &qy);
        friend Query operator|(const Query &lhs, const Query &rhs);
        friend Query operator&(const Query &lhs, const Query &rhs);
        std::shared_ptr<Query_base> q;
        Query(std::shared_ptr<Query_base> qptr) :q(qptr) { std::cout << "Query(std::shared_ptr<Query_base>)\n"; }
    public:
        Query(const std::string &s);
        QueryResult eval(const TextQuery &t)const {
            return q->eval(t);
        }
        std::string rep()const {
            std::cout << "Query rep()\n";
            return q->rep();
        }
    };
}

namespace chapter10
{
    void StrBlob::check(std::vector<std::string>::size_type i, const std::string &msg)const
    {
        if (i >= data->size())
            throw std::out_of_range(msg);
    }
    StrBlob::StrBlob() :data(std::make_shared<std::vector<std::string>>())
    {}
    StrBlob::StrBlob(std::initializer_list<std::string> il) : data(std::make_shared<std::vector<std::string>>(il))
    {}
    StrBlob::size_type StrBlob::size()const
    {
        return data->size();
    }
    bool StrBlob::empty()const
    {
        return data->empty();
    }
    void StrBlob::push_back(const std::string &t)
    {
        data->push_back(t);
    }
    void StrBlob::pop_back()
    {
        check(0, "pop_push on empty StrBlob");
        data->pop_back();
    }
    std::string &StrBlob::front()
    {
        check(0, "front on empty StrBlob");
        return data->front();
    }
    std::string &StrBlob::back()
    {
        check(0, "back on empty StrBlob");
        return data->back();
    }
    std::string StrBlob::front()const
    {
        return data->front();
    }
    std::string StrBlob::back()const
    {
        return data->back();
    }

    TextQuery::TextQuery(std::ifstream &is) :file(new StrBlob())
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
                    lines.reset(new std::set<StrBlob::size_type>);
                lines->insert(n);
            }
        }
    }

    QueryResult TextQuery::query(const std::string &s)const
    {
        static std::shared_ptr<std::set<StrBlob::size_type>> nodata(new std::set<StrBlob::size_type>);
        auto loc = wm.find(s);
        if (loc == wm.end())
            return QueryResult(s, nodata, file);
        else
            return QueryResult(s, loc->second, file);
    }

    std::ostream &print(std::ostream &os, const QueryResult &qr)
    {
        os << qr.sought << " occurs " << qr.lines->size() << " " << (qr.lines->size() > 1 ? "times" : "time") << std::endl;
        for (auto x : *qr.lines)
            os << "\t(line " << x + 1 << ") " << qr.file->shared_ptr()->at(x) << std::endl;
        return os;
    }

}

namespace chapter15
{
    std::ostream &operator<<(std::ostream &os, const Query query)
    {
        return os << query.rep();
    }
    class WordQuery :public Query_base
    {
        friend class Query;
        std::string query_word;
        WordQuery(const std::string s) :query_word(s) { std::cout << "WordQuery(const std::string s)\n"; }
        QueryResult eval(const TextQuery &t)const {
            return t.query(query_word);
        }
        std::string rep()const {
            std::cout << "WordQuery rep()\n";
            return query_word;
        }
    };
    Query::Query(const std::string &s) :q(new WordQuery(s)) { std::cout << "Query(const std::string &s)\n"; }
    class NotQuery :public Query_base
    {
        friend Query operator~(const Query &q);
        Query query;
        NotQuery(const Query &qy) :query(qy) { std::cout << "NotQuery(const Query &qy)\n"; }
        std::string rep()const {
            std::cout << "NotQuery rep()\n";
            return "~(" + query.rep() + ")";
        }
        QueryResult eval(const TextQuery &t)const;
    };
    Query operator~(const Query &q)
    {
        return std::shared_ptr<Query_base>(new NotQuery(q));
    }
    class BinaryQuery :public Query_base
    {
    protected:
        Query lhs, rhs;
        std::string opSym;
        BinaryQuery(const Query &l, const Query &r, std::string s) :lhs(l), rhs(r), opSym(s) { std::cout << "BinaryQuery(const Query &l, const Query &r, std::string s)\n"; }
        std::string rep()const {
            std::cout << "BinaryQuery rep()\n";
            return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")";
        }
    };
    class AndQuery :public BinaryQuery
    {
        friend Query operator&(const Query &lhq, const Query &rhq);
        AndQuery(const Query &left, const Query &right) :BinaryQuery(left, right, "&") { std::cout << "AndQuery(const Query &left, const Query &right)\n"; }
        QueryResult eval(const TextQuery &t)const;
    };
    Query operator&(const Query &lhs, const Query &rhs)
    {
        return std::shared_ptr<Query_base>(new AndQuery(lhs, rhs));
    }
    class OrQuery :public BinaryQuery
    {
        friend Query operator|(const Query &lhs, const Query &rhs);
        OrQuery(const Query &left, const Query &right) :BinaryQuery(left, right, "|") { std::cout << "OrQuery(const Query &left, const Query &right)\n"; }
        QueryResult eval(const TextQuery &tq)const;
    };
    Query operator|(const Query &lhs, const Query &rhs)
    {
        return std::shared_ptr<Query_base>(new OrQuery(lhs, rhs));
    }
    QueryResult OrQuery::eval(const TextQuery &tq)const
    {
        auto right = rhs.eval(tq), left = lhs.eval(tq);
        auto ret_lines = std::make_shared<std::set<line_no>>(left.begin(), left.end());
        ret_lines->insert(right.begin(), right.end());
        return QueryResult(rep(), ret_lines, left.get_file());
    }
    QueryResult AndQuery::eval(const TextQuery &t)const
    {
        auto left = lhs.eval(t), right = rhs.eval(t);
        auto ret_lines = std::make_shared<std::set<line_no>>();
        std::set_intersection(left.begin(), left.end(), right.begin(), right.end(), inserter(*ret_lines, ret_lines->begin()));
        return QueryResult(rep(), ret_lines, left.get_file());
    }
    QueryResult NotQuery::eval(const TextQuery &t)const
    {
        auto result = query.eval(t);
        auto ret_line = std::make_shared<std::set<line_no>>();
        auto beg = result.begin(), end = result.end();
        auto sz = result.get_file()->size();
        for (size_t n = 0; n != sz; ++n)
        {
            if (beg == end || *beg != n)
                ret_line->insert(n);
            else if (beg != end)
                ++beg;
        }
        return QueryResult(rep(), ret_line, result.get_file());
    }
}

using namespace std;
using namespace chapter10;
using namespace chapter15;
int main(int argc, char **argv)
{
    ifstream ifile("letter.txt");
    print(cout, (Query("the") | Query("study")).eval(ifile)) << endl;

    return 0;
} 
