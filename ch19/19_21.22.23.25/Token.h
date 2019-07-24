#include <iostream>
#include <string>
#include <utility>
#include "Sales_data.h"
class Token // 19.21
{
	enum { INT, CHAR, DBL, STR, SALES/*19.22*/ }tok;
	union {
		char cval;
		int ival;
		double dval;
		std::string sval;
		Sales_data sdval; // 19.22
	};
	void copyUnion(const Token &t) {
		switch (t.tok) {
		case INT: ival = t.ival;
			break;
		case CHAR:cval = t.cval;
			break;
		case DBL:dval = t.dval;
			break;
		case STR:new(&sval) std::string(t.sval);  // placement new
			break;
		case SALES:new(&sdval) Sales_data(t.sdval); // 19.22
			break;
		}
	}
	void moveUnion(Token &&t) { // 19.23
		switch (t.tok) {
		case INT:
			ival = std::move(t.ival);
			break;
		case CHAR:
			cval = std::move(t.cval);
			break;
		case DBL:
			dval = std::move(t.dval);
			break;
		case STR:
			new(&sval) std::string(std::move(t.sval));
			break;
		case SALES:
			new(&sdval) Sales_data(std::move(t.sdval));
			break;
		}
	}

public:
	Token() :tok(INT), ival{ 0 } {};
	Token(const Token &t) :tok(t.tok) { copyUnion(t); }
	Token(Token &&t) :tok(std::move(t.tok)) { // 19.23
		moveUnion(std::move(t));
	}
	Token &operator=(Token &&t){ // 19.23
		if(this != &t) {
			this->~Token();
			moveUnion(std::move(t));
			tok = std::move(t.tok);
		}
		return *this;
	}

	Token &operator=(const Token &t) {
		if (tok == STR && t.tok != STR)sval.std::string::~string();
		if (tok == SALES && t.tok != SALES)sdval.~Sales_data();
		if (tok == STR && t.tok == STR)
			sval = t.sval;
		else if (tok == SALES && t.tok == SALES)
			sdval = t.sdval;
		else
			copyUnion(t);
		tok = t.tok;
		return *this;
	}
	~Token() {
		if (tok == STR)
			sval.std::string::~string();
		if (tok == SALES)
			sdval.~Sales_data();
	}
	Token &operator=(const std::string &s) {
		if(tok == SALES)
		    sdval.~Sales_data();
		if(tok == STR)
		    sval = s;
		else
		    new(&sval) std::string(s);
		tok = STR;
		return *this;
	}
	Token &operator=(char c) {
		if(tok == STR || tok == SALES) this->~Token();
		cval = c;
		tok = CHAR;
		return *this;
	}
	Token &operator=(int i) {
		if(tok == STR || tok == SALES) this->~Token();
		ival = i;
		tok = INT;
		return *this;
	}
	Token &operator=(double d) {
		if(tok == STR || tok == SALES) this->~Token();
		dval = d;
		tok = DBL;
		return *this;
	}
	Token &operator=(Sales_data &s) {
		if(tok == STR)
		    sval.std::string::~string();
		if(tok == SALES)
		    sdval = s;
		else
		    new(&sdval) Sales_data(s);
		tok = SALES;
		return *this;
	}
	friend std::ostream &operator<<(std::ostream &os, const Token &t) {
		switch (t.tok) {
		case Token::INT: os << t.ival; break;
		case Token::CHAR: os << t.cval; break;
		case Token::DBL: os << t.dval; break;
		case Token::STR: os << t.sval; break;
		case Token::SALES: os << t.sdval; break;
		}
		return os;
	}
 
};
