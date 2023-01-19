#include <iostream>

#include <libbook/Book.hpp>

std::string& Book::get_isbn()
{
    return ISBN;
}

std::ostream& operator<<(std::ostream& os, const Book& b)
{
    os << b.ISBN << ' ' << b.author << ' ' << b.pages << ' ' << b.price;
    return os;
}

std::istream& operator>>(std::istream& is, Book& b)
{
    is >> b.ISBN >> b.author >> b.pages >> b.price;
    return is;
}
