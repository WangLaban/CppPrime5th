#include "exception_class.h"

class Sales_data
{
public:
    Sales_data() = default;
    Sales_data(const std::string &s) : bookNo(s) {}
    Sales_data(const std::string &s, unsigned n, double p) :
        bookNo(s), units_sold(n), revenue(p*n) {}
    explicit Sales_data(std::istream &is) { is >> *this; }
    std::string isbn() const { return bookNo; }
    Sales_data& operator+=(const Sales_data&);
    Sales_data& operator=(const std::string&);

    friend std::ostream &operator<<(std::ostream&, const Sales_data&);
    friend std::istream &operator>>(std::istream&, Sales_data&);
    friend Sales_data operator+(const Sales_data&, const Sales_data&);
    friend bool operator==(const Sales_data&, const Sales_data&);
    friend bool operator!=(const Sales_data&, const Sales_data&);
    friend Sales_data operator+(const Sales_data&, const Sales_data&);

private:
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
    double avg_price() const;
};

// throws an exception if both objects do not refer to the same book
Sales_data& Sales_data::operator+=(const Sales_data& rhs)
{
    if (isbn() != rhs.isbn())  //18.9
        throw isbn_mismatch("wrong isbns", isbn(), rhs.isbn());
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}
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

std::ostream& operator<<(std::ostream& os, const Sales_data& item)
{
    os << item.bookNo << " "
        << item.units_sold << " "
        << item.revenue << " "
        << item.avg_price();
    return os;
}

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
bool operator==(const Sales_data &lhs, const Sales_data &rhs)
{
    return lhs.bookNo == rhs.bookNo &&
        lhs.units_sold == rhs.units_sold &&
        lhs.revenue == rhs.revenue;
}
bool operator!=(const Sales_data &lhs, const Sales_data &rhs) 
{
    return !(lhs == rhs);
}
Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs)
{
    Sales_data sum = lhs;
    sum += rhs;
    return sum;
}
