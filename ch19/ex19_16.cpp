#include <iostream>
#include <string>
#include <cstddef> 
#include <vector> 
class Sales_data {
	friend std::ostream &operator<<(std::ostream&, const Sales_data&);
	friend std::istream &operator>>(std::istream&, Sales_data&);
	friend Sales_data operator+(const Sales_data&, const Sales_data&);
	friend bool operator==(const Sales_data&, const Sales_data&);
	friend bool operator!=(const Sales_data&, const Sales_data&);
	friend Sales_data operator+(const Sales_data&, const Sales_data&);
public:
	// 19.16
	using Avg = double (Sales_data::*)() const;
	friend void text(Sales_data &s);  // 19.16
	Sales_data() = default;
	Sales_data(const std::string &s) : bookNo(s) {}
	Sales_data(const std::string &s, unsigned n, double p) :
		bookNo(s), units_sold(n), revenue(p*n) {}
	explicit Sales_data(std::istream &is) { is >> *this; }
 
	std::string isbn() const { return bookNo; }
 
	Sales_data& operator+=(const Sales_data&);
 
	Sales_data& operator=(const std::string&);
	// 19.13
	static const std::string Sales_data::* data()
	{
		return &Sales_data::bookNo;
	}
private:
	std::string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
	double avg_price() const;
};
inline
Sales_data& Sales_data::operator+=(const Sales_data& rhs)
{
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;
	return *this;
}
inline
Sales_data& Sales_data::operator=(const std::string &isbn)
{
	bookNo = isbn;
	return *this;
}
inline double Sales_data::avg_price() const
{
	if (units_sold != 0)
		return revenue / units_sold;
	else
		return revenue;
}
inline
std::ostream& operator<<(std::ostream& os, const Sales_data& item)
{
	os << item.bookNo << " "
		<< item.units_sold << " "
		<< item.revenue << " "
		<< item.avg_price();
	return os;
}
inline
std::istream& operator>>(std::istream &is, Sales_data& item)
{
	double price = 0;
	is >> item.bookNo >> item.units_sold >> price;
	if (is) 
		item.revenue = item.units_sold * price;
	else
		item = Sales_data();
	return is;
}
inline
bool operator==(const Sales_data &lhs, const Sales_data &rhs)
{
	return lhs.bookNo == rhs.bookNo &&
		lhs.units_sold == rhs.units_sold &&
		lhs.revenue == rhs.revenue;
}
inline
bool operator!=(const Sales_data &lhs, const Sales_data &rhs)
{
	return !(lhs == rhs);
}
inline
Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs)
{
	Sales_data sum = lhs;
	sum += rhs;
	return sum;
}

void text(Sales_data &s)
{
	Sales_data::Avg fun = &Sales_data::avg_price;
	std::cout << (s.*fun)();
}

int main()
{
	return 0;
}
