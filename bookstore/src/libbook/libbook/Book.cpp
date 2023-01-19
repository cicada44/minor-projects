#include <iostream>

#include <libbook/Book.hpp>

std::ostream& operator<<(std::ostream& os, const Book& b)
{
    os << b.ISBN << ' ' << b.author << ' ' << b.pages << ' ' << b.price << '\n';
    return os;
}

std::istream& operator>>(std::istream& is, Book& b)
{
    is >> b.ISBN >> b.author >> b.pages >> b.price;
    return is;
}
