#include <iostream>
#include <string>
#include <cstddef>
#include <vector>
#include <functional>
#include <algorithm>

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
	// 19.19
	friend std::vector<Sales_data>::const_iterator count(const std::vector<Sales_data> &vec, double d);

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

std::vector<Sales_data>::const_iterator count(const std::vector<Sales_data> &vec, double d) {
	auto fun = std::bind(&Sales_data::avg_price, std::placeholders::_1);
	return find_if(vec.cbegin(), vec.cend(), [&](const Sales_data &s) { return d < fun(s); });
}

int main()
{
	std::vector<Sales_data> sv;
	sv.push_back(Sales_data("b1", 13, 36.4));
	sv.push_back(Sales_data("b2", 32, 24.2));
	sv.push_back(Sales_data("b3", 77, 82));
	sv.push_back(Sales_data("b4", 21, 15.7));
	sv.push_back(Sales_data("b5", 25, 35));
	sv.push_back(Sales_data("b6", 42, 75));
	sv.push_back(Sales_data("b7", 63, 55.5));
	sv.push_back(Sales_data("b8", 43, 25));
	sv.push_back(Sales_data("b9", 68, 34));
	sv.push_back(Sales_data("b0", 44, 43.1));

	std::cout << *count(sv, 50) << std::endl;

	return 0;
}
